* UC Translated to BB4 by Juan Gea Bermúdez 2018.

$onmulti

$if     EXIST '../data/UC_IUCT.inc' $INCLUDE         '../data/UC_IUCT.inc';
$if not EXIST '../data/UC_IUCT.inc' $INCLUDE '../../base/data/UC_IUCT.inc';

$if     EXIST '../data/UC_TECH_TYPE.inc' $INCLUDE         '../data/UC_TECH_TYPE.inc';
$if not EXIST '../data/UC_TECH_TYPE.inc' $INCLUDE '../../base/data/UC_TECH_TYPE.inc';

$if     EXIST '../data/UC_TECH_GROUP.inc' $INCLUDE         '../data/UC_TECH_GROUP.inc';
$if not EXIST '../data/UC_TECH_GROUP.inc' $INCLUDE '../../base/data/UC_TECH_GROUP.inc';

$if     EXIST '../data/UC_FUELS.inc' $INCLUDE         '../data/UC_FUELS.inc';
$if not EXIST '../data/UC_FUELS.inc' $INCLUDE '../../base/data/UC_FUELS.inc';


$ifi not %STEPWISE_RAMPING_UC%==ramp_const_cost $goto STEPWISERAMPING_END
$if     EXIST '../data/RAMPING_RATE.inc' $INCLUDE         '../data/RAMPING_RATE.inc';
$if not EXIST '../data/RAMPING_RATE.inc' $INCLUDE '../../base/data/RAMPING_RATE.inc';
$label  STEPWISERAMPING_END

$offmulti

