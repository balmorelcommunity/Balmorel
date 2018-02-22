* File combtech_setdefine.inc for addon combtech for the Balmorel model

$if     EXIST '../data/GGCOMB.inc' $INCLUDE         '../data/GGCOMB.inc';
$if not EXIST '../data/GGCOMB.inc' $INCLUDE '../../base/data/GGCOMB.inc';
