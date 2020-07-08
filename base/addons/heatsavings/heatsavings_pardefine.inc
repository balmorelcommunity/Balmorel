PARAMETER HEATSV_POT(YYY,AAA,HEATSV_STEPS)   'Potential of heat savings, EUR/MWh' %semislash%
$if     EXIST '../data/HEATSAVINGS_POT.inc' $INCLUDE         '../data/HEATSAVINGS_POT.inc'
$if not EXIST '../data/HEATSAVINGS_POT.inc' $INCLUDE '../../base/data/HEATSAVINGS_POT.inc';
%semislash%

$ifi not %INDHEATSAV%==yes $goto endINDHEATpot
PARAMETER HEATSV_INDHEATPOT(YYY,INDHEAT_AAA,HEATSV_STEPS)   'Potential of heat savings for individual heating, EUR/MWh' %semislash%
$if     EXIST '../data/HEATSAVINGS_INDHEATPOT.inc' $INCLUDE         '../data/HEATSAVINGS_INDHEATPOT.inc'
$if not EXIST '../data/HEATSAVINGS_INDHEATPOT.inc' $INCLUDE '../../base/data/HEATSAVINGS_INDHEATPOT.inc';
%semislash%
$label endINDHEATpot

PARAMETER HEATSV_COST(YYY,RRR,HEATSV_STEPS)   'Cost of heat savings, EUR/MWh' %semislash%
$if     EXIST '../data/HEATSAVINGS_COST%SCNAME%.inc' $INCLUDE         '../data/HEATSAVINGS_COST%SCNAME%.inc'
$if not EXIST '../data/HEATSAVINGS_COST%SCNAME%.inc' $INCLUDE '../data/HEATSAVINGS_COST.inc';
%semislash%

PARAMETER HEATSV_SAVEQ(YYY,CCC) 'Fixed heat savings for each year, MWh' %semislash%
$if     EXIST '../data/HEATSAVINGS_SAVEQ.inc' $INCLUDE         '../data/HEATSAVINGS_SAVEQ.inc'
$if not EXIST '../data/HEATSAVINGS_SAVEQ.inc' $INCLUDE '../../base/data/HEATSAVINGS_SAVEQ.inc';
%semislash%