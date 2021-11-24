$onmulti
$if     EXIST '../data/DATACENTERS_AAA.inc' $INCLUDE         '../data/DATACENTERS_AAA.inc';
$if not EXIST '../data/DATACENTERS_AAA.inc' $INCLUDE '../../base/data/DATACENTERS_AAA.inc';
$offmulti
