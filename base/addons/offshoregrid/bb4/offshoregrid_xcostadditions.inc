*Offshore grid add-on. Implemented by Juan Gea Bermudez 2019



$onmulti
$if     EXIST '../data/OFFSHOREGRID_XCOST.inc' $INCLUDE         '../data/OFFSHOREGRID_XCOST.inc';
$if not EXIST '../data/OFFSHOREGRID_XCOST.inc' $INCLUDE '../../base/data/OFFSHOREGRID_XCOST.inc';
$offmulti
