*Industry add-on. Implemented by Juan Gea Bermudez 2019

$onmulti
$if     EXIST '../data/INDUSTRY_XHINVCOST.inc' $INCLUDE         '../data/INDUSTRY_XHINVCOST.inc';
$if not EXIST '../data/INDUSTRY_XHINVCOST.inc' $INCLUDE '../../base/data/INDUSTRY_XHINVCOST.inc';
$offmulti
