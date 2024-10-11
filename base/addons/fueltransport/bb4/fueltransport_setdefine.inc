
$ifi     EXIST '../data/FUELTRANSPORT_COST.inc'    $INCLUDE   '../data/FUELTRANSPORT_COST.inc' ;
$ifi not EXIST '../data/FUELTRANSPORT_COST.inc'    $INCLUDE   '../../base/data/FUELTRANSPORT_COST.inc';