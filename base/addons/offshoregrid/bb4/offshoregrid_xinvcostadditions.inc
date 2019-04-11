*Offshore grid add-on. Implemented by Juan Gea Bermudez 2019

$onmulti
$if     EXIST '../data/OFFSHOREGRID_XINVCOST.inc' $INCLUDE         '../data/OFFSHOREGRID_XINVCOST.inc';
$if not EXIST '../data/OFFSHOREGRID_XINVCOST.inc' $INCLUDE '../../base/data/OFFSHOREGRID_XINVCOST.inc';
$offmulti
