# -*- coding: utf-8 -*-
"""
Created on Wed Sep 25 11:13:52 2019

@author: pokane
"""

import numpy as np
from scipy.interpolate import interp1d
import pandas as pd

def interpolate_data(data,minute_length_original_data,minutes_of_time_segments):
    
    segments=minute_length_original_data/minutes_of_time_segments
    regions=list(data.columns.values[1:])
    
    
    value_new=[]
    aux=[]
    data_new = pd.DataFrame(columns=regions)
    
    
    for i in regions:
        value=list(data[i])
        x=np.linspace(0, (len(value)-1)*segments ,len(value))
        xnew = np.arange(0, (len(value)-1)*segments  +1  )
        f = interp1d(x, value,kind='cubic' )
        value_new=list(f(xnew))
        aux=[value_new[len(value_new)-1]] * (int(segments)-1)
        value_new.extend(aux)
        data_new[i]=value_new

    return data_new