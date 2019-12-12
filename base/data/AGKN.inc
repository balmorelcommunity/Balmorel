SET INVDATASET                                                                                                                                                                                    
/                                                                                                                                                                                                 
                                                                                                                                                                                                  
COND                                                                                                                'condensing areas with onshore wind and PV'                                   
LDH                                                                                                                 'Large district heating areas'                                                
MDH                                                                                                                 'medium dh areas'                                                             
SDH                                                                                                                 'small dh areas'                                                              
PV                                                                                                                  'PV areas'                                                                    
ONSWND                                                                                                              'onshore wind areas'                                                          
OFFSWND                                                                                                             'offshore wind areas'                                                         
                                                                                                                                                                                                  
                                                                                                                                                                                                  
                                                                                                                                                                                                  
                                                                                                                                                                                                  
/;                                                                                                                                                                                                
                                                                                                                                                                                                  
                                                                                                                                                                                                  
*** TABLE to connect areas to regions, countries and other subsets                                                                                                                                
TABLE INVDATA(AAA,INVDATASET)                                                                                                                                                                     
                                                                                                                    COND                                        LDH  MDH  SDH  PV   ONSWND OFFSWND
DK2_NoDH                                                                                                            1                                                                             
DK1_NoDH                                                                                                            1                                                                             
FinA                                                                                                                1                                                                             
DE4-E_A                                                                                                             1                                           1                                 
DE4-N_A                                                                                                             1                                           1                                 
DE4-S_A                                                                                                             1                                           1                                 
DE4-W_A                                                                                                             1                                           1                                 
NO1_A1                                                                                                              1                                                                             
NO1_A2                                                                                                                                                               1                            
NO1_A3                                                                                                                                                               1                            
NO2_A1                                                                                                              1                                                                             
NO2_A2                                                                                                                                                               1                            
NO3_A1                                                                                                              1                                                                             
NO3_A2                                                                                                                                                               1                            
NO3_A3                                                                                                                                                               1                            
NO4_A1                                                                                                              1                                           1                                 
NO4_A2                                                                                                                                                               1                            
NO5_A1                                                                                                              1                                           1                                 
NO5_A2                                                                                                                                                               1                            
SE1A                                                                                                                1                                                                             
SE2A                                                                                                                1                                                                             
SE3A                                                                                                                1                                                                             
SE4A                                                                                                                1                                                                             
UK_A                                                                                                                1                                                                             
EE_A                                                                                                                1                                                                             
LV_A                                                                                                                1                                                                             
LT_A                                                                                                                1                                                                             
PL_A                                                                                                                1                                           1                                 
NL_A                                                                                                                1                                                                             
DK1_Large                                                                                                                                                       1                                 
DK1_Rural                                                                                                                                                                 1                       
DK1_Medium                                                                                                                                                           1                            
DK2_Large                                                                                                                                                       1                                 
DK2_Rural                                                                                                                                                                 1                       
DK2_Medium                                                                                                                                                           1                            
DK2_MedSmall                                                                                                                                                              1                       
DK1_Small                                                                                                                                                                 1                       
DK1_MedSmall                                                                                                                                                              1                       
DK2_Small                                                                                                                                                                 1                       
FI_large                                                                                                                                                        1                                 
FI_large_gas                                                                                                                                                    1                                 
FI_IND                                                                                                                                                          1                                 
SE3_large                                                                                                                                                       1                                 
SE4_large                                                                                                                                                       1                                 
SE1_IND                                                                                                                                                         1                                 
SE2_IND                                                                                                                                                         1                                 
SE3_IND                                                                                                                                                         1                                 
SE4_IND                                                                                                                                                         1                                 
EE_Narva                                                                                                                                                        1                                 
EE_Parnu                                                                                                                                                        1                                 
EE_Tallinn                                                                                                                                                      1                                 
EE_Tartu                                                                                                                                                        1                                 
LV_RigaR                                                                                                                                                        1                                 
LT_KlaU                                                                                                                                                         1                                 
LT_VilU                                                                                                                                                         1                                 
LT_KauU                                                                                                                                                         1                                 
FI_medium                                                                                                                                                            1                            
FI_medium_gas                                                                                                                                                        1                            
SE1_medium                                                                                                                                                           1                            
SE2_medium                                                                                                                                                           1                            
SE3_medium                                                                                                                                                           1                            
SE4_medium                                                                                                                                                           1                            
FI_small                                                                                                                                                                  1                       
FI_small_gas                                                                                                                                                              1                       
SE1_small                                                                                                                                                                 1                       
SE2_small                                                                                                                                                                 1                       
SE3_small                                                                                                                                                                 1                       
SE4_small                                                                                                                                                                 1                       
EE_Enefit                                                                                                                                                                 1                       
EE_Industry                                                                                                                                                               1                       
EE_Kohtla_Jarve                                                                                                                                                           1                       
EE_Rural                                                                                                                                                                  1                       
EE_Sillamae                                                                                                                                                               1                       
EE_Urban                                                                                                                                                                  1                       
LV_Rural                                                                                                                                                                  1                       
LV_Other_DH                                                                                                                                                               1                       
PL_Rural                                                                                                                                                                  1                       
LT_Other_DH                                                                                                                                                               1                       
LT_Panevezys                                                                                                                                                              1                       
LT_Rural                                                                                                                                                                  1                       
LT_SiaU                                                                                                                                                                   1                       
DK2_Offshore                                                                                                                                                                               1      
DK1_Offshore                                                                                                                                                                               1      
NL_OFFSHORE                                                                                                                                                                                1      
UK_OFFSHORE                                                                                                                                                                                1      
DE4-E_Offshore_A                                                                                                                                                                           1      
DE4-N_Offshore_A                                                                                                                                                                           1      
DE4-W_Offshore_A                                                                                                                                                                           1      
EE_OFFSHORE                                                                                                                                                                                1      
LV_OFFSHORE                                                                                                                                                                                1      
LT_OFFSHORE                                                                                                                                                                                1      
PL_OFFSHORE                                                                                                                                                                                1      
SE1_Offshore                                                                                                                                                                               1      
SE2_Offshore                                                                                                                                                                               1      
SE3_Offshore                                                                                                                                                                               1      
SE4_Offshore                                                                                                                                                                               1      
NO1_Offshore                                                                                                                                                                               1      
NO2_Offshore                                                                                                                                                                               1      
NO3_Offshore                                                                                                                                                                               1      
NO4_Offshore                                                                                                                                                                               1      
NO5_Offshore                                                                                                                                                                               1      
FI_Offshore                                                                                                                                                                                1      
                                                                                                                                                                                                  
                                                                                                                                                                                                  
                                                                                                                                                                                                  
                                                                                                                                                                                                  
                                                                                                                                                                                                  
$ontext                                                                                                                                                                                           
To avoid manual entry in each area the following catagories of areas are defined.                                                                                                                 
Note that each area can belong to one group only                                                                                                                                                  
*currently used:                                                                                                                                                                                  
1 - Central condensing area (possbile to invest in condens, PV and onshore wind.                                                                                                                  
2 - Central CHP area (possible to invest in Large CHP).                                                                                                                                           
3 - Medium CHP areas                                                                                                                                                                              
4 - Small CHP areas                                                                                                                                                                               
7 - Offshore wind area without wave power (possible to invest in offshore wind only)                                                                                                              
                                                                                                                                                                                                  
                                                                                                                                                                                                  
                                                                                                                                                                                                  
*also have been used in other projects:                                                                                                                                                           
3. Decentral small gas area (possible to invest in gas tech).                                                                                                                                     
4. Decentral larger gas area (possible to invest in gas tech).                                                                                                                                    
5. Decentral area without gas (possible to invest in non-gas tech only).                                                                                                                          
6. Waste generation area (possible to invest in waste tech).                                                                                                                                      
8. Offshore wind area with wave power (possible to invest in offshore wind and wave power)                                                                                                        
9. Offshore wind areas far from shore.                                                                                                                                                            
10. Individual heating areas.                                                                                                                                                                     
11. Decentral small gas area with small biomass CHP below 10 MW                                                                                                                                   
$offtext                                                                                                                                                                                          
                                                                                                                                                                                                  
                                                                                                                                                                                                  
                                                                                                                                                                                                  
                                                                                                                                                                                                  
SET ALLOWEDINV(AAA,GGG) "Area, technology where technolgy may be invested based on AGKN and implicit constraints "/                                                                               
                                                                                                                                                                                                  
*GROUP 1 - Condensing + PV + onshore wind                                                                                                                                                         
DK2_NoDH.(                                                                                                                                                                                        
GNR_PV_SUN_LS-4-MW_Y-2020                                                                                                                                                                         
GNR_PV_SUN_LS-4-MW_Y-2030                                                                                                                                                                         
GNR_PV_SUN_LS-4-MW_Y-2050                                                                                                                                                                         
                                                                                                                                                                                                  
GNR_WT_WIND_ON_LS_Y-2020                                                                                                                                                                          
GNR_WT_WIND_ON_LS_Y-2030                                                                                                                                                                          
GNR_WT_WIND_ON_LS_Y-2050                                                                                                                                                                          
                                                                                                                                                                                                  
*GNR_CC_NGAS_CND_E-51_SS-10-MW_Y-2020                                                                                                                                                             
*GNR_CC_NGAS_CND_E-53_SS-10-MW_Y-2030                                                                                                                                                             
*GNR_CC_NGAS_CND_E-55_SS-10-MW_Y-2050                                                                                                                                                             
GNR_CC_NGAS_CND_E-59_LS-100-MW_Y-2020                                                                                                                                                             
GNR_CC_NGAS_CND_E-61_LS-100-MW_Y-2030                                                                                                                                                             
GNR_CC_NGAS_CND_E-63_LS-100-MW_Y-2050                                                                                                                                                             
                                                                                                                                                                                                  
GNR_ENG_BGAS_CND_E-43_Y-2020                                                                                                                                                                      
GNR_ENG_BGAS_CND_E-45_Y-2030                                                                                                                                                                      
GNR_ENG_BGAS_CND_E-47_Y-2050                                                                                                                                                                      
GNR_ENG_NGAS_CND_E-47_Y-2020                                                                                                                                                                      
GNR_ENG_NGAS_CND_E-48_Y-2030                                                                                                                                                                      
GNR_ENG_NGAS_CND_E-50_Y-2050                                                                                                                                                                      
*GNR_GT_NGAS_CND_E-37_SS-5-MW_Y-2020                                                                                                                                                              
*GNR_GT_NGAS_CND_E-39_SS-5-MW_Y-2030                                                                                                                                                              
*GNR_GT_NGAS_CND_E-40_SS-5-MW_Y-2050                                                                                                                                                              
GNR_GT_NGAS_CND_E-42_LS-40-MW_Y-2020                                                                                                                                                              
GNR_GT_NGAS_CND_E-43_LS-40-MW_Y-2030                                                                                                                                                              
GNR_GT_NGAS_CND_E-44_LS-40-MW_Y-2050                                                                                                                                                              
GNR_ST_COAL_CND_E-49_LS-400-MW_Y-2020                                                                                                                                                             
GNR_ST_COAL_CND_E-52_LS-400-MW_Y-2030                                                                                                                                                             
GNR_ST_COAL_CND_E-54_LS-400-MW_Y-2050                                                                                                                                                             
GNR_ST_MSW_CND_E-23_LS-220-MW-FEED_Y-2020                                                                                                                                                         
*GNR_ST_MSW_CND_E-23_SS-35-MW-FEED_Y-2020                                                                                                                                                         
*GNR_ST_MSW_CND_E-23_MS-80-MW-FEED_Y-2020                                                                                                                                                         
GNR_ST_MSW_CND_E-24_LS-220-MW-FEED_Y-2030                                                                                                                                                         
*GNR_ST_MSW_CND_E-24_SS-35-MW-FEED_Y-2030                                                                                                                                                         
*GNR_ST_MSW_CND_E-24_SS-35-MW-FEED_Y-2050                                                                                                                                                         
*GNR_ST_MSW_CND_E-24_MS-80-MW-FEED_Y-2030                                                                                                                                                         
*GNR_ST_MSW_CND_E-24_MS-80-MW-FEED_Y-2050                                                                                                                                                         
GNR_ST_MSW_CND_E-25_LS-220-MW-FEED_Y-2050                                                                                                                                                         
GNR_ST_NGAS_CND_E-47_LS-400-MW_Y-2020                                                                                                                                                             
GNR_ST_NGAS_CND_E-47_LS-400-MW_Y-2030                                                                                                                                                             
GNR_ST_NGAS_CND_E-47_LS-400-MW_Y-2050                                                                                                                                                             
*GNR_ST_STRW_CND_E-17_SS-20-MW-FEED_Y-2020                                                                                                                                                        
*GNR_ST_STRW_CND_E-17_SS-20-MW-FEED_Y-2030                                                                                                                                                        
*GNR_ST_STRW_CND_E-17_SS-20-MW-FEED_Y-2050                                                                                                                                                        
*GNR_ST_STRW_CND_E-25_MS-80-MW-FEED_Y-2020                                                                                                                                                        
*GNR_ST_STRW_CND_E-25_MS-80-MW-FEED_Y-2030                                                                                                                                                        
*GNR_ST_STRW_CND_E-25_MS-80-MW-FEED_Y-2050                                                                                                                                                        
GNR_ST_STRW_CND_E-31_LS-132-MW-FEED_Y-2020                                                                                                                                                        
GNR_ST_STRW_CND_E-31_LS-132-MW-FEED_Y-2030                                                                                                                                                        
GNR_ST_STRW_CND_E-31_LS-132-MW-FEED_Y-2050                                                                                                                                                        
*GNR_ST_WOODCHI_CND_E-16_SS-20-MW-FEED_Y-2030                                                                                                                                                     
*GNR_ST_WOODCHI_CND_E-16_SS-20-MW-FEED_Y-2050                                                                                                                                                     
*GNR_ST_WOODCHI_CND_E-16_SS-20-MW-FEED_Y-2020                                                                                                                                                     
GNR_ST_WOODCHI_CND_E-29_LS-600-MW-FEED_Y-2020                                                                                                                                                     
GNR_ST_WOODCHI_CND_E-29_LS-600-MW-FEED_Y-2030                                                                                                                                                     
GNR_ST_WOODCHI_CND_E-29_LS-600-MW-FEED_Y-2050                                                                                                                                                     
*GNR_ST_WOODCHI_CND_E-29_MS-80-MW-FEED_Y-2020                                                                                                                                                     
*GNR_ST_WOODCHI_CND_E-29_MS-80-MW-FEED_Y-2030                                                                                                                                                     
*GNR_ST_WOODCHI_CND_E-29_MS-80-MW-FEED_Y-2050                                                                                                                                                     
GNR_ST_WOODPEL_CND_E-17_LS-200-MW-FEED_Y-2020                                                                                                                                                     
GNR_ST_WOODPEL_CND_E-17_LS-200-MW-FEED_Y-2030                                                                                                                                                     
GNR_ST_WOODPEL_CND_E-17_LS-200-MW-FEED_Y-2050                                                                                                                                                     
*GNR_ST_WOODPEL_CND_E-30_MS-80-MW-FEED_Y-2020                                                                                                                                                     
*GNR_ST_WOODPEL_CND_E-30_MS-80-MW-FEED_Y-2030                                                                                                                                                     
*GNR_ST_WOODPEL_CND_E-30_MS-80-MW-FEED_Y-2050                                                                                                                                                     
GNR_ST_WOODPEL_CND_E-33_LS-800-MW-FEED_Y-2020                                                                                                                                                     
GNR_ST_WOODPEL_CND_E-33_LS-800-MW-FEED_Y-2030                                                                                                                                                     
GNR_ST_WOODPEL_CND_E-33_LS-800-MW-FEED_Y-2050                                                                                                                                                     
GNR_ST_WOODPEL_CND_E-49_LS-250-MW_Y-2020                                                                                                                                                          
GNR_ST_WOODPEL_CND_E-52_LS-250-MW_Y-2030                                                                                                                                                          
GNR_ST_WOODPEL_CND_E-54_LS-250-MW_Y-2050                                                                                                                                                          
                                                                                                                                                                                                  
GNR_ES_ELEC_BAT-LITHIO_E-95_Y-16-29                                                                                                                                                               
GNR_ES_ELEC_BAT-LITHIO_E-97_Y-30-50                                                                                                                                                               
GNR_ENG_BGAS_CND_E-43_Y-2020_TG                                                                                                                                                                   
GNR_ENG_BGAS_CND_E-45_Y-2030_TG                                                                                                                                                                   
GNR_ENG_BGAS_CND_E-47_Y-2050_TG                                                                                                                                                                   
)                                                                                                                                                                                                 
                                                                                                                                                                                                  
                                                                                                                                                                                                  
                                                                                                                                                                                                  
*Group 2 - Available investments in large CHP areas                                                                                                                                               
DK2_Large.(                                                                                                                                                                                       
                                                                                                                                                                                                  
GNR_BO_ELEC_E-99_LS-10-MW-FEED_Y-2020                                                                                                                                                             
GNR_BO_ELEC_E-99_LS-10-MW-FEED_Y-2030                                                                                                                                                             
GNR_BO_ELEC_E-99_LS-10-MW-FEED_Y-2050                                                                                                                                                             
GNR_BO_MSW_E-106_LS-35-MW-FEED_Y-2020                                                                                                                                                             
GNR_BO_MSW_E-106_LS-35-MW-FEED_Y-2030                                                                                                                                                             
GNR_BO_MSW_E-106_LS-35-MW-FEED_Y-2050                                                                                                                                                             
GNR_BO_STRW_E-104_LS-6-MW-FEED_Y-2020                                                                                                                                                             
GNR_BO_STRW_E-104_LS-6-MW-FEED_Y-2030                                                                                                                                                             
GNR_BO_STRW_E-104_LS-6-MW-FEED_Y-2050                                                                                                                                                             
GNR_BO_WOODCHI_E-117_LS-6-MW-FEED_Y-2020                                                                                                                                                          
GNR_BO_WOODCHI_E-117_LS-6-MW-FEED_Y-2030                                                                                                                                                          
GNR_BO_WOODCHI_E-117_LS-6-MW-FEED_Y-2050                                                                                                                                                          
GNR_BO_WOODPEL_E-102_LS-6-MW-FEED_Y-2020                                                                                                                                                          
GNR_BO_WOODPEL_E-102_LS-6-MW-FEED_Y-2030                                                                                                                                                          
GNR_BO_WOODPEL_E-102_LS-6-MW-FEED_Y-2050                                                                                                                                                          
GNR_CC_NGAS_EXT_E-59_LS-100-MW_Y-2020                                                                                                                                                             
GNR_CC_NGAS_EXT_E-61_LS-100-MW_Y-2030                                                                                                                                                             
GNR_CC_NGAS_EXT_E-63_LS-100-MW_Y-2050                                                                                                                                                             
GNR_GT_NGAS_BP_E-42_LS-40-MW_Y-2020                                                                                                                                                               
GNR_GT_NGAS_BP_E-43_LS-40-MW_Y-2030                                                                                                                                                               
GNR_GT_NGAS_BP_E-44_LS-40-MW_Y-2050                                                                                                                                                               
GNR_ST_COAL_EXT_E-49_LS-400-MW_Y-2020                                                                                                                                                             
GNR_ST_COAL_EXT_E-52_LS-400-MW_Y-2030                                                                                                                                                             
GNR_ST_COAL_EXT_E-54_LS-400-MW_Y-2050                                                                                                                                                             
GNR_ST_MSW_BP_E-23_LS-220-MW-FEED_Y-2020                                                                                                                                                          
*GNR_ST_MSW_BP_E-23_SS-35-MW-FEED_Y-2020                                                                                                                                                          
GNR_ST_MSW_BP_E-24_LS-220-MW-FEED_Y-2030                                                                                                                                                          
*GNR_ST_MSW_BP_E-24_SS-35-MW-FEED_Y-2030                                                                                                                                                          
*GNR_ST_MSW_BP_E-24_SS-35-MW-FEED_Y-2050                                                                                                                                                          
GNR_ST_MSW_BP_E-25_LS-220-MW-FEED_Y-2050                                                                                                                                                          
GNR_ST_NGAS_EXT_E-47_LS-400-MW_Y-2020                                                                                                                                                             
GNR_ST_NGAS_EXT_E-47_LS-400-MW_Y-2030                                                                                                                                                             
GNR_ST_NGAS_EXT_E-47_LS-400-MW_Y-2050                                                                                                                                                             
GNR_ST_STRW_BP_E-31_LS-132-MW-FEED_Y-2020                                                                                                                                                         
GNR_ST_STRW_BP_E-31_LS-132-MW-FEED_Y-2030                                                                                                                                                         
GNR_ST_STRW_BP_E-31_LS-132-MW-FEED_Y-2050                                                                                                                                                         
GNR_ST_WOODCHI_BP_E-29_LS-600-MW-FEED_Y-2020                                                                                                                                                      
GNR_ST_WOODCHI_BP_E-29_LS-600-MW-FEED_Y-2030                                                                                                                                                      
GNR_ST_WOODCHI_BP_E-29_LS-600-MW-FEED_Y-2050                                                                                                                                                      
GNR_ST_WOODPEL_BP_E-17_LS-200-MW-FEED_Y-2020                                                                                                                                                      
GNR_ST_WOODPEL_BP_E-17_LS-200-MW-FEED_Y-2030                                                                                                                                                      
GNR_ST_WOODPEL_BP_E-17_LS-200-MW-FEED_Y-2050                                                                                                                                                      
GNR_ST_WOODPEL_EXT_E-33_LS-800-MW-FEED_Y-2020                                                                                                                                                     
GNR_ST_WOODPEL_EXT_E-33_LS-800-MW-FEED_Y-2030                                                                                                                                                     
GNR_ST_WOODPEL_EXT_E-33_LS-800-MW-FEED_Y-2050                                                                                                                                                     
GNR_ST_WOODPEL_EXT_E-49_LS-250-MW_Y-2020                                                                                                                                                          
GNR_ST_WOODPEL_EXT_E-52_LS-250-MW_Y-2030                                                                                                                                                          
GNR_ST_WOODPEL_EXT_E-54_LS-250-MW_Y-2050                                                                                                                                                          
                                                                                                                                                                                                  
GNR_HS_HEAT_PIT_L-CEN_E-90_Y-2020                                                                                                                                                                 
GNR_HS_HEAT_PIT_L-CEN_E-90_Y-2030                                                                                                                                                                 
GNR_HS_HEAT_PIT_L-CEN_E-90_Y-2050                                                                                                                                                                 
                                                                                                                                                                                                  
GNR_HS_HEAT_WTR-TANK_LS_E-95_Y-2010                                                                                                                                                               
                                                                                                                                                                                                  
GNR_SH_SUN_LS_Y-2020                                                                                                                                                                              
GNR_SH_SUN_LS_Y-2030                                                                                                                                                                              
GNR_SH_SUN_LS_Y-2050                                                                                                                                                                              
                                                                                                                                                                                                  
GNR_HP_ELEC_AIR-WTR_COP-310_LS_Y-2020                                                                                                                                                             
GNR_HP_ELEC_AIR-WTR_COP-330_LS_Y-2030                                                                                                                                                             
GNR_HP_ELEC_AIR-WTR_COP-360_LS_Y-2050                                                                                                                                                             
                                                                                                                                                                                                  
                                                                                                                                                                                                  
                                                                                                                                                                                                  
                                                                                                                                                                                                  
)                                                                                                                                                                                                 
                                                                                                                                                                                                  
                                                                                                                                                                                                  
                                                                                                                                                                                                  
                                                                                                                                                                                                  
                                                                                                                                                                                                  
*Group 3 - Available investments in medium CHP areas                                                                                                                                              
DK2_MedSmall.(                                                                                                                                                                                    
                                                                                                                                                                                                  
GNR_BO_ELEC_E-99_MS-1-MW-FEED_Y-2020                                                                                                                                                              
GNR_BO_ELEC_E-99_MS-1-MW-FEED_Y-2030                                                                                                                                                              
GNR_BO_ELEC_E-99_MS-1-MW-FEED_Y-2050                                                                                                                                                              
* what size technology is the BGAS engine?                                                                                                                                                        
GNR_ENG_BGAS_BP_E-43_Y-2020                                                                                                                                                                       
GNR_ENG_BGAS_BP_E-45_Y-2030                                                                                                                                                                       
GNR_ENG_BGAS_BP_E-47_Y-2050                                                                                                                                                                       
GNR_ENG_NGAS_BP_E-47_Y-2020                                                                                                                                                                       
GNR_ENG_NGAS_BP_E-48_Y-2030                                                                                                                                                                       
GNR_ENG_NGAS_BP_E-50_Y-2050                                                                                                                                                                       
GNR_ST_MSW_BP_E-23_MS-80-MW-FEED_Y-2020                                                                                                                                                           
GNR_ST_MSW_BP_E-24_MS-80-MW-FEED_Y-2030                                                                                                                                                           
GNR_ST_MSW_BP_E-24_MS-80-MW-FEED_Y-2050                                                                                                                                                           
GNR_ST_STRW_BP_E-25_MS-80-MW-FEED_Y-2020                                                                                                                                                          
GNR_ST_STRW_BP_E-25_MS-80-MW-FEED_Y-2030                                                                                                                                                          
GNR_ST_STRW_BP_E-25_MS-80-MW-FEED_Y-2050                                                                                                                                                          
*GNR_ST_WOODCHI_BP_E-16_SS-20-MW-FEED_Y-2030                                                                                                                                                      
*GNR_ST_WOODCHI_BP_E-16_SS-20-MW-FEED_Y-2050                                                                                                                                                      
*GNR_ST_WOODCHI_BP_E-16_SS-20-MW-FEED_Y-2020                                                                                                                                                      
GNR_ST_WOODCHI_BP_E-29_MS-80-MW-FEED_Y-2020                                                                                                                                                       
GNR_ST_WOODCHI_BP_E-29_MS-80-MW-FEED_Y-2030                                                                                                                                                       
GNR_ST_WOODCHI_BP_E-29_MS-80-MW-FEED_Y-2050                                                                                                                                                       
GNR_ST_WOODPEL_BP_E-30_MS-80-MW-FEED_Y-2020                                                                                                                                                       
GNR_ST_WOODPEL_BP_E-30_MS-80-MW-FEED_Y-2030                                                                                                                                                       
GNR_ST_WOODPEL_BP_E-30_MS-80-MW-FEED_Y-2050                                                                                                                                                       
                                                                                                                                                                                                  
                                                                                                                                                                                                  
GNR_HS_HEAT_PIT_L-DEC_E-91_Y-2020                                                                                                                                                                 
GNR_HS_HEAT_PIT_L-DEC_E-91_Y-2030                                                                                                                                                                 
GNR_HS_HEAT_PIT_L-DEC_E-91_Y-2050                                                                                                                                                                 
                                                                                                                                                                                                  
GNR_HS_HEAT_WTR-TANK_LS_E-95_Y-2010                                                                                                                                                               
                                                                                                                                                                                                  
GNR_SH_SUN_LS_Y-2020                                                                                                                                                                              
GNR_SH_SUN_LS_Y-2030                                                                                                                                                                              
GNR_SH_SUN_LS_Y-2050                                                                                                                                                                              
                                                                                                                                                                                                  
GNR_HP_ELEC_AIR-WTR_COP-310_LS_Y-2020                                                                                                                                                             
GNR_HP_ELEC_AIR-WTR_COP-330_LS_Y-2030                                                                                                                                                             
GNR_HP_ELEC_AIR-WTR_COP-360_LS_Y-2050                                                                                                                                                             
                                                                                                                                                                                                  
                                                                                                                                                                                                  
GNR_HP_ELEC_GROUND-WTR_COP-360_LS-4-MW_Y-2020                                                                                                                                                     
GNR_HP_ELEC_GROUND-WTR_COP-380_LS-4-MW_Y-2030                                                                                                                                                     
GNR_HP_ELEC_GROUND-WTR_COP-410_LS-4-MW_Y-2050                                                                                                                                                     
GNR_ENG_BGAS_BP_E-43_Y-2020_TG                                                                                                                                                                    
GNR_ENG_BGAS_BP_E-45_Y-2030_TG                                                                                                                                                                    
GNR_ENG_BGAS_BP_E-47_Y-2050_TG                                                                                                                                                                    
                                                                                                                                                                                                  
)                                                                                                                                                                                                 
                                                                                                                                                                                                  
                                                                                                                                                                                                  
*Group 4 - Available investments in small CHP areas                                                                                                                                               
DK2_Small.(                                                                                                                                                                                       
GNR_BO_NGAS_E-105_SS-500-KW_Y-2020                                                                                                                                                                
GNR_BO_NGAS_E-106_SS-500-KW_Y-2030                                                                                                                                                                
GNR_BO_NGAS_E-106_SS-500-KW_Y-2050                                                                                                                                                                
GNR_CC_NGAS_BP_E-51_SS-10-MW_Y-2020                                                                                                                                                               
GNR_CC_NGAS_BP_E-53_SS-10-MW_Y-2030                                                                                                                                                               
GNR_CC_NGAS_BP_E-55_SS-10-MW_Y-2050                                                                                                                                                               
GNR_GT_NGAS_BP_E-37_SS-5-MW_Y-2020                                                                                                                                                                
GNR_GT_NGAS_BP_E-39_SS-5-MW_Y-2030                                                                                                                                                                
GNR_GT_NGAS_BP_E-40_SS-5-MW_Y-2050                                                                                                                                                                
GNR_ST_STRW_BP_E-17_SS-20-MW-FEED_Y-2020                                                                                                                                                          
GNR_ST_STRW_BP_E-17_SS-20-MW-FEED_Y-2030                                                                                                                                                          
GNR_ST_STRW_BP_E-17_SS-20-MW-FEED_Y-2050                                                                                                                                                          
GNR_ST_WOODCHI_BP_E-16_SS-20-MW-FEED_Y-2020                                                                                                                                                       
GNR_ST_WOODCHI_BP_E-16_SS-20-MW-FEED_Y-2030                                                                                                                                                       
GNR_ST_WOODCHI_BP_E-16_SS-20-MW-FEED_Y-2050                                                                                                                                                       
                                                                                                                                                                                                  
                                                                                                                                                                                                  
GNR_HS_HEAT_PIT_L-DEC_E-91_Y-2020                                                                                                                                                                 
GNR_HS_HEAT_PIT_L-DEC_E-91_Y-2030                                                                                                                                                                 
GNR_HS_HEAT_PIT_L-DEC_E-91_Y-2050                                                                                                                                                                 
                                                                                                                                                                                                  
GNR_HS_HEAT_WTR-TANK_LS_E-95_Y-2010                                                                                                                                                               
                                                                                                                                                                                                  
GNR_SH_SUN_LS_Y-2020                                                                                                                                                                              
GNR_SH_SUN_LS_Y-2030                                                                                                                                                                              
GNR_SH_SUN_LS_Y-2050                                                                                                                                                                              
                                                                                                                                                                                                  
GNR_HP_ELEC_AIR-WTR_COP-310_LS_Y-2020                                                                                                                                                             
GNR_HP_ELEC_AIR-WTR_COP-330_LS_Y-2030                                                                                                                                                             
GNR_HP_ELEC_AIR-WTR_COP-360_LS_Y-2050                                                                                                                                                             
                                                                                                                                                                                                  
GNR_HP_ELEC_GROUND-WTR_COP-360_LS-4-MW_Y-2020                                                                                                                                                     
GNR_HP_ELEC_GROUND-WTR_COP-380_LS-4-MW_Y-2030                                                                                                                                                     
GNR_HP_ELEC_GROUND-WTR_COP-410_LS-4-MW_Y-2050                                                                                                                                                     
                                                                                                                                                                                                  
)                                                                                                                                                                                                 
                                                                                                                                                                                                  
                                                                                                                                                                                                  
                                                                                                                                                                                                  
*Group 7 - Offshore wind w/o wave                                                                                                                                                                 
DK2_Offshore.(                                                                                                                                                                                    
                                                                                                                                                                                                  
GNR_WT_WIND_OFF_L-FS_Y-2020                                                                                                                                                                       
GNR_WT_WIND_OFF_L-FS_Y-2030                                                                                                                                                                       
GNR_WT_WIND_OFF_L-FS_Y-2050                                                                                                                                                                       
GNR_WT_WIND_OFF_L-NS_Y-2020                                                                                                                                                                       
GNR_WT_WIND_OFF_L-NS_Y-2030                                                                                                                                                                       
GNR_WT_WIND_OFF_L-NS_Y-2050                                                                                                                                                                       
                                                                                                                                                                                                  
)                                                                                                                                                                                                 
                                                                                                                                                                                                  
                                                                                                                                                                                                  
*POSSIBLE EXCEPTIONS CAN ALSO BE ADDED, WHICH WILL NOT BE TRANFERRED TO OTHER AREAS                                                                                                               
                                                                                                                                                                                                  
*FOR EXAMPLE SPECIFIC REFURBISHMENT TECHS IN ESTONIA                                                                                                                                              
$ONTEXT                                                                                                                                                                                           
EE_NARVA.(                                                                                                                                                                                        
AUVERE_ST_SHALE_CND_RF_COAL                                                                                                                                                                       
AUVERE_ST_SHALE_CND_RF_WOOD                                                                                                                                                                       
)                                                                                                                                                                                                 
$OFFTEXT                                                                                                                                                                                          
                                                                                                                                                                                                  
*End of set ALLOWEDINV                                                                                                                                                                            
/;                                                                                                                                                                                                
                                                                                                                                                                                                  
*Assigning of investment options to defined groups                                                                                                                                                
ALLOWEDINV(AAA,G)$((INVDATA(AAA,'COND')=1)  and ALLOWEDINV('DK2_NoDH',G))         = yes ;                                                                                                         
ALLOWEDINV(AAA,G)$((INVDATA(AAA,'LDH')=1)   and ALLOWEDINV('DK2_Large',G))         = yes ;                                                                                                        
ALLOWEDINV(AAA,G)$((INVDATA(AAA,'MDH')=1)  and ALLOWEDINV('DK2_MedSmall',G))         = yes ;                                                                                                      
ALLOWEDINV(AAA,G)$((INVDATA(AAA,'SDH')=1)  and ALLOWEDINV('DK2_Small',G))         = yes ;                                                                                                         
                                                                                                                                                                                                  
                                                                                                                                                                                                  
ALLOWEDINV(AAA,G)$((INVDATA(AAA,'OFFSWND')=1)  and ALLOWEDINV('DK2_Offshore',G))         = yes ;                                                                                                  
                                                                                                                                                                                                  
                                                                                                                                                                                                  
                                                                                                                                                                                                  
                                                                                                                                                                                                  
                                                                                                                                                                                                  
                                                                                                                                                                                                  
                                                                                                                                                                                                  
                                                                                                                                                                                                  
AGKN(AAA,G)=YES$ALLOWEDINV(AAA,G);                                                                                                                                                                
                                                                                                                                                                                                  
                                                                                                                                                                                                  
*Data clean-up: commented out for testing purposes temporarely                                                                                                                                    
*INVESTMENTS(AAA)=0;                                                                                                                                                                              
*ALLOWEDINV(AAA,G)=0;                                                                                                                                                                             
