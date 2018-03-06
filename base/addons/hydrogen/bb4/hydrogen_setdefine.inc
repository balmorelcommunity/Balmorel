$onmulti
$if     EXIST '../data/HYDROGEN_GGG.inc' $INCLUDE         '../data/HYDROGEN_GGG.inc';
$if not EXIST '../data/HYDROGEN_GGG.inc' $INCLUDE '../../base/data/HYDROGEN_GGG.inc';

$if     EXIST '../data/HYDROGEN_G.inc' $INCLUDE         '../data/HYDROGEN_G.inc';
$if not EXIST '../data/HYDROGEN_G.inc' $INCLUDE '../../base/data/HYDROGEN_G.inc';

*Ida addition
$if     EXIST '../data/HYDROGEN_FFF.inc' $INCLUDE         '../data/HYDROGEN_FFF.inc';
$if not EXIST '../data/HYDROGEN_FFF.inc' $INCLUDE '../../base/data/HYDROGEN_FFF.inc';

$offmulti
