*Offshore grid add-on. Implemented by Juan Gea Bermudez 2019

$if     EXIST '../data/OFFSHOREGRID_GINVCOST_ES.inc' $INCLUDE         '../data/OFFSHOREGRID_GINVCOST_ES.inc';
$if not EXIST '../data/OFFSHOREGRID_GINVCOST_ES.inc' $INCLUDE '../../base/data/OFFSHOREGRID_GINVCOST_ES.inc';

$if     EXIST '../data/OFFSHOREGRID_GKN_ES.inc' $INCLUDE         '../data/OFFSHOREGRID_GKN_ES.inc';
$if not EXIST '../data/OFFSHOREGRID_GKN_ES.inc' $INCLUDE '../../base/data/OFFSHOREGRID_GKN_ES.inc';

$onmulti
$if     EXIST '../data/OFFSHOREGRID_XINVCOST.inc' $INCLUDE         '../data/OFFSHOREGRID_XINVCOST.inc';
$if not EXIST '../data/OFFSHOREGRID_XINVCOST.inc' $INCLUDE '../../base/data/OFFSHOREGRID_XINVCOST.inc';
$offmulti

$if     EXIST '../data/OFFSHOREGRID_XINVCOST_ES.inc' $INCLUDE         '../data/OFFSHOREGRID_XINVCOST_ES.inc';
$if not EXIST '../data/OFFSHOREGRID_XINVCOST_ES.inc' $INCLUDE '../../base/data/OFFSHOREGRID_XINVCOST_ES.inc';

$if     EXIST '../data/OFFSHOREGRID_XKN_ES.inc' $INCLUDE         '../data/OFFSHOREGRID_XKN_ES.inc';
$if not EXIST '../data/OFFSHOREGRID_XKN_ES.inc' $INCLUDE '../../base/data/OFFSHOREGRID_XKN_ES.inc';

$onmulti
$if     EXIST '../data/OFFSHOREGRID_WNDFLH.inc' $INCLUDE         '../data/OFFSHOREGRID_WNDFLH.inc';
$if not EXIST '../data/OFFSHOREGRID_WNDFLH.inc' $INCLUDE '../../base/data/OFFSHOREGRID_WNDFLH.inc';
$offmulti

$onmulti
$if     EXIST '../data/OFFSHOREGRID_WND_VAR_T.inc' $INCLUDE         '../data/OFFSHOREGRID_WND_VAR_T.inc';
$if not EXIST '../data/OFFSHOREGRID_WND_VAR_T.inc' $INCLUDE '../../base/data/OFFSHOREGRID_WND_VAR_T.inc';
$offmulti

$onmulti
$if     EXIST '../data/OFFSHOREGRID_SUBTECHGROUPKPOT.inc' $INCLUDE         '../data/OFFSHOREGRID_SUBTECHGROUPKPOT.inc';
$if not EXIST '../data/OFFSHOREGRID_SUBTECHGROUPKPOT.inc' $INCLUDE '../../base/data/OFFSHOREGRID_SUBTECHGROUPKPOT.inc';
$offmulti

$onmulti
$if     EXIST '../data/OFFSHOREGRID_XLOSS.inc' $INCLUDE         '../data/OFFSHOREGRID_XLOSS.inc';
$if not EXIST '../data/OFFSHOREGRID_XLOSS.inc' $INCLUDE '../../base/data/OFFSHOREGRID_XLOSS.inc';
$offmulti

$onmulti
$if     EXIST '../data/OFFSHOREGRID_XCOST.inc' $INCLUDE         '../data/OFFSHOREGRID_XCOST.inc';
$if not EXIST '../data/OFFSHOREGRID_XCOST.inc' $INCLUDE '../../base/data/OFFSHOREGRID_XCOST.inc';
$offmulti
