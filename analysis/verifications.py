"""
Verifications of the model

Commands that verify that the model is not behaving nonsensical

Created on 19.03.2026
@author: Mathias Berg Rosendal
         PhD Student at DTU Management (Energy Economics & Modelling)
"""
# ------------------------------- #
#        0. Script Settings       #
# ------------------------------- #

from pathlib import Path
from decouple import config
from pybalmorel.utils import symbol_to_df
from pybalmorel import MainResults
from gams import GamsWorkspace
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import click

# ------------------------------- #
#          1. Functions           #
# ------------------------------- #



# ------------------------------- #
#            2. Main              #
# ------------------------------- #

@click.group()
@click.pass_context
@click.argument('sc-folder', type=str)
def main(ctx, sc_folder):
    """
    CLI for verifications
    """
    
    ctx.ensure_object(dict)
    ctx.obj['sc-folder'] = sc_folder
    

@main.command()
@click.pass_context
def check_all(ctx):
    """
    Run all verifications
    """
    
    ctx.invoke(debug_vars, sc_folder=ctx.obj['sc-folder'])


@main.command()
@click.pass_context
def debug_vars(ctx):
    """
    Check that the debug variables are not crazy
    """

    sc_folder = ctx.obj["sc-folder"]
    ws=GamsWorkspace()
    db=ws.add_database_from_gdx(str(Path(f'{sc_folder}/model/all_endofmodel.gdx').absolute()))

    for var in ['VQHEQ', 'VQHYRSMINVOL', 'VQHYRSSEQ']:
        df=symbol_to_df(db, var)
        print(df)

@main.command()
@click.pass_context
@click.option('--scenario', type=str, default='', help="Check a specific MainResults file in the folder")
def ev_results(ctx, scenario):
    """
    Check EV results
    """
    
    # Get MainResults file
    sc_folder=ctx.obj['sc-folder']
    if scenario != '':
        # If input, choose inputted scenario
        path = Path(f'{sc_folder}/model/MainResults_{scenario}.gdx')
    else:
        # If nothing input, find most recent MainResults
        path = Path(f'{sc_folder}/model')
        results =  [p for p in path.iterdir() if 'MainResults' in str(p)]
        mtimes = [modified.stat().st_mtime for modified in results]
        most_recent = mtimes.index(max(mtimes))
        path = Path(results[most_recent])
        print(f'\nMost recent results in {sc_folder}: {path.name}\n')

    # Load results 
    res = MainResults(path.name, str(path.parent))
    df = (
        res
        .get_result('EL_DEMAND_YCRST')
        .query('Category == "ENDO_EV"')
    )

    # Check max, mean and min
    df_max = (
        df
        .pivot_table(index=['Year', 'Region'],
                    values='Value',
                    aggfunc='max')
        .rename(columns={'Value' : 'Max'})
    )
    df_mean = (
        df
        .pivot_table(index=['Year', 'Region'],
                    values='Value',
                    aggfunc='mean')
        .rename(columns={'Value' : 'Mean'})
    )
    df_min = (
        df
        .pivot_table(index=['Year', 'Region'],
                    values='Value',
                    aggfunc='min')
        .rename(columns={'Value' : 'Min'})
    )
    df_max_pct = df_max['Max'] / df_mean['Mean'] * 100
    df_min_pct = df_min['Min'] / df_mean['Mean'] * 100
    df = (
        df_max
        .join(df_mean)
        .join(df_min)
    )
    df['Max % of Mean'] = df_max_pct
    df['Min % of Mean'] = df_min_pct
    print(df.round())


if __name__ == '__main__':
    main()
