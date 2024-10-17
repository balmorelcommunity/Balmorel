"""
Functions for analysing storage

Created on 17.10.2024
@author: Mathias Berg Rosendal, PhD Student at DTU Management (Energy Economics & Modelling)
"""
#%% ------------------------------- ###
###        0. Script Settings       ###
### ------------------------------- ###

import os
from pybalmorel.utils import symbol_to_df 
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import click
from shapely import Point
import geopandas as gpd
import unittest
from gams import GamsWorkspace

#%% ------------------------------- ###
###        1. 
### ------------------------------- ###

def polygon_with_point(geofile: gpd.GeoDataFrame,
                           point: Point = Point(10.123, 57.226)) -> gpd.GeoDataFrame:
    """
    Gets index to locate the polygon containing the point
    """

    idx = geofile.contains(point)
    
    if np.all(~idx):
        raise ValueError('No point found!')
    else:
        return idx
    
def get_storage_profiles(all_endofmodel: str, 
                         carrier: str,
                         storage_type: str = 'inter',
                         gams_system_directory: str = '/appl/gams/47.6.0'):
    """
    Get storage profiles from all_endofmodel variables
    
    Args:
        all_endofmodel (str): Path to all_endofmodel
        carrier (str): Carrier, electricity, heat or hydrogen
        storage_type (str): Interseasonal or intraseasonal ('inter' or 'intra')
        gams_system_directory (str): The system directory of GAMS
    """
    
    # Load all_endofmodel
    ws = GamsWorkspace(system_directory=gams_system_directory)
    db = ws.add_database_from_gdx(os.path.abspath(all_endofmodel))

    # Balmorel syntax
    carrier_dict = {
        'electricity' : 'E',
        'heat' : 'H',
        'hydrogen' : 'HYDROGEN'
    }
    storage_type_dict = {
        'inter' : 'S',
        'intra' : ''
    }
    if carrier != 'hydrogen':
        charge_symbol = 'V%sSTOLOADT%s'%(carrier_dict[carrier], storage_type_dict[storage_type])
        discharge_symbol = 'VG%s_T'%(carrier_dict[carrier])
        content_symbol = 'V%sSTOVOLT%s'%(carrier_dict[carrier], storage_type_dict[storage_type])
    else:
        charge_symbol = 'VHYDROGEN_GH2_T'
        discharge_symbol = 'VHYDROGEN_STOLOADT'
        content_symbol = 'VHYDROGEN_STOVOL_T'
    
    # Load variables
    charge = symbol_to_df(db, charge_symbol)
    discharge = symbol_to_df(db, discharge_symbol)
    content = symbol_to_df(db, content_symbol)

    # Correct column name    
    charge.columns = pd.Series(charge.columns).str.replace('GGG', 'G')
    discharge.columns = pd.Series(discharge.columns).str.replace('GGG', 'G')

    # Sort away carrier generation technologies from dispatch variable
    sto_set = charge.G.unique()
    discharge = discharge.query('G in @sto_set')
    
    return charge, discharge, content

#%% ------------------------------- ###
###             2. Tests            ### 
### ------------------------------- ###

class Tests(unittest.TestCase):
    def test_polygon_with_point(self):
        # Test 
        filename = 'analysis/geofiles/DE-DH-WNDFLH-SOLEFLH_70cluster_geofile.gpkg'
        geo = gpd.read_file(filename)
        idx = polygon_with_point(geo)
        print('%s was in %s'%(str(Point(10.123, 57.226)), geo.loc[idx, 'cluster_name'].iloc[0]))
        
        try:
            point_not_in_geo = Point(50, 1)
            idx = polygon_with_point(geo, point_not_in_geo)
        except ValueError:
            print('Could not find %s in %s'%(point_not_in_geo, filename))
            
    def test_get_storage_profiles(self):
        filename = '/work3/mberos/Balmorel/N2/model/all_endofmodel.gdx'
        charge, discharge, content = get_storage_profiles(filename, 'heat', 'inter')


#%% ------------------------------- ###
###            X. Main              ###
### ------------------------------- ###

@click.command()
@click.option('--dark-style', is_flag=True, required=False, help='Dark plot style')
def main(dark_style: bool):

    # Set global style of plot
    if dark_style:
        plt.style.use('dark_background')
        fc = 'none'
    else:
        fc = 'white'


if __name__ == '__main__':
    main()
