*Industry grid add-on. Implemented by Juan Gea Bermudez 2019

$onmulti
$if     EXIST '../data/INDUSTRY_CCCRRRAAA.inc' $INCLUDE         '../data/INDUSTRY_CCCRRRAAA.inc';
$if not EXIST '../data/INDUSTRY_CCCRRRAAA.inc' $INCLUDE '../../base/data/INDUSTRY_CCCRRRAAA.inc';
$offmulti
