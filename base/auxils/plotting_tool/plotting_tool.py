# -*- coding: utf-8 -*-
"""
Created on Wed Nov  6 16:12:56 2019

@author: jgeab
"""

# importing required packages and modules (keep order)
import os
import datetime
import glob
import pandas as pd
import numpy as np


#Reading files to plot
csvfiles = []
for file in glob.glob("./input/*.csv"):
    csvfiles.append(file)

csvfiles=[file.replace('./input\\','') for file in csvfiles] 
csvfiles=[file.replace('.csv','') for file in csvfiles]  
csvfiles=[file.split('_') for file in csvfiles]  
csvfiles = np.asarray(csvfiles)  
csvfiles=pd.DataFrame.from_records(csvfiles)
    
csvfiles.rename(columns={0: 'Output', 1: 'Scenario',2: 'Year',3:'Subset'}, inplace=True)
Output_unique=csvfiles.Output.unique().tolist()
Scenario_unique=csvfiles.Scenario.unique().tolist()
Year_unique=csvfiles.Year.unique().tolist()
Subset_unique=csvfiles.Subset.unique().tolist()

#Selecting only to print Output files specified in input file
var_specs = pd.read_excel(r'./variable_specification.xlsx')

# drop all variables that shall NOT be included and set the index to the
# variable names
var_specs = var_specs[var_specs.include == 'YES']
var_specs=var_specs.variable.unique().tolist()

Output_unique=list(set(Output_unique).intersection(var_specs))

for output in Output_unique:
    print("File",output,"is being processed")