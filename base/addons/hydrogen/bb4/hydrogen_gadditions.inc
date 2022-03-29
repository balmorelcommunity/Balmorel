$onmulti
$if     EXIST '../data/HYDROGEN_G.inc' $INCLUDE         '../data/HYDROGEN_G.inc';
$if not EXIST '../data/HYDROGEN_G.inc' $INCLUDE '../../base/data/HYDROGEN_G.inc';
$offmulti
