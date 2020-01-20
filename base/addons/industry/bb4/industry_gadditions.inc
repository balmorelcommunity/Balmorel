*Industry add-on. Implemented by Juan Gea Bermudez 2019

$onmulti
$if     EXIST '../data/INDUSTRY_G.inc' $INCLUDE         '../data/INDUSTRY_G.inc';
$if not EXIST '../data/INDUSTRY_G.inc' $INCLUDE '../../base/data/INDUSTRY_G.inc';
$offmulti
