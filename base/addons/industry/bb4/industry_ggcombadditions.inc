*Industry add-on. Implemented by Juan Gea Bermudez 2019

$onmulti
$if     EXIST '../data/INDUSTRY_GGCOMB.inc' $INCLUDE         '../data/INDUSTRY_GGCOMB.inc';
$if not EXIST '../data/INDUSTRY_GGCOMB.inc' $INCLUDE '../../base/data/INDUSTRY_GGCOMB.inc';
$offmulti
