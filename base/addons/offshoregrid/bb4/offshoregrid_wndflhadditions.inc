*Offshore grid add-on. Implemented by Juan Gea Bermudez 2019

$onmulti
$if     EXIST '../data/OFFSHOREGRID_WNDFLH.inc' $INCLUDE         '../data/OFFSHOREGRID_WNDFLH.inc';
$if not EXIST '../data/OFFSHOREGRID_WNDFLH.inc' $INCLUDE '../../base/data/OFFSHOREGRID_WNDFLH.inc';
$offmulti