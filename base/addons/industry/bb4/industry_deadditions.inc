*Industry add-on. Implemented by Juan Gea Bermudez 2019

$onmulti
$if     EXIST '../data/INDUSTRY_DE.inc' $INCLUDE         '../data/INDUSTRY_DE.inc';
$if not EXIST '../data/INDUSTRY_DE.inc' $INCLUDE '../../base/data/INDUSTRY_DE.inc';
$offmulti