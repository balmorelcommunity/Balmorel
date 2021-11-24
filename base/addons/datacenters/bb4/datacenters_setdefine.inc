$onmulti
$if     EXIST '../data/DATACENTERS_AREAGROUPS.inc' $INCLUDE         '../data/DATACENTERS_AREAGROUPS.inc';
$if not EXIST '../data/DATACENTERS_AREAGROUPS.inc' $INCLUDE '../../base/data/DATACENTERS_AREAGROUPS.inc';
$offmulti
