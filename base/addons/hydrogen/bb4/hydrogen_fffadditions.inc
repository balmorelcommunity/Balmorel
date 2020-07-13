$onmulti
$if     EXIST '../data/HYDROGEN_FFF.inc' $INCLUDE         '../data/HYDROGEN_FFF.inc';
$if not EXIST '../data/HYDROGEN_FFF.inc' $INCLUDE '../../base/data/HYDROGEN_FFF.inc';
$offmulti
