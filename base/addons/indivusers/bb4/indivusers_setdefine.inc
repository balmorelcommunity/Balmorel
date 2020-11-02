*Individual users addon

$onmulti

$if     EXIST '../data/INDIVUSERS_GROUP.inc' $INCLUDE         '../data/INDIVUSERS_GROUP.inc';
$if not EXIST '../data/INDIVUSERS_GROUP.inc' $INCLUDE '../../base/data/INDIVUSERS_GROUP.inc';

$if     EXIST '../data/INDIVUSERS_GROUP_A.inc' $INCLUDE         '../data/INDIVUSERS_GROUP_A.inc';
$if not EXIST '../data/INDIVUSERS_GROUP_A.inc' $INCLUDE '../../base/data/INDIVUSERS_GROUP_A.inc';

$offmulti

