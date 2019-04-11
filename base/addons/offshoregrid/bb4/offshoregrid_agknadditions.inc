*Offshore grid add-on. Implemented by Juan Gea Bermudez 2019

$onmulti
$if     EXIST '../data/OFFSHOREGRID_AGKN.inc' $INCLUDE         '../data/OFFSHOREGRID_AGKN.inc';
$if not EXIST '../data/OFFSHOREGRID_AGKN.inc' $INCLUDE '../../base/data/OFFSHOREGRID_AGKN.inc';
$offmulti
