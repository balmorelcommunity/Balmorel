*DATACENTERS add-on.

$onmulti
$if     EXIST '../data/DATACENTERS_COP.inc' $INCLUDE         '../data/DATACENTERS_COP.inc';
$if not EXIST '../data/DATACENTERS_COP.inc' $INCLUDE '../../base/data/DATACENTERS_COP.inc';
$offmulti
