$onmulti
$if     EXIST '../data/DATACENTERS_DH.inc' $INCLUDE         '../data/DATACENTERS_DH.inc';
$if not EXIST '../data/DATACENTERS_DH.inc' $INCLUDE '../../base/data/DATACENTERS_DH.inc';
$offmulti
