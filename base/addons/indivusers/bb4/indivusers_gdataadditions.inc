$onmulti
$if     EXIST '../data/INDIVUSERS_GDATA.inc' $INCLUDE         '../data/INDIVUSERS_GDATA.inc';
$if not EXIST '../data/INDIVUSERS_GDATA.inc' $INCLUDE '../../base/data/INDIVUSERS_GDATA.inc';
$offmulti
