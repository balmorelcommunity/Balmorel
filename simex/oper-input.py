"""
Disaggregate Capacities from Aggregated Scenario

This script assumes that you have 
1) shapefiles of the spatial resolution of two equivalent energy system models at different resolutions (see hardcoded gpd.read_file statements), 
2) GKACCUMNET files of investment runs from both (see read_gdx statements) 

Sorry about the inefficient and horrible nested for-loops. It can be parallelised by rewriting to a gamspy application.

Created on 16.12.2024
@author: Mathias Berg Rosendal, PhD Student at DTU Management (Energy Economics & Modelling)
"""
#%% ------------------------------- ###
###             0. CLI              ###
### ------------------------------- ###

import gams.control
import gams.control.workspace
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import click
from pybalmorel.utils import symbol_to_df
import gams 
import geopandas as gpd
import os

@click.group()
@click.option('--dark-style', is_flag=True, required=False, help='Dark plot style')
@click.option('--plot-ext', type=str, default='.pdf', required=False, help='The extension of the plot, defaults to ".pdf"')
@click.pass_context
def CLI(ctx, dark_style: bool, plot_ext: str):
    """
    Description of the CLI
    """
    
    # Set global style of plot
    if dark_style:
        plt.style.use('dark_background')
        fc = 'none'
    else:
        fc = 'white'

    # Store global options in the context object
    ctx.ensure_object(dict)
    ctx.obj['fc'] = fc
    ctx.obj['plot_ext'] = plot_ext


#%% ------------------------------- ###
###           1. Commands           ###
### ------------------------------- ###

@CLI.command()
@click.argument('aggregated-scenario', type=str, required=True)
@click.argument('disaggregated-scenario', type=str, required=True)
@click.option('--agg-regcol', type=str, required=False, default='cluster_name', help='The name of the column containing the aggregated regions')
@click.option('--disagg-regcol', type=str, required=False, default='Name', help='The name of the column containing the disaggregated regions')
@click.option('--ssl', is_flag=True, required=False, help='Perform inter- and extrapolation of seasonal storage levels')
@click.pass_context
def disagg(ctx, aggregated_scenario: str, disaggregated_scenario: str,
               agg_regcol: str, disagg_regcol: str, ssl: bool = False):
    """
    Disaggregate capacities and seasonal storage levels from an aggregated scenario result to a disaggregated scenario operational input, 
    by checking which shapefiles in the disaggregated scenario are contained in the aggregated regions.
    
    The capacities in the disaggregated scenario is used to distribute the capacities from the aggregated scenario
    """

    df_agg, GDX_agg = read_gdx(symbol='GKACCUMNET', filename='simex_%s/GKACCUMNET.gdx'%aggregated_scenario)
    df_disagg, GDX_disagg = read_gdx(symbol='GKACCUMNET', filename='simex_%s/GKACCUMNET.gdx'%disaggregated_scenario)
    
    print('Sum of capacities in aggregated scenario: %0.2f MW'%(df_agg.Value.sum()))
    print('Sum of capacities in disaggregated scenario BEFORE processing: %0.2f MW'%(df_disagg.Value.sum()))

    gf_agg = gpd.read_file('analysis/geofiles/DE-DH-WNDFLH-SOLEFLH_%scluster_geofile.gpkg'%(aggregated_scenario.lstrip('N')))
    gf_agg.columns = pd.Series(gf_agg.columns).str.replace(agg_regcol, 'cluster_name')
    gf_disagg = gpd.read_file('analysis/geofiles/municipalities.gpkg')
    gf_disagg.columns = pd.Series(gf_disagg.columns).str.replace(disagg_regcol, 'cluster_name')
    
    # Read seasonal storage files
    if ssl:
        dfHSTO, GDXHS = read_gdx('HSTOVOLTS', 'simex_%s/HSTOVOLTS.gdx'%aggregated_scenario)
        dfH2STO, GDXH2S = read_gdx('H2STOVOLTS', 'simex_%s/H2STOVOLTS.gdx'%aggregated_scenario)
        seasonal_storage_files = {'HSTOVOLTS' : {'df' : dfHSTO, 'GDX' : GDXHS},
                                'H2STOVOLTS' : {'df' : dfH2STO, 'GDX' : GDXH2S}}
    else:
        print('No inter- and extrapolation of seasonal storage levels')
        
    # Loop through polygons of aggregated scenario
    fig, ax = plt.subplots()
    cmap = plt.get_cmap("viridis")
    for i, region in enumerate(gf_agg.cluster_name):
        
        # Find the polygons in the disaggregated scenario within this aggregated region
        geo_disagg_idx = gf_agg.query('cluster_name == @region').geometry.iloc[0].contains(gf_disagg.geometry)
        gf_disagg.loc[geo_disagg_idx].plot(facecolor=cmap(i / len(gf_agg.cluster_name)), ax = ax) # Validate with a plot
        gf_disagg.loc[geo_disagg_idx, 'parent_cluster'] = region # Set parent region
        disagg_regions = '|'.join(gf_disagg.loc[geo_disagg_idx, 'cluster_name']) # Get disaggregated regions as a regex pattern
        M_regions = len(disagg_regions.split('|'))
        
        print('# of disaggregated regions in %s: %d'%(region, M_regions))

        # Loop through areas
        for suffix in ['_A', '_IDVU-SPACEHEAT', '_IND-HT-NODH', '_IND-LT-NODH', '_IND-MT-NODH', '_OFF']:

            # Loop through model years
            for year in df_agg.YYY.unique():
                
                # Get relevant areas
                area_agg = region + suffix
                area_agg_idx = df_agg.query('@area_agg in AAA and YYY == @year').index
                areas_disagg_idx = df_disagg.query('AAA.str.contains(@disagg_regions) and AAA.str.contains(@suffix) and YYY == @year').index
                
                # Check if there is any aggregated capacity in this area
                aggregated_capacity_exists = area_agg in df_agg.AAA.unique()
                
                if aggregated_capacity_exists:
                    
                    aggregated_techs = df_agg.loc[area_agg_idx, 'GGG'].unique()
                    disaggregated_techs = df_disagg.loc[areas_disagg_idx, 'GGG'].unique()
                    
                    # Delete technologies not invested in by aggregated model
                    unique_disaggregated_techs = list(set(disaggregated_techs) - set(aggregated_techs))
                    unique_aggregated_techs = list(set(aggregated_techs) - set(disaggregated_techs))
                    unique_idx = df_disagg.loc[areas_disagg_idx].query('@unique_disaggregated_techs in GGG').index
                    df_disagg.loc[np.intersect1d(areas_disagg_idx, unique_idx), 'Value'] = 0
                    
                    # Loop through aggregated technologies
                    for technology in list(set(aggregated_techs) - set(unique_aggregated_techs)):
                        
                        if 'BACKUP' in technology:
                            continue
                        
                        tech_idx_agg = np.intersect1d(area_agg_idx, df_agg.query('GGG == @technology').index)
                        tech_idx_disagg = np.intersect1d(areas_disagg_idx, df_disagg.query('GGG == @technology').index)
                        
                        cap = df_disagg.loc[tech_idx_disagg]

                        df_disagg.loc[tech_idx_disagg, 'Value'] = df_agg.loc[tech_idx_agg, 'Value'].values.sum() * cap.Value.values / cap.Value.sum()
                        
                        for disaggregated_area in df_disagg.loc[tech_idx_disagg, 'AAA'].unique():
                            GDX_disagg['GKACCUMNET'][year, disaggregated_area, technology].value = df_disagg.loc[tech_idx_disagg].query('AAA == @disaggregated_area')['Value'].sum()
                    
                    # Loop through unique disaggregated technologies to delete them
                    for technology in unique_disaggregated_techs:
                        tech_idx_disagg = np.intersect1d(areas_disagg_idx, df_disagg.query('GGG == @technology').index)
                        df_disagg.loc[tech_idx_disagg, 'Value'] = 0
                        for disaggregated_area in df_disagg.loc[tech_idx_disagg, 'AAA'].unique():
                            try:
                                GDX_disagg['GKACCUMNET'][year, disaggregated_area, technology].value = 0
                            except gams.GamsException:
                                ## In this particular area, the unique tech was not present
                                pass                
                        
                    # Make uniform distribution of technologies unique to aggregated solution
                    ## Create new dataframe with all disaggregated regions
                    temp = pd.DataFrame({'YYY' : year, 'AAA' : gf_disagg.loc[geo_disagg_idx, 'cluster_name'] + suffix})
                    
                    ## Do cartesian product, to distribute aggregated capacities equally to all areas
                    temp = temp.merge(df_agg.loc[area_agg_idx].query('@unique_aggregated_techs in GGG'), on='YYY')
                    
                    ## Clean up
                    temp = temp.drop(columns=['AAA_y'])
                    temp.columns = ['YYY', 'AAA', 'GGG', 'Value']
                    
                    ## Make uniform distribution by taking the average 
                    temp.loc[:, 'Value'] = temp.loc[:, 'Value'] / M_regions
                    
                    ## Append to disaggregated capacity dataframe
                    df_disagg = pd.concat((df_disagg, temp), ignore_index=True)
                    for technology in temp.GGG.unique():
                        tech_idx_agg = np.intersect1d(area_agg_idx, df_agg.query('GGG == @technology').index)
                        for disaggregated_area in temp.AAA.unique():
                            GDX_disagg['GKACCUMNET'].add_record((year, disaggregated_area, technology))
                            GDX_disagg['GKACCUMNET'][year, disaggregated_area, technology].value = temp.loc[0, 'Value']
                            
                    # Disaggregate storage levels    
                    if ssl:
                        for seasonal_storage in ['HSTOVOLTS', 'H2STOVOLTS']:
                            ## Merge
                            try:
                                # Interpolate 
                                merged = interpolate_seasons(area_agg, year, seasonal_storage_files[seasonal_storage]['df'])
                                    
                                # Adapt the GDX file
                                for technology in merged.drop(columns='SSS').columns:
                                    
                                    # Normalise timeseries
                                    # print('Before normalisation: ', merged)
                                    merged.loc[:, technology] = merged.loc[:, technology] / (merged.loc[:, technology].max() + 0.01) # Add 0.01 for feasibility
                                    # print('After normalisation: ', merged)
                                    
                                    for disaggregated_area in temp.AAA.unique():
                                        
                                        # Try to get capacity in this area
                                        try:
                                            cap = GDX_disagg['GKACCUMNET'][year, disaggregated_area, technology].value
                                            print('Capacity of %s in %s'%(technology, disaggregated_area), cap)
                                            for season in merged.SSS.unique():
                                                seasonal_storage_files[seasonal_storage]['GDX'][seasonal_storage].add_record((year, disaggregated_area, technology, season, 'T001'))
                                                seasonal_storage_files[seasonal_storage]['GDX'][seasonal_storage][year, disaggregated_area, technology, season, 'T001'].value = merged.loc[merged.SSS == season, technology].values[0] * cap
                                        except gams.GamsException:
                                            pass

                            except KeyError:
                                print('No seasonal storage in %s'%area_agg)
                                                    
                else:
                    # Will delete all technologies in this area
                    df_disagg.loc[areas_disagg_idx, 'Value'] = 0
                    for technology in df_disagg.loc[areas_disagg_idx, 'GGG'].unique():
                        for disaggregated_area in df_disagg.loc[areas_disagg_idx, 'AAA'].unique():
                            GDX_disagg['GKACCUMNET'].delete_record((year, disaggregated_area, technology))
                       
    print('Sum of capacities in disaggregated scenario AFTER processing: %0.2f MW'%(df_disagg.Value.sum()))
    print('Sum of disaggregated capacities AFTER - Sum of aggregated capacities = %0.2f'%(df_disagg.Value.sum() - df_agg.Value.sum()))
    plot_style(fig, ax, 'simex/%s_%s_connection-validation'%(aggregated_scenario, disaggregated_scenario))
    
    GDX_disagg.export('/work3/mberos/Balmorel/simex/GKACCUMNET.gdx')
    if ssl:
        seasonal_storage_files['HSTOVOLTS']['GDX'].export('/work3/mberos/Balmorel/simex/HSTOVOLTS.gdx')
        seasonal_storage_files['H2STOVOLTS']['GDX'].export('/work3/mberos/Balmorel/simex/H2STOVOLTS.gdx')
    

@CLI.command()
@click.argument('aggregated-scenario', type=str, required=True)
@click.pass_context
def seasonal_levels(ctx, aggregated_scenario: str):
    """
    Inter- and extrapolates seasonal storage levels to all seasons based on a previous run
    """
    
    all_seasons = ['S0%d'%i for i in range(1, 10)] + ['S%d'%i for i in range(10, 53)]
    
    for seasonal_storage in ['HSTOVOLTS', 'H2STOVOLTS']:
        
        # Read file
        df, GDX = read_gdx(seasonal_storage, 'simex_%s/%s.gdx'%(aggregated_scenario, seasonal_storage))
        included_seasons = df.SSS.unique()        

        # Interpolate with a circular yearly logic
        for year in df.Y.unique():
            for area in df.AAA.unique():
                ## Merge
                merged = interpolate_seasons(area, year, df)
                    
                ## Adapt the GDX file
                for technology in merged.drop(columns='SSS').columns:
                    for season in list(set(all_seasons) - set(included_seasons)):
                        GDX[seasonal_storage].add_record((year, area, technology, season, 'T001'))
                        GDX[seasonal_storage][year, area, technology, season, 'T001'].value = merged.loc[merged.SSS == season, technology].values[0]

        GDX.export('/work3/mberos/Balmorel/simex/%s.gdx'%seasonal_storage)
   
    
#%% ------------------------------- ###
###            2. Utils             ###
### ------------------------------- ###

@click.pass_context
def plot_style(ctx, fig: plt.figure, ax: plt.axes, name: str, legend: bool = True):
    
    ax.set_facecolor(ctx.obj['fc'])
    
    if legend:
        ax.legend(loc='center', bbox_to_anchor=(.5, 1.15), ncol=3)
    
    fig.savefig(name + ctx.obj['plot_ext'], bbox_inches='tight', transparent=True)
    
    return fig, ax

def read_gdx(symbol: str, filename: str, gams_system_directory: str = None):
    "Read gdx file"
    
    ws = gams.GamsWorkspace(system_directory=gams_system_directory)
    db = ws.add_database_from_gdx(os.path.abspath(filename))
    
    df = symbol_to_df(db, symbol)
    
    return df, db
    

def interpolate_seasons(area: str, year: int | str,
                        incomplete_timeseries: pd.DataFrame):
    
    # Make all seasons
    all_seasons = ['S0%d'%i for i in range(1, 10)] + ['S%d'%i for i in range(10, 53)]
    translator = pd.DataFrame(data={'SSS' : all_seasons})
    
    # Prepare dataframe
    incomplete_timeseries.columns = pd.Series(incomplete_timeseries.columns).str.replace('YYY', 'Y') # Minor correction
    temp = incomplete_timeseries.query('TTT == "T001"')
    temp.loc[temp.Value < 1e-9, 'Value'] = 0
    temp = temp.pivot_table(index=['Y', 'SSS'], columns=['AAA', 'GGG'], values='Value', aggfunc='sum').fillna(0)
    
    # Add all seasons
    full_timeseries = pd.merge(translator, temp.loc[(str(year), slice(None)), area], on='SSS', how='left')
    
    # Interpolate
    try:
        # If S01 exists, add that to the end to make a cycle
        full_timeseries = pd.concat((full_timeseries, full_timeseries.query('SSS == "S01"')), ignore_index=True)
        full_timeseries = full_timeseries.interpolate(method='linear').drop(index=52)
    except KeyError:
        # S01 was not present, so last values will be constants until S52
        full_timeseries = full_timeseries.interpolate(method='linear')  

    return full_timeseries     
    
#%% ------------------------------- ###
###             3. Main             ###
### ------------------------------- ###
if __name__ == '__main__':
    CLI()
