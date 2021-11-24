$onmulti
$if     EXIST '../data/DATACENTERS_CCCRRRAAA.inc' $INCLUDE         '../data/DATACENTERS_CCCRRRAAA.inc';
$if not EXIST '../data/DATACENTERS_CCCRRRAAA.inc' $INCLUDE '../../base/data/DATACENTERS_CCCRRRAAA.inc';
$offmulti
