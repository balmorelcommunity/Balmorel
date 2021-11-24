$onmulti
$if     EXIST '../data/DATACENTERS_DE_VAR_T.inc' $INCLUDE         '../data/DATACENTERS_DE_VAR_T.inc';
$if not EXIST '../data/DATACENTERS_DE_VAR_T.inc' $INCLUDE '../../base/data/DATACENTERS_DE_VAR_T.inc';
$offmulti
