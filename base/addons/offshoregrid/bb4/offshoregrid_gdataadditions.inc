$onmulti
$if     EXIST '../data/OFFSHOREGRID_GDATA.inc' $INCLUDE         '../data/OFFSHOREGRID_GDATA.inc';
$if not EXIST '../data/OFFSHOREGRID_GDATA.inc' $INCLUDE '../../base/data/OFFSHOREGRID_GDATA.inc';
$offmulti
