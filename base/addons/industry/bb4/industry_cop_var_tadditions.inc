*Industry add-on. Implemented by Juan Gea Bermudez 2019

$onmulti
$if     EXIST '../data/INDUSTRY_COP_VAR_T.inc' $INCLUDE         '../data/INDUSTRY_COP_VAR_T.inc';
$if not EXIST '../data/INDUSTRY_COP_VAR_T.inc' $INCLUDE '../../base/data/INDUSTRY_COP_VAR_T.inc';
$offmulti
