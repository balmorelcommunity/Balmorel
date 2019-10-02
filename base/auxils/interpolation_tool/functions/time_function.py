# -*- coding: utf-8 -*-
"""
Created on Wed Sep 25 11:11:39 2019

@author: pokane
"""

def time_S_T(data,minute_length_original_data,minutes_of_time_segments):
    time=[]
    for s in range(1,len(data)+1):
        for t in range(1,int(minute_length_original_data/minutes_of_time_segments)+1):
            if s<=9:
                if t<=9:
                    stringS='S000'+str(s)
                    stringT='T0'+str(t)
                    string=stringS + '.' +stringT
                    time.append(string)
                if t>9:
                    stringS='S000'+str(s)
                    stringT='T'+str(t)
                    string=stringS + '.' +stringT
                    time.append(string)
            if s>9 and s<=99:
                if t<=9:
                    stringS='S00'+str(s)
                    stringT='T0'+str(t)
                    string=stringS + '.' +stringT
                    time.append(string)
                if t>9:
                    stringS='S00'+str(s)
                    stringT='T'+str(t)
                    string=stringS + '.' +stringT
                    time.append(string)
                
            if s>99 and s<=999:
                if t<=9:
                    stringS='S0'+str(s)
                    stringT='T0'+str(t)
                    string=stringS + '.' +stringT
                    time.append(string)
                if t>9:
                    stringS='S0'+str(s)
                    stringT='T'+str(t)
                    string=stringS + '.' +stringT
                    time.append(string)
     
            if s>999 and s<=9999:
                if t<=9:
                    stringS='S'+str(s)
                    stringT='T0'+str(t)
                    string=stringS + '.' +stringT
                    time.append(string)
                if t>9:
                    stringS='S'+str(s)
                    stringT='T'+str(t)
                    string=stringS + '.' +stringT
                    time.append(string)
    return time
    
