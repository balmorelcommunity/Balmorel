"""
Analysis Script

Will plot different things, depending on command-line input.
Meant to be used with the analyse.sh shell-script, to ease command writing.

Created on 06.10.2024
@author: Mathias Berg Rosendal, PhD Student at DTU Management (Energy Economics & Modelling)
"""
#%% ------------------------------- ###
###        0. Script Settings       ###
### ------------------------------- ###

import matplotlib.pyplot as plt
import numpy as np
import click
from pybalmorel import Balmorel
from pybalmorel.formatting import balmorel_colours
import pickle
import os

def plot_style(fig: plt.figure, ax: plt.axes, 
               path: str, name: str,
               fc: tuple,
               plot_ext: str):

    ax.set_facecolor(fc)
    ax.legend(loc='center',
            bbox_to_anchor=(.5, 1.15),
            ncol=3)
    
    fig.savefig(os.path.join(path, 'analysis', 'files', name + plot_ext),
                bbox_inches='tight', transparent=True)

    return fig, ax

#%% ------------------------------- ###
###        1. 
### ------------------------------- ###

def collect_results(symbol: str,
                    path_to_Balmorel: str = '.',
                    overwrite: bool = False):
    
    abspath = os.path.abspath(path_to_Balmorel)
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

def plot_capacities(path_to_Balmorel: str, types: dict, overwrite: bool, **kwargs):
    
    for key in [key for key in types.keys() if types[key]]:
        print('\nPlotting %s capacities..'%key)
        
        fig, ax = plt.subplots()
        if key == 'gen':
            df = (
                collect_results('G_CAP_YCRAF', path_to_Balmorel, overwrite)
                .query('Technology != "H2-STORAGE" and not Technology.str.contains("INTERSEASONAL") and not Technology.str.contains("INTRASEASONAL")')
            ) 
            ax.set_ylabel('Generation Capacity [GW]')
        else:
            df = (
                collect_results('G_STO_YCRAF', path_to_Balmorel, overwrite)
                .query('Technology == "H2-STORAGE" or Technology.str.contains("INTERSEASONAL") or Technology.str.contains("INTRASEASONAL")')
            )
            df['Value'] = df['Value'] / 1e3 
            ax.set_ylabel('Storage Capacity [TWh]')
        
        df = (
            df
            .pivot_table(index='Scenario', columns='Technology', 
                            values='Value', aggfunc='sum')
            .plot(ax=ax, kind='bar', stacked=True, color=balmorel_colours)
        )
        
        plot_style(fig, ax, path_to_Balmorel, '%scap'%key, **kwargs)
        
        
def plot_costs(path_to_Balmorel: str, overwrite: bool, **kwargs):
    print('\nPlotting system costs..')
    
    fig, ax = plt.subplots()
    df = (
        collect_results('OBJ_YCR', path_to_Balmorel, overwrite)
        .pivot_table(index='Scenario', columns='Category', 
                     values='Value', aggfunc=lambda x: np.sum(x)/1e3)
        .plot(ax=ax, kind='bar', stacked=True)
        .set_ylabel('System Costs [B€]')
    ) 
    
    # Y limits were a bit too tight
    ylims = ax.get_ylim()
    ax.set_ylim(ylims[0], ylims[1]*1.05)
    
    plot_style(fig, ax, path_to_Balmorel, 'systemcosts', **kwargs)

#%% ------------------------------- ###
###            X. Main              ###
### ------------------------------- ###
# @click.option('gencap', is_flag=True, required=False, help='Get capacity plot')

@click.command(context_settings=dict(ignore_unknown_options=True))
@click.option('--gencap', is_flag=True, required=False, help='Plot generation capacities')
@click.option('--stocap', is_flag=True, required=False, help='Plot storage capacities')
@click.option('--obj', is_flag=True, required=False, help='Plot objective function')
@click.option('--all', is_flag=True, required=False, help='Plot everything')
@click.option('--overwrite', is_flag=True, required=False, help='Overwrite previous collected results?')
@click.option('--dark-style', is_flag=True, required=False, help='Dark style of the plot')
@click.option('--plot-ext', type=str, required=False, default='.pdf', help='The extension of the plots, defaults to ".pdf"')
@click.option('--path', type=str, required=False, default='.', help='Path to top level of Balmorel folders')
def main(gencap: bool, stocap: bool, obj: bool, all: bool, 
         overwrite: bool, dark_style: bool, plot_ext: str, path: str):
    
    # Set global style of plot
    if dark_style:
        plt.style.use('dark_background')
        fc = 'none'
    else:
        fc = 'white'
        
    if all:
        gencap = True
        stocap = True
        obj = True
    
    if gencap | stocap:
        plot_capacities(path, {'gen' : gencap, 'sto' : stocap}, overwrite, plot_ext=plot_ext, fc=fc)
    
    if obj: 
        plot_costs(path, overwrite, plot_ext=plot_ext, fc=fc)
    
    print('') # A nice little space in the end

if __name__ == '__main__':
    main()
