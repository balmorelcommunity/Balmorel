*Industry add-on. Implemented by Juan Gea Bermudez 2019

$onmulti
$if     EXIST '../data/INDUSTRY_SOLHFLH.inc' $INCLUDE         '../data/INDUSTRY_SOLHFLH.inc';
$if not EXIST '../data/INDUSTRY_SOLHFLH.inc' $INCLUDE '../../base/data/INDUSTRY_SOLHFLH.inc';
$offmulti
