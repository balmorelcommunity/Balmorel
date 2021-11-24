$onmulti
$if     EXIST '../data/DATACENTERS_DEUSER.inc' $INCLUDE         '../data/DATACENTERS_DEUSER.inc';
$if not EXIST '../data/DATACENTERS_DEUSER.inc' $INCLUDE '../../base/data/DATACENTERS_DEUSER.inc';
$offmulti
