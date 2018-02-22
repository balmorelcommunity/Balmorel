
$if     EXIST '../data/FBLINE.inc' $INCLUDE         '../data/FBLINE.inc';
$if not EXIST '../data/FBLINE.inc' $INCLUDE '../../base/data/FBLINE.inc';

$if     EXIST '../data/FBHUB.inc' $INCLUDE         '../data/FBHUB.inc';
$if not EXIST '../data/FBHUB.inc' $INCLUDE '../../base/data/FBHUB.inc';

$ifi not %x3v%==yes $goto noX3VinFBCA
$if     EXIST '../data/FBX3VHUB.inc' $INCLUDE         '../data/FBX3VHUB.inc';
$if not EXIST '../data/FBX3VHUB.inc' $INCLUDE '../../base/data/FBX3VHUB.inc';
$label noX3VinFBCA

$if     EXIST '../data/FBX3FXHUB.inc' $INCLUDE         '../data/FBX3FXHUB.inc';
$if not EXIST '../data/FBX3FXHUB.inc' $INCLUDE '../../base/data/FBX3FXHUB.inc';

$if     EXIST '../data/FB_NTCRRR.inc' $INCLUDE         '../data/FB_NTCRRR.inc';
$if not EXIST '../data/FB_NTCRRR.inc' $INCLUDE '../../base/data/FB_NTCRRR.inc';


