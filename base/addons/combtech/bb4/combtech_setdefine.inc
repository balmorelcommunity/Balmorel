$onmulti
$if     EXIST '../data/COMBTECH_GGG.inc' $INCLUDE         '../data/COMBTECH_GGG.inc';
$if not EXIST '../data/COMBTECH_GGG.inc' $INCLUDE '../../base/data/COMBTECH_GGG.inc';

$if     EXIST '../data/COMBTECH_G.inc' $INCLUDE         '../data/COMBTECH_G.inc';
$if not EXIST '../data/COMBTECH_G.inc' $INCLUDE '../../base/data/COMBTECH_G.inc';

$if     EXIST '../data/COMBTECH_FFF.inc' $INCLUDE         '../data/COMBTECH_FFF.inc';
$if not EXIST '../data/COMBTECH_FFF.inc' $INCLUDE '../../base/data/COMBTECH_FFF.inc';
$offmulti

SET GGCOMB(GGG,GGG) 'Pair of combination technologies'  %semislash%
$if     EXIST '../data/COMBTECH_GGCOMB.inc' $INCLUDE         '../data/COMBTECH_GGCOMB.inc';
$if not EXIST '../data/COMBTECH_GGCOMB.inc' $INCLUDE '../../base/data/COMBTECH_GGCOMB.inc';
%semislash%;