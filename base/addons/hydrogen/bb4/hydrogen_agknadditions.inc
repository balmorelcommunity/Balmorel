$onmulti
$if     EXIST '../data/HYDROGEN_AGKN.inc' $INCLUDE         '../data/HYDROGEN_AGKN.inc';
$if not EXIST '../data/HYDROGEN_AGKN.inc' $INCLUDE '../../base/data/HYDROGEN_AGKN.inc';
$offmulti
