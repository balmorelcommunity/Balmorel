$onmulti
$if     EXIST '../data/DATACENTERS_GDATA.inc' $INCLUDE         '../data/DATACENTERS_GDATA.inc';
$if not EXIST '../data/DATACENTERS_GDATA.inc' $INCLUDE '../../base/data/DATACENTERS_GDATA.inc';
$offmulti
