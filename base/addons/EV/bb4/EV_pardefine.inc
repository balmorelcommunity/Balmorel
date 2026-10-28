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

* Charging infrastructure costs and lifetime
$if     EXIST '../data/EV_INFRA_DATA.inc' $INCLUDE         '../data/EV_INFRA_DATA.inc';
$if not EXIST '../data/EV_INFRA_DATA.inc' $INCLUDE '../../base/data/EV_INFRA_DATA.inc';
SCALAR EV_G2V_INFRA_MARGIN 'G2V infrastructure is built this much above the peak charging seen in the investment run (fraction)' /0.05/;

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

* Regions without Monte Carlo profiles of their own can use another region's: EV_PROFILE_PROXY(region, source),
* set in the optional data file EV_PROFILE_PROXY.inc. Copied before the year-edge fix below, which then covers them too.
SET EV_PROFILE_PROXY(RRR,RRR) 'Region (first) uses the EV profiles of region (second)';
EV_PROFILE_PROXY(RRR,IRRRE) = NO;
$if     EXIST '../data/EV_PROFILE_PROXY.inc' $INCLUDE         '../data/EV_PROFILE_PROXY.inc';
$if not EXIST '../data/EV_PROFILE_PROXY.inc' $if EXIST '../../base/data/EV_PROFILE_PROXY.inc' $INCLUDE '../../base/data/EV_PROFILE_PROXY.inc';
LOOP((RRR,IRRRE)$EV_PROFILE_PROXY(RRR,IRRRE),
    EV_BEV_return_profile(YYY,SSS,TTT,RRR)  = EV_BEV_return_profile(YYY,SSS,TTT,IRRRE);
    EV_BEV_leave_profile(YYY,SSS,TTT,RRR)   = EV_BEV_leave_profile(YYY,SSS,TTT,IRRRE);
    EV_PHEV_return_profile(YYY,SSS,TTT,RRR) = EV_PHEV_return_profile(YYY,SSS,TTT,IRRRE);
    EV_PHEV_leave_profile(YYY,SSS,TTT,RRR)  = EV_PHEV_leave_profile(YYY,SSS,TTT,IRRRE);
$ifi %EV_allreturn%==yes    EV_BEV_return_energy(TTT,RRR) = EV_BEV_return_energy(TTT,IRRRE);
);

* The Monte Carlo profiles simulate a closed year: every EV starts S01/T001 and ends S52/T168 on the charger
* (Balanza et al., Appendix D), so S01 holds a start-up transient (~2x the weekly driving energy) and S52 a return spike.
* That only cancels out when all 52 weeks are simulated and linked. For representative weeks, intra-seasonal weeks
* or rolling windows, give the two edge weeks the profile of their neighbour week.
* The year must then also start from the share of the fleet that the original S01 transient leaves on the charger,
* not from the whole fleet, or availability stays at ~100 % all year. EV_ipardecdef.inc scales the start by these shares.
PARAMETER EV_BEV_start_share(YYY,RRR)  'Share of the BEV fleet on the charger at S01/T001 (1 = whole fleet)'
          EV_PHEV_start_share(YYY,RRR) 'Share of the PHEV fleet on the charger at S01/T001 (1 = whole fleet)';
EV_BEV_start_share(YYY,RRR)  = 1;
EV_PHEV_start_share(YYY,RRR) = 1;
$ifi not %EV_fix_year_edges%==yes $goto NO_EV_fix_year_edges
EV_BEV_start_share(YYY,RRR)$SUM(TTT, EV_BEV_return_profile(YYY,'S01',TTT,RRR))
    = MIN(1, MAX(0, 1 + SUM(TTT, EV_BEV_return_profile(YYY,'S01',TTT,RRR) + EV_BEV_leave_profile(YYY,'S01',TTT,RRR))));
EV_PHEV_start_share(YYY,RRR)$SUM(TTT, EV_PHEV_return_profile(YYY,'S01',TTT,RRR))
    = MIN(1, MAX(0, 1 + SUM(TTT, EV_PHEV_return_profile(YYY,'S01',TTT,RRR) + EV_PHEV_leave_profile(YYY,'S01',TTT,RRR))));
EV_BEV_return_profile(YYY,'S01',TTT,RRR)  = EV_BEV_return_profile(YYY,'S02',TTT,RRR);
EV_BEV_leave_profile(YYY,'S01',TTT,RRR)   = EV_BEV_leave_profile(YYY,'S02',TTT,RRR);
EV_PHEV_return_profile(YYY,'S01',TTT,RRR) = EV_PHEV_return_profile(YYY,'S02',TTT,RRR);
EV_PHEV_leave_profile(YYY,'S01',TTT,RRR)  = EV_PHEV_leave_profile(YYY,'S02',TTT,RRR);
EV_BEV_return_profile(YYY,'S52',TTT,RRR)  = EV_BEV_return_profile(YYY,'S51',TTT,RRR);
EV_BEV_leave_profile(YYY,'S52',TTT,RRR)   = EV_BEV_leave_profile(YYY,'S51',TTT,RRR);
EV_PHEV_return_profile(YYY,'S52',TTT,RRR) = EV_PHEV_return_profile(YYY,'S51',TTT,RRR);
EV_PHEV_leave_profile(YYY,'S52',TTT,RRR)  = EV_PHEV_leave_profile(YYY,'S51',TTT,RRR);
$label NO_EV_fix_year_edges


* import_results parameters
PARAMETER   EV_BE_BEV(YYY,RRR,SSS,TTT)        'State of charge of the BEV vehicle fleet to be used in future runs';
PARAMETER   EV_BE_PHEV(YYY,RRR,SSS,TTT)       'State of charge of the PHEV vehicle fleet to be used in future runs';
PARAMETER   EV_BEV_NETCHARGING(YYY,RRR,SSS,TTT)        'Net charging of BEV vehicle fleet to be used in future runs';
PARAMETER   EV_PHEV_NETCHARGING(YYY,RRR,SSS,TTT)      'Net charging of PHEV vehicle fleet to be used in future runs';

PARAMETER PARAM_V2G_INFRA_CAP(YYY,RRR) 'V2G infrastructure capacity to be used in future runs';
PARAMETER PARAM_G2V_INFRA_CAP(YYY,RRR) 'G2V infrastructure capacity to be used in future runs';
PARAMETER PARAM_V2G_INFRA_EXTRA(YYY,RRR) 'Extra V2G infrastructure capacity to be used in future runs';
PARAMETER PARAM_G2V_INFRA_ACCUMNET(YYY,RRR) 'Accumulated G2V infrastructure capacity to be used in future runs';
PARAMETER PARAM_V2G_INFRA_ACCUMNET(YYY,RRR) 'Accumulated V2G infrastructure capacity to be used in future runs';
