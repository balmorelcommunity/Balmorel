* File heattrans_pardeclare.inc for addon heattrans
* Latest revision 20181014(hr)


$LOG "#####  In %system.incname%  ";


PARAMETER XHKFX(YYY,IAAAE,IAAAI)  "Initial heat transmission capacity between areas (MW)";

PARAMETER XHINVCOST(IAAAE,IAAAI)  "Investment cost in new heat transmission capacity (Money/MW)"
* Observe: if INF is entered in XHINVCOST, this means that no tranmission capacity can be established between the two associated areas.

PARAMETER XHCOST(IAAAE,IAAAI)  "Heat transmission cost between areas (calculated from exported quantity) (Money/MWh)" ;

PARAMETER XHLOSS(IAAAE,IAAAI)  "Heat transmission loss between areas (calculated from exported quantity) (share)";
PARAMETER ANNUITYCXH(CCC) "Transforms investment in heat transmission lines into annual payment (fraction). Possibly different meaning in BB4";

* In case of temperature lift by heat pump:

*PARAMETER XHTEMPLIFT(IAAAE,IAAAI) "Temperature lift supplied by heat pump used for lifting temperature for heat transmitted from low to high temperature Area (share)";
*PARAMETER XHTEMPLIFT(IAAAE,IAAAI,GGG) "Temperature lift for lifting temperature for heat transmitted from low to high temperature Area supplied by heat pump used (share)";
