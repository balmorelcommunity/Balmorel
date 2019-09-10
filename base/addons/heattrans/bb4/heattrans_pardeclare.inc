* File heattrans_pardeclare.inc for addon heattrans
* Latest revision 20181014(hr)

* Transmission capacity (MW) between areas IAE (exporting) and  IAI (importing)
* at the beginning of current simulation year:
PARAMETER XHKFX(YYY,IAAAE,IAAAI) "Heat transmission capacity between regions at beginning of year (MW)";

PARAMETER XHINVCOST(YYY,IAAAE,IAAAI)  "Investment cost in new heat transmission capacity (Money/MW)"
* Observe: if INF is entered in XHINVCOST, this means that no tranmission capacity can be established between the two associated areas.

PARAMETER XHCOST(IAAAE,IAAAI)  "Heat transmission cost between areas (calculated from exported quantity) (Money/MWh)" ;

PARAMETER XHLOSS(IAAAE,IAAAI)  "Heat transmission loss between areas (calculated from exported quantity) (share)";

PARAMETER ANNUITYCXH(CCC) "Transforms investment in heat transmission lines into annual payment (fraction). Possibly different meaning in BB4";

PARAMETER XHMAXK(YYY,IAAAE,IAAAI)  "Max heat transmission capacity between two areas (MW)";

SCALAR    LIFETIME_XH                   "Lifetime of heat transmission lines (years)";

PARAMETER  XHKACCUMNET(YYY,IAAAE,IAAAI) "Resulting heat transmission capacity development at end (MISSING: minus any decommissioning of them due to lifetime expiration) this BB4, at end of previous (i.e., available at start of current) year (MW) to be transferred to future runs";
PARAMETER  XH_T(Y,IAAAE,IAAAI,S,T)      "Heat export from region IRRRE to IRRRI to be transferred to future runs (MW)  to be transferred to future runs";

$ontext
*to be checked
* In case of temperature lift by heat pump:
PARAMETER XHTEMPLIFT(IAAAE,IAAAI) "Temperature lift supplied by heat pump used for lifting temperature for heat transmitted from low to high temperature Area (share)";
PARAMETER XHTEMPLIFT(IAAAE,IAAAI,GGG) "Temperature lift for lifting temperature for heat transmitted from low to high temperature Area supplied by heat pump used (share)";
$offtext
