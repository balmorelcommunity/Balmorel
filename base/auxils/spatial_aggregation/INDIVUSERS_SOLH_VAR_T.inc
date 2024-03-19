



* ---- DO NOT MODIFY LINES FROM HERE AND BELOW ----

* ---- PYTHON SPATIAL AGGREGATION START LOCATER ----

* These commands are automatically created with the tool SpatialAggregation.py (see auxils folder)        

* DO NOT insert new commands in between the "PYTHON SPATIAL AGREGGATION START/STOP" strings,        

* and do not modify these strings in any way as they are used as locaters for the script.        

* It is bad practice as commands could be overwritten by a future, different aggregation.

                                                                                                                             



SOLH_VAR_T('BE_IDVU-HOTWTR',SSS,TTT)=SOLH_VAR_T('BE_A',SSS,TTT);                                                             



SOLH_VAR_T('DE4-E_IDVU-HOTWTR',SSS,TTT)=SOLH_VAR_T('DE4-E_A',SSS,TTT);                                                       



SOLH_VAR_T('DE4-N_IDVU-HOTWTR',SSS,TTT)=SOLH_VAR_T('DE4-E_A',SSS,TTT);                                                       



SOLH_VAR_T('DE4-S_IDVU-HOTWTR',SSS,TTT)=SOLH_VAR_T('DE4-E_A',SSS,TTT);                                                       



SOLH_VAR_T('DE4-W_IDVU-HOTWTR',SSS,TTT)=SOLH_VAR_T('DE4-E_A',SSS,TTT);                                                       



SOLH_VAR_T('DK1_IDVU-HOTWTR',SSS,TTT)=SOLH_VAR_T('DK1_Heat',SSS,TTT);                                                       



SOLH_VAR_T('DK2_IDVU-HOTWTR',SSS,TTT)=SOLH_VAR_T('DK1_Heat',SSS,TTT);                                                       



SOLH_VAR_T('EE_IDVU-HOTWTR',SSS,TTT)=SOLH_VAR_T('EE_Enefit',SSS,TTT);                                                        



SOLH_VAR_T('FIN_IDVU-HOTWTR',SSS,TTT)=SOLH_VAR_T('FinA',SSS,TTT);                                                            



SOLH_VAR_T('FR_IDVU-HOTWTR',SSS,TTT)=SOLH_VAR_T('FR_A',SSS,TTT);                                                             



SOLH_VAR_T('LT_IDVU-HOTWTR',SSS,TTT)=SOLH_VAR_T('LT_A',SSS,TTT);                                                             



SOLH_VAR_T('LV_IDVU-HOTWTR',SSS,TTT)=SOLH_VAR_T('LV_A',SSS,TTT);                                                             



SOLH_VAR_T('NL_IDVU-HOTWTR',SSS,TTT)=SOLH_VAR_T('NL_A',SSS,TTT);                                                             



SOLH_VAR_T('NO1_IDVU-HOTWTR',SSS,TTT)=SOLH_VAR_T('NO1_Heat',SSS,TTT);                                                          



SOLH_VAR_T('NO2_IDVU-HOTWTR',SSS,TTT)=SOLH_VAR_T('NO1_Heat',SSS,TTT);                                                          



SOLH_VAR_T('NO3_IDVU-HOTWTR',SSS,TTT)=SOLH_VAR_T('NO1_Heat',SSS,TTT);                                                          



SOLH_VAR_T('NO4_IDVU-HOTWTR',SSS,TTT)=SOLH_VAR_T('NO1_Heat',SSS,TTT);                                                          



SOLH_VAR_T('NO5_IDVU-HOTWTR',SSS,TTT)=SOLH_VAR_T('NO1_Heat',SSS,TTT);                                                          



SOLH_VAR_T('PL_IDVU-HOTWTR',SSS,TTT)=SOLH_VAR_T('PL_A',SSS,TTT);                                                             



SOLH_VAR_T('SE1_IDVU-HOTWTR',SSS,TTT)=SOLH_VAR_T('SE1A',SSS,TTT);                                                            



SOLH_VAR_T('SE2_IDVU-HOTWTR',SSS,TTT)=SOLH_VAR_T('SE1A',SSS,TTT);                                                            



SOLH_VAR_T('SE3_IDVU-HOTWTR',SSS,TTT)=SOLH_VAR_T('SE1A',SSS,TTT);                                                            



SOLH_VAR_T('SE4_IDVU-HOTWTR',SSS,TTT)=SOLH_VAR_T('SE1A',SSS,TTT);                                                            



SOLH_VAR_T('UK_IDVU-HOTWTR',SSS,TTT)=SOLH_VAR_T('UK_A',SSS,TTT);                                                             



SOLH_VAR_T('IT_IDVU-HOTWTR',SSS,TTT)=SOLH_VAR_T('FR_A',SSS,TTT);                                                             



SOLH_VAR_T('CH_IDVU-HOTWTR',SSS,TTT)=SOLH_VAR_T('DE4-E_A',SSS,TTT);                                                          



SOLH_VAR_T('AT_IDVU-HOTWTR',SSS,TTT)=SOLH_VAR_T('DE4-E_A',SSS,TTT);                                                          



SOLH_VAR_T('CZ_IDVU-HOTWTR',SSS,TTT)=SOLH_VAR_T('PL_A',SSS,TTT);                                                             



SOLH_VAR_T('ES_IDVU-HOTWTR',SSS,TTT)=SOLH_VAR_T('FR_A',SSS,TTT);                                                             



SOLH_VAR_T('PT_IDVU-HOTWTR',SSS,TTT)=SOLH_VAR_T('FR_A',SSS,TTT);                                                             



                                                                                                                             



                                                                                                                             



$ifi not %GROUP_DEMAND_SHIFT%==yes                                     $goto NO_INDIVUSERS_AAA                               



SOLH_VAR_T('BE_IDVU_RES-HOTWTR',SSS,TTT)    =                          SOLH_VAR_T('BE_IDVU-HOTWTR',SSS,TTT)    ;             



SOLH_VAR_T('DE4-E_IDVU_RES-HOTWTR',SSS,TTT) =                          SOLH_VAR_T('DE4-E_IDVU-HOTWTR',SSS,TTT) ;             



SOLH_VAR_T('DE4-N_IDVU_RES-HOTWTR',SSS,TTT) =                          SOLH_VAR_T('DE4-N_IDVU-HOTWTR',SSS,TTT) ;             



SOLH_VAR_T('DE4-S_IDVU_RES-HOTWTR',SSS,TTT) =                          SOLH_VAR_T('DE4-S_IDVU-HOTWTR',SSS,TTT) ;             



SOLH_VAR_T('DE4-W_IDVU_RES-HOTWTR',SSS,TTT) =                          SOLH_VAR_T('DE4-W_IDVU-HOTWTR',SSS,TTT) ;             



SOLH_VAR_T('DK1_IDVU_RES-HOTWTR',SSS,TTT)   =                          SOLH_VAR_T('DK1_IDVU-HOTWTR',SSS,TTT)   ;             



SOLH_VAR_T('DK2_IDVU_RES-HOTWTR',SSS,TTT)   =                          SOLH_VAR_T('DK2_IDVU-HOTWTR',SSS,TTT)   ;             



SOLH_VAR_T('EE_IDVU_RES-HOTWTR',SSS,TTT)    =                          SOLH_VAR_T('EE_IDVU-HOTWTR',SSS,TTT)    ;             



SOLH_VAR_T('FIN_IDVU_RES-HOTWTR',SSS,TTT)   =                          SOLH_VAR_T('FIN_IDVU-HOTWTR',SSS,TTT)   ;             



SOLH_VAR_T('FR_IDVU_RES-HOTWTR',SSS,TTT)    =                          SOLH_VAR_T('FR_IDVU-HOTWTR',SSS,TTT)    ;             



SOLH_VAR_T('LT_IDVU_RES-HOTWTR',SSS,TTT)    =                          SOLH_VAR_T('LT_IDVU-HOTWTR',SSS,TTT)    ;             



SOLH_VAR_T('LV_IDVU_RES-HOTWTR',SSS,TTT)    =                          SOLH_VAR_T('LV_IDVU-HOTWTR',SSS,TTT)    ;             



SOLH_VAR_T('NL_IDVU_RES-HOTWTR',SSS,TTT)    =                          SOLH_VAR_T('NL_IDVU-HOTWTR',SSS,TTT)    ;             



SOLH_VAR_T('NO1_IDVU_RES-HOTWTR',SSS,TTT)   =                          SOLH_VAR_T('NO1_IDVU-HOTWTR',SSS,TTT)   ;             



SOLH_VAR_T('NO2_IDVU_RES-HOTWTR',SSS,TTT)   =                          SOLH_VAR_T('NO2_IDVU-HOTWTR',SSS,TTT)   ;             



SOLH_VAR_T('NO3_IDVU_RES-HOTWTR',SSS,TTT)   =                          SOLH_VAR_T('NO3_IDVU-HOTWTR',SSS,TTT)   ;             



SOLH_VAR_T('NO4_IDVU_RES-HOTWTR',SSS,TTT)   =                          SOLH_VAR_T('NO4_IDVU-HOTWTR',SSS,TTT)   ;             



SOLH_VAR_T('NO5_IDVU_RES-HOTWTR',SSS,TTT)   =                          SOLH_VAR_T('NO5_IDVU-HOTWTR',SSS,TTT)   ;             



SOLH_VAR_T('PL_IDVU_RES-HOTWTR',SSS,TTT)    =                          SOLH_VAR_T('PL_IDVU-HOTWTR',SSS,TTT)    ;             



SOLH_VAR_T('SE1_IDVU_RES-HOTWTR',SSS,TTT)   =                          SOLH_VAR_T('SE1_IDVU-HOTWTR',SSS,TTT)   ;             



SOLH_VAR_T('SE2_IDVU_RES-HOTWTR',SSS,TTT)   =                          SOLH_VAR_T('SE2_IDVU-HOTWTR',SSS,TTT)   ;             



SOLH_VAR_T('SE3_IDVU_RES-HOTWTR',SSS,TTT)   =                          SOLH_VAR_T('SE3_IDVU-HOTWTR',SSS,TTT)   ;             



SOLH_VAR_T('SE4_IDVU_RES-HOTWTR',SSS,TTT)   =                          SOLH_VAR_T('SE4_IDVU-HOTWTR',SSS,TTT)   ;             



SOLH_VAR_T('UK_IDVU_RES-HOTWTR',SSS,TTT)    =                          SOLH_VAR_T('UK_IDVU-HOTWTR',SSS,TTT)    ;             



                                                                                                                             



SOLH_VAR_T('BE_IDVU_TER-HOTWTR',SSS,TTT)    =                          SOLH_VAR_T('BE_IDVU-HOTWTR',SSS,TTT)    ;             



SOLH_VAR_T('DE4-E_IDVU_TER-HOTWTR',SSS,TTT) =                          SOLH_VAR_T('DE4-E_IDVU-HOTWTR',SSS,TTT) ;             



SOLH_VAR_T('DE4-N_IDVU_TER-HOTWTR',SSS,TTT) =                          SOLH_VAR_T('DE4-N_IDVU-HOTWTR',SSS,TTT) ;             



SOLH_VAR_T('DE4-S_IDVU_TER-HOTWTR',SSS,TTT) =                          SOLH_VAR_T('DE4-S_IDVU-HOTWTR',SSS,TTT) ;             



SOLH_VAR_T('DE4-W_IDVU_TER-HOTWTR',SSS,TTT) =                          SOLH_VAR_T('DE4-W_IDVU-HOTWTR',SSS,TTT) ;             



SOLH_VAR_T('DK1_IDVU_TER-HOTWTR',SSS,TTT)   =                          SOLH_VAR_T('DK1_IDVU-HOTWTR',SSS,TTT)   ;             



SOLH_VAR_T('DK2_IDVU_TER-HOTWTR',SSS,TTT)   =                          SOLH_VAR_T('DK2_IDVU-HOTWTR',SSS,TTT)   ;             



SOLH_VAR_T('EE_IDVU_TER-HOTWTR',SSS,TTT)    =                          SOLH_VAR_T('EE_IDVU-HOTWTR',SSS,TTT)    ;             



SOLH_VAR_T('FIN_IDVU_TER-HOTWTR',SSS,TTT)   =                          SOLH_VAR_T('FIN_IDVU-HOTWTR',SSS,TTT)   ;             



SOLH_VAR_T('FR_IDVU_TER-HOTWTR',SSS,TTT)    =                          SOLH_VAR_T('FR_IDVU-HOTWTR',SSS,TTT)    ;             



SOLH_VAR_T('LT_IDVU_TER-HOTWTR',SSS,TTT)    =                          SOLH_VAR_T('LT_IDVU-HOTWTR',SSS,TTT)    ;             



SOLH_VAR_T('LV_IDVU_TER-HOTWTR',SSS,TTT)    =                          SOLH_VAR_T('LV_IDVU-HOTWTR',SSS,TTT)    ;             



SOLH_VAR_T('NL_IDVU_TER-HOTWTR',SSS,TTT)    =                          SOLH_VAR_T('NL_IDVU-HOTWTR',SSS,TTT)    ;             



SOLH_VAR_T('NO1_IDVU_TER-HOTWTR',SSS,TTT)   =                          SOLH_VAR_T('NO1_IDVU-HOTWTR',SSS,TTT)   ;             



SOLH_VAR_T('NO2_IDVU_TER-HOTWTR',SSS,TTT)   =                          SOLH_VAR_T('NO2_IDVU-HOTWTR',SSS,TTT)   ;             



SOLH_VAR_T('NO3_IDVU_TER-HOTWTR',SSS,TTT)   =                          SOLH_VAR_T('NO3_IDVU-HOTWTR',SSS,TTT)   ;             



SOLH_VAR_T('NO4_IDVU_TER-HOTWTR',SSS,TTT)   =                          SOLH_VAR_T('NO4_IDVU-HOTWTR',SSS,TTT)   ;             



SOLH_VAR_T('NO5_IDVU_TER-HOTWTR',SSS,TTT)   =                          SOLH_VAR_T('NO5_IDVU-HOTWTR',SSS,TTT)   ;             



SOLH_VAR_T('PL_IDVU_TER-HOTWTR',SSS,TTT)    =                          SOLH_VAR_T('PL_IDVU-HOTWTR',SSS,TTT)    ;             



SOLH_VAR_T('SE1_IDVU_TER-HOTWTR',SSS,TTT)   =                          SOLH_VAR_T('SE1_IDVU-HOTWTR',SSS,TTT)   ;             



SOLH_VAR_T('SE2_IDVU_TER-HOTWTR',SSS,TTT)   =                          SOLH_VAR_T('SE2_IDVU-HOTWTR',SSS,TTT)   ;             



SOLH_VAR_T('SE3_IDVU_TER-HOTWTR',SSS,TTT)   =                          SOLH_VAR_T('SE3_IDVU-HOTWTR',SSS,TTT)   ;             



SOLH_VAR_T('SE4_IDVU_TER-HOTWTR',SSS,TTT)   =                          SOLH_VAR_T('SE4_IDVU-HOTWTR',SSS,TTT)   ;             



SOLH_VAR_T('UK_IDVU_TER-HOTWTR',SSS,TTT)    =                          SOLH_VAR_T('UK_IDVU-HOTWTR',SSS,TTT)    ;             



$label NO_INDIVUSERS_AAA                                                                                                     



* ---- PYTHON SPATIAL AGGREGATION END LOCATER ----

* ---- DO NOT MODIFY LINES FROM HERE AND ABOVE ----