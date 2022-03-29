*Offshore grid add-on. Implemented by Juan Gea Bermudez 2019

$onmulti
$if     EXIST '../data/OFFSHOREGRID_CCCRRRAAA.inc' $INCLUDE         '../data/OFFSHOREGRID_CCCRRRAAA.inc';
$if not EXIST '../data/OFFSHOREGRID_CCCRRRAAA.inc' $INCLUDE '../../base/data/OFFSHOREGRID_CCCRRRAAA.inc';
$offmulti
