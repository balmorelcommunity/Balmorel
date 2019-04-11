*Offshore grid add-on. Implemented by Juan Gea Bermudez 2019

$onmulti
$if     EXIST '../data/OFFSHOREGRID_XES.inc' $INCLUDE         '../data/OFFSHOREGRID_XES.inc';
$if not EXIST '../data/OFFSHOREGRID_XES.inc' $INCLUDE '../../base/data/OFFSHOREGRID_XES.inc';
$offmulti

