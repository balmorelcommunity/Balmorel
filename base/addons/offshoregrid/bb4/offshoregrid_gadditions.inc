$onmulti
$if     EXIST '../data/OFFSHOREGRID_G.inc' $INCLUDE         '../data/OFFSHOREGRID_G.inc';
$if not EXIST '../data/OFFSHOREGRID_G.inc' $INCLUDE '../../base/data/OFFSHOREGRID_G.inc';
$offmulti
