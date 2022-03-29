*Individual users addon

$ifi not %GROUP_DEMAND_SHIFT%==yes $goto NO_GROUP_DEMAND_SHIFT
$onmulti

$if     EXIST '../data/INDIVUSERS_DHUSER.inc' $INCLUDE         '../data/INDIVUSERS_DHUSER.inc';
$if not EXIST '../data/INDIVUSERS_DHUSER.inc' $INCLUDE '../../base/data/INDIVUSERS_DHUSER.inc';

$if     EXIST '../data/INDIVUSERS_GROUP.inc' $INCLUDE         '../data/INDIVUSERS_GROUP.inc';
$if not EXIST '../data/INDIVUSERS_GROUP.inc' $INCLUDE '../../base/data/INDIVUSERS_GROUP.inc';

$if     EXIST '../data/INDIVUSERS_DEMANDTYPE.inc' $INCLUDE         '../data/INDIVUSERS_DEMANDTYPE.inc';
$if not EXIST '../data/INDIVUSERS_DEMANDTYPE.inc' $INCLUDE '../../base/data/INDIVUSERS_DEMANDTYPE.inc';

$if     EXIST '../data/INDIVUSERS_GROUP_A.inc' $INCLUDE         '../data/INDIVUSERS_GROUP_A.inc';
$if not EXIST '../data/INDIVUSERS_GROUP_A.inc' $INCLUDE '../../base/data/INDIVUSERS_GROUP_A.inc';

$if     EXIST '../data/INDIVUSERS_DEMANDTYPE_A.inc' $INCLUDE         '../data/INDIVUSERS_DEMANDTYPE_A.inc';
$if not EXIST '../data/INDIVUSERS_DEMANDTYPE_A.inc' $INCLUDE '../../base/data/INDIVUSERS_DEMANDTYPE_A.inc';

$offmulti
$label NO_GROUP_DEMAND_SHIFT
