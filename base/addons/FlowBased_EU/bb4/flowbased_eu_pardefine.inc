

$if     EXIST '../data/FB_AC_PTDF.inc' $INCLUDE         '../data/FB_AC_PTDF.inc';
$if not EXIST '../data/FB_AC_PTDF.inc' $INCLUDE '../../base/data/FB_AC_PTDF.inc';

$if     EXIST '../data/FB_AC_RAM.inc' $INCLUDE         '../data/FB_AC_RAM.inc';
$if not EXIST '../data/FB_AC_RAM.inc' $INCLUDE '../../base/data/FB_AC_RAM.inc';

*Change XKINI into INF between FBHUBs. Important! This statement must occur after XKINI is defined, otherwise will not function as intended.
*LOOP(IFBHUB,
*       LOOP (FBHUB,
*               XKINI(YYY,IFBHUB,FBHUB)$((XKINI(YYY,IFBHUB,FBHUB)>0) and (not FB_NTCRRR(IFBHUB,FBHUB)))= INF
*       );
*);

