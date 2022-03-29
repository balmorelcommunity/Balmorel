$onmulti
$if     EXIST '../data/OPTIFLOW_TECH_GROUP.inc' $INCLUDE         '../data/OPTIFLOW_TECH_GROUP.inc';
$if not EXIST '../data/OPTIFLOW_TECH_GROUP.inc' $INCLUDE '../../base/data/OPTIFLOW_TECH_GROUP.inc';
$offmulti
