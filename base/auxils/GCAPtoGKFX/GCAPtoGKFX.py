# -*- coding: utf-8 -*-
"""
Created on Wed Oct 19 16:11:44 2022

@author: mathi
"""

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import rc
from formplot import *
from scipy.optimize import curve_fit
import os

style = 'ppt'

if style == 'report':
    plt.style.use('default')
    fc = 'white'
elif style == 'ppt':
    plt.style.use('dark_background')
    fc = 'none'

#%% ----------------------------- ###
###          Load files           ###
### ----------------------------- ###

files = []
filenames = []
for file in os.listdir():
    if file[-3:] == 'csv':
        files.append(pd.read_csv(file, sep=';'))
        filenames.append(file)
        
#%% ----------------------------- ###
###         Display Input         ###
### ----------------------------- ###

GKFX = "PARAMETER GKFX(YYY,AAA,GGG)        'Capacity of generation technologies';"
XKFX = "PARAMETER XKFX(YYY,IRRRE,IRRRI)  'Initial transmission capacity between regions';"
HYDROGEN_XH2KFX = "PARAMETER XH2KFX(YYY,IRRRE,IRRRI) 'H2 transmission capacity between regions at beginning of year (MW)';"

for i in range(len(files)):
    cols = files[i].columns
    # cols = cols[(cols != 'VARIABLE_CATEGORY')]
    
    file = files[i][cols].groupby(list(cols[(cols != 'Val') & (cols != 'VARIABLE_CATEGORY')]), as_index=False)
    file = file.aggregate({'Val' : np.sum})
    # file = files[i][files[i]
    file.index = np.arange(len(file))
    
    if ('Generation' in filenames[i]):
        # print(filenames[i])
        # print(file.loc[5])
        for j in range(len(file)):
            GKFX = GKFX + '\n' + "GKFX('%s','%s','%s') = GKFX('%s','%s','%s') + %0.5f;"%(tuple(file.loc[j, ['Y', 'AAA', 'G']])*2+(file.loc[j, ['Val']].values[0]*1000,))
    elif 'HydrogenTransmission' in filenames[i]:
        for j in range(len(file)):
            HYDROGEN_XH2KFX = HYDROGEN_XH2KFX + '\n' + "XH2KFX('%s','%s','%s') = %0.5f;"%(tuple(file.loc[j, ['Y', 'IRRRE', 'IRRRI']])+(file.loc[j, ['Val']].values[0]*1000,))
    elif 'PowerTransmission' in filenames[i]:
        for j in range(len(file)):
            XKFX = XKFX + '\n' + "XKFX('%s','%s','%s') = %0.5f;"%(tuple(file.loc[j, ['Y', 'IRRRE', 'IRRRI']])+(file.loc[j, ['Val']].values[0]*1000,))
    elif 'HeatTransmission' in filenames[i]:
        print(filenames[i])

f = open('GKFX.inc', 'w')
with open('GKFX.inc', 'a') as f:
    f.write(GKFX)

f = open('XKFX.inc', 'w')
with open('XKFX.inc', 'a') as f:
    f.write(XKFX)

f = open('HYDROGEN_XH2KFX.inc', 'w')
with open('HYDROGEN_XH2KFX.inc', 'a') as f:
    f.write(HYDROGEN_XH2KFX)

# string = "DE('%s','%s','PtX') = %d ;"%(yr, dict_A[node][:3], val)
# fDE = fDE + '\n' + string
# f = open('directsave.inc', 'w')
# with open('directsave.inc', 'a') as f:
#     dfAsString = fe.to_string(header=True, index=False)
#     f.write(dfAsString)

    # PT = file.pivot_table(values='Val', index=ind, columns=col)
    
    # fig, ax = newplot(fc=fc)
    # ax = PT.plot(kind='bar',
    #              stacked=True, zorder=5)


# PT = FT4.pivot_table(values='Value', index=Types, columns=['Reg'])


#%% ----------------------------- ###
###           Plot Techs          ###
### ----------------------------- ###
# PT = FT2.pivot_table(values='Value', index=Types, columns=['Tech'])


techs = files[0].copy()
techs = techs.groupby(['Y', 'TECH_TYPE'], as_index=False)
techs = techs.aggregate({'Val' : np.sum})
techs = techs.pivot_table(values='Val', index='Y', columns='TECH_TYPE')

fig, ax = newplot(fc=fc)
techs.plot(ax=ax, kind='bar', stacked=True, zorder=5)
l = ax.get_legend()
l.set_bbox_to_anchor((1.1, 1.2))


# fig, ax = newplot(fc=fc)

# vals = np.zeros(3)
# for bar in techs:
#     ax.bar(x=[2030, 2040, 2050], height=techs[bar].values, bottom=vals, label=bar)    
#     print(techs[bar])
#     vals = vals + techs[bar].values


# ax.legend(loc='center', bbox_to_anchor=(1.4, .5))


# ax.bar([2030, 2040, 2050], [5,5,5])
# techs.plot(kind='bar', stacked=True, figsize=(5, 6))


# FT4 = FT4.groupby(Types + ['Reg'], as_index=False)
# FT4 = FT4.groupby(['SC', 'Year', 'Reg'], as_index=False)
# FT4 = FT4.aggregate({'Value' : np.sum})

