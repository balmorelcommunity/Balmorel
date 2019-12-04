$onmulti
$if     EXIST '../data/COMBTECH_GGG.inc' $INCLUDE         '../data/COMBTECH_GGG.inc';
$if not EXIST '../data/COMBTECH_GGG.inc' $INCLUDE '../../base/data/COMBTECH_GGG.inc';
$offmulti
