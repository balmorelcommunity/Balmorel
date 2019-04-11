*Offshore grid add-on. Implemented by Juan Gea Bermudez 2019

$onmulti
$if     EXIST '../data/OFFSHOREGRID_CCCRRR.inc' $INCLUDE         '../data/OFFSHOREGRID_CCCRRR.inc';
$if not EXIST '../data/OFFSHOREGRID_CCCRRR.inc' $INCLUDE '../../base/data/OFFSHOREGRID_CCCRRR.inc';
$offmulti
