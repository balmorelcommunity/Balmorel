$onmulti
$if     EXIST '../data/COMBTECH_FDATA.inc' $INCLUDE         '../data/COMBTECH_FDATA.inc';
$if not EXIST '../data/COMBTECH_FDATA.inc' $INCLUDE '../../base/data/COMBTECH_FDATA.inc';
$offmulti
