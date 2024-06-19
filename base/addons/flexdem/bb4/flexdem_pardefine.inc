* Flex add-on. Added by Juan Gea Bermudez

PARAMETER FLEXYDEMAND(YYY,CCCRRRAAA,FLEXUSER) 'Flexible yearly demand node and user (MWh)'  %semislash%
$if     EXIST '../data/FLEXDEM_FLEXYDEMAND.inc' $INCLUDE         '../data/FLEXDEM_FLEXYDEMAND.inc';
$if not EXIST '../data/FLEXDEM_FLEXYDEMAND.inc' $INCLUDE '../../base/data/FLEXDEM_FLEXYDEMAND.inc';
%semislash%;

PARAMETER FLEXSDEMAND(YYY,SSS,CCCRRRAAA,FLEXUSER) 'Flexible seasonal demand per year, node and user (MWh)'  %semislash%
$if     EXIST '../data/FLEXDEM_FLEXSDEMAND.inc' $INCLUDE         '../data/FLEXDEM_FLEXSDEMAND.inc';
$if not EXIST '../data/FLEXDEM_FLEXSDEMAND.inc' $INCLUDE '../../base/data/FLEXDEM_FLEXSDEMAND.inc';
%semislash%;


