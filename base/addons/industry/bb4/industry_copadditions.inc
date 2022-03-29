*Industry add-on. Implemented by Juan Gea Bermudez 2019

$onmulti
$if     EXIST '../data/INDUSTRY_COP.inc' $INCLUDE         '../data/INDUSTRY_COP.inc';
$if not EXIST '../data/INDUSTRY_COP.inc' $INCLUDE '../../base/data/INDUSTRY_COP.inc';
$offmulti
