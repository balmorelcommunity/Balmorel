$onmulti
$if     EXIST '../data/HD_GDATA.inc' $INCLUDE         '../data/HD_GDATA.inc';
$if not EXIST '../data/HD_GDATA.inc' $INCLUDE '../../base/data/HD_GDATA.inc';
$offmulti
