*Industry add-on. Implemented by Juan Gea Bermudez 2019

$onmulti
$if     EXIST '../data/INDUSTRY_RRRAAA.inc' $INCLUDE         '../data/INDUSTRY_RRRAAA.inc';
$if not EXIST '../data/INDUSTRY_RRRAAA.inc' $INCLUDE '../../base/data/INDUSTRY_RRRAAA.inc';
$offmulti
