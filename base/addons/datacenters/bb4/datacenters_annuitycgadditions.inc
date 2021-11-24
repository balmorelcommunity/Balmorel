$onmulti
$if     EXIST '../data/DATACENTERS_ANNUITYCG.inc' $INCLUDE         '../data/DATACENTERS_ANNUITYCG.inc';
$if not EXIST '../data/DATACENTERS_ANNUITYCG.inc' $INCLUDE '../../base/data/DATACENTERS_ANNUITYCG.inc';
$offmulti
