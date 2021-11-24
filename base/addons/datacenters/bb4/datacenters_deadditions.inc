$onmulti
$if     EXIST '../data/DATACENTERS_DE.inc' $INCLUDE         '../data/DATACENTERS_DE.inc';
$if not EXIST '../data/DATACENTERS_DE.inc' $INCLUDE '../../base/data/DATACENTERS_DE.inc';
$offmulti
