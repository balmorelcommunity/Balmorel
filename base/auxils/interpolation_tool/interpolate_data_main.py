# -*- coding: utf-8 -*-
"""
Created on Wed Sep 18 14:42:12 2019

@author: pokane
"""


import pandas as pd
import sys 
sys.path.insert(1,".\\functions")

from time_function import time_S_T
from interpolate_function import interpolate_data
from writting_txt_function import writting_newdata_to_txt

##############################################
minutes_of_time_segments=5
minute_length_original_data=60

data = pd.read_excel(".\\input\\de_var_t.xls")
output_file='.\\output\\DE_VAR_T.inc'
##############################################


data_new=interpolate_data(data,minute_length_original_data,minutes_of_time_segments)

time= time_S_T(data,minute_length_original_data,minutes_of_time_segments)

data_new.insert(0,'', time, allow_duplicates=False)

writting_newdata_to_txt(output_file,data_new)









