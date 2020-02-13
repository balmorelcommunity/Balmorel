*INDUSTRY add-on. Implemented by Juan Gea Bermudez 2019

$onmulti
$if     EXIST '../data/INDUSTRY_DISLOSS_E_AG.inc' $INCLUDE         '../data/INDUSTRY_DISLOSS_E_AG.inc';
$if not EXIST '../data/INDUSTRY_DISLOSS_E_AG.inc' $INCLUDE '../../base/data/INDUSTRY_DISLOSS_E_AG.inc';
$offmulti
