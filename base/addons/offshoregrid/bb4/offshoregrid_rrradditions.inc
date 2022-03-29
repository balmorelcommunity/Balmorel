*Offshore grid add-on. Implemented by Juan Gea Bermudez 2019

$onmulti
$if     EXIST '../data/OFFSHOREGRID_RRR.inc' $INCLUDE         '../data/OFFSHOREGRID_RRR.inc';
$if not EXIST '../data/OFFSHOREGRID_RRR.inc' $INCLUDE '../../base/data/OFFSHOREGRID_RRR.inc';
$offmulti
