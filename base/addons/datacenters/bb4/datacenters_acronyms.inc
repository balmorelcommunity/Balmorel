$onmulti
$if     EXIST '../data/DATACENTERS_ACRONYMS.inc' $INCLUDE         '../data/DATACENTERS_ACRONYMS.inc';
$if not EXIST '../data/DATACENTERS_ACRONYMS.inc' $INCLUDE '../../base/data/DATACENTERS_ACRONYMS.inc';
$offmulti
