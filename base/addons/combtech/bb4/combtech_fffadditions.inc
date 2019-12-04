$onmulti
$if     EXIST '../data/COMBTECH_FFF.inc' $INCLUDE         '../data/COMBTECH_FFF.inc';
$if not EXIST '../data/COMBTECH_FFF.inc' $INCLUDE '../../base/data/COMBTECH_FFF.inc';
$offmulti
