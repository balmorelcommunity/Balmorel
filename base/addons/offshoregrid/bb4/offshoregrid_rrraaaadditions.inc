*Offshore grid add-on. Implemented by Juan Gea Bermudez 2019

$onmulti
$if     EXIST '../data/OFFSHOREGRID_RRRAAA.inc' $INCLUDE         '../data/OFFSHOREGRID_RRRAAA.inc';
$if not EXIST '../data/OFFSHOREGRID_RRRAAA.inc' $INCLUDE '../../base/data/OFFSHOREGRID_RRRAAA.inc';
$offmulti
