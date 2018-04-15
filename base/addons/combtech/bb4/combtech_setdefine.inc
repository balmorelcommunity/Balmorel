$onmulti
$if     EXIST '../data/COMBTECH_GGG.inc' $INCLUDE         '../data/COMBTECH_GGG.inc';
$if not EXIST '../data/COMBTECH_GGG.inc' $INCLUDE '../../base/data/COMBTECH_GGG.inc';

$if     EXIST '../data/COMBTECH_G.inc' $INCLUDE         '../data/COMBTECH_G.inc';
$if not EXIST '../data/COMBTECH_G.inc' $INCLUDE '../../base/data/COMBTECH_G.inc';

$if     EXIST '../data/COMBTECH_FFF.inc' $INCLUDE         '../data/COMBTECH_FFF.inc';
$if not EXIST '../data/COMBTECH_FFF.inc' $INCLUDE '../../base/data/COMBTECH_FFF.inc';
$offmulti
