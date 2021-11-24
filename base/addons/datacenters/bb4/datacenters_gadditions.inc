$onmulti
$if     EXIST '../data/DATACENTERS_G.inc' $INCLUDE         '../data/DATACENTERS_G.inc';
$if not EXIST '../data/DATACENTERS_G.inc' $INCLUDE '../../base/data/DATACENTERS_G.inc';
$offmulti
