$onmulti
$if     EXIST '../data/HYDROGEN_ANNUITYCG.inc' $INCLUDE         '../data/HYDROGEN_ANNUITYCG.inc';
$if not EXIST '../data/HYDROGEN_ANNUITYCG.inc' $INCLUDE '../../base/data/HYDROGEN_ANNUITYCG.inc';
$offmulti
