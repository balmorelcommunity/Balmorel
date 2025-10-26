"""
Final Result Analyses

Final analyses for the PhD Thesis

Created on 26.10.2025
@author: Mathias Berg Rosendal
         PhD Student at DTU Management (Energy Economics & Modelling)
"""
# ------------------------------- #
#        0. Script Settings       #
# ------------------------------- #

import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import click
from pybalmorel import MainResults
from pathlib import Path

# ------------------------------- #
#          1. Functions           #
# ------------------------------- #

def get_scenario_name(filename: str):
    return filename.lstrip("MainResults_").split('_ZCEHX')[0]

# ------------------------------- #
#            2. Main              #
# ------------------------------- #

@click.group()
@click.pass_context
def main(ctx):
    
    ctx.ensure_object(dict)
    


@main.command()
def biomass_transport():
    
    x = Path('.')
    files1 = [path.name for path in x.glob('**/model/MainResults_*_ZCEHX.gdx')]
    paths1 = [path.parent for path in x.glob('**/model/MainResults_*_ZCEHX.gdx')]
    files2 = [file for file in files1 if 'H1' not in file]
    paths2 = [path.parent for path in x.glob('**/model/MainResults_*_ZCEHX.gdx') if 'H1' not in path.name]
    files3 = [path.name for path in x.glob('**/model/MainResults_*_ZCEHX_ENSC.gdx')] + [path.name for path in x.glob('**/model/MainResults_*_ZCEHX_ESNC.gdx')] + ['MainResults_N2_ZCEHX_ES.gdx']
    paths3 = [path.parent for path in x.glob('**/model/MainResults_*_ZCEHX_ENSC.gdx')] + [path.parent for path in x.glob('**/model/MainResults_*_ZCEHX_ESNC.gdx')] + ['N2/model']

    # Original results
    res2 = MainResults(files2, paths2, [get_scenario_name(name) for name in files2])

    # Results with economy of scaling approximation
    res3 = MainResults(files3, paths3, [get_scenario_name(name) for name in files3])

    print('\nMain scenarios:\n')
    df2 = res2.get_result('OBJ_YCR')
    print(df2.pivot_table(index='Scenario', columns='Category', 
                         values='Value', aggfunc='sum').loc[['N2', 'N10', 'N30', 'N50', 'N70', 'N2', 'N10M2', 'N30M2', 'N50M2', 'N70M2']])

    print('\nEconomy of scale:\n')
    df3 = res3.get_result('OBJ_YCR')
    print(df3.pivot_table(index='Scenario', columns='Category', 
                         values='Value', aggfunc='sum').loc[['N2', 'N10', 'N30', 'N50', 'N70', 'N2', 'N10M2', 'N30M2', 'N50M2', 'N70M2']])
if __name__ == '__main__':
    main()
