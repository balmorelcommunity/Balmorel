$onmulti
$if     EXIST '../data/COMBTECH_GDATA.inc' $INCLUDE         '../data/COMBTECH_GDATA.inc';
$if not EXIST '../data/COMBTECH_GDATA.inc' $INCLUDE '../../base/data/COMBTECH_GDATA.inc';
$offmulti
