SET X3VPLACE0 "Set of possible places with price dependent electricity exchange data" %semislash%
$if     EXIST '../data/X3V_X3VPLACE0.inc' $INCLUDE         '../data/X3V_X3VPLACE0.inc';
$if not EXIST '../data/X3V_X3VPLACE0.inc' $INCLUDE '../../base/data/X3V_X3VPLACE0.inc';
%semislash%;

SET X3VPLACE(X3VPLACE0) "Set of simulatd places with price dependent electricity exchange data" %semislash%
$if     EXIST '../data/X3V_X3VPLACE.inc' $INCLUDE         '../data/X3V_X3VPLACE.inc';
$if not EXIST '../data/X3V_X3VPLACE.inc' $INCLUDE '../../base/data/X3V_X3VPLACE.inc';
%semislash%;

SET X3VX(RRR,X3VPLACE0) "Simulated transmisision lines for price dependent electricity exchange" %semislash%
$if     EXIST '../data/X3V_X3VX.inc' $INCLUDE         '../data/X3V_X3VX.inc';
$if not EXIST '../data/X3V_X3VX.inc' $INCLUDE '../../base/data/X3V_X3VX.inc';
%semislash%;

SET RX3VSUBSTI(RRR,X3VPLACE0) "Substitutes in price dependent electricity exchange" %semislash%
$if     EXIST '../data/X3V_RX3VSUBSTI.inc' $INCLUDE         '../data/X3V_RX3VSUBSTI.inc';
$if not EXIST '../data/X3V_RX3VSUBSTI.inc' $INCLUDE '../../base/data/X3V_RX3VSUBSTI.inc';
%semislash%;

SET X3VSTEP0 "Steps for price dependent electricity exchange data"  %semislash%
$if     EXIST '../data/X3V_X3VSTEP0.inc' $INCLUDE         '../data/X3V_X3VSTEP0.inc';
$if not EXIST '../data/X3V_X3VSTEP0.inc' $INCLUDE '../../base/data/X3V_X3VSTEP0.inc';
%semislash%;

SET X3VSTEP(X3VSTEP0) "Simulated steps for price dependent electricity  exchange" %semislash%
$if     EXIST '../data/X3V_X3VSTEP.inc' $INCLUDE         '../data/X3V_X3VSTEP.inc';
$if not EXIST '../data/X3V_X3VSTEP.inc' $INCLUDE '../../base/data/X3V_X3VSTEP.inc';
%semislash%;

