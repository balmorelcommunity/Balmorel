"""
Analysis Script

Will plot different things, depending on command-line input.
Meant to be used with the analyse/analyse.bat shell/batch scripts (Linux/Windows), to ease command writing.

Created on 06.10.2024
@author: Mathias Berg Rosendal, PhD Student at DTU Management (Energy Economics & Modelling)
"""
#%% ------------------------------- ###
###           0. Main CLI           ###
### ------------------------------- ###

from matplotlib.dates import DateFormatter
from gams import GamsWorkspace
import geopandas as gpd
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import click
import re
from premailer import transform
from typing import Union
import gams
from specific.pit_storage.pit_storage import get_storage_profiles, polygon_with_point
from pybalmorel import Balmorel, MainResults
from pybalmorel.utils import symbol_to_df
from pybalmorel.formatting import balmorel_colours
from pybalmorel.plotting import plot_bar_chart
import pickle
import os

# Some formatting
balmorel_colours['SYNFUELPRODUCER'] = '#E8C3A8'
balmorel_colours['FUEL_TRANSPORT'] = balmorel_colours['WIND-ON']
balmorel_colours['H2_TRANSMISSION_CAPITAL_COSTS'] = '#A8D9E8'
balmorel_colours['H2_TRANSMISSION_OPERATIONAL_COSTS'] = '#D3EBF2'
balmorel_colours['TRANSMISSION_CAPITAL_COSTS'] = '#BA1600'
balmorel_colours['TRANSMISSION_OPERATIONAL_COSTS'] = '#FF2B10'
balmorel_colours['GENERATION_CAPITAL_COSTS'] = '#FFA500'
balmorel_colours['GENERATION_FIXED_COSTS'] = '#D2A106'
balmorel_colours['GENERATION_FUEL_COSTS'] = '#747474'
balmorel_colours['GENERATION_OPERATIONAL_COSTS'] = '#E5D8D8'
balmorel_colours['ELECTRICITY'] = '#FFD700'
balmorel_colours['HEAT'] = '#@BA4E00'


@click.group()
@click.option('--overwrite', is_flag=True, required=False, help='Overwrite previous collected results?')
@click.option('--dark-style', is_flag=True, required=False, help='Dark plot style')
@click.option('--plot-ext', type=str, required=False, default='.pdf', help='The extension of the plots, defaults to ".pdf"')
@click.option('--path', type=str, required=False, default='.', help='Path to top level of Balmorel folders, defaults to "."')
@click.option('--gams-sysdir', type=str, required=False, default='/appl/gams/47.6.0', help='Path to GAMS system directory')
@click.option('--large-plot', is_flag=True, required=False, default=False, help='Makes the plots large or small')
@click.pass_context
def CLI(ctx, overwrite: bool, dark_style: bool, plot_ext: str, path: str,
        gams_sysdir: str, large_plot: bool):
    "A CLI to analyse Balmorel results"
    
    # Store global options in the context object
    ctx.ensure_object(dict)
    
    # Large or small plot?
    if large_plot:
        plt.rcParams.update({'font.size' : 15})
    
    # Detect which command has been passed
    command = ctx.invoked_subcommand
    if command in ['all', 'all-bars', 'all-profiles', 'all_maps',
                   'costs', 'cost-change', 'cap', 'map', 'profile', 'bar-chart', 'adequacy']:

        # Locate results
        model = Balmorel(path)
        model.locate_results() 
        ctx.obj['Balmorel'] = model # Find Balmorel folder

    else:
        pass
    
    ctx.obj['overwrite'] = overwrite
    ctx.obj['dark_style'] = dark_style
    ctx.obj['plot_ext'] = plot_ext
    ctx.obj['path'] = path
    ctx.obj['plot_path'] = os.path.join(path, 'analysis', 'plots')
    ctx.obj['gams_system_directory'] = gams_sysdir
    
    # Set global style of plot (only true for plots using function in THIS script)
    if dark_style:
        plt.style.use('dark_background')
        ctx.obj['fc'] = 'none'                              # Facecolor
        ctx.obj['plot_style_for_modules'] = 'dark'          # Plot style for modules
    else:
        ctx.obj['fc'] = 'white'  
        ctx.obj['plot_style_for_modules'] = 'light'         # Plot style for modules
            


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
    ctx.invoke(all_maps)

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
    m = ctx.obj['Balmorel']
    
    for sc_folder in m.scenarios:
        for scenario in m.scfolder_to_scname[sc_folder]:
            for commodity in ['electricity', 'heat', 'hydrogen']:
                ctx.invoke(profile, commodity=commodity, scenario=scenario, year=year)
    
@CLI.command()
@click.pass_context
@click.option('--year', type=int, required=False, default=2050, help="Which year to plot profiles from")
def all_maps(ctx, year: int):
    """
    Generate all maps for a year (2050 default) 
    """
    
    for scenario in ctx.obj['Balmorel'].scenarios:
        for commodity in ['Electricity', 'Hydrogen']:
            ctx.invoke(map, commodity=commodity, scenario=scenario, year=year)
           
              
@CLI.command()
@click.option('--gen', '-g', is_flag=True, default=True, required=False, help='Plot generation capacities')
@click.option('--sto', '-s', is_flag=True, default=True, required=False, help='Plot storage capacities')
@click.option('--filters', type=str, default='', required=False, help='Filters for df.query(...)')
@click.option('--include-backup', is_flag=True, default=False, help="Include interpreted backup capacities from the @adequacy function in this plot")
@click.option('--backup-nth-max', type=int, default=3, help="The nth-max value used for the @adequacy function, if backup capacities should be included")
@click.option('--drop-hydro', is_flag=True, default=True, help="Include hydro-run-of-river in generation capacity plot?")
def cap(gen: bool, sto: bool, filters: str, include_backup: bool,
        backup_nth_max: int, drop_hydro: bool):
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
                .query('Technology != "H2-STORAGE" and not Technology.str.contains("INTERSEASONAL") and not Technology.str.contains("INTRASEASONAL") and not Generation.str.contains("BACKUP")')
            ) 
            ax.set_ylabel('Generation Capacity [GW]')
        else:
            df = (
                collect_results('G_STO_YCRAF')
                .query('Technology == "H2-STORAGE" or Technology.str.contains("INTERSEASONAL") or Technology.str.contains("INTRASEASONAL")')
            )
            df.loc[:, 'Value'] = df['Value'] / 1e3 
            ax.set_ylabel('Storage Capacity [TWh]')
        
        # Apply exclusion filters
        if filters != '':
            df = df.query(filters)

        # Sort scenarios, e.g. so N2 comes before N10
        df = sort_scenarios(df).pivot_table(index=['Scenario'], columns='Technology', 
                                            values='Value', aggfunc='sum')
        
        if key == 'generation':
                
            # Drop hydro, as it is an invisibly small capacity
            if drop_hydro and 'HYDRO-RUN-OF-RIVER' in df.columns:
                df = df.drop(columns='HYDRO-RUN-OF-RIVER')
                
            # Re-arrange technologies
            if 'Technology' not in filters:
                cols = df.columns
                cols = cols[(cols != 'WIND-OFF') & (cols != 'SYNFUELPRODUCER') & (cols != 'ELECTROLYZER')]
                cols = list(cols) + ['WIND-OFF', 'ELECTROLYZER', 'SYNFUELPRODUCER']
            else:
                cols = list(df.columns)
            
            # Include interpreted backup capacity
            if include_backup:
                for scenario in df.index.unique():
                    if scenario == 'N2_ZCEHX' or scenario == 'N10_ZCEHX':
                        scenario_csv = scenario.replace('ZCEHX', 'synfheur')
                    else:
                        scenario_csv = scenario
                    df.loc[scenario, 'BACKUP'] = 0
                    try:
                        f = pd.read_csv('analysis/output/%s_backcapN%d.csv'%(scenario_csv, backup_nth_max)).drop(columns='Region').sum()
                    
                        for commodity in f.index:
                            df.loc[scenario, 'BACKUP'] += f[commodity] / 1e3
                    except FileNotFoundError:
                        print('No backup capacity for scenario %s'%scenario)
                balmorel_colours['BACKUP'] = '#000000'
                cols = cols + ['BACKUP'] 
            
            df = df.loc[:, cols]
        
        (
            df
            .plot(ax=ax, kind='bar', stacked=True, color=balmorel_colours)
        )
        
        
        ax.legend(loc='lower center', bbox_to_anchor=(.5, 1.01), ncols=2)
        
        fig, ax = plot_style(fig, ax, '%s_capacity'%key, legend=False)

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
@click.option('--filters', type=str, required=False, default=None, help="Query input for filtering")
def costs(filters: str):
    """
    Plot system costs
    """
    print('\nPlotting system costs..')
    
    fig, ax = plt.subplots()
    
    df = collect_results('OBJ_YCR') 
    
    if filters != None:
        df = df.query(filters)
    
    df = sort_scenarios(df)
    
    (
        df
        .pivot_table(index='Scenario', columns='Category', 
                     values='Value', aggfunc=lambda x: np.sum(x)/1e3)
        .plot(ax=ax, kind='bar', stacked=True, color=balmorel_colours)
        .set_ylabel('System Costs [B€]')
    )
    
    # Y limits were a bit too tight
    ylims = ax.get_ylim()
    ax.set_ylim(ylims[0], ylims[1]*1.05)
    ax.legend(loc='lower center', bbox_to_anchor=(.5, 1.01), ncols=2)
    
    fig, ax = plot_style(fig, ax, 'systemcosts', legend=False)
    
@CLI.command()
@click.option('--sc-group', type=str, required=True, default=None, help="Groups of scenarios, with groups separated by ; and scenarios by ,")
@click.option('--group-names', type=str, required=True, default=None, help="Scenario group names separated by ;")
@click.option('--filters', type=str, required=False, default=None, help="Query input for filtering")
@click.option('--filename', type=str, required=False, default=None, help="Output filename")
def cost_change(sc_group: str, group_names: str, filters: str, filename: str):
    """
    Plot change in system costs between scenarios
    """
    print('\nPlotting system costs..')
    
    df = collect_results('OBJ_YCR') 
    
    all_scenarios = sc_group.replace(' ', '').replace(';', ',').split(',')
    scenario_groups = sc_group.replace(' ', '').split(';')
    group_names = group_names.split(';')
    
    if filters != None:
        df = df.query(filters + " Scenario in %s"%str(all_scenarios))
    else:
        df = df.query("Scenario in %s"%str(all_scenarios))
        
    df = sort_scenarios(df)  
    
    fig, ax = plt.subplots(figsize=(.2,.3))
    
    n = 0
    colors = ['r', 'k']
    for group in group_names:
                
        # Filter
        scenarios = scenario_groups[n].split(',')
        temp = df.pivot_table(index='Scenario', 
                        values='Value', 
                        aggfunc=lambda x: np.sum(x)/1e3).loc[scenarios]
        
        # Replace scenario names with resolution
        scenarios = pd.Series(scenarios).str.replace('base', 'N99').str.extract(r'([N]\d*)')[0]
        
        temp.index = scenarios 
        temp.plot(ax=ax, color=colors[n])
        # print(temp.to_csv('analysis/output/%s_cost_change.csv'%group_names[n]))
        
        n += 1
        
    
    ax.set_xticks(np.arange(len(scenarios)))
    ax.set_xticklabels(scenarios)
    # Y limits were a bit too tight
    ylims = ax.get_ylim()
    ax.legend(group_names, loc='lower center', 
              bbox_to_anchor=(.5, 1.01), ncol=len(group_names))
    ax.set_ylim(ylims[0], ylims[1]*1.05)
    ax.set_ylabel('System Costs [B€]')
    # ax.set_xlabel('Resolution in # of Nodes')
    ax.set_xlabel('')
    
    if filename == None:
        filename = 'systemcost_changes'
    
    fig, ax = plot_style(fig, ax, filename, legend=False)


@CLI.command()
@click.pass_context
@click.argument('commodity', type=str)
@click.argument('scenario', type=str)
@click.argument('node', type=str, default='all')
@click.argument('year', type=int, default=2050)
@click.option('--columns', type=str, default='Technology', help="Which parameter to stack, either 'Technology' or 'Fuel'")
def profile(ctx, commodity: str, scenario: str, node: str, year: int, columns: str):
    """Plot energy balance of electricity, heat or hydrogen"""

    m = ctx.obj['Balmorel']

    model_path = os.path.join(ctx.obj['path'], m.scname_to_scfolder[scenario], 'model')

    # Get mainresults files
    res = MainResults('MainResults_%s.gdx'%scenario, paths=model_path, system_directory=ctx.obj['gams_system_directory'])
    
    fig, ax = res.plot_profile(commodity, year, scenario, region=node, style=ctx.obj['plot_style_for_modules'],
                               columns=columns)
    
    if node != 'all':
        scenario += '_' + node
    
    fig, ax = plot_style(fig, ax, 'profile_%s'%(commodity + '-' + str(year) + '-' + scenario))


@CLI.command()
@click.pass_context
@click.argument('commodity', type=str)
@click.argument('scenario', type=str)
@click.argument('year', type=int, default=2050)
@click.argument('geofile', type=str, default='analysis/geofiles/municipalities.gpkg')
@click.argument('geofile_region_column', type=str, default='Name')
@click.argument('lon-lims', type=list, default=[7.8, 13])
@click.argument('lat-lims', type=list, default=[54.4, 58])
@click.option('--lines', type=str, default='UtilizationYear')
@click.option('--generation', type=str, default='Production')
@click.option('--hier', is_flag=True, default=False, help="A hierarchically clustered run?")
def map(ctx, commodity: str, scenario: str, year: int, 
        geofile: str, geofile_region_column: str,
        lon_lims: list, lat_lims: list,
        lines: str, generation: str, hier: bool):
    """Plot transmission capacity maps for electricity or hydrogen"""

    model = ctx.obj['Balmorel']
    model_path = os.path.join(ctx.obj['path'], model.scname_to_scfolder[scenario], 'model')

    # Get mainresults files
    res = MainResults('MainResults_%s.gdx'%scenario, paths=model_path, system_directory=ctx.obj['gams_system_directory'])
    
    if hier and geofile=='analysis/geofiles/municipalities.gpkg':
        geofile = model_path.replace('model', 'data') + '/DE_%dcluster_geofile_2nd-order.gpkg'%(int(re.findall('M\d+', scenario)[0].lstrip('M')))
        geofile_region_column = 'cluster_name'
    elif 'N' in scenario and not 'TransRelaxation' in scenario and geofile=='analysis/geofiles/municipalities.gpkg':
        geofile = 'analysis/geofiles/DE-DH-WNDFLH-SOLEFLH_%dcluster_geofile.gpkg'%(int(re.findall('N\d+', scenario)[0].lstrip('N')))
        geofile_region_column = 'cluster_name'
    
    
    # Pie radius for comparing scenarios
    pie_radius_max = 0.5 # The largest one for comparison (N70 largest cluster is CL36 with 13.244423 GW)
    pie_radius_max = 0.5*(7.07/13.24) # The smaller one (base largest cluster is Frederikshavn with 7.07 GW)
    
    fig, ax = res.plot_map(scenario, year, commodity.capitalize(), 
                           path_to_geofile=os.path.abspath(geofile), geo_file_region_column=geofile_region_column, 
                           lines=lines, generation=generation,
                           style=ctx.obj['plot_style_for_modules'], pie_radius_max=pie_radius_max, pie_radius_min=0.03)
    ax.set_xlim(lon_lims)
    ax.set_ylim(lat_lims)
    fig, ax = plot_style(fig, ax, 'map_%s'%(commodity + '-' + str(year) + '-' + scenario), legend=False)
    
    
@CLI.command()
@click.pass_context
@click.argument('cluster', type=str, required=True)
@click.argument('scenarios', type=str, required=False, default=None)
@click.argument('size', type=str, required=False, default='decentral')
def storage_profile(ctx, cluster: str, scenarios: str, size: str):
    """
    Get storage profiles
    """
    if scenarios == None:
        scenarios = ctx.obj['Balmorel'].scenarios
    else:
        scenarios = scenarios.replace(' ', '').split(',')
        
    if size == 'decentral':
        size_type = 'GNR_HS_HEAT_PIT_L-DEC_E-70_Y-2050'
    else:
        size_type = 'GNR_HS_HEAT_PIT_L-CEN_E-70_Y-2050'
        
    sto = collect_storage_profiles(scenarios=scenarios)

    for scenario in scenarios:
        
        # geofile = load_geofile(scenario)
        
        # Find Brønderslev cluster
        # idx = polygon_with_point(geofile)
        # cluster = geofile.loc[idx, 'cluster_name'].iloc[0] # Will only be one cluster
        
        # Find the storage with the largest stored volume
        

        # Filter
        cluster_area = cluster + '_A'
        temp = {}
        for profile in ['charge', 'discharge', 'level']:
            temp[profile] = sto[profile].query(
                'A == @cluster_area \
                and Technology == "inter" \
                and Commodity == "heat" \
                and Scenario == @scenario \
                and G == @size_type' 
            )
                # and G == "GNR_HS_HEAT_PIT_L-CEN_E-70_Y-2050"'
                # and G == "GNR_HS_HEAT_PIT_L-DEC_E-70_Y-2050"'
            # if len(temp[profile].G.unique()) > 1:
            #     print(temp[profile].G.unique())
            #     raise ValueError('Several interseasonal technologies in cluster %s!'%cluster)
              
            temp[profile] = temp[profile].pivot_table(index=['S', 'T'], values='Value')
              
        # Plot  
        fig, ax1 = plt.subplots()
        ax2 = ax1.twinx()
        discharge_charge = temp['charge'] - temp['discharge']
        # discharge_charge.Value.name = 'Char/Dischar'
        discharge_charge['Value'].plot(color='k', linestyle='--', linewidth=1, ax=ax1, label='Dischar/Char', legend=True)
        temp['level']['Value'].plot(color='r', ax=ax2, label='Volume', legend=True)
        ax1.set_ylabel('Charge (+) and Discharge (-) (MWh)')
        ax2.set_ylabel('Storage Volume (MWh)')
        ax2.legend(loc='upper right')
        fig.savefig('%s/%s_storageprofile.pdf'%(ctx.obj['plot_path'], scenario), bbox_inches='tight')

@CLI.command()
@click.pass_context
@click.argument('scenario', type=str, required=True)
@click.argument('cluster', type=str, required=True)
@click.argument('size', type=str, required=False, default='decentral')
@click.argument('weather-year', type=int, required=False, default=2012)
@click.argument('freq', type=str, required=False, default='1M')
def sifnaios_profile(ctx, scenario: str, cluster: str, size: str, 
                        weather_year: int, freq: str):
    """
    Make a plot like in Sifnaios et al. 2023
    """

    if size == 'decentral':
        size_type = 'GNR_HS_HEAT_PIT_L-DEC_E-70_Y-2050'
    elif size == 'central':
        size_type = 'GNR_HS_HEAT_PIT_L-CEN_E-70_Y-2050'
    else:
        raise ValueError('Choose size = decentral or central!')
        
    sto = collect_storage_profiles(scenarios=[scenario])
    
    # Make datetime index corresponding to S and T set
    time_ind = pd.Series(pd.date_range('%d-01-01-00:00'%weather_year, 
                                       '%d-12-31-23:00'%weather_year, freq='1h'))
    
    ## Get it in 52 weeks, i.e. 8736 hours
    idx = time_ind.dt.isocalendar().query('year == @weather_year').index
    time_ind = time_ind[idx]
    
    ## Get corresponding S and T set
    S = ['S0%d'%i for i in range(1, 10)] + ['S%d'%i for i in range(10, 53)]
    T = ['T00%d'%i for i in range(1, 10)] + ['T0%d'%i for i in range(10, 100)] + ['T%d'%i for i in range(100, 169)] 
    ST_ind = pd.MultiIndex.from_product((S, T))
    index = pd.DataFrame(index=ST_ind).reset_index()
    
    ## Combine
    index = index.set_index(time_ind).reset_index()
    index.columns = ['time', 'S', 'T']
    
    
    # Filter data
    cluster_area = cluster + '_A'
    df = sto.query(
                'A == @cluster_area \
                and Technology == "inter" \
                and Commodity == "heat" \
                and Scenario == @scenario \
                and G == @size_type' 
            ).loc[:, ['S', 'T', 'result', 'Value_ts-scaled']]

    # Join time index to S,T set in results
    df = df.merge(index, on=['S', 'T'], how='inner').pivot_table(index='time', columns=['result'], values='Value_ts-scaled', aggfunc='sum')
    storage_content = df['level'].copy()
    
    dfr = df.resample(freq).sum()

    bar_width = pd.Timedelta(days=25)
    x = dfr.index
    lw = 0.75

    # Plot
    fig, ax = plt.subplots(figsize=(9, 5))
    if ctx.obj['dark_style']:
        linecolor = 'w'
    else:
        linecolor = 'k'
        
    ax.bar(x=x, height=dfr['charge'], width=bar_width, label='Charge', lw=lw, edgecolor=linecolor)
    ax.bar(x=x, height=-dfr['discharge'], width=bar_width, label='Discharge', lw=lw, edgecolor=linecolor)
    ax.set_ylabel('Heat [MWh]')

    # Hide the right and top spines
    ax.spines['right'].set_visible(False)
    ax.spines['top'].set_visible(False)

    # Plot energy content
    ax.plot(storage_content.index+pd.Timedelta(weeks=2), storage_content, c=linecolor, linestyle='--', label='Energy content')

    # Format x-ticks and set x-limit
    ax.set_xticks(pd.date_range(index['time'].iloc[0], freq=freq, periods=15))
    ax.xaxis.set_major_formatter(DateFormatter('%b'))
    ax.set_xlim(index['time'].iloc[0], index['time'].iloc[-1]+pd.Timedelta(weeks=2))
    ax.set_xlabel('')

    ax.legend(loc='upper center', ncol=3, frameon=False, handleheight=0.5, handlelength=1.5, bbox_to_anchor=[0.5,1.03])
    # ax.set_ylim(-2500, 6000)

    ax.axhline(0, c=linecolor, lw=0.35)
    
    fig, ax = plot_style(fig, ax, '%s_sifstoprofile'%(scenario+'_'+cluster+'_'+size), legend=False)
    # fig.savefig(os.path.join(ctx.obj['plot_path'], ))


@CLI.command()
@click.pass_context
@click.argument('scenario', type=str, required=True)
@click.argument('symbol', type=str, required=True)
def allendofmodel(ctx, scenario: str, symbol: str):
    """
    Get and print a symbol from all_endofmodel as a dataframe
    """
    
    # Load all_endofmodel for the specified scenario
    ws = GamsWorkspace(system_directory=ctx.obj['gams_system_directory'])
    db = ws.add_database_from_gdx(os.path.abspath(os.path.join(ctx.obj['path'], scenario, 'model', 'all_endofmodel.gdx')))
    
    # Get symbol
    df = symbol_to_df(db, symbol)
    
    print(df)
    
    return df

@CLI.command()
@click.pass_context
@click.argument('symbol', type=str, required=True)
@click.argument('pars', required=True)
@click.option('--filters', type=str, required=False, help='String for filtering that can be passed to a query')
@click.option('--diff', is_flag=True, required=False, help='Show difference or not?')
def get(ctx, symbol: str, pars, filters: str, diff: bool):
    """
    Get a certain symbol and show the values as a table.
    This function retrieves results for a specified symbol from a Balmorel model context,
    applies optional filters, and generates both absolute and relative difference tables.
    The results are then saved as HTML files with conditional formatting.

    Parameters:
    ctx (object): The context object containing the Balmorel model.
    symbol (str): The symbol to retrieve results for.
    pars (list): The parameters to use for pivoting the table.
    filters (str): The filters to apply to the results, specified as a query string.
    Returns:
    None    
    """
    
    model = ctx.obj['Balmorel']
    model.collect_results()
    
    df = model.results.get_result(symbol)
    if type(filters) == str:
        df = df.query(filters).pivot_table(index='Scenario', columns=pars, values='Value', aggfunc='sum')
    else:
        df = df.pivot_table(index='Scenario', columns=pars, values='Value', aggfunc='sum')
   
    # Some HTML formatting
    cell_format = {
    "selector": "td",
    "props": [("text-align", "right")]
    }
    
    if diff:
        # Make absolute and relative difference calculations 
        df_abs = df - df.loc['base', :]
        df_rel = (df - df.loc['base', :]) / df.loc['base', :] * 100
        
        print(df_rel.to_string())
        
        
        # Loop through both absolute and relative difference dataframes
        for df_name in ['df_abs', 'df_rel']:
            
            df = eval(df_name)
            df_styled = df.style.format(precision=1).set_table_styles([cell_format]) # Precision and general formatting
            
            # Style each column, so zero is white (with cmap RdBu reversed, higher values become red and lower blue)
            for col in df.columns: 
                max_abs = df[col].abs().max() 
                df_styled = df_styled.background_gradient(
                    cmap="RdBu_r", subset=[col], vmin=-max_abs, vmax=max_abs
                )
            
            html = df_styled.to_html()
            with open('analysis/output/%s_output.html'%df_name, 'w') as f: 
                f.write(transform(html)) # Use transform to get inline styling, which is supported by Obsidian's markdown
    else:
        print(df.to_string())
        # Precision and general formatting
        html = df.style.format(precision=1).set_table_styles([cell_format]).background_gradient(cmap="RdYlGn_r").to_html()
        with open('analysis/output/df_tot_output.html', 'w') as f: 
            f.write(transform(html)) # Use transform to get inline styling, which is supported by Obsidian's markdown
            
        

@CLI.command()
@click.pass_context
@click.argument('scenario', type=str, required=True)
@click.option('--nth-max', type=int, required=False, default=3, help="Which nth maximum backup production to interpret as required backup capacity Default is 3, as it could be interpreted as a LOLE = 3 h condition.")
def adequacy(ctx, scenario: str, nth_max: int):
    "Quantify the adequacy in terms of LOLE (h) and energy not supplied (TWh)"
    
    # Find path to scenario
    model = ctx.obj['Balmorel']
    model_path = os.path.join(ctx.obj['path'], model.scname_to_scfolder[scenario], 'model')

    # Get mainresults files
    res = MainResults('MainResults_%s.gdx'%scenario, paths=model_path, system_directory=ctx.obj['gams_system_directory'])
    
    # Get backup production
    df = res.get_result('PRO_YCRAGFST').query('Scenario == @scenario and Generation.str.contains("BACKUP")')
    
    # Get backup 'capacity' based on the nth maximum production from BACKUP units (nth_max = 1 => No inadequacy, nth_max = 3 => LOLE = 3 h, perhaps)
    if nth_max == -1:
        cap = df.pivot_table(index=['Region'], columns=['Commodity'],
                            values='Value', aggfunc='max')
    else:
        cap = (
            df.groupby(['Region', 'Commodity'])['Value']    
            .apply(lambda x: x.nlargest(nth_max).iloc[-1])  # Selects N'th max
            .unstack()  # Reshapes the data into a table
        )
    cap.to_csv('analysis/output/%s_backcapN%d.csv'%(scenario.replace('_operun', ''), nth_max))
    
    ## Get energy not served
    ENS = df.pivot_table(index=['Season', 'Time'], columns='Commodity',
                          values='Value', aggfunc='sum')
    
    df_out = pd.DataFrame({
        'ENS_TWh' : ENS.sum() / 1e6,
        'LOLE_h'  : ENS.count()
    })
    
    df_out.to_csv('analysis/output/%s_adeq.csv'%scenario.replace('_operun', ''))

@CLI.command()
@click.pass_context
@click.argument('scenarios', type=str, required=True)
def RA_Plot(ctx, scenarios: str):
    "Plot LOLE and ENS"
    
    scenarios = scenarios.replace(' ', '').split(',')
    
    for scenario in scenarios:
        if 'df' not in locals():
            df = pd.read_csv('analysis/output/%s_adeq.csv'%scenario)
            df['Scenario'] = scenario
        else:
            temp = pd.read_csv('analysis/output/%s_adeq.csv'%scenario)
            temp['Scenario'] = scenario
            df = pd.concat((df, temp), ignore_index=True)
            
    # Plot
    fig, ax = plt.subplots()
    ax2 = ax.twinx()
    
    df = sort_scenarios(df)
    df = df.pivot_table(index='Scenario', values=['ENS_TWh', 'LOLE_h'], 
                     columns='Commodity', aggfunc='sum')
    
    df['ENS_TWh'].plot(ax=ax, kind='bar', stacked=True, color=balmorel_colours)
    for commodity in df.LOLE_h.columns:
        ax2.plot(df.index, df.LOLE_h[commodity], linestyle='none', marker='o', 
                markeredgecolor='k', color=balmorel_colours[commodity], label=f'LOLE {commodity}')
    
    ax2.set_ylabel('LOLE (h)')
    ax2.set_ylim((0, df.LOLE_h.max().max()*1.1))
    ax.set_ylabel('Energy Not Served (TWh)')
    
    plot_style(fig, ax, 'RA-plot', legend_pos='up')

@CLI.command()
@click.pass_context
@click.argument('scenarios', type=str, required=True)
@click.argument('symbol', type=str, required=True)
@click.argument('index', type=str, required=True)
@click.argument('columns', type=str, required=True)
@click.option('--filters', type=str, default=None, required=False, help='Filters for df.query(...)')
def bar_chart(ctx, scenarios: str, symbol: str, 
              index: Union[str | list], columns: Union[str | list],
              filters: str):
    """
    Generates a bar chart from the specified scenarios and symbol.
    This function retrieves data from the specified scenarios, processes it, and generates a bar chart
    based on the provided symbol, index, and columns. The resulting chart is saved as 'bar_chart_output.png'.
    
    Args:
        ctx (click.Context): The Click context object containing the Balmorel model and path information.
        scenarios (str): A comma-separated string of scenario names.
        symbol (str): The symbol to retrieve data for.
        index (Union[str, list]): The index or indices to use for the pivot table.
        columns (Union[str, list]): The columns to use for the pivot table.
    """
    
    # Find scenarios
    model = ctx.obj['Balmorel']
    scenarios = scenarios.replace(' ', '').split(',')
    paths = []
    files = []
    for sc in scenarios:
        paths.append(os.path.join(ctx.obj['path'], model.scname_to_scfolder[sc], 'model'))
        files.append('MainResults_%s.gdx'%sc)
    mr = MainResults(files=files, paths=paths, system_directory=ctx.obj['gams_system_directory'])
    
    # Prepare index and columns
    if ',' in index:
        index = index.replace(' ', '').split(',')
    if ',' in columns:
        columns = columns.replace(' ', '').split(',')
    
    # Get symbol
    fig, ax = plt.subplots()
    df = sort_scenarios(mr.get_result(symbol))
    
    # Apply filters
    if filters != None:
        df = df.query(filters)
        
    df = df.pivot_table(index=index, columns=columns, values='Value', aggfunc='sum')
    try:
        df.plot(kind='bar', stacked=True, ax=ax, color=balmorel_colours)
    except KeyError:
        df.plot(kind='bar', stacked=True, ax=ax)
    
    ax.legend(bbox_to_anchor=(1.01, .5), loc='center left')
    
    fig.savefig('analysis/plots/bar_chart_output.png', bbox_inches='tight')
    

#%% ------------------------------- ###
###            2. Utils             ###
### ------------------------------- ###

def sort_scenarios(df: pd.DataFrame):
    "Will sort scenarios, so e.g. N2 comes before N10"
    
    df['Scenario'] = pd.Categorical(df['Scenario'], categories=sorted(df['Scenario'].unique(), key=lambda x: int(re.findall(r'N\d+', x)[0][1:]) if re.findall(r'N\d+', x) else float('inf')))
    
    return df

@click.pass_context
def plot_style(ctx, fig: plt.figure, ax: plt.axes, name: str,
               legend: bool = True, legend_pos: str = 'right'):
    fig.set_size_inches((7, 4))
    ax.set_facecolor(ctx.obj['fc'])
    
    if legend and legend_pos == 'up':
        ax.legend(loc='lower center',
                bbox_to_anchor=(.5, 1),
                ncol=3)
    elif legend and legend_pos == 'right':
        ax.legend(loc='center left',
                bbox_to_anchor=(1, .5),
                ncol=1)
    
    plot_path = ctx.obj['plot_path']
    if not(os.path.exists(plot_path)):
        os.mkdir(plot_path)
            
    fig.savefig(os.path.join(ctx.obj['plot_path'], name + ctx.obj['plot_ext']),
                bbox_inches='tight', transparent=True)

    return fig, ax

@click.pass_context
def collect_storage_profiles(ctx, scenarios: list):
    
    abspath = os.path.abspath(ctx.obj['path'])
    file_path = os.path.join(abspath, 'analysis', 'files', 'storage_profiles.pkl')
    if os.path.exists(file_path) and not(ctx.obj['overwrite']):
        print('Result file already exists, loading storage profiles..')
        file_exists = True
        with open(file_path, 'rb') as f:
            sto = pickle.load(f)

        # Check if scenarios in file
        scenario_in_existing_file = True
        scenarios_not_in_file = [] 
        for scenario in scenarios:
            if not(np.any(sto.Scenario.str.contains(scenario))):
                scenarios_not_in_file.append(scenario)
                scenario_in_existing_file = False
                print('Could not find %s in existing storage profile files..'%scenario)
    else:
        file_exists = False
        scenario_in_existing_file = False
        
    if not(scenario_in_existing_file):
        print('\nCollecting storage results to storage profiles..\n')
        
        # New dataframe or append to existing        
        if not(file_exists):
            # If there is no file, append to these empty dataframes
            sto = pd.DataFrame()
        else:
            # In this case, the file existed, but the following scenarios were missing, so we append
            scenarios = scenarios_not_in_file

        # Find paths
        m = ctx.obj['Balmorel']

        for scenario in scenarios:
            for storage_type in ['inter', 'intra']:
                for carrier in ['electricity', 'heat', 'hydrogen']:
                    if storage_type == 'inter' and (carrier == 'electricity' or carrier == 'hydrogen'):
                        continue
                    
                    if carrier == 'hydrogen':
                        storage_type = 'h2-storage'
                    
                    storage_results = get_storage_profiles(os.path.join(abspath, m.scname_to_scfolder[scenario], 'model', 'all_endofmodel.gdx'),
                                                                    carrier, storage_type)

                    storage_results['Scenario'] = scenario
                    storage_results['Technology'] = storage_type
                    storage_results['Commodity'] = carrier
                    sto = pd.concat((sto, storage_results))
                        
        
        file_folder_path = os.path.join(abspath, 'analysis', 'files')
        if not(os.path.exists(file_folder_path)):
            os.mkdir(file_folder_path)
    
        with open(file_path, 'wb') as f:
            pickle.dump(sto, f)

    return sto

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

@click.pass_context
def load_geofile(scenario: str, cluster_params: str = 'DE, DH, WNDFLH, SOLEFLH'):
    """
    Get the geofile for the scenario
    """    
    
    cluster_params = '-'.join(cluster_params.replace(' ', '').split(','))
    
    if 'N' in scenario:
        geofile = gpd.read_file('analysis/geofiles/%s_%dcluster_geofile.gpkg'%(cluster_params, int(scenario.replace('N', ''))))
    else:
        geofile = gpd.read_file('analysis/geofiles/gadm36_DNK_2.shp')
        name_column = 'NAME_2'
        geofile[name_column] = (
            geofile[name_column]
            .str.replace('Æ', 'Ae')
            .str.replace('Ø', 'Oe')
            .str.replace('Å', 'Aa')
            .str.replace('æ', 'ae')
            .str.replace('ø', 'oe')
            .str.replace('å', 'aa')
        )
        geofile.columns = pd.Series(geofile.columns).str.replace('NAME_2', 'cluster_name')
        
    return geofile


# 3. Main
if __name__ == '__main__':
    CLI()
