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
@click.pass_context
def cap_disagg(ctx, aggregated_scenario: str, disaggregated_scenario: str,
               agg_regcol: str, disagg_regcol: str):
    """
    Disaggregate capacities from an aggregated to a disaggregated scenario, 
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
                
                # Check if there is any capacity
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
                else:
                    raise Exception("Need to set every capacity in this area to zero!")
                       
    print('Sum of capacities in disaggregated scenario AFTER processing: %0.2f MW'%(df_disagg.Value.sum()))
    
    # df_disagg.to_excel('./GKACCUMNET.xlsx', index=False)
    GDX_disagg.export('/work3/mberos/Balmorel/GKACCUMNET2.gdx')
    
    fig.savefig('simex/%s_%s_connection-validation.png'%(aggregated_scenario, disaggregated_scenario))
    
    # How to change a GDX
    # for rec in GDX:
    #     if rec.keys == ['2050', 'CL1_A', 'GNR_TG-MeOH-2050']:
    #         print('The capacity of TG-MeOH in CL1_A: ', rec.value)
    #         print('Changing that..')
    #         rec.value = 50000
    
    # exported_file = 'output_gdx.gdx'
    # print('Saving to %s'%exported_file)
    # db.export(os.path.join('/work3/mberos/Balmorel', exported_file))

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
    

    
#%% ------------------------------- ###
###             3. Main             ###
### ------------------------------- ###
if __name__ == '__main__':
    CLI()
