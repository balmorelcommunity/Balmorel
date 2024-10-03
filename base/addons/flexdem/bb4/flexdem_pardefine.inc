* Flex add-on. Added by Juan Gea Bermudez

$ifi %seasonal_demand%==yes $goto flexible_demand_within_seasons
PARAMETER FLEXYDEMAND(YYY,CCCRRRAAA,FLEXUSER) 'Flexible yearly demand node and user (MWh)'  %semislash%
$if     EXIST '../data/FLEXDEM_FLEXYDEMAND.inc' $INCLUDE         '../data/FLEXDEM_FLEXYDEMAND.inc';
$if not EXIST '../data/FLEXDEM_FLEXYDEMAND.inc' $INCLUDE '../../base/data/FLEXDEM_FLEXYDEMAND.inc';
%semislash%;

$label flexible_demand_within_seasons
$ifi not %seasonal_demand%==yes $goto flexible_demand_within_year
PARAMETER FLEXSDEMAND(YYY,SSS,CCCRRRAAA,FLEXUSER) 'Flexible seasonal demand per year, node and user (MWh)'  %semislash%
$if     EXIST '../data/FLEXDEM_FLEXSDEMAND.inc' $INCLUDE         '../data/FLEXDEM_FLEXSDEMAND.inc';
$if not EXIST '../data/FLEXDEM_FLEXSDEMAND.inc' $INCLUDE '../../base/data/FLEXDEM_FLEXSDEMAND.inc';
%semislash%;
$label flexible_demand_within_year

PARAMETER FLEXMAXLIMIT(FLEXUSER, RRR, SSS, TTT) 'Maximum flexible consumption wrt. season and term (%)'  %semislash%
$if     EXIST '../data/FLEXDEM_FLEXMAXLIMIT.inc' $INCLUDE         '../data/FLEXDEM_FLEXMAXLIMIT.inc';
$if not EXIST '../data/FLEXDEM_FLEXMAXLIMIT.inc' $INCLUDE '../../base/data/FLEXDEM_FLEXMAXLIMIT.inc';
%semislash%;

