
$onmulti

$if     EXIST '../data/RAMPING_TECH_TYPE.inc' $INCLUDE         '../data/RAMPING_TECH_TYPE.inc';
$if not EXIST '../data/RAMPING_TECH_TYPE.inc' $INCLUDE '../../base/data/RAMPING_TECH_TYPE.inc';

$if     EXIST '../data/RAMPING_TECH_GROUP.inc' $INCLUDE         '../data/RAMPING_TECH_GROUP.inc';
$if not EXIST '../data/RAMPING_TECH_GROUP.inc' $INCLUDE '../../base/data/RAMPING_TECH_GROUP.inc';

$if     EXIST '../data/RAMPING_FUELS.inc' $INCLUDE         '../data/RAMPING_FUELS.inc';
$if not EXIST '../data/RAMPING_FUELS.inc' $INCLUDE '../../base/data/RAMPING_FUELS.inc';

$if     EXIST '../data/RAMPING_RATE.inc' $INCLUDE         '../data/RAMPING_RATE.inc';
$if not EXIST '../data/RAMPING_RATE.inc' $INCLUDE '../../base/data/RAMPING_RATE.inc';

$offmulti



