$onmulti
$if     EXIST '../data/HYDROGEN_GKFX.inc' $INCLUDE         '../data/HYDROGEN_GKFX.inc';
$if not EXIST '../data/HYDROGEN_GKFX.inc' $INCLUDE '../../base/data/HYDROGEN_GKFX.inc';
$offmulti
