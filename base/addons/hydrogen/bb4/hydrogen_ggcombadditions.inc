$onmulti
$if     EXIST '../data/HYDROGEN_GGCOMB.inc' $INCLUDE         '../data/HYDROGEN_GGCOMB.inc';
$if not EXIST '../data/HYDROGEN_GGCOMB.inc' $INCLUDE '../../base/data/HYDROGEN_GGCOMB.inc';
$offmulti
