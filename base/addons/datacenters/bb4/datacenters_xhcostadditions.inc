$onmulti
$if     EXIST '../data/DATACENTERS_XHCOST.inc' $INCLUDE         '../data/DATACENTERS_XHCOST.inc';
$if not EXIST '../data/DATACENTERS_XHCOST.inc' $INCLUDE '../../base/data/DATACENTERS_XHCOST.inc';
$offmulti
