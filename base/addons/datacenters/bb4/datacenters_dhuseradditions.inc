$onmulti
$if     EXIST '../data/DATACENTERS_DHUSER.inc' $INCLUDE         '../data/DATACENTERS_DHUSER.inc';
$if not EXIST '../data/DATACENTERS_DHUSER.inc' $INCLUDE '../../base/data/DATACENTERS_DHUSER.inc';
$offmulti
