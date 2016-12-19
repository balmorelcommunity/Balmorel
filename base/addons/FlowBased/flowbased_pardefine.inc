

$if     EXIST '../data/FBPTDF_VAR_T.inc' $INCLUDE         '../data/FBPTDF_VAR_T.inc';
$if not EXIST '../data/FBPTDF_VAR_T.inc' $INCLUDE '../../base/data/FBPTDF_VAR_T.inc';

$if     EXIST '../data/FBRAM.inc' $INCLUDE         '../data/FBRAM.inc';
$if not EXIST '../data/FBRAM.inc' $INCLUDE '../../base/data/FBRAM.inc';

*Change XKINI into INF between FBHUBs. Important! This statement must occur after XKINI is defined, otherwise will not function as intended.
LOOP(IFBHUB,
       LOOP (FBHUB,
               XKINI(YYY,IFBHUB,FBHUB)$((XKINI(YYY,IFBHUB,FBHUB)>0) and (not FB_NTCRRR(IFBHUB,FBHUB)))= INF
       );
);

