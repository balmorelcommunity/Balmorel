* Include data for the EV addon
$if     EXIST '../data/EV_BEV_Dumb.inc' $INCLUDE      '../data/EV_BEV_Dumb.inc';
$if not EXIST '../data/EV_BEV_Dumb.inc'  $INCLUDE '../../base/data/EV_BEV_Dumb.inc';

$if     EXIST '../data/EV_BEV_SOCDumb.inc' $INCLUDE      '../data/EV_BEV_SOCDumb.inc';
$if not EXIST '../data/EV_BEV_SOCDumb.inc'  $INCLUDE '../../base/data/EV_BEV_SOCDumb.inc';

$if     EXIST '../data/EV_BEV_Flex.inc' $INCLUDE      '../data/EV_BEV_Flex.inc';
$if not EXIST '../data/EV_BEV_Flex.inc' $INCLUDE '../../base/data/EV_BEV_Flex.inc';

$if     EXIST '../data/EV_BEV_Inflex.inc' $INCLUDE         '../data/EV_BEV_Inflex.inc';
$if not EXIST '../data/EV_BEV_Inflex.inc' $INCLUDE '../../base/data/EV_BEV_Inflex.inc';

$if     EXIST '../data/EV_BEV_SOCFlex.inc' $INCLUDE         '../data/EV_BEV_SOCFlex.inc';
$if not EXIST '../data/EV_BEV_SOCFlex.inc' $INCLUDE '../../base/data/EV_BEV_SOCFlex.inc';

$if     EXIST '../data/EV_BEV_Avail.inc' $INCLUDE         '../data/EV_BEV_Avail.inc';
$if not EXIST '../data/EV_BEV_Avail.inc' $INCLUDE '../../base/data/EV_BEV_Avail.inc';

$if     EXIST '../data/EV_BEV_Max.inc' $INCLUDE         '../data/EV_BEV_Max.inc';
$if not EXIST '../data/EV_BEV_Max.inc' $INCLUDE '../../base/data/EV_BEV_Max.inc';

$if     EXIST '../data/EV_BEV_Min.inc' $INCLUDE         '../data/EV_BEV_Min.inc';
$if not EXIST '../data/EV_BEV_Min.inc' $INCLUDE '../../base/data/EV_BEV_Min.inc';


$if     EXIST '../data/EV_PHEV_Dumb.inc' $INCLUDE      '../data/EV_PHEV_Dumb.inc';
$if not EXIST '../data/EV_PHEV_Dumb.inc'  $INCLUDE '../../base/data/EV_PHEV_Dumb.inc';

$if     EXIST '../data/EV_PHEV_SOCDumb.inc' $INCLUDE      '../data/EV_PHEV_SOCDumb.inc';
$if not EXIST '../data/EV_PHEV_SOCDumb.inc'  $INCLUDE '../../base/data/EV_PHEV_SOCDumb.inc';

$if     EXIST '../data/EV_PHEV_Flex.inc' $INCLUDE      '../data/EV_PHEV_Flex.inc';
$if not EXIST '../data/EV_PHEV_Flex.inc' $INCLUDE '../../base/data/EV_PHEV_Flex.inc';

$if     EXIST '../data/EV_PHEV_Inflex.inc' $INCLUDE         '../data/EV_PHEV_Inflex.inc';
$if not EXIST '../data/EV_PHEV_Inflex.inc' $INCLUDE '../../base/data/EV_PHEV_Inflex.inc';

$if     EXIST '../data/EV_PHEV_SOCFlex.inc' $INCLUDE         '../data/EV_PHEV_SOCFlex.inc';
$if not EXIST '../data/EV_PHEV_SOCFlex.inc' $INCLUDE '../../base/data/EV_PHEV_SOCFlex.inc';

$if     EXIST '../data/EV_PHEV_Avail.inc' $INCLUDE         '../data/EV_PHEV_Avail.inc';
$if not EXIST '../data/EV_PHEV_Avail.inc' $INCLUDE '../../base/data/EV_PHEV_Avail.inc';

$if     EXIST '../data/EV_PHEV_Max.inc' $INCLUDE         '../data/EV_PHEV_Max.inc';
$if not EXIST '../data/EV_PHEV_Max.inc' $INCLUDE '../../base/data/EV_PHEV_Max.inc';

$if     EXIST '../data/EV_PHEV_Min.inc' $INCLUDE         '../data/EV_PHEV_Min.inc';
$if not EXIST '../data/EV_PHEV_Min.inc' $INCLUDE '../../base/data/EV_PHEV_Min.inc';

$if     EXIST '../data/EV_TECH_DATA.inc' $INCLUDE         '../data/EV_TECH_DATA.inc';
$if not EXIST '../data/EV_TECH_DATA.inc' $INCLUDE '../../base/data/EV_TECH_DATA.inc';

*$ontext
EV_BEV_SOCFlex('2025',S,T,IR)    = EV_BEV_SOCFlex('2020',S,T,IR) ;
EV_BEV_Flex('2025',S,T,IR) = EV_BEV_Flex('2020',S,T,IR);
EV_BEV_Avail('2025',S,T,IR) = EV_BEV_Avail('2020',S,T,IR) ;
EV_BEV_CHARGERCAP('2025') = EV_BEV_CHARGERCAP('2020') ;
EV_BEV_Inflex('2025',S,T,IR) = EV_BEV_Inflex('2020',S,T,IR);
EV_PHEV_SOCFlex('2025',S,T,IR) = EV_PHEV_SOCFlex('2020',S,T,IR);
EV_PHEV_Flex('2025',S,T,IR) = EV_PHEV_Flex('2020',S,T,IR);
EV_PHEV_Avail('2025',S,T,IR) = EV_PHEV_Avail('2020',S,T,IR);
EV_PHEV_CHARGERCAP('2025') = EV_PHEV_CHARGERCAP('2020');
EV_PHEV_Inflex('2025',S,T,IR) = EV_PHEV_Inflex('2020',S,T,IR);
EV_BEV_Max('2025',S,T,IR) = EV_BEV_Max('2020',S,T,IR);
EV_PHEV_Max('2025',S,T,IR) = EV_PHEV_Max('2020',S,T,IR);
EV_BEV_Min('2025',S,T,IR) = EV_BEV_Min('2020',S,T,IR);
EV_PHEV_Min('2025',S,T,IR) = EV_PHEV_Min('2020',S,T,IR);

EV_BEV_Dumb('2025',S,T,IR) = EV_BEV_Dumb('2020',S,T,IR);
EV_PHEV_Dumb('2025',S,T,IR) = EV_PHEV_Dumb('2020',S,T,IR);

EV_BEV_CHARGERCAP('2025') = EV_BEV_CHARGERCAP('2020');
EV_PHEV_CHARGERCAP('2025') = EV_PHEV_CHARGERCAP('2020');

EV_PEFF('2025') = EV_PEFF('2020');
EV_BATTOVERSIZED('2025') = EV_BATTOVERSIZED('2020');
EV_LIFEFACTOR('2025') = EV_LIFEFACTOR('2020') ;
EV_BATTCOST('2025') = EV_BATTCOST('2020');
EV_BATTDEGCYCLE('2025') = EV_BATTDEGCYCLE('2020');
EV_BATTDEGCALCONST('2025') = EV_BATTDEGCALCONST('2020');
EV_BATTDEGCALFLEX('2025') = EV_BATTDEGCALFLEX('2020');
EV_CHARGERCOST('2025') = EV_CHARGERCOST('2020');

*$offtext