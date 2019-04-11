*Offshore grid add-on. Implemented by Juan Gea Bermudez 2019

$onmulti
$if     EXIST '../data/OFFSHOREGRID_AAA.inc' $INCLUDE         '../data/OFFSHOREGRID_AAA.inc';
$if not EXIST '../data/OFFSHOREGRID_AAA.inc' $INCLUDE '../../base/data/OFFSHOREGRID_AAA.inc';
$offmulti
