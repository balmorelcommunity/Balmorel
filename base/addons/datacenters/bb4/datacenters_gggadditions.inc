$onmulti
$if     EXIST '../data/DATACENTERS_GGG.inc' $INCLUDE         '../data/DATACENTERS_GGG.inc';
$if not EXIST '../data/DATACENTERS_GGG.inc' $INCLUDE '../../base/data/DATACENTERS_GGG.inc';
$offmulti
