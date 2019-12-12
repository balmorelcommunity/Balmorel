PARAMETER WNDFLH(AAA)  'Full load hours for wind power (hours)'     
/                                                                   
DK2_NoDH                                                        2959
DK1_NoDH                                                        3199
FinA                                                            1937
DE4-E_A                                                         2263
DE4-N_A                                                         2467
DE4-S_A                                                         1887
DE4-W_A                                                         2177
NO1_A1                                                          2798
NO2_A1                                                          2798
NO3_A1                                                          2782
NO4_A1                                                          3120
NO5_A1                                                          2798
SE1A                                                            2533
SE2A                                                            2533
SE3A                                                            2212
SE4A                                                            2012
UK_A                                                            3176
                                                                    
EE_A                                                            2020
LV_A                                                            2019
LT_A                                                            1932
PL_A                                                            2286
NL_A                                                            2860
                                                                    
                                                                    
DK2_Offshore                                                    4380
DK1_Offshore                                                    4466
DE4-E_Offshore_A                                                4380
DE4-N_Offshore_A                                                4477
DE4-W_Offshore_A                                                4477
SE1_Offshore                                                    3942
SE2_Offshore                                                    3942
SE3_Offshore                                                    3942
SE4_Offshore                                                    3942
NO1_Offshore                                                    3942
NO2_Offshore                                                    3942
NO3_Offshore                                                    3942
NO4_Offshore                                                    3942
NO5_Offshore                                                    3942
FI_Offshore                                                     3942
                                                                    
                                                                    
                                                                    
                                                                    
                                                                    
                                                                    
UK_OFFSHORE                                                     3324
/;                                                                  
WNDFLH(AAA)$(WNDFLH(AAA) EQ 0) = WNDFLH('FinA') ;                   
