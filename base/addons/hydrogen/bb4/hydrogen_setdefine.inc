
$ifi not %generic_synfuel%==yes $goto NO_GENERIC_SYNFUEL
$ifi     EXIST '../data/HYDROGEN_SYNFUELUSER.inc'    $INCLUDE   '../data/HYDROGEN_SYNFUELUSER.inc' ;
$ifi not EXIST '../data/HYDROGEN_SYNFUELUSER.inc'    $INCLUDE   '../../base/data/HYDROGEN_SYNFUELUSER.inc';
$label NO_GENERIC_SYNFUEL
