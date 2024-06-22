$SETGLOBAL format prn



put        file_e_rev        ;
Put "Generator revenue from electricity generation Mio OMONEY"/;
$libinclude gams2tbl e_rev

put        file_h_rev        ;
Put "Generator revenue from heat generation"/;
$libinclude gams2tbl h_rev

put        file_fxcost        ;
Put "Generator fixed costs"/;
$libinclude gams2tbl fxcost

put        file_fuelcost        ;
Put "Generator fuel costs"/;
$libinclude gams2tbl fuelcost

put        file_vcost        ;
Put "Generator variable costs"/;
$libinclude gams2tbl vcost
*Erkki
put        file_UCstartcost       ;
Put "Generator start-up costs"/;
$libinclude gams2tbl UCstartcost

put        file_UCshutcost       ;
Put "Generator shut-down costs"/;
$libinclude gams2tbl UCshutcost

put        file_UCfixedcost       ;
Put "Generator fixed UC costs"/;
$libinclude gams2tbl UCfixedcost
*Erkki
put        file_capcost_ex        ;
Put "Generator total capital costs - exogenous units"/;
$libinclude gams2tbl capcost_ex

put        file_capcost_en        ;
Put "Generator total capital costs - endogenous units"/;
$libinclude gams2tbl capcost_en

put        file_capcost_trans_ex        ;
Put "Transmission total capital costs - exogenous units"/;
$libinclude gams2tbl capcost_trans_ex

put        file_capcost_trans_en        ;
Put "Transmission total capital costs - endogenous units"/;
$libinclude gams2tbl capcost_trans_en

put        file_co2cost        ;
Put "Value of CO2 emissions"/;
$libinclude gams2tbl co2cost

put        file_so2cost        ;
Put "Value of SO2 emissions"/;
$libinclude gams2tbl so2cost

put        file_noxcost        ;
Put "Value of NOx emissions"/;
$libinclude gams2tbl noxcost

put        file_fueltax        ;
Put "Value of fuel taxes"/;
$libinclude gams2tbl fueltax

put        file_heattaxGH        ;
Put "Value of heat taxes on units"/;
$libinclude gams2tbl heattax_GH

put        file_vindSubsidy        ;
Put "Value of vind subsidies"/;
$libinclude gams2tbl vindSubsidy

put        file_e_cost        ;
Put "Consumer electricity costs"/;
$libinclude gams2tbl e_cost

put        file_h_cost        ;
Put "Consumer heating costs"/;
$libinclude gams2tbl h_cost

put        file_e_util        ;
Put "Consumer utility of electricity consumption"/;
$libinclude gams2tbl e_util

put        file_h_util        ;
Put "Consumer utility heat consumption"/;
$libinclude gams2tbl h_util

put        file_bottleneck        ;
Put "TSO bottleneck income net of transmission losses"/;
$libinclude gams2tbl bottleneck

put        file_tradesurp        ;
Put "Trade value of exogenous imports from 3rd countries"/;
$libinclude gams2tbl tradesurp

put        file_transcost        ;
Put "Transmission variable costs"/;
$libinclude gams2tbl transcost

put        file_watervaluevar        ;
Put "Seasonal calibration value of water"/;
$libinclude gams2tbl watervaluevar


put        file_watervalue        ;
Put "Water value transfered and used"/;
$libinclude gams2tbl watervalue

put        file_NOxemission        ;
Put "NOx emissions (mio tonnes)"/;
$libinclude gams2tbl NOxemission

put        file_SO2emission        ;
Put "SO2 emissions (mio tonnes)"/;
$libinclude gams2tbl SO2emission

put        file_CO2shadowval        ;
Put "Shadow value of CO2 constraint"/;
$libinclude gams2tbl CO2shadowval

put        file_VEShadowval        ;
Put "Shadow value of VE constraint"/;
$libinclude gams2tbl VEShadowval

put        file_Fosshadowval        ;
Put "Shadow value of fossil fuel constraint"/;
$libinclude gams2tbl Fosshadowval

put        file_e_tax        ;
Put "Consumer tax on electricity"/;
$libinclude gams2tbl e_tax

put        file_h_tax        ;
Put "Consumer tax on heat"/;
$libinclude gams2tbl h_tax

put        file_dist_e        ;
Put "Electricity distribution costs"/;
$libinclude gams2tbl dist_e

put        file_dist_h        ;
Put "Heat distribution costs"/;
$libinclude gams2tbl dist_h

*Erkki
$ontext
put        file_reacEf        ;
Put "Base load services"/;
$libinclude gams2tbl reacEf
$offtext
*Erkki



*-------------------------------------------------------------------------------
* Add output for addon modules. It is best if addon code is in include files.
*-------------------------------------------------------------------------------

$ifi %H2%==yes $include '../../base/addons/Hydrogen/compare/hymkcompare.inc';
$ifi %transport%==yes $include '../../base/addons/transport/compare/trmkcompare.inc';


