* Flexible demand add-on. Added by Mathias Berg Rosendal

SET FLEXUSER 'Flexible demand users'  %semislash%
$if     EXIST '../data/FLEXDEM_FLEXUSER.inc' $INCLUDE         '../data/FLEXDEM_FLEXUSER.inc';
$if not EXIST '../data/FLEXDEM_FLEXUSER.inc' $INCLUDE '../../base/data/FLEXDEM_FLEXUSER.inc';
%semislash%;

PARAMETER FLEXSDEMAND(YYY,SSS,CCCRRRAAA,FLEXUSER) 'Flexible seasonal demand per year, node and user (MWh)';
PARAMETER FLEXYDEMAND(YYY,CCCRRRAAA,FLEXUSER) 'Flexible yearly demand node and user (MWh)';
