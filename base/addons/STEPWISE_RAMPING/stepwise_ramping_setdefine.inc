* Stepwise ramping Juan Gea Bermúdez 2018. 

$onmulti


$if     EXIST '../data/UC_TECH_TYPE.inc' $INCLUDE         '../data/UC_TECH_TYPE.inc';
$if not EXIST '../data/UC_TECH_TYPE.inc' $INCLUDE '../../base/data/UC_TECH_TYPE.inc';

$if     EXIST '../data/UC_TECH_GROUP.inc' $INCLUDE         '../data/UC_TECH_GROUP.inc';
$if not EXIST '../data/UC_TECH_GROUP.inc' $INCLUDE '../../base/data/UC_TECH_GROUP.inc';

$if     EXIST '../data/UC_FUELS.inc' $INCLUDE         '../data/UC_FUELS.inc';
$if not EXIST '../data/UC_FUELS.inc' $INCLUDE '../../base/data/UC_FUELS.inc';


$if     EXIST '../data/RAMPING_RATE.inc' $INCLUDE         '../data/RAMPING_RATE.inc';
$if not EXIST '../data/RAMPING_RATE.inc' $INCLUDE '../../base/data/RAMPING_RATE.inc';


$offmulti

