$onmulti
$if     EXIST '../data/COMBTECH_G.inc' $INCLUDE         '../data/COMBTECH_G.inc';
$if not EXIST '../data/COMBTECH_G.inc' $INCLUDE '../../base/data/COMBTECH_G.inc';
$offmulti
