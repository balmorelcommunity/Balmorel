$onmulti
$if     EXIST '../data/COMBTECH_FUELPRICE.inc' $INCLUDE         '../data/COMBTECH_FUELPRICE.inc';
$if not EXIST '../data/COMBTECH_FUELPRICE.inc' $INCLUDE '../../base/data/COMBTECH_FUELPRICE.inc';
$offmulti
