*Offshore grid add-on. Implemented by Juan Gea Bermudez 2019



$onmulti
$if     EXIST '../data/OFFSHOREGRID_XLOSS.inc' $INCLUDE         '../data/OFFSHOREGRID_XLOSS.inc';
$if not EXIST '../data/OFFSHOREGRID_XLOSS.inc' $INCLUDE '../../base/data/OFFSHOREGRID_XLOSS.inc';
$offmulti