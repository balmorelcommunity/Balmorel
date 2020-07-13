$onmulti
$if     EXIST '../data/HYDROGEN_FUELPRICE.inc' $INCLUDE         '../data/HYDROGEN_FUELPRICE.inc';
$if not EXIST '../data/HYDROGEN_FUELPRICE.inc' $INCLUDE '../../base/data/HYDROGEN_FUELPRICE.inc';
$offmulti
