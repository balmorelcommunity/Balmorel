*Balancing market introduced by Juan Gea-Bermudez and Polyneikis Kanellas

*Fixing heat side
$ifi not %NOHEATMARKET%==yes $goto NO_HEATMARKET
EQUATION QBMGH_T(YYY,AAA,GGG,SSS)       'Equation forcing heat production in SSS to match previous runs. Mind the timesteps used in the runs.';

QBMGH_T(IY411,IA,IGEH,IS3)$(IAGK_HASORPOT(IY411,IA,IGEH))..
SUM(T,VGH_T(IY411,IA,IGEH,IS3,T)-GH_T(IY411,IA,IGEH,IS3,T))
=E=
0
$include "../../base/addons/_hooks/qmbgh_t.inc"
;


$label NO_HEATMARKET




