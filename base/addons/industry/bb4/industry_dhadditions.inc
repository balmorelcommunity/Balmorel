*Industry add-on. Implemented by Juan Gea Bermudez 2019

$onmulti
$if     EXIST '../data/INDUSTRY_DH.inc' $INCLUDE         '../data/INDUSTRY_DH.inc';
$if not EXIST '../data/INDUSTRY_DH.inc' $INCLUDE '../../base/data/INDUSTRY_DH.inc';
$offmulti