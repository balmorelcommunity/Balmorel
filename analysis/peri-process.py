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
from pybalmorel import Balmorel, MainResults

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
@click.option('--scenario', type=str, required=True, help="Scenario")
@click.option('--thresh', type=float, required=True, help="Threshold that capacities cannot be below")
@click.option('--iteration', type=int, required=True, help="Iteration number")
def inv_options(scenario: str, thresh: float, iteration: int):
    "Disallow investment options below a certain treshold"
    
    # Find scenario
    m = Balmorel('.')
    m.locate_results()
    scfolder = m.scname_to_scfolder[scenario]
    
    # Load MainResults
    mr = MainResults('MainResults_%s.gdx'%scenario, 
                     paths='./%s/model'%scfolder)
    
    df = mr.get_result('G_CAP_YCRAF')
    df = df.query('Commodity == "SYNFUEL"').pivot_table(index='Area', columns='Generation', values='Value', aggfunc='sum')
    
    # Find too small investments from the sum of all synfuelproducertypes
    idx = df.sum(axis=1) < thresh
    
    if len(df.loc[idx]) == 0:
        print('No investments below threshold!')
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
        with open('./%s/data/AGKN.inc'%scfolder, '+a') as f:
            f.write('\n\n* ------ Beginning of Iteration %d scenario %s Disallowed Investments ------\n\n'%(iteration, scenario))
            f.write(append_lines)
            f.write('\n\n* ------ End of Iteration %d scenario %s Disallowed Investments ------\n\n'%(iteration, scenario))
        
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
