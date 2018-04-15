$onmulti
$if     EXIST '../data/HYDROGEN_GDATA.inc' $INCLUDE         '../data/HYDROGEN_GDATA.inc';
$if not EXIST '../data/HYDROGEN_GDATA.inc' $INCLUDE '../../base/data/HYDROGEN_GDATA.inc';
$offmulti