* CODE TO CONVERT THE TIMESTEP USED - JUAN GEA BERMUDEZ
* Important note: make sure the full year data is used, otherwise there will be errors in some files

*---------- DATA DEFINITION--------------------
*Possible conversion of timesteps

$setglobal timestep_conversion DaysHours_Hours5min
*!option WeeksHours_DaysHours
*!option WeeksHours_HoursHours
*!option DaysHours_HoursHours
*!option DaysHours_Hours5min

$ifi  %timestep_conversion%==WeeksHours_DaysHours  SET SSS /S01*S52/;
$ifi  %timestep_conversion%==WeeksHours_DaysHours  SET TTT /T001*T168/;
$ifi  %timestep_conversion%==WeeksHours_DaysHours  SET SSS_NEW /S001*S364/;
$ifi  %timestep_conversion%==WeeksHours_DaysHours  SET TTT_NEW /T01*T24/;

$ifi  %timestep_conversion%==WeeksHours_HoursHours  SET SSS /S01*S52/;
$ifi  %timestep_conversion%==WeeksHours_HoursHours  SET TTT /T001*T168/;
$ifi  %timestep_conversion%==WeeksHours_HoursHours  SET SSS_NEW /S0001*S8736/;
$ifi  %timestep_conversion%==WeeksHours_HoursHours  SET TTT_NEW /T01/;

$ifi  %timestep_conversion%==DaysHours_HoursHours  SET SSS /S001*S364/;
$ifi  %timestep_conversion%==DaysHours_HoursHours  SET TTT /T01*T24/;
$ifi  %timestep_conversion%==DaysHours_HoursHours  SET SSS_NEW /S0001*S8736/;
$ifi  %timestep_conversion%==DaysHours_HoursHours  SET TTT_NEW /T01/;

$ifi  %timestep_conversion%==DaysHours_Hours5min  SET SSS /S001*S364/;
$ifi  %timestep_conversion%==DaysHours_Hours5min  SET TTT /T01*T24/;
$ifi  %timestep_conversion%==DaysHours_Hours5min  SET SSS_NEW /S0001*S8736/;
$ifi  %timestep_conversion%==DaysHours_Hours5min  SET TTT_NEW /T01*T12/;

SET ST_LINK(SSS,TTT,SSS_NEW,TTT_NEW);
$ifi  %timestep_conversion%==WeeksHours_DaysHours   $INCLUDE   '../../base/auxils/timestep_conversion/input/ST_LINK_WeeksHours_DaysHours.inc';
$ifi  %timestep_conversion%==WeeksHours_HoursHours  $INCLUDE   '../../base/auxils/timestep_conversion/input/ST_LINK_WeeksHours_HoursHours.inc';
$ifi  %timestep_conversion%==DaysHours_HoursHours   $INCLUDE   '../../base/auxils/timestep_conversion/input/ST_LINK_DaysHours_HoursHours.inc';
$ifi  %timestep_conversion%==DaysHours_Hours5min    $INCLUDE   '../../base/auxils/timestep_conversion/input/ST_LINK_DaysHours_Hours5min.inc';

SET S_LINK(SSS,SSS_NEW);
$ifi  %timestep_conversion%==WeeksHours_DaysHours   $INCLUDE   '../../base/auxils/timestep_conversion/input/S_LINK_WeeksHours_DaysHours.inc';
$ifi  %timestep_conversion%==WeeksHours_HoursHours  $INCLUDE   '../../base/auxils/timestep_conversion/input/S_LINK_WeeksHours_HoursHours.inc';
$ifi  %timestep_conversion%==DaysHours_HoursHours   $INCLUDE   '../../base/auxils/timestep_conversion/input/S_LINK_DaysHours_HoursHours.inc';
$ifi  %timestep_conversion%==DaysHours_Hours5min    $INCLUDE   '../../base/auxils/timestep_conversion/input/S_LINK_DaysHours_Hours5min.inc';


ALIAS(SSS_NEW,ISSS_NEW);
ALIAS(SSS,ISSS);
ALIAS(TTT_NEW,ITTT_NEW);
ALIAS(TTT,ITTT);


SET CCCRRRAAA          "All geographical entities (CCC + RRR + AAA)" ;
$INCLUDE         '../data/CCCRRRAAA.inc';
$include   "../../base/addons/offshoregrid/bb4/offshoregrid_cccrrraaaadditions.inc";
$include   "../../base/addons/industry/bb4/industry_cccrrraaaadditions.inc";

SET CCC       "All regions" ;
$INCLUDE         '../data/CCC.inc';

SET RRR(CCCRRRAAA)       "All regions" ;
$INCLUDE         '../data/RRR.inc';
$include   "../../base/addons/offshoregrid/bb4/offshoregrid_rrradditions.inc";

ALIAS(RRR,IRRR);
ALIAS(RRR,IRRRE);
ALIAS(RRR,IRRRI);

SET AAA(CCCRRRAAA)       "All areas";
$INCLUDE         '../data/AAA.inc';
$include   "../../base/addons/offshoregrid/bb4/offshoregrid_aaaadditions.inc";
$include   "../../base/addons/industry/bb4/industry_aaaadditions.inc";

ALIAS(AAA,IAAA);
ALIAS(AAA,IAAAE);
ALIAS(AAA,IAAAI);

SET GGG          "All generation technologies"   ;
$INCLUDE         '../data/GGG.inc';

SET FFF       "All fuels"
$INCLUDE         '../data/FFF.inc';

SET YYY                "All years" ;
$INCLUDE         '../data/YYY.inc';


SET CATEGORY /COSTS,INCOME,PROFIT/;
SET SUBCATEGORY /ELECTRICITY_SALE,HEAT_SALE,H2_SALE,BIOMETHANE_SALE,GENERATION_CAPITAL_COSTS,GENERATION_FIXED_COSTS,GENERATION_OPERATIONAL_COSTS,GENERATION_FUEL_COSTS,GENERATION_TAXES,GENERATION_GRID_TARIFFS,TRANSMISSION_CAPITAL_COSTS,TRANSMISSION_OPERATIONAL_COSTS,TRANSMISSION_TRADE_INCOME,TRANSMISSION_TRADE_COSTS,HEAT_TRANSMISSION_CAPITAL_COSTS,HEAT_TRANSMISSION_OPERATIONAL_COSTS,GENERATION_CO2_TAX,GENERATION_UC_COSTS,GENERATION_OTHER_EMI_TAX,HYDRO_PROFILE,TAXES,GRID_TARIFFS,TOTAL_PROFIT,ENERGY_SPECIFIC_PROFIT/;
SET COMMODITY /ELECTRICITY,HEAT,HYDROGEN,BIOMETHANE/;
SET TECH_TYPE /CONDENSING,CHP-BACK-PRESSURE,CHP-EXTRACTION,BOILERS,ELECT-TO-HEAT,INTERSEASONAL-HEAT-STORAGE,INTERSEASONAL-ELECT-STORAGE,INTRASEASONAL-HEAT-STORAGE,INTRASEASONAL-ELECT-STORAGE,HYDRO-RESERVOIRS,HYDRO-RUN-OF-RIVER,WIND-ON,WIND-OFF,SOLAR-PV,SOLAR-HEATING,HYDRO-WAVE,HEAT-PUMP,EL-BOILER,FUELCELL,ELECTROLYZER,H2-STORAGE,BIOMETH-DAC,HUB-OFF/;
SET GTECH_TYPE(GGG,TECH_TYPE);
SET PRICE_CATEGORY /AVERAGE,AVERAGE_WEIGHTED_BY_CONSUMPTION,AVERAGE_WEIGHTED_BY_PRODUCTION/;
SET VARIABLE_CATEGORY /EXOGENOUS,ENDOGENOUS,DECOMMISSIONING,ENDOGENOUS_ELECT2HEAT,ENDO_INTRASTO,ENDO_INTERSTO,ENDO_EV,ENDO_HEATPUMP,ENDO_ELBOILER,ENDO_OTHERTRANS,DIST_LOSSES,TRANS_LOSSES,ENDO_CCS,ENDO_H2,ENDO_BIOMETHANE/;
SET EL_BAL_TYPE /CURTAILMENT,NETEXPORT,PRICE,DEMAND_EXO,DEMAND_LOSS,DEMAND_INTERSTO,DEMAND_INTRASTO,DEMAND_P2H,DEMAND_EV,CONDENSING,CHP-BACK-PRESSURE,CHP-EXTRACTION,ELECT-TO-HEAT,INTER-STO,INTRA-STO,HYDRO-RESERVOIRS,HYDRO-RUN-OF-RIVER,WIND-ON,WIND-OFF,SOLAR-PV,HYDRO-WAVE,FUELCELL,DEMAND_OTHERTRANS,DEMAND_DISTLOSSES,DEMAND_CCS,DEMAND_P2G/;
SET H_BAL_TYPE /CURTAILMENT,NETEXPORT,PRICE,DEMAND_EXO,DEMAND_LOSS,DEMAND_INTERSTO,DEMAND_INTRASTO,BOILERS,CHP-BACK-PRESSURE,CHP-EXTRACTION,INTER-STO,INTRA-STO,SOLAR-HEATING,P2H,G2P,DEMAND_P2G,DEMAND_DISTLOSSES/;
SET UNITS /GW,TWh,MWh,Money_per_MWh,Mmoney,kton,GWh/;

PARAMETER WEIGHT_S(SSS)                            "Weight (relative length) of each season"    ;
execute_load  '../../base/auxils/timestep_conversion/input/INPUTDATAOUT.gdx', WEIGHT_S;

PARAMETER WEIGHT_T(TTT)                            "Weight (relative length) of each time period"  ;
execute_load  '../../base/auxils/timestep_conversion/input/INPUTDATAOUT.gdx', WEIGHT_T;

PARAMETER G_CAP_YCRAF(YYY,CCC,RRR,AAA,GGG,FFF,COMMODITY,TECH_TYPE,VARIABLE_CATEGORY,UNITS) "Generation capacity for each year, country, region, area, technology, fuel, commodity, technology type and variable type (GW)";
execute_load  '../../base/auxils/timestep_conversion/input/MainResults.gdx', G_CAP_YCRAF;
PARAMETER G_STO_YCRAF(YYY,CCC,RRR,AAA,GGG,FFF,COMMODITY,TECH_TYPE,VARIABLE_CATEGORY,UNITS) "Generation storage for each year, country, region, area, technology, fuel, commodity, technology type and variable type (GWh)";
execute_load  '../../base/auxils/timestep_conversion/input/MainResults.gdx', G_STO_YCRAF;
PARAMETER PRO_YCRAGFST(YYY,CCC,RRR,AAA,GGG,FFF,SSS,TTT,COMMODITY,TECH_TYPE,UNITS) "Energy Production for each year, country, region, area, technology, fuel, season, hour, commodity and technology type (MWh)" ;
execute_load  '../../base/auxils/timestep_conversion/input/MainResults.gdx', PRO_YCRAGFST;
PARAMETER PRO_YCRAGF(YYY,CCC,RRR,AAA,GGG,FFF,COMMODITY,TECH_TYPE,UNITS) "Annual Energy Production for each year, country, region, area, technology, fuel, commodity and technology type (TWh)";
execute_load  '../../base/auxils/timestep_conversion/input/MainResults.gdx', PRO_YCRAGF;
PARAMETER F_CONS_YCRAST(YYY,CCC,RRR,AAA,GGG,FFF,SSS,TTT,TECH_TYPE,UNITS) "Fuel consumption for each year, country, region, area, technology, fuel, season, hour and technology type (MWh)";
execute_load  '../../base/auxils/timestep_conversion/input/MainResults.gdx', F_CONS_YCRAST;
PARAMETER F_CONS_YCRA(YYY,CCC,RRR,AAA,GGG,FFF,TECH_TYPE,UNITS) "Fuel consumption for each year, country, region, area, technology, fuel and technology type (TWh)";
execute_load  '../../base/auxils/timestep_conversion/input/MainResults.gdx', F_CONS_YCRA;
PARAMETER X_CAP_YCR(YYY,CCC,IRRRE,IRRRI,VARIABLE_CATEGORY,UNITS) "Transmission capacity for each year, country, from region to region (GW)";
execute_load  '../../base/auxils/timestep_conversion/input/MainResults.gdx', X_CAP_YCR;
PARAMETER X_FLOW_YCRST(YYY,CCC,IRRRE,IRRRI,SSS,TTT,UNITS) "Transmission flow for each year, country, from region to region, for each season and hour (MWh)";
execute_load  '../../base/auxils/timestep_conversion/input/MainResults.gdx', X_FLOW_YCRST;
PARAMETER X_FLOW_YCR(YYY,CCC,IRRRE,IRRRI,UNITS) "Transmission flow for each year, country, from region to region (TWh)";
execute_load  '../../base/auxils/timestep_conversion/input/MainResults.gdx', X_FLOW_YCR;
PARAMETER ECO_G_YCRAG(YYY,CCC,RRR,AAA,GGG,FFF,TECH_TYPE,CATEGORY,SUBCATEGORY,UNITS) "Generation Economic Output for each year, country, region, fuel, technology type, area and technology (Mmoney)";
execute_load  '../../base/auxils/timestep_conversion/input/MainResults.gdx', ECO_G_YCRAG;
PARAMETER ECO_X_YCR(YYY,CCC,RRR,CATEGORY,SUBCATEGORY,UNITS) "Electric Transmission Economic Output for each year, country and region (Mmoney)";
execute_load  '../../base/auxils/timestep_conversion/input/MainResults.gdx', ECO_X_YCR;
PARAMETER OBJ_YCR(YYY,CCC,RRR,SUBCATEGORY,UNITS) "Objective function (Mmoney)";
execute_load  '../../base/auxils/timestep_conversion/input/MainResults.gdx', OBJ_YCR;
PARAMETER EL_PRICE_YCR(YYY,CCC,RRR,PRICE_CATEGORY,UNITS) "Average Electricity Prices for each region (money/MWh)";
execute_load  '../../base/auxils/timestep_conversion/input/MainResults.gdx', EL_PRICE_YCR;
PARAMETER EL_PRICE_YCRST(YYY,CCC,RRR,SSS,TTT,UNITS) "Hourly Electricity Prices for each region (money/MWh)";
execute_load  '../../base/auxils/timestep_conversion/input/MainResults.gdx', EL_PRICE_YCRST;
PARAMETER H_PRICE_YCRA(YYY,CCC,RRR,AAA,PRICE_CATEGORY,UNITS) "Average heating Prices for each area(money/MWh)";
execute_load  '../../base/auxils/timestep_conversion/input/MainResults.gdx', H_PRICE_YCRA;
PARAMETER H_PRICE_YCRAST(YYY,CCC,RRR,AAA,SSS,TTT,UNITS) "Hourly heating Prices for each area (money(MWh)";
execute_load  '../../base/auxils/timestep_conversion/input/MainResults.gdx', H_PRICE_YCRAST;
PARAMETER EL_DEMAND_YCRST(YYY,CCC,RRR,SSS,TTT,VARIABLE_CATEGORY,UNITS) "Aggregated Hourly Electricity Demand (MWh)";
execute_load  '../../base/auxils/timestep_conversion/input/MainResults.gdx', EL_DEMAND_YCRST;
PARAMETER EL_DEMAND_YCR(YYY,CCC,RRR,VARIABLE_CATEGORY,UNITS) "Aggregated annual Electricity Demand (TWh)";
execute_load  '../../base/auxils/timestep_conversion/input/MainResults.gdx', EL_DEMAND_YCR;
PARAMETER H_DEMAND_YCRAST(YYY,CCC,RRR,AAA,SSS,TTT,VARIABLE_CATEGORY,UNITS) "Aggregated Hourly heat Demand (MWh)";
execute_load  '../../base/auxils/timestep_conversion/input/MainResults.gdx', H_DEMAND_YCRAST;
PARAMETER H_DEMAND_YCRA(YYY,CCC,RRR,AAA,VARIABLE_CATEGORY,UNITS) "Aggregated Annual heat Demand (MWh)";
execute_load  '../../base/auxils/timestep_conversion/input/MainResults.gdx', H_DEMAND_YCRA;
PARAMETER EMI_YCRAG(YYY,CCC,RRR,AAA,GGG,FFF,TECH_TYPE,UNITS) "Annual CO2 emissions(ktons)";
execute_load  '../../base/auxils/timestep_conversion/input/MainResults.gdx', EMI_YCRAG;
PARAMETER CURT_YCRAGFST(YYY,CCC,RRR,AAA,GGG,FFF,SSS,TTT,COMMODITY,TECH_TYPE,UNITS) "Hourly energy curtailment per country, region, area, technology, fuel, hour and technology type (MWh)";
execute_load  '../../base/auxils/timestep_conversion/input/MainResults.gdx', CURT_YCRAGFST;
PARAMETER CURT_YCRAGF(YYY,CCC,RRR,AAA,GGG,FFF,COMMODITY,TECH_TYPE,UNITS) "Hourly energy curtailment per country, region, area, technology, fuel, hour and technology type (MWh)";
execute_load  '../../base/auxils/timestep_conversion/input/MainResults.gdx', CURT_YCRAGF;
PARAMETER EL_BALANCE_YCRST(YYY,CCC,RRR,EL_BAL_TYPE,SSS,TTT,UNITS);
execute_load  '../../base/auxils/timestep_conversion/input/MainResults.gdx', EL_BALANCE_YCRST;
PARAMETER H_BALANCE_YCRAST(YYY,CCC,RRR,AAA,H_BAL_TYPE,SSS,TTT,UNITS);
execute_load  '../../base/auxils/timestep_conversion/input/MainResults.gdx', H_BALANCE_YCRAST;
PARAMETER XH_CAP_YCA(YYY,CCC,IAAAE,IAAAI,VARIABLE_CATEGORY,UNITS) "Heat Transmission capacity for each year, country, from area to area (GW)";
execute_load  '../../base/auxils/timestep_conversion/input/MainResults.gdx', XH_CAP_YCA;
PARAMETER XH_FLOW_YCAST(YYY,CCC,IAAAE,IAAAI,SSS,TTT,UNITS) "Heat Transmission flow for each year, country, from areas to area, for each season and hour (MWh)";
execute_load  '../../base/auxils/timestep_conversion/input/MainResults.gdx', XH_FLOW_YCAST;
PARAMETER XH_FLOW_YCA(YYY,CCC,IAAAE,IAAAI,UNITS) "Heat Transmission flow for each year, country, from area to area (TWh)";
execute_load  '../../base/auxils/timestep_conversion/input/MainResults.gdx', XH_FLOW_YCA;
PARAMETER ECO_XH_YCRA(YYY,CCC,RRR,AAA,CATEGORY,SUBCATEGORY,UNITS) "Heat Transmission Economic Output for each year, country and region and area (Mmoney)";
execute_load  '../../base/auxils/timestep_conversion/input/MainResults.gdx', ECO_XH_YCRA;
PARAMETER H2_PRICE_YCRST(YYY,CCC,RRR,SSS,TTT,UNITS) "Hourly hydrogen Prices for each region (money/MWh)";
execute_load  '../../base/auxils/timestep_conversion/input/MainResults.gdx', H2_PRICE_YCRST;
PARAMETER  BIOMETH_PRICE_YST(Y,SSS,TTT,UNITS) "Hourly biomethane Prices for each region (money/MWh)";
execute_load  '../../base/auxils/timestep_conversion/input/MainResults.gdx', BIOMETH_PRICE_YST;

*New timeseries
PARAMETER WEIGHT_S_NEW(SSS_NEW)                            "Weight (relative length) of each season"    ;
PARAMETER WEIGHT_T_NEW(TTT_NEW)                            "Weight (relative length) of each time period" ;
PARAMETER PRO_YCRAGFST_NEW(YYY,CCC,RRR,AAA,GGG,FFF,SSS_NEW,TTT_NEW,COMMODITY,TECH_TYPE,UNITS) "Energy Production for each year, country, region, area, technology, fuel, season, hour, commodity and technology type (MWh)" ;
PARAMETER F_CONS_YCRAST_NEW(YYY,CCC,RRR,AAA,GGG,FFF,SSS_NEW,TTT_NEW,TECH_TYPE,UNITS) "Fuel consumption for each year, country, region, area, technology, fuel, season, hour and technology type (MWh)";
PARAMETER X_FLOW_YCRST_NEW(YYY,CCC,IRRRE,IRRRI,SSS_NEW,TTT_NEW,UNITS) "Transmission flow for each year, country, from region to region, for each season and hour (MWh)";
PARAMETER EL_PRICE_YCRST_NEW(YYY,CCC,RRR,SSS_NEW,TTT_NEW,UNITS) "Hourly Electricity Prices for each region (money/MWh)";
PARAMETER H_PRICE_YCRAST_NEW(YYY,CCC,RRR,AAA,SSS_NEW,TTT_NEW,UNITS) "Hourly heating Prices for each area (money(MWh)";
PARAMETER EL_DEMAND_YCRST_NEW(YYY,CCC,RRR,SSS_NEW,TTT_NEW,VARIABLE_CATEGORY,UNITS) "Aggregated Hourly Electricity Demand (MWh)";
PARAMETER H_DEMAND_YCRAST_NEW(YYY,CCC,RRR,AAA,SSS_NEW,TTT_NEW,VARIABLE_CATEGORY,UNITS) "Aggregated Hourly heat Demand (MWh)";
PARAMETER CURT_YCRAGFST_NEW(YYY,CCC,RRR,AAA,GGG,FFF,SSS_NEW,TTT_NEW,COMMODITY,TECH_TYPE,UNITS) "Hourly energy curtailment per country, region, area, technology, fuel, hour and technology type (MWh)";
PARAMETER EL_BALANCE_YCRST_NEW(YYY,CCC,RRR,EL_BAL_TYPE,SSS_NEW,TTT_NEW,UNITS);
PARAMETER H_BALANCE_YCRAST_NEW(YYY,CCC,RRR,AAA,H_BAL_TYPE,SSS_NEW,TTT_NEW,UNITS);
PARAMETER XH_FLOW_YCAST_NEW(YYY,CCC,IAAAE,IAAAI,SSS_NEW,TTT_NEW,UNITS) "Heat Transmission flow for each year, country, from areas to area, for each season and hour (MWh)";
PARAMETER H2_PRICE_YCRST_NEW(YYY,CCC,RRR,SSS_NEW,TTT_NEW,UNITS) "Hourly hydrogen Prices for each region (money/MWh)";
PARAMETER  BIOMETH_PRICE_YST_NEW(Y,SSS,TTT,UNITS) "Hourly biomethane Prices for each region (money/MWh)";
*----------END OF INPUT DATA--------------------


*------------CALCULATIONS-------------
$ifi  NOT %timestep_conversion%==WeeksHours_DaysHours   $goto No_WeeksHours_DaysHours
WEIGHT_S_NEW(SSS_NEW)=24;
WEIGHT_T_NEW(TTT_NEW)=1;
$label No_WeeksHours_DaysHours

$ifi  NOT %timestep_conversion%==WeeksHours_HoursHours   $goto No_WeeksHours_HoursHours
WEIGHT_S_NEW(SSS_NEW)=1;
WEIGHT_T_NEW(TTT_NEW)=1;
$label No_WeeksHours_HoursHours

$ifi  NOT %timestep_conversion%==DaysHours_HoursHours   $goto No_DaysHours_HoursHours
WEIGHT_S_NEW(SSS_NEW)=1;
WEIGHT_T_NEW(TTT_NEW)=1;
$label No_DaysHours_HoursHours

$ifi  NOT %timestep_conversion%==DaysHours_Hours5min   $goto No_DaysHours_Hours5min
WEIGHT_S_NEW(SSS_NEW)=1;
WEIGHT_T_NEW(TTT_NEW)=1/12;
$label No_DaysHours_Hours5min

PRO_YCRAGFST_NEW(YYY,CCC,RRR,AAA,GGG,FFF,SSS_NEW,TTT_NEW,COMMODITY,TECH_TYPE,UNITS)=SUM((SSS,TTT)$ST_LINK(SSS,TTT,SSS_NEW,TTT_NEW),PRO_YCRAGFST(YYY,CCC,RRR,AAA,GGG,FFF,SSS,TTT,COMMODITY,TECH_TYPE,UNITS));
F_CONS_YCRAST_NEW(YYY,CCC,RRR,AAA,GGG,FFF,SSS_NEW,TTT_NEW,TECH_TYPE,UNITS)=SUM((SSS,TTT)$ST_LINK(SSS,TTT,SSS_NEW,TTT_NEW),F_CONS_YCRAST(YYY,CCC,RRR,AAA,GGG,FFF,SSS,TTT,TECH_TYPE,UNITS));
X_FLOW_YCRST_NEW(YYY,CCC,IRRRE,IRRRI,SSS_NEW,TTT_NEW,UNITS)=SUM((SSS,TTT)$ST_LINK(SSS,TTT,SSS_NEW,TTT_NEW),X_FLOW_YCRST(YYY,CCC,IRRRE,IRRRI,SSS,TTT,UNITS));
EL_PRICE_YCRST_NEW(YYY,CCC,RRR,SSS_NEW,TTT_NEW,UNITS)=SUM((SSS,TTT)$ST_LINK(SSS,TTT,SSS_NEW,TTT_NEW),EL_PRICE_YCRST(YYY,CCC,RRR,SSS,TTT,UNITS))*WEIGHT_T_NEW(TTT_NEW);
H_PRICE_YCRAST_NEW(YYY,CCC,RRR,AAA,SSS_NEW,TTT_NEW,UNITS)=SUM((SSS,TTT)$ST_LINK(SSS,TTT,SSS_NEW,TTT_NEW),H_PRICE_YCRAST(YYY,CCC,RRR,AAA,SSS,TTT,UNITS))*WEIGHT_T_NEW(TTT_NEW);
EL_DEMAND_YCRST_NEW(YYY,CCC,RRR,SSS_NEW,TTT_NEW,VARIABLE_CATEGORY,UNITS)=SUM((SSS,TTT)$ST_LINK(SSS,TTT,SSS_NEW,TTT_NEW),EL_DEMAND_YCRST(YYY,CCC,RRR,SSS,TTT,VARIABLE_CATEGORY,UNITS));
H_DEMAND_YCRAST_NEW(YYY,CCC,RRR,AAA,SSS_NEW,TTT_NEW,VARIABLE_CATEGORY,UNITS)=SUM((SSS,TTT)$ST_LINK(SSS,TTT,SSS_NEW,TTT_NEW),H_DEMAND_YCRAST(YYY,CCC,RRR,AAA,SSS,TTT,VARIABLE_CATEGORY,UNITS));
CURT_YCRAGFST_NEW(YYY,CCC,RRR,AAA,GGG,FFF,SSS_NEW,TTT_NEW,COMMODITY,TECH_TYPE,UNITS)=SUM((SSS,TTT)$ST_LINK(SSS,TTT,SSS_NEW,TTT_NEW),CURT_YCRAGFST(YYY,CCC,RRR,AAA,GGG,FFF,SSS,TTT,COMMODITY,TECH_TYPE,UNITS));
EL_BALANCE_YCRST_NEW(YYY,CCC,RRR,EL_BAL_TYPE,SSS_NEW,TTT_NEW,UNITS)=SUM((SSS,TTT)$ST_LINK(SSS,TTT,SSS_NEW,TTT_NEW),EL_BALANCE_YCRST(YYY,CCC,RRR,EL_BAL_TYPE,SSS,TTT,UNITS));
EL_BALANCE_YCRST_NEW(YYY,CCC,RRR,'PRICE',SSS_NEW,TTT_NEW,UNITS)=EL_BALANCE_YCRST_NEW(YYY,CCC,RRR,'PRICE',SSS_NEW,TTT_NEW,UNITS)*WEIGHT_T_NEW(TTT_NEW);
H_BALANCE_YCRAST_NEW(YYY,CCC,RRR,AAA,H_BAL_TYPE,SSS_NEW,TTT_NEW,UNITS)=SUM((SSS,TTT)$ST_LINK(SSS,TTT,SSS_NEW,TTT_NEW),H_BALANCE_YCRAST(YYY,CCC,RRR,AAA,H_BAL_TYPE,SSS,TTT,UNITS));
H_BALANCE_YCRAST_NEW(YYY,CCC,RRR,AAA,'PRICE',SSS_NEW,TTT_NEW,UNITS)=H_BALANCE_YCRAST_NEW(YYY,CCC,RRR,AAA,'PRICE',SSS_NEW,TTT_NEW,UNITS)*WEIGHT_T_NEW(TTT_NEW);
XH_FLOW_YCAST_NEW(YYY,CCC,IAAAE,IAAAI,SSS_NEW,TTT_NEW,UNITS)=SUM((SSS,TTT)$ST_LINK(SSS,TTT,SSS_NEW,TTT_NEW),XH_FLOW_YCAST(YYY,CCC,IAAAE,IAAAI,SSS,TTT,UNITS));
H2_PRICE_YCRST_NEW(YYY,CCC,RRR,SSS_NEW,TTT_NEW,UNITS)=SUM((SSS,TTT)$ST_LINK(SSS,TTT,SSS_NEW,TTT_NEW),H2_PRICE_YCRST(YYY,CCC,RRR,SSS,TTT,UNITS))*WEIGHT_T_NEW(TTT_NEW);
BIOMETH_PRICE_YCRST_NEW(YYY,SSS_NEW,TTT_NEW,UNITS)=SUM((SSS,TTT)$ST_LINK(SSS,TTT,SSS_NEW,TTT_NEW),BIOMETH_PRICE_YCRST(YYY,SSS,TTT,UNITS))*WEIGHT_T_NEW(TTT_NEW);
*------------END OF CALCULATIONS-------------





*------------OUTPUT GENERATION-------------

execute_unload "../../base/auxils/timestep_conversion/output/MainResults.gdx"
ECO_G_YCRAG,
ECO_X_YCR,
OBJ_YCR,
EL_PRICE_YCR,
EL_PRICE_YCRST_NEW=EL_PRICE_YCRST,
PRO_YCRAGFST_NEW=PRO_YCRAGFST,
EL_DEMAND_YCRST_NEW=EL_DEMAND_YCRST,
EL_DEMAND_YCR,
H_DEMAND_YCRAST_NEW=H_DEMAND_YCRAST,
H_DEMAND_YCRA,
PRO_YCRAGF,
H_PRICE_YCRAST_NEW=H_PRICE_YCRAST,
H_PRICE_YCRA,
G_CAP_YCRAF,
G_STO_YCRAF,
X_CAP_YCR,
X_FLOW_YCRST_NEW=X_FLOW_YCRST,
X_FLOW_YCR,
F_CONS_YCRAST_NEW=F_CONS_YCRAST,
F_CONS_YCRA,
EMI_YCRAG,
EL_BALANCE_YCRST_NEW=EL_BALANCE_YCRST,
CURT_YCRAGFST_NEW=CURT_YCRAGFST,
CURT_YCRAGF,
H_BALANCE_YCRAST_NEW=H_BALANCE_YCRAST
XH_CAP_YCA,
XH_FLOW_YCAST_NEW=XH_FLOW_YCAST,
XH_FLOW_YCA,
H2_PRICE_YCRST_NEW=H2_PRICE_YCRST,
BIOMETH_PRICE_YCRST_NEW=BIOMETH_PRICE_YCRST,
ECO_XH_YCRA

;

*------------END OF OUTPUT GENERATION-------------

