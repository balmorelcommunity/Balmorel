TABLE EMI_POLNA(YYY,GROUP,EMIPOLSET)  "Emission policy data; default for the 'LIM_' entries: 0 implies irrelevant, EPS implies no emission permitted (aggregated countries)"                                                                 
                                                                                                                                                                                                                                             
                                                                                                                                                                            ALL_SECTORS.LIM_CO2 ALL_SECTORS.LIM_SO2 ALL_SECTORS.LIM_NOX     
* Units:                                                                                                                                                                     t CO2/year          t SO2/year          t NOx/year              
*2050                                                                                                                                                                   		 EPS																																																																				
;
*EMI_POLNA(YYY,GROUP,EMIPOLSET)=0;
*23580297

* Scenario-local override (2026-05-29): negcap2050 = A1 bio-CCS-realism + 2050 neg-emi cap.
* Clone of the A1 scenario (..._aaa_reduced_transcost: biomass-CCS investable only where
* base biomass is ALLOWEDINV; all feedstocks; B1 undone) with ONE addition: a hard 2050 cap
* forcing net CO2 <= -82 Mt/yr, all sectors aggregated. Cap binds ONLY in the 2050 cohort
* (myopic LOOP); 2030/2040 LPs are identical to the uncapped A1 run.
* With CCS=yes and QLIMCO2NA subtracting captured (IM_CO2+IM_CO2RE) x capteff, this forces
* BECCS deployment to reach the net-negative target -- IF A1's ~100 realistic biomass areas
* hold enough BECCS capacity. If not, the 2050 cohort is INFEASIBLE (feasibility risk noted).
* 2_1_Scenario_EU_Normal_Res_PB_max_nocap (2026-05-30): NO cap. Cap-free arm -- the
* -82 Mt/yr 2050 aggregate cap stays COMMENTED, so LIM_CO2 = 0 (table default). The
* sibling 2_2_..._neg_emi_cap enables the same line; the two differ ONLY here.
*EMI_POLNA('2050','ALL_SECTORS','LIM_CO2')=-82000000;
