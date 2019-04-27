*Industry add-on. Implemented by Juan Gea Bermudez 2019

$onmulti
$if     EXIST '../data/INDUSTRY_XHCOST.inc' $INCLUDE         '../data/INDUSTRY_XHCOST.inc';
$if not EXIST '../data/INDUSTRY_XHCOST.inc' $INCLUDE '../../base/data/INDUSTRY_XHCOST.inc';
$offmulti