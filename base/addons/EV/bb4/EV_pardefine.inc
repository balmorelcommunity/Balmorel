* Total BEVs
PARAMETER EV_BEV_available(YYY,RRR);
$if     EXIST '../data/EV_BEV_available.inc' $INCLUDE         '../data/EV_BEV_available.inc';
$if not EXIST '../data/EV_BEV_available.inc' $INCLUDE '../../base/data/EV_BEV_available.inc';

* Total PHEVs
PARAMETER EV_PHEV_available(YYY,RRR);
$if     EXIST '../data/EV_PHEV_available.inc' $INCLUDE         '../data/EV_PHEV_available.inc';
$if not EXIST '../data/EV_PHEV_available.inc' $INCLUDE '../../base/data/EV_PHEV_available.inc';

* Percentage of BEV fleet is dumb charging
PARAMETER EV_BEV_dumb(YYY,RRR);
$if     EXIST '../data/EV_BEV_dumb.inc' $INCLUDE         '../data/EV_BEV_dumb.inc';
$if not EXIST '../data/EV_BEV_dumb.inc' $INCLUDE '../../base/data/EV_BEV_dumb.inc';

* Percentage of PHEV fleet is dumb charging
PARAMETER EV_PHEV_dumb(YYY,RRR);
$if     EXIST '../data/EV_PHEV_dumb.inc' $INCLUDE         '../data/EV_PHEV_dumb.inc';
$if not EXIST '../data/EV_PHEV_dumb.inc' $INCLUDE '../../base/data/EV_PHEV_dumb.inc';

* If INTERSEASONAL use INTERSEASONAL data
$ifi %EV_allreturn%==yes $goto allreturn

$if     EXIST '../data/EV_TECH_DATA.inc' $INCLUDE         '../data/EV_TECH_DATA.inc';
$if not EXIST '../data/EV_TECH_DATA.inc' $INCLUDE '../../base/data/EV_TECH_DATA.inc';


* If using scenario that all EVs return after usage OR not INTERSEASONAL
$label allreturn
$ifi not %EV_allreturn%==yes $goto NO_allreturn

$if     EXIST '../data/EV_TECH_DATA_allreturn.inc' $INCLUDE         '../data/EV_TECH_DATA_allreturn.inc';
$if not EXIST '../data/EV_TECH_DATA_allreturn.inc' $INCLUDE '../../base/data/EV_TECH_DATA_allreturn.inc';

PARAMETER EV_BEV_return_energy(TTT,RRR);
$if     EXIST '../data/EV_BEV_return_energy.inc' $INCLUDE         '../data/EV_BEV_return_energy.inc';
$if not EXIST '../data/EV_BEV_return_energy.inc' $INCLUDE '../../base/data/EV_BEV_return_energy.inc';

$label NO_allreturn

* Select profile by setting. See Balopt.
* Percentage of BEV fleet is connecting to grid
PARAMETER EV_BEV_return_profile(YYY,SSS,TTT,RRR);
$if     EXIST '../data/EV_BEV_return_%EV_profile%.inc' $INCLUDE         '../data/EV_BEV_return_%EV_profile%.inc'
$if not EXIST '../data/EV_BEV_return_%EV_profile%.inc' $INCLUDE '../../base/data/EV_BEV_return_%EV_profile%.inc'

$if %EV_profile% == profile3
    EV_BEV_return_profile(YYY,SSS,TTT,RRR) = EV_BEV_return_profile(YYY,SSS,TTT,RRR) * 0.6;

* Percentage of BEV fleet is disconnecting from grid
PARAMETER EV_BEV_leave_profile(YYY,SSS,TTT,RRR);
$if     EXIST '../data/EV_BEV_leave_%EV_profile%.inc' $INCLUDE         '../data/EV_BEV_leave_%EV_profile%.inc'
$if not EXIST '../data/EV_BEV_leave_%EV_profile%.inc' $INCLUDE '../../base/data/EV_BEV_leave_%EV_profile%.inc'

$if %EV_profile% == profile3
    EV_BEV_leave_profile(YYY,SSS,TTT,RRR) = EV_BEV_leave_profile(YYY,SSS,TTT,RRR) * 0.6;
    
* NOTE: Currently no profiles made for PHEV, using a BEV profile that is not based on assumptions for PHEV. PHEV available is set to 0, so its not using this.
* The option is here for the day there is data, and the model is made to include this.
* Percentage of PHEV fleet is connecting to grid
PARAMETER EV_PHEV_return_profile(YYY,SSS,TTT,RRR);
$if     EXIST '../data/EV_PHEV_return_profile1.inc' $INCLUDE         '../data/EV_PHEV_return_profile1.inc';
$if not EXIST '../data/EV_PHEV_return_profile1.inc' $INCLUDE '../../base/data/EV_PHEV_return_profile1.inc';

* Percentage of PHEV fleet is disconnecting from grid
PARAMETER EV_PHEV_leave_profile(YYY,SSS,TTT,RRR);
$if     EXIST '../data/EV_PHEV_leave_profile1.inc' $INCLUDE         '../data/EV_PHEV_leave_profile1.inc';
$if not EXIST '../data/EV_PHEV_leave_profile1.inc' $INCLUDE '../../base/data/EV_PHEV_leave_profile1.inc';


* import_results parameters
PARAMETER   EV_BE_BEV(YYY,RRR,SSS,TTT)        'State of charge of the BEV vehicle fleet to be used in future runs';
PARAMETER   EV_BE_PHEV(YYY,RRR,SSS,TTT)       'State of charge of the PHEV vehicle fleet to be used in future runs';
PARAMETER   EV_BEV_NETCHARGING(YYY,RRR,SSS,TTT)        'Net charging of BEV vehicle fleet to be used in future runs';
PARAMETER   EV_PHEV_NETCHARGING(YYY,RRR,SSS,TTT)      'Net charging of PHEV vehicle fleet to be used in future runs';