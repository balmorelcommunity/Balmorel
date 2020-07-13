$onmulti
$if     EXIST '../data/HYDROGEN_FDATA.inc' $INCLUDE         '../data/HYDROGEN_FDATA.inc';
$if not EXIST '../data/HYDROGEN_FDATA.inc' $INCLUDE '../../base/data/HYDROGEN_FDATA.inc';
$offmulti
