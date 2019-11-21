*Balancing market introduced by Juan Gea-Bermudez and Polyneikis Kanellas

*Fixing heat side
$ifi not %RESTRICTHEATMARKET%==yes $goto NO_HEATMARKET
EQUATION QBMGH_T(YYY,AAA,GGG,SSS)       'Equation forcing heat production in SSS to match previous runs. Mind the timesteps used in the runs.';
EQUATION QBMHSTOLOADT(YYY,AAA,GGG,SSS)  'Equation forcing intraseasonal heat storage loading in SSS to match previous runs. Mind the timesteps used in the runs.';
EQUATION QBMHSTOLOADTS(YYY,AAA,GGG,SSS) 'Equation forcing interseasonal heat storage loading in SSS to match previous runs. Mind the timesteps used in the runs.';

QBMGH_T(IY411,IA,IGH,IS3)$IAGK_HASORPOT(IY411,IA,IGH)..
SUM(T,VGH_T(IY411,IA,IGH,IS3,T)-GH_T(IY411,IA,IGH,IS3,T))
=E=
0;

QBMHSTOLOADT(IY411,IA,IGHSTO,IS3)$IAGK_HASORPOT(IY411,IA,IGHSTO)..
SUM(T,VHSTOLOADT(IY411,IA,IGHSTO,IS3,T)-HSTOLOADT(IY411,IA,IGHSTO,IS3,T))
=E=
0;

QBMHSTOLOADTS(IY411,IA,IGHSTOS,IS3)$IAGK_HASORPOT(IY411,IA,IGHSTOS)..
SUM(T,VHSTOLOADT(IY411,IA,IGHSTOS,IS3,T)-HSTOLOADT(IY411,IA,IGHSTOS,IS3,T))
=E=
0;

$label NO_HEATMARKET