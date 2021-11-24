$onmulti
$if     EXIST '../data/DATACENTERS_RRRAAA.inc' $INCLUDE         '../data/DATACENTERS_RRRAAA.inc';
$if not EXIST '../data/DATACENTERS_RRRAAA.inc' $INCLUDE '../../base/data/DATACENTERS_RRRAAA.inc';
$offmulti
