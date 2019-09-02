Set MontecarloParameters   'Parameters analysed in a Montecarlo simulations' %semislash%
$INCLUDE      '../../sensitivity_analysis/montecarlo_simulations/MontecarloParameters.inc';
%semislash%;

TABLE LHSSAMPLING(scenarios,MontecarloParameters)
**Creation of inc file
$call =xls2gms r=A1:BA796 I="../../sensitivity_analysis/montecarlo_simulations/scenario_creation/output/LHS_Sampling.xlsx" O="../../sensitivity_analysis/montecarlo_simulations/scenario_creation/output/LHS_Sampling_out.inc"
**Reading scenario parameters
$include "../../sensitivity_analysis/montecarlo_simulations/scenario_creation/output/LHS_Sampling_out.inc"
;

PARAMETER SAMPLING(scenarios,MontecarloParameters);
SAMPLING(scenarios,MontecarloParameters)=LHSSAMPLING(scenarios,MontecarloParameters);


Parameter WNDFLH_Scenarios(scenarios,AAA) 'Change of the full load hours of operation of wind turbines in the different scenarios';
*FLH ONSHORE
WNDFLH_Scenarios(scenarios,'DK2_Large')=SAMPLING(scenarios,'FLH_WIND_ON_DK');
WNDFLH_Scenarios(scenarios,'DK2_Medium')=SAMPLING(scenarios,'FLH_WIND_ON_DK');
WNDFLH_Scenarios(scenarios,'DK2_MedSmall')=SAMPLING(scenarios,'FLH_WIND_ON_DK');
WNDFLH_Scenarios(scenarios,'DK2_Small')=SAMPLING(scenarios,'FLH_WIND_ON_DK');
WNDFLH_Scenarios(scenarios,'DK2_Rural')=SAMPLING(scenarios,'FLH_WIND_ON_DK');
WNDFLH_Scenarios(scenarios,'DK1_Large')=SAMPLING(scenarios,'FLH_WIND_ON_DK');
WNDFLH_Scenarios(scenarios,'DK1_Medium')=SAMPLING(scenarios,'FLH_WIND_ON_DK');
WNDFLH_Scenarios(scenarios,'DK1_MedSmall')=SAMPLING(scenarios,'FLH_WIND_ON_DK');
WNDFLH_Scenarios(scenarios,'DK1_Small')=SAMPLING(scenarios,'FLH_WIND_ON_DK');
WNDFLH_Scenarios(scenarios,'DK1_Rural')=SAMPLING(scenarios,'FLH_WIND_ON_DK');

*FLH OFFSHORE
*WNDFLH_Scenarios(scenarios,'DK1_Offshore10')=SAMPLING(scenarios,'FLH_WIND_OFF_DK');
*WNDFLH_Scenarios(scenarios,'DK2_Offshore10')=SAMPLING(scenarios,'FLH_WIND_OFF_DK');

Parameter SOLEFLH_Scenarios(scenarios,AAA) 'Change of the full load hours of operation of PV in the different scenarios';
*SOLEFLH_Scenarios(scenarios,'DK_E_Large')=SAMPLING(scenarios,'PI_SolarPV');
*SOLEFLH_Scenarios(scenarios,IA)$(SUM(IGSOLE,IAGK_Y(IA,IGSOLE)+IAGKN(IA,IGSOLE)) AND ICA('DENMARK',IA))=(SOLEFLH_Scenarios(scenarios,'DK_E_Large')/SOLEFLH('DK_E_Large'))*SOLEFLH(IA);
SOLEFLH_Scenarios(scenarios,'DK2_Large')=SAMPLING(scenarios,'FLH_PV');
SOLEFLH_Scenarios(scenarios,'DK2_Medium')=SAMPLING(scenarios,'FLH_PV');
SOLEFLH_Scenarios(scenarios,'DK2_MedSmall')=SAMPLING(scenarios,'FLH_PV');
SOLEFLH_Scenarios(scenarios,'DK2_Small')=SAMPLING(scenarios,'FLH_PV');
SOLEFLH_Scenarios(scenarios,'DK2_Rural')=SAMPLING(scenarios,'FLH_PV');
SOLEFLH_Scenarios(scenarios,'DK1_Large')=SAMPLING(scenarios,'FLH_PV');
SOLEFLH_Scenarios(scenarios,'DK1_Medium')=SAMPLING(scenarios,'FLH_PV');
SOLEFLH_Scenarios(scenarios,'DK1_MedSmall')=SAMPLING(scenarios,'FLH_PV');
SOLEFLH_Scenarios(scenarios,'DK1_Small')=SAMPLING(scenarios,'FLH_PV');
SOLEFLH_Scenarios(scenarios,'DK1_Rural')=SAMPLING(scenarios,'FLH_PV');


Parameter WTRRSFLH_Scenarios(scenarios,AAA) 'Change of the full load hours of operation of hydropower with reservoirs in the different scenarios';
WTRRSFLH_Scenarios(scenarios,'NO1_A1')=SAMPLING(scenarios,'FLH_WATER_NO');
WTRRSFLH_Scenarios(scenarios,'NO2_A1')=SAMPLING(scenarios,'FLH_WATER_NO');
WTRRSFLH_Scenarios(scenarios,'NO3_A1')=SAMPLING(scenarios,'FLH_WATER_NO');
WTRRSFLH_Scenarios(scenarios,'NO4_A1')=SAMPLING(scenarios,'FLH_WATER_NO');
WTRRSFLH_Scenarios(scenarios,'NO5_A1')=SAMPLING(scenarios,'FLH_WATER_NO');
WTRRSFLH_Scenarios(scenarios,'SE1A')=SAMPLING(scenarios,'FLH_WATER_SE');
WTRRSFLH_Scenarios(scenarios,'SE2A')=SAMPLING(scenarios,'FLH_WATER_SE');
WTRRSFLH_Scenarios(scenarios,'SE3A')=SAMPLING(scenarios,'FLH_WATER_SE');
WTRRSFLH_Scenarios(scenarios,'SE4A')=SAMPLING(scenarios,'FLH_WATER_SE');

Parameter IHYINF_S_Scenarios 'Internal parameter for hydropower plants with reservoir';
IHYINF_S_Scenarios(scenarios,IA,S)= ((WTRRSFLH_Scenarios(scenarios,IA) * WTRRSVAR_S(IA,S) * (IOF365*WEIGHT_S(S)/IWEIGHSUMS)) / IWTRRSSUM(IA))$IWTRRSSUM(IA);

*CO2 PRICE
PARAMETER M_POL_Scenarios(scenarios,YYY,MPOLSET,CCC) 'CO2 price change for the different scenarios';
M_POL_Scenarios(scenarios,'2020','TAX_CO2',CCC)=SAMPLING(scenarios,'PR_CO2_2020');
M_POL_Scenarios(scenarios,'2030','TAX_CO2',CCC)=SAMPLING(scenarios,'PR_CO2_2030');


PARAMETER FUELPRICE_Scenario(scenarios,YYY,AAA,FFF) 'Fuel price change for the different scenarios';
*FUELPRICE_Scenario(scenarios,Y,IA,'WOOD_PELLETS')$FUELPRICE(Y,IA,'WOOD_PELLETS')=SAMPLING(scenarios,'RHO_WPprice');

FUELPRICE_Scenario(scenarios,'2020',IA,'NATGAS')$FUELPRICE('2020',IA,'NATGAS')=SAMPLING(scenarios,'PR_NG_2020');
*FUELPRICE_Scenario(scenarios,'2025',IA,'NATGAS')$FUELPRICE('2025',IA,'NATGAS')=SAMPLING(scenarios,'PR_NG_2025');
FUELPRICE_Scenario(scenarios,'2030',IA,'NATGAS')$FUELPRICE('2030',IA,'NATGAS')=SAMPLING(scenarios,'PR_NG_2030');
FUELPRICE_Scenario(scenarios,'2020',IA,'COAL')$FUELPRICE('2020',IA,'COAL')=SAMPLING(scenarios,'PR_CO_2020');
*FUELPRICE_Scenario(scenarios,'2025',IA,'COAL')$FUELPRICE('2025',IA,'COAL')=SAMPLING(scenarios,'PR_CO_2025');
FUELPRICE_Scenario(scenarios,'2030',IA,'COAL')$FUELPRICE('2030',IA,'COAL')=SAMPLING(scenarios,'PR_CO_2030');
FUELPRICE_Scenario(scenarios,'2020',IA,'WOODPELLETS')$FUELPRICE('2020',IA,'WOODPELLETS')=SAMPLING(scenarios,'PR_WP_2020');
*FUELPRICE_Scenario(scenarios,'2025',IA,'WOODPELLETS')$FUELPRICE('2025',IA,'WOODPELLETS')=SAMPLING(scenarios,'PR_WP_2025');
FUELPRICE_Scenario(scenarios,'2030',IA,'WOODPELLETS')$FUELPRICE('2030',IA,'WOODPELLETS')=SAMPLING(scenarios,'PR_WP_2030');
FUELPRICE_Scenario(scenarios,'2020',IA,'STRAW')$FUELPRICE('2020',IA,'STRAW')=SAMPLING(scenarios,'PR_STR_2020');
*FUELPRICE_Scenario(scenarios,'2025',IA,'STRAW')$FUELPRICE('2025',IA,'STRAW')=SAMPLING(scenarios,'PR_STR_2025');
FUELPRICE_Scenario(scenarios,'2030',IA,'STRAW')$FUELPRICE('2030',IA,'STRAW')=SAMPLING(scenarios,'PR_STR_2030');
FUELPRICE_Scenario(scenarios,'2020',IA,'WOODCHIPS')$FUELPRICE('2020',IA,'WOODCHIPS')=SAMPLING(scenarios,'PR_WC_2020');
*FUELPRICE_Scenario(scenarios,'2025',IA,'WOODCHIPS')$FUELPRICE('2025',IA,'WOODCHIPS')=SAMPLING(scenarios,'PR_WC_2025');
FUELPRICE_Scenario(scenarios,'2030',IA,'WOODCHIPS')$FUELPRICE('2030',IA,'WOODCHIPS')=SAMPLING(scenarios,'PR_WC_2030');


*PARAMETER IFUELP_Y_Scenario(scenarios,AAA,FFF) 'Fuel price for the different scenarios in the year of simulation';
*LOOP(Y,IFUELP_Y_Scenario(scenarios,IA,FFF)=FUELPRICE_Scenario(scenarios,Y,IA,FFF););

*PARAMETER IGMAXF_Y_Scenarios(scenarios,CCCRRRAAA,FFF) 'Maximum fuel use';
*IGMAXF_Y_Scenarios(scenarios,'DENMARK','STRAW')=SAMPLING(scenarios,'MU_Straw')*IOF1000000;
*IGMAXF_Y_Scenarios(scenarios,'DENMARK','COAL')=SAMPLING(scenarios,'Lambda_coal')*IOF1000000;
*IGMAXF_Y_Scenarios(scenarios,'DENMARK','NAT_GAS')=SAMPLING(scenarios,'Lambda_NG')*IOF1000000;

Parameter IAGK_Y_Scenarios(scenarios,AAA,GGG) 'Installed plants';
**IAGK_Y_Scenarios(scenarios,IA,IGF(G,'COAL'))$(SUM((C)$(ICA('DENMARK',IA) AND GKFX('2035',IA,IGF(G,'COAL')))))=YES;

*Parameter IAGKN_Scenarios(scenarios,AAA,GGG) 'Investment in new plants';
**IAGKN_Scenarios(scenarios,IA,IGF(G,'COAL'))$(SUM((C)$(IGF(G,'COAL') AND ICA('DENMARK',IA) AND AGKN(IA,IGF(G,'COAL')))))=YES;

*PARAMETER IGEQF_Y_Scenarios(scenarios,CCCRRRAAA,FFF) 'Naximum fuel use';
*IGEQF_Y_Scenarios(scenarios,'DENMARK','BIOGAS_EC_net')=SAMPLING(scenarios,'MU_Biogas')*IOF1000000;
*IGEQF_Y_Scenarios(scenarios,'DK_E','MUNI_WASTE')=SAMPLING(scenarios,'MU_MSW')*IOF1000000*(GEQF('2035','DK_E','MUNI_WASTE')/(GEQF('2035','DK_W','MUNI_WASTE')+GEQF('2035','DK_E','MUNI_WASTE')));
*IGEQF_Y_Scenarios(scenarios,'DK_W','MUNI_WASTE')=SAMPLING(scenarios,'MU_MSW')*IOF1000000*(GEQF('2035','DK_W','MUNI_WASTE')/(GEQF('2035','DK_W','MUNI_WASTE')+GEQF('2035','DK_E','MUNI_WASTE')));

*Parameter INSCAPHEATPUMP_Y_Scenarios(scenarios,AAA) 'Maximum installed capacity of high efficient heat pumps in Large DH';
*INSCAPHEATPUMP_Y_Scenarios(scenarios,AAA)$(INSCAPHEATPUMP_Y(AAA))=INSCAPHEATPUMP_Y(AAA)*SAMPLING(scenarios,'MU_HP')/4.7;


Parameter GDATA_Scenario(scenarios,GGG,GDATASET) 'Changes in CAPEX of wind turbines for the different scenarios';
*GDATA_Scenario(scenarios,'PV_2020','GDINVCOST0')=SAMPLING(scenarios,'CPX_PV_2020');

*GDATA_Scenario(scenarios,'PV_2030','GDINVCOST0')=SAMPLING(scenarios,'CPX_PV_2030');
*GDATA_Scenario(scenarios,'Wind_Onshore_2020','GDINVCOST0')=SAMPLING(scenarios,'CPX_Wind_Onshore_2020');
*GDATA_Scenario(scenarios,'Wind_Onshore_2025','GDINVCOST0')=SAMPLING(scenarios,'CPX_Wind_Onshore_2025');
*GDATA_Scenario(scenarios,'Wind_Onshore_2030','GDINVCOST0')=SAMPLING(scenarios,'CPX_Wind_Onshore_2030');
*GDATA_Scenario(scenarios,'Wind_Offshore_2020','GDINVCOST0')=SAMPLING(scenarios,'CPX_Wind_Offshore_2020');
*GDATA_Scenario(scenarios,'Wind_Offshore_2025','GDINVCOST0')=SAMPLING(scenarios,'CPX_Wind_Offshore_2025');
*GDATA_Scenario(scenarios,'Wind_Offshore_2030','GDINVCOST0')=SAMPLING(scenarios,'CPX_Wind_Offshore_2030');
*GDATA_Scenario(scenarios,'ST_BP_STR_2020','GDINVCOST0')=SAMPLING(scenarios,'CPX_ST_BP_STR_2020');


Parameter GINVCOST_Scenario(scenarios,AAA,GGG) ' Changes in investment costs for the different scenarios';
*GINVCOST_Scenario(scenarios,IA,G)$((SUM(Y,GKFX(Y,IA,G)) OR AGKN(IA,G)) AND GDATA_Scenario(scenarios,G,'GDINVCOST0'))= GDATA_Scenario(scenarios,G,'GDINVCOST0');

PARAMETER GKFX_Scenario(scenarios,YYY,AAA,GGG) 'Update in capacities in for excess heat from biorefineries and nuclear capacity for some scenarios';
*GKFX_Scenario(scenarios,YYY,AAA,'Biofuel_SURPLUS_H')$GKFX(YYY,AAA,'Biofuel_SURPLUS_H')=SAMPLING(scenarios,'NU_biorefineries')*GKFX(YYY,AAA,'Biofuel_SURPLUS_H')/4.4;
*GKFX_Scenario(scenarios,'2020','SE3A','GCND_NUCLEAR')=SAMPLING(scenarios,'NUC');
*GKFX_Scenario(scenarios,'2025','SE3A','GCND_NUCLEAR')=SAMPLING(scenarios,'NUC');
*GKFX_Scenario(scenarios,'2030','SE3A','GCND_NUCLEAR')=SAMPLING(scenarios,'NUC');

*PARAMETER IGKFX_Y_Scenario(scenarios,AAA,GGG) 'Installed exogenous capacity in the year of simulation';
*LOOP(Y,IGKFX_Y_Scenario(scenarios,IA,G)=GKFX_Scenario(scenarios,Y,IA,G););

*PARAMETER IGKFXYMAX_Scenario(scenarios,AAA,GGG) 'Maximum Installed exogenous capacity in the year of simulation';
*IGKFXYMAX_Scenario(scenarios,IA,G)$(IGKFX_Y_Scenario(scenarios,IA,G))=IGKFX_Y_Scenario(scenarios,IA,G);


PARAMETER IXKRATE_Scenario(scenarios,IRRRE,IRRRI,SSS,TTT) 'Availability of transmission lines in Denmark';
IXKRATE_Scenario(scenarios,IRRRE,IRRRI,S,T)=SAMPLING(scenarios,'TRANS');

*Parameter XMAXINV_Scenario(scenarios,IYALIAS,YYY,IRRRE,IRRRI) 'Maximum investment in transmission capacity for the different scenarios';
*XMAXINV_Scenario(scenarios,IYALIAS,Y,IRE,IRI)$(XMAXINV(IYALIAS,Y,IRE,IRI))=SAMPLING(scenarios,'TAU_investments')*XMAXINV(IYALIAS,Y,IRE,IRI)/10000;

*Parameter IXMAXINV_Y_Scenario(scenarios,IYALIAS,IRRRE,IRRRI) 'Maximum investment in transmission capacity in the current simulation year for the different scenarios';
*LOOP(Y,IXMAXINV_Y_Scenario(scenarios,IYALIAS,IRE,IRI)=XMAXINV_Scenario(scenarios,IYALIAS,Y,IRE,IRI););

PARAMETER DISCOUNTRATE_Scenario(scenarios)  'Transforms investment to annual payment (fraction)';
DISCOUNTRATE_Scenario(scenarios)=SAMPLING(scenarios,'DR');

Parameter DE_Scenario(scenarios,YYY,RRR) 'Change on total electricity demand';
DE_Scenario(scenarios,'2020','DK1')=SAMPLING(scenarios,'DE_DK_2020')*0.599;
*DE_Scenario(scenarios,'2025','DK1')=SAMPLING(scenarios,'DE_DK_2025')*0.599;
DE_Scenario(scenarios,'2030','DK1')=SAMPLING(scenarios,'DE_DK_2030')*0.599;
DE_Scenario(scenarios,'2020','DK2')=SAMPLING(scenarios,'DE_DK_2020')*0.401;
*DE_Scenario(scenarios,'2025','DK2')=SAMPLING(scenarios,'DE_DK_2025')*0.401;
DE_Scenario(scenarios,'2030','DK2')=SAMPLING(scenarios,'DE_DK_2030')*0.401;

DE_Scenario(scenarios,'2020','NO1')=SAMPLING(scenarios,'DE_NO_2020')*0.309;
*DE_Scenario(scenarios,'2025','NO1')=SAMPLING(scenarios,'DE_NO_2025')*0.309;
DE_Scenario(scenarios,'2030','NO1')=SAMPLING(scenarios,'DE_NO_2030')*0.309;
DE_Scenario(scenarios,'2020','NO2')=SAMPLING(scenarios,'DE_NO_2020')*0.177;
*DE_Scenario(scenarios,'2025','NO2')=SAMPLING(scenarios,'DE_NO_2025')*0.177;
DE_Scenario(scenarios,'2030','NO2')=SAMPLING(scenarios,'DE_NO_2030')*0.177;
DE_Scenario(scenarios,'2020','NO3')=SAMPLING(scenarios,'DE_NO_2020')*0.237;
*DE_Scenario(scenarios,'2025','NO3')=SAMPLING(scenarios,'DE_NO_2025')*0.237;
DE_Scenario(scenarios,'2030','NO3')=SAMPLING(scenarios,'DE_NO_2030')*0.237;
DE_Scenario(scenarios,'2020','NO4')=SAMPLING(scenarios,'DE_NO_2020')*0.132;
*DE_Scenario(scenarios,'2025','NO4')=SAMPLING(scenarios,'DE_NO_2025')*0.132;
DE_Scenario(scenarios,'2030','NO4')=SAMPLING(scenarios,'DE_NO_2030')*0.132;
DE_Scenario(scenarios,'2020','NO5')=SAMPLING(scenarios,'DE_NO_2020')*0.145;
*DE_Scenario(scenarios,'2025','NO5')=SAMPLING(scenarios,'DE_NO_2025')*0.145;
DE_Scenario(scenarios,'2030','NO5')=SAMPLING(scenarios,'DE_NO_2030')*0.145;

DE_Scenario(scenarios,'2020','SE1')=SAMPLING(scenarios,'DE_SE_2020')*0.088;
*DE_Scenario(scenarios,'2025','SE1')=SAMPLING(scenarios,'DE_SE_2025')*0.088;
DE_Scenario(scenarios,'2030','SE1')=SAMPLING(scenarios,'DE_SE_2030')*0.088;
DE_Scenario(scenarios,'2020','SE2')=SAMPLING(scenarios,'DE_SE_2020')*0.103;
*DE_Scenario(scenarios,'2025','SE2')=SAMPLING(scenarios,'DE_SE_2025')*0.103;
DE_Scenario(scenarios,'2030','SE2')=SAMPLING(scenarios,'DE_SE_2030')*0.103;
DE_Scenario(scenarios,'2020','SE3')=SAMPLING(scenarios,'DE_SE_2020')*0.628;
*DE_Scenario(scenarios,'2025','SE3')=SAMPLING(scenarios,'DE_SE_2025')*0.628;
DE_Scenario(scenarios,'2030','SE3')=SAMPLING(scenarios,'DE_SE_2030')*0.628;
DE_Scenario(scenarios,'2020','SE4')=SAMPLING(scenarios,'DE_SE_2020')*0.181;
*DE_Scenario(scenarios,'2025','SE4')=SAMPLING(scenarios,'DE_SE_2025')*0.181;
DE_Scenario(scenarios,'2030','SE4')=SAMPLING(scenarios,'DE_SE_2030')*0.181;




Parameter DH_Scenario(scenarios,YYY,AAA) 'Change on total DH demand';
*DH_Scenario(scenarios,YYY,IA)$(ICA('DENMARK',IA) AND DH(YYY,IA) AND (NOT AINDHEAT(IA)))=SAMPLING(scenarios,'DH_DK');
DH_Scenario(scenarios,'2020','DK2_Large')=SAMPLING(scenarios,'DH_DK_2020')*0.254;
*DH_Scenario(scenarios,'2025','DK2_Large')=SAMPLING(scenarios,'DH_DK_2025')*0.205;
DH_Scenario(scenarios,'2030','DK2_Large')=SAMPLING(scenarios,'DH_DK_2030')*0.189;

DH_Scenario(scenarios,'2020','DK2_Medium')=SAMPLING(scenarios,'DH_DK_2020')*0.049;
*DH_Scenario(scenarios,'2025','DK2_Medium')=SAMPLING(scenarios,'DH_DK_2025')*0.040;
DH_Scenario(scenarios,'2030','DK2_Medium')=SAMPLING(scenarios,'DH_DK_2030')*0.037;

DH_Scenario(scenarios,'2020','DK2_MedSmall')=SAMPLING(scenarios,'DH_DK_2020')*0.020;
*DH_Scenario(scenarios,'2025','DK2_MedSmall')=SAMPLING(scenarios,'DH_DK_2025')*0.016;
DH_Scenario(scenarios,'2030','DK2_MedSmall')=SAMPLING(scenarios,'DH_DK_2030')*0.015;

DH_Scenario(scenarios,'2020','DK2_Rural')=SAMPLING(scenarios,'DH_DK_2020')*0.058;
*DH_Scenario(scenarios,'2025','DK2_Rural')=SAMPLING(scenarios,'DH_DK_2025')*0.047;
DH_Scenario(scenarios,'2030','DK2_Rural')=SAMPLING(scenarios,'DH_DK_2030')*0.043;

DH_Scenario(scenarios,'2020','DK2_Small')=SAMPLING(scenarios,'DH_DK_2020')*0.005;
*DH_Scenario(scenarios,'2025','DK2_Small')=SAMPLING(scenarios,'DH_DK_2025')*0.004;
DH_Scenario(scenarios,'2030','DK2_Small')=SAMPLING(scenarios,'DH_DK_2030')*0.003;

DH_Scenario(scenarios,'2020','DK1_Large')=SAMPLING(scenarios,'DH_DK_2020')*0.267;
*DH_Scenario(scenarios,'2025','DK1_Large')=SAMPLING(scenarios,'DH_DK_2025')*0.216;
DH_Scenario(scenarios,'2030','DK1_Large')=SAMPLING(scenarios,'DH_DK_2030')*0.199;

DH_Scenario(scenarios,'2020','DK1_Medium')=SAMPLING(scenarios,'DH_DK_2020')*0.118;
*DH_Scenario(scenarios,'2025','DK1_Medium')=SAMPLING(scenarios,'DH_DK_2025')*0.096;
DH_Scenario(scenarios,'2030','DK1_Medium')=SAMPLING(scenarios,'DH_DK_2030')*0.088;

DH_Scenario(scenarios,'2020','DK1_MedSmall')=SAMPLING(scenarios,'DH_DK_2020')*0.056;
*DH_Scenario(scenarios,'2025','DK1_MedSmall')=SAMPLING(scenarios,'DH_DK_2025')*0.045;
DH_Scenario(scenarios,'2030','DK1_MedSmall')=SAMPLING(scenarios,'DH_DK_2030')*0.042;

DH_Scenario(scenarios,'2020','DK1_Rural')=SAMPLING(scenarios,'DH_DK_2020')*0.160;
*DH_Scenario(scenarios,'2025','DK1_Rural')=SAMPLING(scenarios,'DH_DK_2025')*0.129;
DH_Scenario(scenarios,'2030','DK1_Rural')=SAMPLING(scenarios,'DH_DK_2030')*0.119;

DH_Scenario(scenarios,'2020','DK1_Small')=SAMPLING(scenarios,'DH_DK_2020')*0.014;
*DH_Scenario(scenarios,'2025','DK1_Small')=SAMPLING(scenarios,'DH_DK_2025')*0.011;
DH_Scenario(scenarios,'2030','DK1_Small')=SAMPLING(scenarios,'DH_DK_2030')*0.010;


