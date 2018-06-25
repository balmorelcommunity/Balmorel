
PARAMETER X3VPIM(YYY,RRR,X3VPLACE0,X3VSTEP0,SSS,TTT)   "Price (Money/MWh) of price dependent imported electricity"  %semislash%
$if     EXIST '../data/X3VPIM.inc' $INCLUDE      '../data/x3vpim.inc';
$if not EXIST '../data/X3VPIM.inc' $INCLUDE '../../base/addons/x3v/demodata/x3vpim.inc';

PARAMETER X3VPEX(YYY,RRR,X3VPLACE0,X3VSTEP0,SSS,TTT)   "Price (Money/MWh) of price dependent exported electricity"  %semislash%
$if     EXIST '../data/X3VPEX.inc' $INCLUDE      '../data/X3VPEX.inc';
$if not EXIST '../data/X3VPEX.inc' $INCLUDE '../../base/addons/x3v/demodata/x3vpex.inc';
%semislash%;

PARAMETER X3VQIM(YYY,RRR,X3VPLACE0,X3VSTEP0,SSS,TTT)   "Limit (MW) on price dependent electricity import"  %semislash%
$if     EXIST '../data/X3VQIM.inc' $INCLUDE      '../data/X3VQIM.inc';
$if not EXIST '../data/X3VQIM.inc' $INCLUDE '../../base/addons/x3v/demodata/x3vqim.inc';
%semislash%;

PARAMETER X3VQEX(YYY,RRR,X3VPLACE0,X3VSTEP0,SSS,TTT)   "Limit (MW) on price dependent electricity export"  %semislash%
$if     EXIST '../data/X3VQEX.inc' $INCLUDE      '../data/X3VQEX.inc';
$if not EXIST '../data/X3VQEX.inc' $INCLUDE '../../base/addons/x3v/demodata/x3vqex.inc';
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