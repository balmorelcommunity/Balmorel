
$onmulti
SET GGCOMB(GGG,GGG) 'Pair of combination technologies'  %semislash%
$if     EXIST '../data/COMBTECH_GGCOMB.inc' $INCLUDE         '../data/COMBTECH_GGCOMB.inc';
$if not EXIST '../data/COMBTECH_GGCOMB.inc' $INCLUDE '../../base/data/COMBTECH_GGCOMB.inc';
%semislash%;
*------------- Any GGCOMB additions for addon to be placed here: ----------------
$include "../../base/addons/_hooks/ggcombadditions.inc"
$offmulti
