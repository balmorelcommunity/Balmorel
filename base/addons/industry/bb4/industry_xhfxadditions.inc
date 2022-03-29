*Industry add-on. Implemented by Juan Gea Bermudez 2019

$onmulti
$if     EXIST '../data/INDUSTRY_XHKFX.inc' $INCLUDE         '../data/INDUSTRY_XHKFX.inc';
$if not EXIST '../data/INDUSTRY_XHKFX.inc' $INCLUDE '../../base/data/INDUSTRY_XHKFX.inc';
$offmulti