* Include data for the EV addon
PARAMETER EV_BEV_Dumb(YYY,SSS,TTT,RRR);
$if     EXIST '../data/EV_BEV_Dumb.inc' $INCLUDE      '../data/EV_BEV_Dumb.inc';
$if not EXIST '../data/EV_BEV_Dumb.inc'  $INCLUDE '../../base/data/EV_BEV_Dumb.inc';

PARAMETER EV_BEV_SOCDumb(YYY,SSS,TTT,RRR);
$if     EXIST '../data/EV_BEV_SOCDumb.inc' $INCLUDE      '../data/EV_BEV_SOCDumb.inc';
$if not EXIST '../data/EV_BEV_SOCDumb.inc'  $INCLUDE '../../base/data/EV_BEV_SOCDumb.inc';

PARAMETER EV_BEV_Flex(YYY,SSS,TTT,RRR);
$if     EXIST '../data/EV_BEV_Flex.inc' $INCLUDE      '../data/EV_BEV_Flex.inc';
$if not EXIST '../data/EV_BEV_Flex.inc' $INCLUDE '../../base/data/EV_BEV_Flex.inc';

PARAMETER EV_BEV_Inflex(YYY,SSS,TTT,RRR);
$if     EXIST '../data/EV_BEV_Inflex.inc' $INCLUDE         '../data/EV_BEV_Inflex.inc';
$if not EXIST '../data/EV_BEV_Inflex.inc' $INCLUDE '../../base/data/EV_BEV_Inflex.inc';

PARAMETER EV_BEV_SOCFlex(YYY,SSS,TTT,RRR);
$if     EXIST '../data/EV_BEV_SOCFlex.inc' $INCLUDE         '../data/EV_BEV_SOCFlex.inc';
$if not EXIST '../data/EV_BEV_SOCFlex.inc' $INCLUDE '../../base/data/EV_BEV_SOCFlex.inc';

PARAMETER EV_BEV_Avail(YYY,SSS,TTT,RRR);
$if     EXIST '../data/EV_BEV_Avail.inc' $INCLUDE         '../data/EV_BEV_Avail.inc';
$if not EXIST '../data/EV_BEV_Avail.inc' $INCLUDE '../../base/data/EV_BEV_Avail.inc';

PARAMETER EV_BEV_Max(YYY,SSS,TTT,RRR);
$if     EXIST '../data/EV_BEV_Max.inc' $INCLUDE         '../data/EV_BEV_Max.inc';
$if not EXIST '../data/EV_BEV_Max.inc' $INCLUDE '../../base/data/EV_BEV_Max.inc';

PARAMETER EV_BEV_Min(YYY,SSS,TTT,RRR);
$if     EXIST '../data/EV_BEV_Min.inc' $INCLUDE         '../data/EV_BEV_Min.inc';
$if not EXIST '../data/EV_BEV_Min.inc' $INCLUDE '../../base/data/EV_BEV_Min.inc';

PARAMETER EV_PHEV_Dumb(YYY,SSS,TTT,RRR);
$if     EXIST '../data/EV_PHEV_Dumb.inc' $INCLUDE      '../data/EV_PHEV_Dumb.inc';
$if not EXIST '../data/EV_PHEV_Dumb.inc'  $INCLUDE '../../base/data/EV_PHEV_Dumb.inc';

PARAMETER EV_PHEV_SOCDumb(YYY,SSS,TTT,RRR);
$if     EXIST '../data/EV_PHEV_SOCDumb.inc' $INCLUDE      '../data/EV_PHEV_SOCDumb.inc';
$if not EXIST '../data/EV_PHEV_SOCDumb.inc'  $INCLUDE '../../base/data/EV_PHEV_SOCDumb.inc';

PARAMETER EV_PHEV_Flex(YYY,SSS,TTT,RRR);
$if     EXIST '../data/EV_PHEV_Flex.inc' $INCLUDE      '../data/EV_PHEV_Flex.inc';
$if not EXIST '../data/EV_PHEV_Flex.inc' $INCLUDE '../../base/data/EV_PHEV_Flex.inc';

PARAMETER EV_PHEV_Inflex(YYY,SSS,TTT,RRR);
$if     EXIST '../data/EV_PHEV_Inflex.inc' $INCLUDE         '../data/EV_PHEV_Inflex.inc';
$if not EXIST '../data/EV_PHEV_Inflex.inc' $INCLUDE '../../base/data/EV_PHEV_Inflex.inc';

PARAMETER EV_PHEV_SOCFlex(YYY,SSS,TTT,RRR);
$if     EXIST '../data/EV_PHEV_SOCFlex.inc' $INCLUDE         '../data/EV_PHEV_SOCFlex.inc';
$if not EXIST '../data/EV_PHEV_SOCFlex.inc' $INCLUDE '../../base/data/EV_PHEV_SOCFlex.inc';

PARAMETER EV_PHEV_Avail(YYY,SSS,TTT,RRR);
$if     EXIST '../data/EV_PHEV_Avail.inc' $INCLUDE         '../data/EV_PHEV_Avail.inc';
$if not EXIST '../data/EV_PHEV_Avail.inc' $INCLUDE '../../base/data/EV_PHEV_Avail.inc';

PARAMETER EV_PHEV_Max(YYY,SSS,TTT,RRR);
$if     EXIST '../data/EV_PHEV_Max.inc' $INCLUDE         '../data/EV_PHEV_Max.inc';
$if not EXIST '../data/EV_PHEV_Max.inc' $INCLUDE '../../base/data/EV_PHEV_Max.inc';

PARAMETER EV_PHEV_Min(YYY,SSS,TTT,RRR);
$if     EXIST '../data/EV_PHEV_Min.inc' $INCLUDE         '../data/EV_PHEV_Min.inc';
$if not EXIST '../data/EV_PHEV_Min.inc' $INCLUDE '../../base/data/EV_PHEV_Min.inc';

$if     EXIST '../data/EV_TECH_DATA.inc' $INCLUDE         '../data/EV_TECH_DATA.inc';
$if not EXIST '../data/EV_TECH_DATA.inc' $INCLUDE '../../base/data/EV_TECH_DATA.inc';


PARAMETER   EV_VSOC_BEV(YYY,RRR,SSS,TTT)        'State of charge of the BEV vehicle fleet to be used in future runs';
PARAMETER   EV_VSOC_PHEV(YYY,RRR,SSS,TTT)       'State of charge of the PHEV vehicle fleet to be used in future runs';










