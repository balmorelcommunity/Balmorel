
PARAMETER X3VPIM(YYY,RRR,X3VPLACE0,X3VSTEP0,SSS,TTT)   "Price (Money/MWh) of price dependent imported electricity"  %semislash%
$if     EXIST '../data/X3V_PIM.inc' $INCLUDE      '../data/X3V_PIM.inc';
$if not EXIST '../data/X3V_PIM.inc' $INCLUDE '../../base/data/X3V_PIM.inc';

PARAMETER X3VPEX(YYY,RRR,X3VPLACE0,X3VSTEP0,SSS,TTT)   "Price (Money/MWh) of price dependent exported electricity"  %semislash%
$if     EXIST '../data/X3V_PEX.inc' $INCLUDE      '../data/X3V_PEX.inc';
$if not EXIST '../data/X3V_PEX.inc' $INCLUDE '../../base/data/X3V_PEX.inc';
%semislash%;

PARAMETER X3VQIM(YYY,RRR,X3VPLACE0,X3VSTEP0,SSS,TTT)   "Limit (MW) on price dependent electricity import"  %semislash%
$if     EXIST '../data/X3V_QIM.inc' $INCLUDE      '../data/X3V_QIM.inc';
$if not EXIST '../data/X3V_QIM.inc' $INCLUDE '../../base/data/X3V_QIM.inc';
%semislash%;

PARAMETER X3VQEX(YYY,RRR,X3VPLACE0,X3VSTEP0,SSS,TTT)   "Limit (MW) on price dependent electricity export"  %semislash%
$if     EXIST '../data/X3V_QEX.inc' $INCLUDE      '../data/X3V_QEX.inc';
$if not EXIST '../data/X3V_QEX.inc' $INCLUDE '../../base/data/X3V_QEX.inc';
%semislash%;

* Net exports assumed to be zero based on the assumption that competetative investments ensure
* long run equilibrium prices.
* LARS: Nogen skulle måske fylde de historiske exportmænger til verifikations formål?
PARAMETER X3VBAL(YYY,X3VPLACE);
X3VBAL(YYY,X3VPLACE)=2016.20000

*PARAMETER X3VBALSP(YYY,X3VPLACE);
* Get shadow price of the annual balance constraint.
*$ifi %X3VfxP%==yes execute_load '../../base/addons/x3v/data/X3V_%X3VPRICECASE%_BALSP.gdx',X3VBALSP;
*%X3VfxQ%
;
