*Industry add-on. Implemented by Juan Gea Bermudez 2019

$onmulti
$if     EXIST '../data/INDUSTRY_XHMAXK.inc' $INCLUDE         '../data/INDUSTRY_XHMAXK.inc';
$if not EXIST '../data/INDUSTRY_XHMAXK.inc' $INCLUDE '../../base/data/INDUSTRY_XHMAXK.inc';
$offmulti