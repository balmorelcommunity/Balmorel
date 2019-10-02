# -*- coding: utf-8 -*-
"""
Created on Wed Sep 25 14:47:37 2019

@author: pokane
"""

def writting_newdata_to_txt(file,data_new):
    with open(file,'w') as outfile:
        outfile.write("TABLE DE_VAR_T1(SSS,TTT,RRR)  \n")
        data_new.to_string(outfile,index=False)
        outfile.write("\n")
        outfile.write("; \n")
        outfile.write("PARAMETER DE_VAR_T(RRR,DEUSER,SSS,TTT) ;  \n")
        outfile.write("DE_VAR_T(RRR,DEUSER,SSS,TTT) =  DE_VAR_T1(SSS,TTT,RRR);     ")
    outfile.close() 