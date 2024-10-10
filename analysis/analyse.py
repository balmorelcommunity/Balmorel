"""
Analysis Script

Will plot different things, depending on command-line input.
Meant to be used with the analyse.sh shell-script, to ease command writing.

Created on 06.10.2024
@author: Mathias Berg Rosendal, PhD Student at DTU Management (Energy Economics & Modelling)
"""
#%% ------------------------------- ###
###           0. Main CLI           ###
### ------------------------------- ###

import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import click
from pybalmorel import Balmorel, MainResults
from pybalmorel.formatting import balmorel_colours
import pickle
import os

@click.group()
@click.option('--overwrite', is_flag=True, required=False, help='Overwrite previous collected results?')
@click.option('--dark-style', is_flag=True, required=False, help='Dark plot style')
@click.option('--plot-ext', type=str, required=False, default='.pdf', help='The extension of the plots, defaults to ".pdf"')
@click.option('--path', type=str, required=False, default='.', help='Path to top level of Balmorel folders, defaults to "."')
@click.pass_context
def CLI(ctx, overwrite: bool, dark_style: bool, plot_ext: str, path: str):
    "A CLI to analyse Balmorel results"
    
    # Set global style of plot
    if dark_style:
        plt.style.use('dark_background')
        fc = 'none'
    else:
        fc = 'white'
        
    # Store global options in the context object
    ctx.ensure_object(dict)
    ctx.obj['Balmorel'] = Balmorel(path) # Find Balmorel folder
    ctx.obj['fc'] = fc  # Store facecolor in context
    ctx.obj['overwrite'] = overwrite
    ctx.obj['dark_style'] = dark_style
    ctx.obj['plot_ext'] = plot_ext
    ctx.obj['path'] = path


#%% ------------------------------- ###
###            1. Commands          ###
### ------------------------------- ###

@CLI.command()
@click.pass_context
def all(ctx):
    """
    Generate all plots
    """
    ctx.invoke(all_bars)
    ctx.invoke(all_profiles)

@CLI.command()
@click.pass_context
def all_bars(ctx):
    """
    Generate all bar charts
    """
    ctx.invoke(cap, gen=True, sto=True)
    ctx.invoke(fuel)
    ctx.invoke(costs)
    for commodity in ['electricity', 'heat', 'hydrogen']:
        ctx.invoke(dem, commodity=commodity)
    
@CLI.command()
@click.pass_context
@click.option('--year', type=int, required=False, default=2050, help="Which year to plot profiles from")
def all_profiles(ctx, year: int):
    """
    Generate all profiles for a year (2050 default) 
    """
    
    for scenario in ctx.obj['Balmorel'].scenarios:
        for commodity in ['electricity', 'heat', 'hydrogen']:
            ctx.invoke(profile, commodity=commodity, scenario=scenario, year=year)
                
@CLI.command()
@click.option('--gen', '-g', is_flag=True, default=True, required=False, help='Plot generation capacities')
@click.option('--sto', '-s', is_flag=True, default=True, required=False, help='Plot storage capacities')
def cap(gen: bool, sto: bool):
    """
    Plot generation or storage capacities
    """
    
    plot_types = {'generation' : gen, 'storage' : sto}
    for key in [key for key in plot_types.keys() if plot_types[key]]:
        print('\nPlotting %s capacities..'%key)
        
        fig, ax = plt.subplots()
        if key == 'generation':
            df = (
                collect_results('G_CAP_YCRAF')
                .query('Technology != "H2-STORAGE" and not Technology.str.contains("INTERSEASONAL") and not Technology.str.contains("INTRASEASONAL")')
            ) 
            ax.set_ylabel('Generation Capacity [GW]')
        else:
            df = (
                collect_results('G_STO_YCRAF')
                .query('Technology == "H2-STORAGE" or Technology.str.contains("INTERSEASONAL") or Technology.str.contains("INTRASEASONAL")')
            )
            df['Value'] = df['Value'] / 1e3 
            ax.set_ylabel('Storage Capacity [TWh]')
        
        (
            df
            .pivot_table(index='Scenario', columns='Fuel', 
                            values='Value', aggfunc='sum')
            .plot(ax=ax, kind='bar', stacked=True, color=balmorel_colours)
        )
        
        fig, ax = plot_style(fig, ax, '%s_capacity'%key)

@CLI.command()
def fuel():
    """
    Plot fuel consumption
    """

    print('\nPlotting fuel consumption..')
    
    fig, ax = plt.subplots()
    ax.set_ylabel('Fuel Consumption [TWh]')
    
    df = (
        collect_results('F_CONS_YCRA')
    ) 
    
    (
        df
        .pivot_table(index='Scenario', columns='Fuel', 
                        values='Value', aggfunc='sum')
        .plot(ax=ax, kind='bar', stacked=True, color=balmorel_colours)
    )
    
    fig, ax = plot_style(fig, ax, 'fuelconsumption')
    
@CLI.command()
@click.argument('commodity', type=str)
def dem(commodity: str):
    """
    Plot fuel consumption
    """

    print('\nPlotting %s demand..'%commodity)
    
    symbol = {'electricity' : 'EL_DEMAND_YCR',
              'hydrogen' : 'H2_DEMAND_YCR',
              'heat' : 'H_DEMAND_YCRA'}
    
    fig, ax = plt.subplots()
    ax.set_ylabel('%s Demand [TWh]'%(commodity.capitalize()))
    
    df = (
        collect_results(symbol[commodity.lower()])
    ) 
    
    (
        df
        .pivot_table(index='Scenario', columns='Category', 
                        values='Value', aggfunc='sum')
        .plot(ax=ax, kind='bar', stacked=True)
    )
    
    fig, ax = plot_style(fig, ax, '%s_demand'%commodity.lower())
    
     
@CLI.command()
def costs():
    """
    Plot system costs
    """
    print('\nPlotting system costs..')
    
    fig, ax = plt.subplots()
    (
        collect_results('OBJ_YCR')
        .pivot_table(index='Scenario', columns='Category', 
                     values='Value', aggfunc=lambda x: np.sum(x)/1e3)
        .plot(ax=ax, kind='bar', stacked=True)
        .set_ylabel('System Costs [B€]')
    )
    
    # Y limits were a bit too tight
    ylims = ax.get_ylim()
    ax.set_ylim(ylims[0], ylims[1]*1.05)
    
    fig, ax = plot_style(fig, ax, 'systemcosts')
    

@CLI.command()
@click.pass_context
@click.argument('commodity', type=str)
@click.argument('scenario', type=str)
@click.argument('year', type=int, default=2050)
def profile(ctx, commodity: str, scenario: str, year: int):
    """Plot energy balance of a commodity"""

    model_path = os.path.join(ctx.obj['path'], scenario, 'model')

    # Get mainresults files
    mainresult_files = pd.Series(os.listdir(model_path))
    idx = mainresult_files.str.contains('MainResults')
    mainresult_files = mainresult_files[idx]
    
    m = MainResults(list(mainresult_files), paths=model_path)
    
    if len(m.sc) > 1:
        for sc in m.sc:
            fig, ax = m.plot_profile(commodity, year, sc)
            fig, ax = plot_style(fig, ax, '%s_profile'%(commodity + '-' + str(year) + '-' + scenario + '-' + sc))
    else:
        fig, ax = m.plot_profile(commodity, year, m.sc[0])
        fig, ax = plot_style(fig, ax, '%s_profile'%(commodity + '-' + str(year) + '-' + sc))
    

@CLI.command()
@click.pass_context
@click.argument('symbol', type=str, required=True)
@click.argument('filter_input', type=str, required=False, default='INTER-STO')
def get(ctx, symbol: str, filter_input: str):
    """Get some result (i.e.: symbol in GAMS language)

    Args:
        symbol (str): The symbol from the .gdx
        filter_input (str): An input for a filter
    """
    
    df = collect_results(symbol)
    
    fig, ax = plt.subplots()
    
    res = (
        df
        # .query(f'Generation == "{filter_input}" and Area == "Aabenraa_A" and not Scenario.str.contains("_lowtemp")')
        # .query(f'Category == "{filter_input}"')
        .pivot_table(index=['Scenario'],  columns=['Category'], values='Value', aggfunc='sum')
    )
    
    print(res.to_string(), res)
    
    # res.plot(ax=ax)
    
    # ax.set_title(filter_input)
    # fig, ax = plot_style(fig, ax, f'{result}_filter{filter_input}_intersto_hightemp')
    
        


#%% ------------------------------- ###
###            2. Utils             ###
### ------------------------------- ###

@click.pass_context
def plot_style(ctx, fig: plt.figure, ax: plt.axes, name: str):
    
    ax.set_facecolor(ctx.obj['fc'])
    ax.legend(loc='center',
            bbox_to_anchor=(.5, 1.15),
            ncol=3)
    
    plot_path = os.path.join(ctx.obj['path'], 'analysis', 'plots')
    if not(os.path.exists(plot_path)):
        os.mkdir(plot_path)
            
    fig.savefig(os.path.join(ctx.obj['path'], 'analysis', 'plots', name + ctx.obj['plot_ext']),
                bbox_inches='tight', transparent=True)

    return fig, ax

@click.pass_context
def collect_results(ctx, symbol: str):
    
    abspath = os.path.abspath(ctx.obj['path'])
    file_path = os.path.join(abspath, 'analysis', 'files', f'{symbol}.pkl')
    if os.path.exists(file_path) and not(ctx.obj['overwrite']):
        print('Result file already exists, loading %s..'%file_path)
        with open(file_path, 'rb') as f:
            df = pickle.load(f)
    
    else:
        print('\nCollecting results to %s..\n'%file_path, flush=True)
        m = ctx.obj['Balmorel']
        m.collect_results()
        
        df = m.results.get_result(symbol)
    
        file_folder_path = os.path.join(abspath, 'analysis', 'files')
        if not(os.path.exists(file_folder_path)):
            os.mkdir(file_folder_path)
    
        with open(file_path, 'wb') as f:
            pickle.dump(df, f)

    return df


# 3. Main
if __name__ == '__main__':
    CLI()
