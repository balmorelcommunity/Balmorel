$onmulti
$if     EXIST '../data/OPTIFLOW_TECH_GROUP_VALUE.inc' $INCLUDE         '../data/OPTIFLOW_TECH_GROUP_VALUE.inc';
$if not EXIST '../data/OPTIFLOW_TECH_GROUP_VALUE.inc' $INCLUDE '../../base/data/OPTIFLOW_TECH_GROUP_VALUE.inc';
$offmulti
