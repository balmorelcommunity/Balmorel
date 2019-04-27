*Industry add-on. Implemented by Juan Gea Bermudez 2019

$onmulti
$if     EXIST '../data/INDUSTRY_RRR.inc' $INCLUDE         '../data/INDUSTRY_RRR.inc';
$if not EXIST '../data/INDUSTRY_RRR.inc' $INCLUDE '../../base/data/INDUSTRY_RRR.inc';
$offmulti
