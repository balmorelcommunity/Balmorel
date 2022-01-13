* File HYRSBB123includebb12data.inc for the Balmorel model.
* For use with addon HYRSBB123.

* Data for handling of annual hydro constraints in BB3.
* Supposed to be saved by a previous execution of model BALBASE1 or BALBASE2 (BB1 or BB2).

$ifi %HYRSBB123%==none    $goto label_no_hydro_results_import

execute_load '../../simex/HYRSG.gdx',    HYRSG;
execute_load '../../simex/WATERVAL.gdx', WATERVAL;
execute_load '../../simex/VHYRS_SL.gdx', VHYRS_SL;

* Trim with respect to S for the case that S in the current run is a proper subset of the S used in the import run, for nicety of output only:
HYRSG(Y,AAA,SSS)$(not S(SSS))    = 0;
WATERVAL(Y,AAA,SSS)$(not S(SSS)) = 0;
VHYRS_SL(Y,AAA,SSS)$(not S(SSS)) = 0;
* The indexes Y and IA(AAA) are simply assumed to be the same.

$label label_no_hydro_results_import

*Storage
$ifi not %ADDESTOVOLTS%==none  execute_load  '../../simex/ESTOVOLTS.gdx', ESTOVOLTS;
$ifi not %ADDHSTOVOLTS%==none  execute_load  '../../simex/HSTOVOLTS.gdx', HSTOVOLTS;
$ifi not %ADDESTOVOLTS%==none  execute_load  '../../simex/ESTOVOLTSVAL.gdx', ESTOVOLTSVAL;
$ifi not %ADDHSTOVOLTS%==none  execute_load  '../../simex/HSTOVOLTSVAL.gdx', HSTOVOLTSVAL;
$ifi not %ADDESTOVOLT%==none  execute_load  '../../simex/ESTOVOLT.gdx', ESTOVOLT;
$ifi not %ADDHSTOVOLT%==none  execute_load  '../../simex/HSTOVOLT.gdx', HSTOVOLT;
$ifi not %ADDESTOVOLT%==none  execute_load  '../../simex/ESTOVOLTVAL.gdx', ESTOVOLTVAL;
$ifi not %ADDHSTOVOLT%==none  execute_load  '../../simex/HSTOVOLTVAL.gdx', HSTOVOLTVAL;
$ifi %HYDROGEN%==yes $ifi not %ADDH2STOVOLTS%==none  execute_load  '../../simex/H2STOVOLTS.gdx', H2STOVOLTS;
$ifi %HYDROGEN%==yes $ifi not %ADDH2STOVOLTS%==none  execute_load  '../../simex/H2STOVOLTSVAL.gdx', H2STOVOLTSVAL;
$ifi %HYDROGEN%==yes $ifi not %ADDBIOMETHSTOVOLTS%==none  execute_load  '../../simex/BIOMETHSTOVOLTS.gdx', BIOMETHSTOVOLTS;
$ifi %HYDROGEN%==yes $ifi not %ADDBIOMETHSTOVOLTS%==none  execute_load  '../../simex/BIOMETHSTOVOLTSVAL.gdx', BIOMETHSTOVOLTSVAL;
$ifi %EV%==yes $ifi not %ADDEVSTOS%==none   execute_load  '../../simex/EV_VSOC_BEV.gdx', EV_VSOC_BEV;
$ifi %EV%==yes $ifi not %ADDEVSTOS%==none   execute_load  '../../simex/EV_VSOC_PHEV.gdx', EV_VSOC_PHEV;
$ifi %EV%==yes $ifi not %ADDEVSTOS%==none   execute_load  '../../simex/EV_BEV_NETCHARGING.gdx', EV_BEV_NETCHARGING;
$ifi %EV%==yes $ifi not %ADDEVSTOS%==none   execute_load  '../../simex/EV_PHEV_NETCHARGING.gdx', EV_PHEV_NETCHARGING;


*Investments with/without decommissioning of endogenous capacity
$ifi %ADDTECHDEV%==yes      execute_load  '../../simex/GKACCUMNET.gdx', GKACCUMNET;
$ifi %ADDTRANSDEV%==yes     execute_load  '../../simex/XKACCUMNET.gdx', XKACCUMNET;
$ifi %HEATTRANS%==yes  $ifi %ADDHEATTRANSDEV%==yes execute_load  '../../simex/XHKACCUMNET.gdx', XHKACCUMNET;
$ifi %HYDROGEN%==yes   $ifi %ADDH2TRANSDEV%==yes   execute_load  '../../simex/XH2KACCUMNET.gdx', XH2KACCUMNET;


*Energy dispatch from previous optimization
*$ifi %ADDENERGYDISPATCH%==yes execute_load  '../../simex/DE_T.gdx', DE_T;
*$ifi %ADDENERGYDISPATCH%==yes execute_load  '../../simex/DH_T.gdx', DH_T;
$ifi %ADDENERGYDISPATCH%==yes execute_load  '../../simex/GE_T.gdx', GE_T;
$ifi %ADDENERGYDISPATCH%==yes execute_load  '../../simex/GH_T.gdx', GH_T;
$ifi %ADDENERGYDISPATCH%==yes $ifi %HYDROGEN%==yes  execute_load '../../simex/GH2_T.gdx', GH2_T;
$ifi %ADDENERGYDISPATCH%==yes $ifi %HYDROGEN%==yes  execute_load '../../simex/GBIOMETHANE_T.gdx', GBIOMETHANE_T;
*$ifi %ADDENERGYDISPATCH%==yes execute_load  '../../simex/GF_T.gdx', GF_T;
*$ifi %ADDENERGYDISPATCH%==yes execute_load  '../../simex/ESTOLOADT.gdx', ESTOLOADT;
*$ifi %ADDENERGYDISPATCH%==yes execute_load  '../../simex/ESTOLOADTS.gdx', ESTOLOADTS;
*$ifi %ADDENERGYDISPATCH%==yes execute_load  '../../simex/HSTOLOADT.gdx', HSTOLOADT;
*$ifi %ADDENERGYDISPATCH%==yes execute_load  '../../simex/HSTOLOADTS.gdx', HSTOLOADTS;
*$ifi %ADDENERGYDISPATCH%==yes execute_load  '../../simex/X_T.gdx', X_T;
*$ifi %ADDENERGYDISPATCH%==yes $ifi %HEATTRANS%==yes execute_load  '../../simex/XH_T.gdx', XH_T;
$ifi %ADDENERGYDISPATCH%==yes $ifi %UnitComm%==yes execute_load  '../../simex/UCON.gdx', UCON;
$ifi %ADDENERGYDISPATCH%==yes $ifi %UnitComm%==yes execute_load  '../../simex/UCON_STOLOAD.gdx', UCON_STOLOAD;

*Fuel prices from previous optimization
$ifi %ADDFUELPRICE%==yes execute_load  '../../simex/FUELPRICE_EXC.gdx', FUELPRICE_EXC;

*Import maximum fuel use per season from previous runs
$ifi %ADDMAXFUELUSES%==yes GMAXFS(Y,CCCRRRAAA,FFF,S)=0;
$ifi %ADDMAXFUELUSES%==yes execute_load  '../../simex/GMAXFS.gdx', GMAXFS;

*Import planned maintenance
$ifi %ADDPLANNEDMAINTENANCE%==yes $ifi %UnitComm%==yes execute_load  '../../simex/UCONMAINT.gdx', UCONMAINT;

*Import transport demand
$ifi %ADDTERMTRANSPORTDEMAND%==yes $ifi %transport%==yes execute_load  '../../simex/TRANSDEMAND_T.gdx', TRANSDEMAND_T;
$ifi %ADDSEASONALTRANSPORTDEMAND%==yes $ifi %transport%==yes execute_load  '../../simex/TRANSDEMAND_S.gdx', TRANSDEMAND_S;
$ifi %ADDPEAKTRANSPORTDEMAND%==yes $ifi %transport%==yes execute_load  '../../simex/TRANSDEMAND_T_MAX.gdx', TRANSDEMAND_T_MAX;

*Import Share of heat demand in an individual user group
$ifi %INDIVUSERS%==yes $ifi %GROUP_DEMAND_SHIFT%==yes $ifi %ADDGROUP_DEMAND_SHIFT%==yes  execute_load  '../../simex/INDIVUSERS_GROUPSHARE.gdx', INDIVUSERS_GROUPSHARE;
