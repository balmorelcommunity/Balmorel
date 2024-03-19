# -*- coding: utf-8 -*-
"""
Created on Tue Oct 25 11:20:35 2022

@author: Mathias Berg Rosendal, Research Assistant at DTU Management

-------------------------------------
TOOL FOR SPATIAL AGGREGATION COMMANDS
-------------------------------------

This python script may be used to aggregate areas (not regions, yet) in Balmorel,
using simple commands.

NOTE:
For AAA, CCCRRRAAA and RRRAAA, you may need to change the position of the set-ending
GAMS-command, /;
 
Running this script will replace all commands in between the following strings:
    
             * ---- PYTHON SPATIAL AGGREGATION START LOCATER ----
             ...
             ...COMMANDS ARE REPLACED HERE...
             ...
             * ---- PYTHON SPATIAL AGGREGATION END LOCATER ----

If these strings are not present in the respective .inc file in base/data,
this string and modifications will be appended to the file.


This tool is currently compatible with the following addons:
    - HYDROGEN
    - TRANSPORT
    - INDUSTRY (Note: not tested by aggregation of industry areas)
    - INDIVUSERS (Note: not tested by aggregation of individual user areas)
        
It reads the following files from base/data:
    - AAA
    - AGKN
    - CCCRRRAAA
    - DH
    - DH_VAR_T
    - GKFX
    - HYDROGEN_AGKN
    - HYDROGEN_GKFX
    - INDIVUSERS_SOLH_VAR_T
    - INDUSTRY_SOLH_VAR_T
    - INDUSTRY_XHKFX
    - RRRAAA
    - SOLH_VAR_T
    - SOLHFLH

...and creates new, modified files in the auxils folder, that can then be 
copy+pasted to the wanted, aggregated scenario data folder.
"""

import pandas as pd
import numpy as np


### ----------------------------- ###
###        Define Parameters      ###
### ----------------------------- ###

### Set the top path 
# This should be the path leading to the folder containing base and simex,
# or other scenario folders
path = r'C:\Users\mathi\OneDrive\Dokumenter\GitHub\Balmorel'


### Create new heat areas
# Key'ed like this:
# Old : New 
# The demand in old areas will be aggregated to the new areas
area_key = {'DK1_Large' : 'DK1_Heat', 'DK1_Medium' : 'DK1_Heat', 'DK1_MedSmall' : 'DK1_Heat', 
            'DK1_Small' : 'DK1_Heat', 'DK1_Rural' : 'DK1_Heat',
            'DK2_Large' : 'DK2_Heat', 'DK2_Medium' : 'DK2_Heat', 'DK2_MedSmall' : 'DK2_Heat', 
            'DK2_Small' : 'DK2_Heat', 'DK2_Rural' : 'DK2_Heat',
            'FI_large' : 'FI_Heat', 'FI_medium' : 'FI_Heat', 'FI_small' : 'FI_Heat',
            'NO1_A1' : 'NO1_Heat', 'NO1_A2' : 'NO1_Heat', 'NO1_A3' : 'NO1_Heat',
            'NO2_A1' : 'NO2_Heat', 'NO2_A2' : 'NO2_Heat' , 'NO3_A1' : 'NO3_Heat' ,
            'NO3_A2' : 'NO3_Heat', 'NO3_A3' : 'NO3_Heat', 'NO4_A1' : 'NO4_Heat',
            'NO4_A2' : 'NO4_Heat' , 'NO5_A1' : 'NO5_Heat' , 'NO5_A2' : 'NO5_Heat',
            'SE1_medium' : 'SE1_Heat', 'SE1_small' : 'SE1_Heat', 'SE2_medium' : 'SE2_Heat',
            'SE2_small' : 'SE2_Heat', 'SE3_large' : 'SE3_Heat', 'SE3_medium' : 'SE3_Heat',
            'SE3_small' : 'SE3_Heat', 'SE4_large' : 'SE4_Heat', 'SE4_medium' : 'SE4_Heat',
            'SE4_small' : 'SE4_Heat'}
# area_key = {'DK1_Large' : 'DK011_A',
#             'DK1_Large' : 'DK012_A',
#             'DK1_Large' : 'DK031_A'
            'DK013_A'
            'DK014_A'
            'DK041_A'
            'DK021_A'
            'DK032_A'
            'DK022_A'
            'DK050_A'
            'DK042_A'}
keys = list(area_key.keys())
area_key_df = pd.DataFrame({'New Area' : np.array(list(area_key.values())), 'Old Area' : np.array(list(area_key.keys()))})


### Specify custom weights for FLH aggregation
# FLH in new area will be weighted average of old areas
try:
    area_key_df['Weights'] = [1/5, 1/5, 1/5, 1/5, 1/5,  # DK1
                              1/5, 1/5, 1/5, 1/5, 1/5,  # DK2
                              1/3, 1/3, 1/3,    # FIN
                              1/3, 1/3, 1/3,    # NO1
                              1/2, 1/2,         # NO2
                              1/3, 1/3, 1/3,    # NO3
                              1/2, 1/2,         # NO4
                              1/2, 1/2,         # NO5
                              1/2, 1/2,         # SE1
                              1/2, 1/2,         # SE2   
                              1/3, 1/3, 1/3,    # SE3
                              1/3, 1/3, 1/3]    # SE4
except ValueError:
    print('The specified weights for FLH average does not match the amount of regions!')
    
### Is hydrogen addon on?
# If yes, the GKFX commands will be inserted in the HYDROGEN_GKFX.inc instead of GKFX
# NOTE: If aggregation is wanted for other addons, the modification of GKFX.inc should
# be changed to the last GKFX.inc (placing the commands in bb4datainc.inc could be a 
# more robust solution)
hy_addon = 'Y'


### The unique areas
areas = np.unique(list(area_key.values()))

### Function for searching for python aggregation locater and adding block of commands
def add_lines(f, line):
    # Aggregation locaters and warningtext
    pstart = '* ---- PYTHON SPATIAL AGGREGATION START LOCATER ----'
    warningtext = '\n* These commands are automatically created with the tool SpatialAggregation.py (see auxils folder)\
        \n* DO NOT insert new commands in between the "PYTHON SPATIAL AGREGGATION START/STOP" strings,\
        \n* and do not modify these strings in any way as they are used as locaters for the script.\
        \n* It is bad practice as commands could be overwritten by a future, different aggregation.'
    pend = '* ---- PYTHON SPATIAL AGGREGATION END LOCATER ----'
    
    # Read file
    file = pd.Series(f.readlines()).str.replace('\n','')
    
    # Search for aggregation locaters
    if np.any(file == pstart):
        
        # Find block of python aggregation commands
        i0 = file.index[file == pstart][0]
        i1 = file.index[file == pend][0]
        
        # Replace block with new commands
        # First line: First block
        # Second line: Aggregation commands
        # Thirds line: Second block
        newstring = '\n'.join(file[:i0-1]) + '\n* ---- DO NOT MODIFY LINES FROM HERE AND BELOW ----\n' + pstart + warningtext +\
            line + '\n' + pend + '\n* ---- DO NOT MODIFY LINES FROM HERE AND ABOVE ----\n'\
            + '\n'.join(file[i1+2:])                             
        
    # Append commands to end of file, if no locaters are found
    else:
        newstring = '\n'.join(file) + '\n* ---- DO NOT MODIFY LINES FROM HERE AND BELOW ----\n' + pstart + warningtext\
            + line + '\n' + pend + '\n* ---- DO NOT MODIFY LINES FROM HERE AND ABOVE ----\n'
                
    return newstring


### AAA
# NOTE: You may need to change the position of the set-ending GAMS command "/;" afterwards
f = open(path + '/base/data/AAA.inc')
newstring = add_lines(f, '\n' + '\n'.join(areas))
f = open('AAA.inc', 'w')
f.write(newstring)

#%% CCCRRRAAA
# NOTE: You may need to change the position of the set-ending GAMS command "/;" afterwards
f = open(path + '/base/data/CCCRRRAAA.inc')
newstring = add_lines(f, '\n' + '\n'.join(areas) + '\n')
f = open('CCCRRRAAA.inc', 'w')
f.write(newstring)

### RRRAAA
# NOTE: You may need to change the position of the set-ending GAMS command "/;" afterwards
f = open(path + '/base/data/RRRAAA.inc')
newstring = add_lines(f, '\n' + '\n'.join(['%s . %s'%(area.split('_')[0], area) for area in areas]) + '\n')
f = open('RRRAAA.inc', 'w')
f.write(newstring)

### DH
string = ''

# Set demand of new areas
for i in range(len(area_key)):
    # if i == 0:
        # string = "DH(YYY, '%s', DHUSER) = DH(YYY, '%s', DHUSER);"%(area_key[keys[i]], keys[i])
    # else:
    
    string = string + '\n' + "DH(YYY, '%s', DHUSER) = DH(YYY, '%s', DHUSER) + DH(YYY, '%s', DHUSER);"%(area_key[keys[i]], area_key[keys[i]], keys[i])

# Set demand of old areas to zero
for i in range(len(area_key)):
    string = string + '\n' + "DH(YYY, '%s', DHUSER) = 0;"%list(area_key.keys())[i]

f = open(path + '/base/data/DH.inc')
newstring = add_lines(f, string)
f = open('DH.inc', 'w')
f.write(newstring)


### DH_VAR_T
string = ''

# Set heat demand variation in new areas
for i in range(len(area_key)):
    # if i == 0:
        # string = "DH(YYY, '%s', DHUSER) = DH(YYY, '%s', DHUSER);"%(area_key[keys[i]], keys[i])
    # else:
    
    string = string + '\n' + "DH_VAR_T('%s', DHUSER, SSS, TTT) = DH_VAR_T('%s', DHUSER, SSS, TTT) + DH_VAR_T('%s', DHUSER, SSS, TTT);"%(area_key[keys[i]], area_key[keys[i]], keys[i])

# Set heat demand variation of old areas to zero
for i in range(len(area_key)):
    string = string + '\n' + "DH_VAR_T('%s', DHUSER, SSS, TTT) = 0;"%list(area_key.keys())[i]

f = open(path + '/base/data/DH_VAR_T.inc')
newstring = add_lines(f, string)
f = open('DH_VAR_T.inc', 'w')
f.write(newstring)


### SOLH_VAR_T
string = ''

# Set solar heating variation in new areas
for i in range(len(area_key)):
    # if i == 0:
        # string = "DH(YYY, '%s', DHUSER) = DH(YYY, '%s', DHUSER);"%(area_key[keys[i]], keys[i])
    # else:
    
    string = string + '\n' + "SOLH_VAR_T('%s', SSS, TTT) = SOLH_VAR_T('%s', SSS, TTT) + SOLH_VAR_T('%s', SSS, TTT);"%(area_key[keys[i]], area_key[keys[i]], keys[i])

# Set solar heating variation of old areas to zero
for i in range(len(area_key)):
    string = string + '\n' + "SOLH_VAR_T('%s', SSS, TTT) = 0;"%list(area_key.keys())[i]

f = open(path + '/base/data/SOLH_VAR_T.inc')
newstring = add_lines(f, string)
f = open('SOLH_VAR_T.inc', 'w')
f.write(newstring)


#%% INDIVUSERS_SOLH_VAR_T

# REPLACES indivusers_solh_var_t - doesn't only add (due to calls to previously deleted timeseries)
f = open(path + '/base/data/INDIVUSERS_SOLH_VAR_T.inc')
string = '\n'.join(f.readlines())
# string = '* ---- PYTHON SPATIAL AGGREGATION ----\n' + string
# Set solar heating variation in new areas
for i in range(len(area_key)):
    # if i == 0:
        # string = "DH(YYY, '%s', DHUSER) = DH(YYY, '%s', DHUSER);"%(area_key[keys[i]], keys[i])
    # else:
    string = string.replace(keys[i], area_key[keys[i]])
    # string = string + '\n' + "SOLH_VAR_T('%s', SSS, TTT) = SOLH_VAR_T('%s', SSS, TTT) + SOLH_VAR_T('%s', SSS, TTT);"%(area_key[keys[i]], area_key[keys[i]], keys[i])

# Set solar heating variation of old areas to zero
# for i in range(len(area_key)):
#     string = string + '\n' + "SOLH_VAR_T('%s', SSS, TTT) = 0;"%list(area_key.keys())[i]

# newstring = add_lines(f, string)
f = open('INDIVUSERS_SOLH_VAR_T.inc', 'w')
f.write(string)

#%% INDUSTRY_SOLH_VAR_T

# REPLACES indivusers_solh_var_t - doesn't only add (due to calls to previously deleted timeseries)
f = open(path + '/base/data/INDUSTRY_SOLH_VAR_T.inc')
string = '\n'.join(f.readlines())
# string = '* ---- PYTHON SPATIAL AGGREGATION ----\n' + string
# Set solar heating variation in new areas
for i in range(len(area_key)):
    # if i == 0:
        # string = "DH(YYY, '%s', DHUSER) = DH(YYY, '%s', DHUSER);"%(area_key[keys[i]], keys[i])
    # else:
    string = string.replace(keys[i], area_key[keys[i]])
    # string = string + '\n' + "SOLH_VAR_T('%s', SSS, TTT) = SOLH_VAR_T('%s', SSS, TTT) + SOLH_VAR_T('%s', SSS, TTT);"%(area_key[keys[i]], area_key[keys[i]], keys[i])

# Set solar heating variation of old areas to zero
# for i in range(len(area_key)):
#     string = string + '\n' + "SOLH_VAR_T('%s', SSS, TTT) = 0;"%list(area_key.keys())[i]

# newstring = add_lines(f, string)
f = open('INDUSTRY_SOLH_VAR_T.inc', 'w')
f.write(string)



#%% SOLHFLH
# Using weighted average for FLH of new region (equal weights as of now)

# Set solar heating full load hours in new areas
string = ''
for newA in np.unique(area_key_df['New Area']):
    
    string = string + "\nSOLHFLH('%s') = "%newA
    oldAs = area_key_df.loc[area_key_df['New Area']==newA]
    
    for i in range(len(oldAs)):
        # Add old area FLH
        string = string + "%0.3f*SOLHFLH('%s') + "%(oldAs.iloc[i, 2], oldAs.iloc[i, 1])
        
        if i == len(oldAs) - 1:
            # Take average of all old FLH 
            string = string[:-3] + ';'

# Set solar heating full load hours in new areas
for i in range(len(area_key)):
    string = string + "\nSOLHFLH('%s') = 0;"%(keys[i])


f = open(path + '/base/data/SOLHFLH.inc')
newstring = add_lines(f, string)
f = open('SOLHFLH.inc', 'w')
f.write(newstring)


#%% INDUSTRY_XHKFX
string = ''

# Set heat transmission capacity in new areas
for i in range(len(area_key)):
    # if i == 0:
        # string = "DH(YYY, '%s', DHUSER) = DH(YYY, '%s', DHUSER);"%(area_key[keys[i]], keys[i])
    # else:
    
    string = string + '\n' + "XHKFX(YYY, '%s', IAAAI) = XHKFX(YYY, '%s', IAAAI) + XHKFX(YYY, '%s', IAAAI);"%(area_key[keys[i]], area_key[keys[i]], keys[i])
    string = string + '\n' + "XHKFX(YYY, IAAAE, '%s') = XHKFX(YYY, IAAAE, '%s') + XHKFX(YYY, IAAAE, '%s');"%(area_key[keys[i]], area_key[keys[i]], keys[i])

# Set heat transmission capacity of old areas to zero
for i in range(len(area_key)):
    string = string + '\n' + "XHKFX(YYY, '%s', IAAAI) = 0;"%list(area_key.keys())[i]
    string = string + '\n' + "XHKFX(YYY, IAAAE, '%s') = 0;"%list(area_key.keys())[i]


f = open(path + '/base/data/INDUSTRY_XHKFX.inc')
newstring = add_lines(f, string)
f = open('INDUSTRY_XHKFX.inc', 'w')
f.write(newstring)



### If hydrogen addon is on, the aggregation of GKFX will shift from GKFX.inc to HYDROGEN_GKFX.inc
if hy_addon == 'Y':
    ### HYDROGEN_GKFX
    string = ''
    
    # Set capacities in new areas
    for i in range(len(area_key)):
        # if i == 0:
            # string = "DH(YYY, '%s', DHUSER) = DH(YYY, '%s', DHUSER);"%(area_key[keys[i]], keys[i])
        # else:
        
        string = string + '\n' + "GKFX(YYY,'%s',GGG) = GKFX(YYY,'%s',GGG) + GKFX(YYY,'%s',GGG);"%(area_key[keys[i]], area_key[keys[i]], keys[i])
    
    # Set capacities in old areas to zero
    for i in range(len(area_key)):
        string = string + '\n' + "GKFX(YYY,'%s',GGG) = 0;"%list(area_key.keys())[i]
    
    f = open(path + '/base/data/HYDROGEN_GKFX.inc')
    newstring = add_lines(f, string)
    f = open('HYDROGEN_GKFX.inc', 'w')
    f.write(newstring)
    
    # Remove lines from GKFX:
    f = open(path + '/base/data/GKFX.inc')
    newstring = add_lines(f, '')
    f = open('GKFX.inc', 'w')
    f.write(newstring)

else:
    ### GKFX
    string = ''

    # Set capacities in new areas
    for i in range(len(area_key)):
        # if i == 0:
            # string = "DH(YYY, '%s', DHUSER) = DH(YYY, '%s', DHUSER);"%(area_key[keys[i]], keys[i])
        # else:
        
        string = string + '\n' + "GKFX(YYY,'%s',GGG) = GKFX(YYY,'%s',GGG) + GKFX(YYY,'%s',GGG);"%(area_key[keys[i]], area_key[keys[i]], keys[i])

    # Set capacities in old areas to zero
    for i in range(len(area_key)):
        string = string + '\n' + "GKFX(YYY,'%s',GGG) = 0;"%list(area_key.keys())[i]

    f = open(path + '/base/data/GKFX.inc')
    newstring = add_lines(f, string)
    f = open('GKFX.inc', 'w')
    f.write(newstring)
        
    # Remove lines from hydrogen addon:
    f = open(path + '/base/data/HYDROGEN_GKFX.inc')
    newstring = add_lines(f, '')
    f = open('HYDROGEN_GKFX.inc', 'w')
    f.write(newstring)


### HYDROGEN_AGKN
string = ''
# Set initial investment opportunities in new areas
for i in range(len(area_key)):
    # if i == 0:
        # string = "DH(YYY, '%s', DHUSER) = DH(YYY, '%s', DHUSER);"%(area_key[keys[i]], keys[i])
    # else:
    
    string = string + '\n' + "AGKN('%s',GGG) = AGKN('%s',GGG) + AGKN('%s',GGG);"%(area_key[keys[i]], area_key[keys[i]], keys[i])

# Set initial investment opportunities of old areas to zero
for i in range(len(area_key)):
    string = string + '\n' + "AGKN('%s',GGG) = 0;"%list(area_key.keys())[i]

# Recalculate
string = string + '\n* Overlapping values are set to 1'
string = string + 'AGKN(AAA,GGG)$(AGKN(AAA,GGG).val GE 1) = 1;'

f = open(path + '/base/data/HYDROGEN_AGKN.inc')
newstring = add_lines(f, string)
f = open('HYDROGEN_AGKN.inc', 'w')
f.write(newstring)




### AGKN
string = ''
# Set initial investment opportunities in new areas
for i in range(len(area_key)):
    # if i == 0:
        # string = "DH(YYY, '%s', DHUSER) = DH(YYY, '%s', DHUSER);"%(area_key[keys[i]], keys[i])
    # else:
    
    string = string + '\n' + "AGKN('%s',GGG) = AGKN('%s',GGG) + AGKN('%s',GGG);"%(area_key[keys[i]], area_key[keys[i]], keys[i])

# Set initial investment opportunities of old areas to zero
for i in range(len(area_key)):
    string = string + '\n' + "AGKN('%s',GGG) = 0;"%list(area_key.keys())[i]


f = open(path + '/base/data/AGKN.inc')
newstring = add_lines(f, string)
f = open('AGKN.inc', 'w')
f.write(newstring)