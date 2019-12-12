PARAMETER SOLHFLH(AAA)  'Full load hours for solar heat (hours)'                                                                           
* Average FLH from existing solar plants in Denmark. Assumed the same values for all countries except Germany and UK - Juan 30-05-2018     
/                                                                                                                                          
DK2_NoDH                                                                                                                               703 
DK1_NoDH                                                                                                                               703 
                                                                                                                                           
FinA                                                                                                                                   703 
DE4-E_A                                                                                                                                1040
DE4-N_A                                                                                                                                1040
DE4-S_A                                                                                                                                1040
DE4-W_A                                                                                                                                1040
NL_A                                                                                                                                   1040
NO1_A1                                                                                                                                 703 
NO2_A1                                                                                                                                 703 
NO3_A1                                                                                                                                 703 
NO4_A1                                                                                                                                 703 
NO5_A1                                                                                                                                 703 
SE1A                                                                                                                                   703 
SE2A                                                                                                                                   703 
SE3A                                                                                                                                   703 
SE4A                                                                                                                                   703 
UK_A                                                                                                                                   1040
EE_Rural                                                                                                                               703 
LV_A                                                                                                                                   703 
LT_A                                                                                                                                   703 
/;                                                                                                                                         
SOLHFLH(AAA)$(SOLHFLH(AAA) EQ 0) = SOLHFLH('DK2_NoDH') ;                                                                                   
