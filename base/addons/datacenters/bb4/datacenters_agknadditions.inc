$onmulti
$if     EXIST '../data/DATACENTERS_AGKN.inc' $INCLUDE         '../data/DATACENTERS_AGKN.inc';
$if not EXIST '../data/DATACENTERS_AGKN.inc' $INCLUDE '../../base/data/DATACENTERS_AGKN.inc';
$offmulti
