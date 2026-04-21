

$onmulti
$if     EXIST '../data/PB_LCA_DATASET.inc' $INCLUDE         '../data/PB_LCA_DATASET.inc';
$if not EXIST '../data/PB_LCA_DATASET.inc' $INCLUDE '../../base/data/PB_LCA_DATASET.inc';
$offmulti

$onmulti
$if     EXIST '../data/PB_THRESHOLDS_SET.inc' $INCLUDE         '../data/PB_THRESHOLDS_SET.inc';
$if not EXIST '../data/PB_THRESHOLDS_SET.inc' $INCLUDE '../../base/data/PB_THRESHOLDS_SET.inc';
$offmulti

$onmulti
$if     EXIST '../data/PB_GDTYPE_SET.inc' $INCLUDE         '../data/PB_GDTYPE_SET.inc';
$if not EXIST '../data/PB_GDTYPE_SET.inc' $INCLUDE '../../base/data/PB_GDTYPE_SET.inc';
$offmulti