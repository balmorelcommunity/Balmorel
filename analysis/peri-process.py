"""
TITLE

Description

Created on 11.02.2025
@author: Mathias Berg Rosendal, PhD Student at DTU Management (Energy Economics & Modelling)
"""
#%% ------------------------------- ###
###             0. CLI              ###
### ------------------------------- ###

import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import click
from pybalmorel import Balmorel, MainResults, IncFile

@click.group()
@click.argument('scenario', type=str, required=True)
@click.option('--dark-style', is_flag=True, required=False, help='Dark plot style')
@click.option('--plot-ext', type=str, default='.pdf', required=False, help='The extension of the plot, defaults to ".pdf"')
@click.pass_context
def CLI(ctx, scenario: str, dark_style: bool, plot_ext: str):
    """
    Description of the CLI
    """
    
    # Find scenario
    m = Balmorel('.')
    m.locate_results()
    scfolder = m.scname_to_scfolder[scenario]
    
    # Load MainResults
    mr = MainResults('MainResults_%s.gdx'%scenario, 
                     paths='./%s/model'%scfolder)
    
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
    ctx.obj['scenario'] = scenario
    ctx.obj['model'] = m
    ctx.obj['scfolder'] = scfolder
    ctx.obj['mainresults'] = mr

#%% ------------------------------- ###
###           1. Commands           ###
### ------------------------------- ###

@CLI.command()
@click.pass_context
@click.option('--thresh', type=float, required=True, help="Threshold that capacities cannot be below")
def inv_options(ctx, thresh: float):
    "Disallow investment options below a certain treshold"
    
    df = ctx.obj['mainresults'].get_result('G_CAP_YCRAF')
    df = df.query('Commodity == "SYNFUEL"').pivot_table(index='Area', columns='Generation', values='Value', aggfunc='sum')
    
    # Find too small investments from the sum of all synfuelproducertypes
    idx = df.sum(axis=1) < thresh
    
    if len(df.loc[idx]) == 0:
        print('No investments below threshold!')
        exit(5)
        
    else:
        # Write lines for AGKN to disallow investments
        all_generators = ['GNR_TG-MeOH-STRAW-2050_H2', 
                        'GNR_TG-MeOH-STRAW-2050',
                        'GNR_TG-MeOH-WOOD-2050_H2', 
                        'GNR_TG-MeOH-WOOD-2050',
                        'GNR_TG-FT-STRAW-2050',
                        'GNR_TG-FT-WOOD-2050',
                        'GNR_eNH3-2050']
        
        lines = []
        for area in df.loc[idx].index:
            for generator in all_generators:
                lines.append("AGKN('%s','%s') = NO;"%(area, generator))
        append_lines = '\n'.join(lines)
        
        # Write to file
        scenario = ctx.obj['scenario']
        scfolder = ctx.obj['scfolder']
        with open('./%s/data/AGKN.inc'%scfolder, '+a') as f:
            f.write('\n\n* ------ Beginning of scenario %s Disallowed Investments ------\n\n'%scenario)
            f.write(append_lines)
            f.write('\n\n* ------ End of scenario %s Disallowed Investments ------\n\n'%scenario)
        
@CLI.command()
@click.pass_context
@click.option('--squeeze-factor', type=float, default=0.05, help="A factor to squeeze the profile, to avoid infeasibility (1 = flat, 0 = no adjustment)")
def seasonal_synfuel(ctx, squeeze_factor: float):
    "Convert seasonal production from investment runs (and interpolate) to create seasonal variation pattern for synfuelproducers in operational run"
    
    # Load context
    scenario = ctx.obj['scenario']
    df = ctx.obj['mainresults'].get_result('PRO_YCRAGFST')
    seasons_in_model = ctx.obj['mainresults'].get_result('EL_PRICE_YCRST')['Season'].unique()
    
    # Filter
    df = (
        df
        .query('Commodity == "SYNFUEL" and Technology == "SYNFUELPRODUCER"')
        .pivot_table(index='Season', values='Value', aggfunc='sum')
        .fillna(0)
    )
    
    # Fill zeros
    for S in seasons_in_model:
        try:
            df.loc[S]
        except KeyError:
            df.loc[S, :] = 0
    
    # Interpolate
    all_seasons = ['S0%d'%i for i in range(1, 10)] + ['S%d'%i for i in range(10, 53)]
    for S in [season for season in all_seasons if season not in df.index]:
        idx = all_seasons.index(S)
        S_before = all_seasons[idx-1]
        if idx == 51:
            S_after = all_seasons[0]
        else:
            S_after = all_seasons[idx+1]
        df.loc[S, :] = (df.loc[S_after, :] + df.loc[S_before, :]) / 2
    
    # Normalise to full year production
    df = df.loc[all_seasons] # Sort
    df = df / df.sum()
    
    # Squeeze profile to avoid infeasibility
    df = df * (1 - squeeze_factor) + squeeze_factor/52
    
    # Write to file
    scfolder = ctx.obj['scfolder']
    f = IncFile(name='HYDROGEN_SYNFUELDEMANDS',
                path='./%s/data'%scfolder,
                prefix='PARAMETER SYNFUELDEMANDS(SSS) "Normalised, seasonal variation of synfueldemand"\n/',
                body=df,
                suffix='\n/;'
                )
    f.body_prepare(index='Season', columns=None, values='Value')
    f.body.columns = ['']
    f.save()

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

#%% ------------------------------- ###
###             3. Main             ###
### ------------------------------- ###
if __name__ == '__main__':
    CLI()
