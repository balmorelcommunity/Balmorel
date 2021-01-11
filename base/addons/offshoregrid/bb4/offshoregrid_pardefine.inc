*Offshore grid add-on. Implemented by Juan Gea Bermudez 2019

$if     EXIST '../data/OFFSHOREGRID_GINVCOST_ES.inc' $INCLUDE         '../data/OFFSHOREGRID_GINVCOST_ES.inc';
$if not EXIST '../data/OFFSHOREGRID_GINVCOST_ES.inc' $INCLUDE '../../base/data/OFFSHOREGRID_GINVCOST_ES.inc';

$if     EXIST '../data/OFFSHOREGRID_GKN_ES.inc' $INCLUDE         '../data/OFFSHOREGRID_GKN_ES.inc';
$if not EXIST '../data/OFFSHOREGRID_GKN_ES.inc' $INCLUDE '../../base/data/OFFSHOREGRID_GKN_ES.inc';

$if     EXIST '../data/OFFSHOREGRID_XINVCOST_ES.inc' $INCLUDE         '../data/OFFSHOREGRID_XINVCOST_ES.inc';
$if not EXIST '../data/OFFSHOREGRID_XINVCOST_ES.inc' $INCLUDE '../../base/data/OFFSHOREGRID_XINVCOST_ES.inc';

$if     EXIST '../data/OFFSHOREGRID_XKN_ES.inc' $INCLUDE         '../data/OFFSHOREGRID_XKN_ES.inc';
$if not EXIST '../data/OFFSHOREGRID_XKN_ES.inc' $INCLUDE '../../base/data/OFFSHOREGRID_XKN_ES.inc';



