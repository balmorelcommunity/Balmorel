*Offshore grid add-on. Implemented by Juan Gea Bermudez 2019

$onmulti
$if     EXIST '../data/OFFSHOREGRID_WND_VAR_T.inc' $INCLUDE         '../data/OFFSHOREGRID_WND_VAR_T.inc';
$if not EXIST '../data/OFFSHOREGRID_WND_VAR_T.inc' $INCLUDE '../../base/data/OFFSHOREGRID_WND_VAR_T.inc';
$offmulti