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
import click
from pybalmorel import Balmorel
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
    ctx.invoke(cap, gen=True, sto=True)
    ctx.invoke(costs)

@CLI.command()
@click.option('--gen', '-g', is_flag=True, default=True, required=False, help='Plot generation capacities')
@click.option('--sto', '-s', is_flag=True, default=True, required=False, help='Plot storage capacities')
@click.pass_context
def cap(ctx, gen: bool, sto: bool):
    """
    Plot generation or storage capacities
    """
    
    plot_types = {'generation' : gen, 'storage' : sto}
    for key in [key for key in plot_types.keys() if plot_types[key]]:
        print('\nPlotting %s capacities..'%key)
        
        fig, ax = plt.subplots()
        if key == 'generation':
            df = (
                collect_results('G_CAP_YCRAF', ctx.obj['path'], ctx.obj['overwrite'])
                .query('Technology != "H2-STORAGE" and not Technology.str.contains("INTERSEASONAL") and not Technology.str.contains("INTRASEASONAL")')
            ) 
            ax.set_ylabel('Generation Capacity [GW]')
        else:
            df = (
                collect_results('G_STO_YCRAF', ctx.obj['path'], ctx.obj['overwrite'])
                .query('Technology == "H2-STORAGE" or Technology.str.contains("INTERSEASONAL") or Technology.str.contains("INTRASEASONAL")')
            )
            df['Value'] = df['Value'] / 1e3 
            ax.set_ylabel('Storage Capacity [TWh]')
        
        (
            df
            .pivot_table(index='Scenario', columns='Technology', 
                            values='Value', aggfunc='sum')
            .plot(ax=ax, kind='bar', stacked=True, color=balmorel_colours)
        )
        
        fig, ax = plot_style(fig, ax, '%s_capacity'%key)
        
@CLI.command()
@click.pass_context
def costs(ctx):
    """
    Plot system costs
    """
    print('\nPlotting system costs..')
    
    fig, ax = plt.subplots()
    (
        collect_results('OBJ_YCR', ctx.obj['path'], ctx.obj['overwrite'])
        .pivot_table(index='Scenario', columns='Category', 
                     values='Value', aggfunc=lambda x: np.sum(x)/1e3)
        .plot(ax=ax, kind='bar', stacked=True)
        .set_ylabel('System Costs [B€]')
    )
    
    # Y limits were a bit too tight
    ylims = ax.get_ylim()
    ax.set_ylim(ylims[0], ylims[1]*1.05)
    
    fig, ax = plot_style(fig, ax, 'systemcosts')

#%% ------------------------------- ###
###            2. Utils             ###
### ------------------------------- ###

@click.pass_context
def plot_style(ctx, fig: plt.figure, ax: plt.axes, name: str):
    
    ax.set_facecolor(ctx.obj['fc'])
    ax.legend(loc='center',
            bbox_to_anchor=(.5, 1.15),
            ncol=3)
    
    fig.savefig(os.path.join(ctx.obj['path'], 'analysis', 'files', name + ctx.obj['plot_ext']),
                bbox_inches='tight', transparent=True)

    return fig, ax

def collect_results(symbol: str,
                    path: str,
                    overwrite: bool = False):
    
    abspath = os.path.abspath(path)
    file_path = os.path.join(abspath, 'analysis', 'files', f'{symbol}.pkl')
    if os.path.exists(file_path) and not(overwrite):
        with open(file_path, 'rb') as f:
            df = pickle.load(f)
    
    else:
        print('\nCollecting results to %s..\n'%file_path, flush=True)
        m = Balmorel(abspath)
        m.collect_results()
        
        df = m.results.get_result(symbol)
    
        with open(file_path, 'wb') as f:
            pickle.dump(df, f)

    return df


# 3. Main
if __name__ == '__main__':
    CLI()
