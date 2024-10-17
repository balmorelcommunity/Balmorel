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

from gams import GamsWorkspace
import geopandas as gpd
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import click
from specific.pit_storage.pit_storage import get_storage_profiles, polygon_with_point
from pybalmorel import Balmorel, MainResults
from pybalmorel.utils import symbol_to_df
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
    
    # Store global options in the context object
    ctx.ensure_object(dict)
    ctx.obj['Balmorel'] = Balmorel(path) # Find Balmorel folder
    ctx.obj['overwrite'] = overwrite
    ctx.obj['dark_style'] = dark_style
    ctx.obj['plot_ext'] = plot_ext
    ctx.obj['path'] = path
    ctx.obj['plot_path'] = os.path.join(path, 'analysis', 'plots')
    
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
    
    for scenario in ctx.obj['Balmorel'].scenarios:
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
@click.option('--exclude-filters', '-e', type=str, default={}, required=False, help='Filters in .json format')
def cap(gen: bool, sto: bool, exclude_filters: str):
    """
    Plot generation or storage capacities
    """
    
    exclude_filters = eval(exclude_filters)
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
        
        # Apply exclusion filters
        for filter0 in exclude_filters.keys():
            print('Filtering %s from'%(str(exclude_filters[filter0])), filter0)
            if type(exclude_filters[filter0]) is list:
                for val in exclude_filters[filter0]:
                    df = df.query(f'{filter0} != @val')
            else:
                val = exclude_filters[filter0]
                df = df.query(f'{filter0} != @val')
                
        (
            df
            .pivot_table(index=['Commodity', 'Scenario'], columns='Technology', 
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
    """Plot energy balance of electricity, heat or hydrogen"""

    model_path = os.path.join(ctx.obj['path'], scenario, 'model')

    # Get mainresults files
    mainresult_files = pd.Series(os.listdir(model_path))
    idx = mainresult_files.str.contains('MainResults')
    mainresult_files = mainresult_files[idx]
    
    m = MainResults(list(mainresult_files), paths=model_path)
    
    if len(m.sc) > 1:
        for sc in m.sc:
            fig, ax = m.plot_profile(commodity, year, sc, style=ctx.obj['plot_style_for_modules'])
            fig, ax = plot_style(fig, ax, 'profile_%s'%(commodity + '-' + str(year) + '-' + scenario + '-' + sc))
    elif len(m.sc) == 1:
        fig, ax = m.plot_profile(commodity, year, m.sc[0], style=ctx.obj['plot_style_for_modules'])
        fig, ax = plot_style(fig, ax, 'profile_%s'%(commodity + '-' + str(year) + '-' + m.sc[0]))
    else:
        print('No results for %s'%scenario)

@CLI.command()
@click.pass_context
@click.argument('commodity', type=str)
@click.argument('scenario', type=str)
@click.argument('year', type=int, default=2050)
@click.argument('geofile', type=str, default='analysis/geofiles/gadm36_DNK_2.shp')
@click.argument('geofile_region_column', type=str, default='NAME_2')
@click.argument('lon-lims', type=list, default=[7.8, 13])
@click.argument('lat-lims', type=list, default=[54.4, 58])
def map(ctx, commodity: str, scenario: str, year: int, 
        geofile: str, geofile_region_column: str,
        lon_lims: list, lat_lims: list):
    """Plot transmission capacity maps for electricity or hydrogen"""

    model_path = os.path.join(ctx.obj['path'], scenario, 'model')

    # Get mainresults files
    mainresult_files = pd.Series(os.listdir(model_path))
    idx = mainresult_files.str.contains('MainResults')
    mainresult_files = mainresult_files[idx]
    
    m = MainResults(list(mainresult_files), paths=model_path)
    
    if 'N' in scenario:
        geofile = 'analysis/geofiles/DE-DH-WNDFLH-SOLEFLH_%dcluster_geofile.gpkg'%(int(scenario.lstrip('N')))
        geofile_region_column = 'cluster_name'
    
    if len(m.sc) > 1:
        for sc in m.sc:
            fig, ax = m.plot_map(sc, commodity.capitalize(), year, path_to_geofile=geofile, geo_file_region_column=geofile_region_column, style=ctx.obj['plot_style_for_modules'])
            ax.set_xlim(lon_lims)
            ax.set_ylim(lat_lims)
            fig, ax = plot_style(fig, ax, 'map_%s'%(commodity + '-' + str(year) + '-' + scenario + '-' + sc), legend=False)
    elif len(m.sc) == 1:
        fig, ax = m.plot_map(m.sc[0], commodity.capitalize(), year, path_to_geofile=geofile, geo_file_region_column=geofile_region_column, style=ctx.obj['plot_style_for_modules'])
        ax.set_xlim(lon_lims)
        ax.set_ylim(lat_lims)
        fig, ax = plot_style(fig, ax, 'map_%s'%(commodity + '-' + str(year) + '-' + m.sc[0]), legend=False)
    else:
        print('No results for %s'%scenario)
        
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
        if 'N' in scenario:
            geofile = gpd.read_file('analysis/geofiles/DE-DH-WNDFLH-SOLEFLH_%dcluster_geofile.gpkg'%int(scenario.replace('N', '')))
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
        .query(f'Technology == "{filter_input}"')
        .pivot_table(index=['Scenario', 'Region'],  columns='Generation', values='Value', aggfunc='sum')
    )
    
    for col in res.columns:
        print('Largest %s'%col)
        print(res.nlargest(10, col))
        print('Smallest %s'%col)
        print(res.nsmallest(10, col))
    
    # res.plot(ax=ax)
    
    # ax.set_title(filter_input)
    # fig, ax = plot_style(fig, ax, f'{result}_filter{filter_input}_intersto_hightemp')
    
@CLI.command()
@click.pass_context
@click.argument('scenario', type=str, required=True)
@click.argument('symbol', type=str, required=True)
def allendofmodel(ctx, scenario: str, symbol: str,
                   gams_system_directory: str = '/appl/gams/47.6.0'):
    
    # Load all_endofmodel for the specified scenario
    ws = GamsWorkspace(system_directory=gams_system_directory)
    db = ws.add_database_from_gdx(os.path.abspath(os.path.join(ctx.obj['path'], scenario, 'model', 'all_endofmodel.gdx')))
    
    # Get symbol
    df = symbol_to_df(db, symbol)
    
    print(df)
    
    return df

#%% ------------------------------- ###
###            2. Utils             ###
### ------------------------------- ###

@click.pass_context
def plot_style(ctx, fig: plt.figure, ax: plt.axes, name: str,
               legend: bool = True):
    
    ax.set_facecolor(ctx.obj['fc'])
    
    if legend:
        ax.legend(loc='center',
                bbox_to_anchor=(.5, 1.15),
                ncol=3)
    
    plot_path = ctx.obj['plot_path']
    if not(os.path.exists(plot_path)):
        os.mkdir(plot_path)
            
    fig.savefig(os.path.join(ctx.obj['plot_path'], name + ctx.obj['plot_ext']),
                bbox_inches='tight', transparent=True)

    return fig, ax

@click.pass_context
def collect_storage_profiles(ctx, scenarios: list):
    
    abspath = os.path.abspath(ctx.obj['path'])
    profiles = ['charge', 'discharge', 'level']
    sto = {}
    file_paths = [os.path.join(abspath, 'analysis', 'files', '%s_profile.pkl'%profile) for profile in profiles]
    if os.path.exists(file_paths[0]) and os.path.exists(file_paths[1]) and os.path.exists(file_paths[2]) and not(ctx.obj['overwrite']):
        print('Result file already exists, loading storage profiles..')
        file_exists = True
        for i in range(len(profiles)):
            with open(file_paths[i], 'rb') as f:
                sto[profiles[i]] = pickle.load(f)

        # Check if scenarios in file
        scenario_in_existing_file = True
        scenarios_not_in_file = [] 
        for scenario in scenarios:
            if not(np.any(sto[profiles[0]].Scenario.str.contains(scenario))) or not(np.any(sto[profiles[1]].Scenario.str.contains(scenario))) or not(np.any(sto[profiles[2]].Scenario.str.contains(scenario))):
                scenarios_not_in_file.append(scenario)
                scenario_in_existing_file = False
                print('Could not find %s in existing storage profile files..'%scenario)
    else:
        file_exists = False
        scenario_in_existing_file = False
        
    if not(scenario_in_existing_file):
        print('\nCollecting storage results to storage profiles..\n')
        
        if not(file_exists):
            # If there is no file, append to these empty dataframes
            sto['charge'] =  pd.DataFrame()
            sto['discharge'] =  pd.DataFrame()
            sto['level'] =  pd.DataFrame()
        else:
            # In this case, the file existed, but the following scenarios were missing, so we append
            scenarios = scenarios_not_in_file

        for scenario in scenarios:
            for storage_type in ['inter', 'intra']:
                for carrier in ['electricity', 'heat', 'hydrogen']:
                    if storage_type == 'inter' and (carrier == 'electricity' or carrier == 'hydrogen'):
                        continue
                    
                    if carrier == 'hydrogen':
                        storage_type = 'h2-storage'
                    
                    charge, discharge, level = get_storage_profiles(os.path.join(abspath, scenario, 'model', 'all_endofmodel.gdx'),
                                                                    carrier, storage_type)

                    for profile in profiles:
                        data = eval(profile)
                        data['Scenario'] = scenario
                        data['Technology'] = storage_type
                        data['Commodity'] = carrier
                        sto[profile] = pd.concat((sto[profile], data))
                        
        
        file_folder_path = os.path.join(abspath, 'analysis', 'files')
        if not(os.path.exists(file_folder_path)):
            os.mkdir(file_folder_path)
    
        for i in range(len(profiles)):
            with open(file_paths[i], 'wb') as f:
                pickle.dump(sto[profiles[i]], f)

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


# 3. Main
if __name__ == '__main__':
    CLI()
