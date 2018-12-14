* File heattrans_hellolog.inc for the Balmorel model. For use with addon heattrans.
* Latest revision 20180922(hr)



$LOG "#####  In %system.incname%  ";

PARAMETER XHKFX       "Initial heat transmission capacity between areas (MW)" %semislash%
$if     EXIST "../data/HEATTRANS_XHKFX.inc" $INCLUDE         "../data/HEATTRANS_XHKFX.inc";
$if not EXIST "../data/HEATTRANS_XHKFX.inc" $INCLUDE "../../base/data/HEATTRANS_XHKFX.inc";
%semislash%;

SET XHKN(IAAAE,IAAAI) "Pair of areas that may get new heat transmission capacity" %semislash%
$if     EXIST "../data/HEATTRANS_XHKN.inc" $INCLUDE         "../data/HEATTRANS_XHKN.inc";
$if not EXIST "../data/HEATTRANS_XHKN.inc" $INCLUDE "../../base/data/HEATTRANS_XHKN.inc";
%semislash%;

PARAMETER XHCOST(IAAAE,IAAAI)  "Heat transmission cost between areas (calculated from exported quantity) (Money/MWh)" %semislash%
$if     EXIST "../data/HEATTRANS_XHCOST.inc" $INCLUDE         "../data/HEATTRANS_XHCOST.inc";
$if not EXIST "../data/HEATTRANS_XHCOST.inc" $INCLUDE "../../base/data/HEATTRANS_XHCOST.inc";
%semislash%;

PARAMETER XHLOSS(IAAAE,IAAAI)       "Heat transmission loss between areas (calculated from exported quantity) (share)" %semislash%
$if     EXIST "../data/HEATTRANS_XHLOSS.inc" $INCLUDE         "../data/HEATTRANS_XHLOSS.inc";
$if not EXIST "../data/HEATTRANS_XHLOSS.inc" $INCLUDE "../../base/data/HEATTRANS_XHLOSS.inc";
%semislash%;

PARAMETER ANNUITYCXH(CCC)  "Transforms investment in heat transmission lines into annual payment (fraction). Possibly different meaning in BB4" %semislash%
$if     EXIST "../data/HEATTRANS_ANNUITYCXH.inc" $INCLUDE         "../data/HEATTRANS_ANNUITYCXH.inc";
$if not EXIST "../data/HEATTRANS_ANNUITYCXH.inc" $INCLUDE "../../base/data/HEATTRANS_ANNUITYCXH.inc";
%semislash%;

* In case of temperature lift by heat pump:

SET XHGETOH(GGG) "Heat pumps used for lifting temperature for heat transmitted between two Areas" %semislash%
$if     EXIST "../data/HEATTRANS_XHGETOH.inc" $INCLUDE         "../data/HEATTRANS_XHGETOH.inc";
$if not EXIST "../data/HEATTRANS_XHGETOH.inc" $INCLUDE "../../base/data/HEATTRANS_XHGETOH.inc";
%semislash%;

SET XHTEMPLIFT(IAAAE,IAAAI) "Pair of areas for which temperature lift necessary" %semislash%
$if     EXIST "../data/HEATTRANS_XHTEMPLIFT.inc" $INCLUDE         "../data/HEATTRANS_XHTEMPLIFT.inc";
$if not EXIST "../data/HEATTRANS_XHTEMPLIFT.inc" $INCLUDE "../../base/data/HEATTRANS_XHTEMPLIFT.inc";
%semislash%;

* In case of investments:
* Note: Investments not implemented, therefore the following is merely expectations

PARAMETER XHINVCOST       "Investment cost in new heat transmission capacity (Money/MW)" %semislash%
$if     EXIST "../data/HEATTRANS_XHINVCOST.inc" $INCLUDE         "../data/HEATTRANS_XHINVCOST.inc";
$if not EXIST "../data/HEATTRANS_XHINVCOST.inc" $INCLUDE "../../base/data/HEATTRANS_XHINVCOST.inc";
%semislash%;






