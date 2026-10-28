$onmulti
$if     EXIST '../data/OFFSHOREGRID_GGG.inc' $INCLUDE         '../data/OFFSHOREGRID_GGG.inc';
$if not EXIST '../data/OFFSHOREGRID_GGG.inc' $INCLUDE '../../base/data/OFFSHOREGRID_GGG.inc';
$offmulti
