$onmulti
$if     EXIST '../data/DATACENTERS_XHLOSS.inc' $INCLUDE         '../data/DATACENTERS_XHLOSS.inc';
$if not EXIST '../data/DATACENTERS_XHLOSS.inc' $INCLUDE '../../base/data/DATACENTERS_XHLOSS.inc';
$offmulti
