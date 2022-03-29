*INDIVUSERS add-on. Implemented by Juan Gea Bermudez 2019

$onmulti
$if     EXIST '../data/INDIVUSERS_XHCOST.inc' $INCLUDE         '../data/INDIVUSERS_XHCOST.inc';
$if not EXIST '../data/INDIVUSERS_XHCOST.inc' $INCLUDE '../../base/data/INDIVUSERS_XHCOST.inc';
$offmulti
