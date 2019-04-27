* File heattrans_pardefine.inc for the Balmorel model. For use with addon heattrans.
* Latest revision 20180922(hr)


PARAMETER XHKFX(YYY,IAAAE,IAAAI)  "Initial heat transmission capacity between areas (MW)" %semislash%
$if     EXIST "../data/HEATTRANS_XHKFX.inc" $INCLUDE         "../data/HEATTRANS_XHKFX.inc";
$if not EXIST "../data/HEATTRANS_XHKFX.inc" $INCLUDE "../../base/data/HEATTRANS_XHKFX.inc";
%semislash%;
*------------- Any XHKFX additions for other addon to be placed here: ----------------
$include "../../base/addons/_hooks/xhfxadditions.inc"

PARAMETER XHCOST(IAAAE,IAAAI)  "Heat transmission cost between areas (calculated from exported quantity) (Money/MWh)" %semislash%
$if     EXIST "../data/HEATTRANS_XHCOST.inc" $INCLUDE         "../data/HEATTRANS_XHCOST.inc";
$if not EXIST "../data/HEATTRANS_XHCOST.inc" $INCLUDE "../../base/data/HEATTRANS_XHCOST.inc";
%semislash%;
*------------- Any XHCOST additions for other addon to be placed here: ----------------
$include "../../base/addons/_hooks/xhcostadditions.inc"

PARAMETER XHLOSS(IAAAE,IAAAI)       "Heat transmission loss between areas (calculated from exported quantity) (share)" %semislash%
$if     EXIST "../data/HEATTRANS_XHLOSS.inc" $INCLUDE         "../data/HEATTRANS_XHLOSS.inc";
$if not EXIST "../data/HEATTRANS_XHLOSS.inc" $INCLUDE "../../base/data/HEATTRANS_XHLOSS.inc";
%semislash%;
*------------- Any XHLOSS additions for other addon to be placed here: ----------------
$include "../../base/addons/_hooks/xhlossadditions.inc"

PARAMETER ANNUITYCXH(CCC)  "Transforms investment in heat transmission lines into annual payment (fraction). Possibly different meaning in BB4" %semislash%
$if     EXIST "../data/HEATTRANS_ANNUITYCXH.inc" $INCLUDE         "../data/HEATTRANS_ANNUITYCXH.inc";
$if not EXIST "../data/HEATTRANS_ANNUITYCXH.inc" $INCLUDE "../../base/data/HEATTRANS_ANNUITYCXH.inc";
%semislash%;

* In case of investments:
PARAMETER XHINVCOST(YYY,IAAAE,IAAAI)   "Investment cost in new heat transmission capacity (Money/MW)" %semislash%
$if     EXIST "../data/HEATTRANS_XHINVCOST.inc" $INCLUDE         "../data/HEATTRANS_XHINVCOST.inc";
$if not EXIST "../data/HEATTRANS_XHINVCOST.inc" $INCLUDE "../../base/data/HEATTRANS_XHINVCOST.inc";
%semislash%;

SCALAR    LIFETIME_XH               "Lifetime of heat transmission lines (years)"%semislash%
$if     EXIST "../data/HEATTRANS_LIFETIME_XH.inc" $INCLUDE         "../data/HEATTRANS_LIFETIME_XH.inc";
$if not EXIST "../data/HEATTRANS_LIFETIME_XH.inc" $INCLUDE "../../base/data/HEATTRANS_LIFETIME_XH.inc";
%semislash%  ;

*------------- Any XHINVCOST additions for other addon to be placed here: ----------------
$include "../../base/addons/_hooks/xhinvcostadditions.inc"


$ontext
*to be checked
* In case of temperature lift by heat pump:

SET XHGETOH(GGG) "Heat pumps used for lifting temperature for heat transmitted between two Areas" %semislash%
$if     EXIST "../data/HEATTRANS_XHGETOH.inc" $INCLUDE         "../data/HEATTRANS_XHGETOH.inc";
$if not EXIST "../data/HEATTRANS_XHGETOH.inc" $INCLUDE "../../base/data/HEATTRANS_XHGETOH.inc";
%semislash%;

SET XHTEMPLIFT(IAAAE,IAAAI) "Pair of areas for which temperature lift necessary" %semislash%
$if     EXIST "../data/HEATTRANS_XHTEMPLIFT.inc" $INCLUDE         "../data/HEATTRANS_XHTEMPLIFT.inc";
$if not EXIST "../data/HEATTRANS_XHTEMPLIFT.inc" $INCLUDE "../../base/data/HEATTRANS_XHTEMPLIFT.inc";
%semislash%;

$offtext




