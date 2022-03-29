$onmulti
$if     EXIST '../data/HYDROGEN_GGG.inc' $INCLUDE         '../data/HYDROGEN_GGG.inc';
$if not EXIST '../data/HYDROGEN_GGG.inc' $INCLUDE '../../base/data/HYDROGEN_GGG.inc';
$offmulti
