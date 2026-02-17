* PB add-on. Added by Théo Balanza

$onmulti
$if     EXIST '../data/PB_LCA_DATA_%IAM_Scenario%.inc' $INCLUDE         '../data/PB_LCA_DATA_%IAM_Scenario%.inc';
$if not EXIST '../data/PB_LCA_DATA_%IAM_Scenario%.inc' $INCLUDE '../../base/data/PB_LCA_DATA_%IAM_Scenario%.inc';
$offmulti

$onmulti
$if     EXIST '../data/PB_LCA_DATA_X_%IAM_Scenario%.inc' $INCLUDE         '../data/PB_LCA_DATA_X_%IAM_Scenario%.inc';
$if not EXIST '../data/PB_LCA_DATA_X_%IAM_Scenario%.inc' $INCLUDE '../../base/data/PB_LCA_DATA_X_%IAM_Scenario%.inc';
$offmulti

*$onmulti
*$if     EXIST '../data/PB_LCA_DATA_H2_%IAM_Scenario%.inc' $INCLUDE         '../data/PB_LCA_DATA_H2_%IAM_Scenario%.inc';
*$if not EXIST '../data/PB_LCA_DATA_H2_%IAM_Scenario%.inc' $INCLUDE '../../base/data/PB_LCA_DATA_H2_%IAM_Scenario%.inc';
*$offmulti

$onmulti
$if     EXIST '../data/PB_LCA_DATA_X_H2_%IAM_Scenario%.inc' $INCLUDE         '../data/PB_LCA_DATA_X_H2_%IAM_Scenario%.inc';
$if not EXIST '../data/PB_LCA_DATA_X_H2_%IAM_Scenario%.inc' $INCLUDE '../../base/data/PB_LCA_DATA_X_H2_%IAM_Scenario%.inc';
$offmulti

$ifi not %CCS%==yes goto $No_CCS 
$onmulti
$if     EXIST '../data/PB_LCA_DATA_CCS_%IAM_Scenario%.inc' $INCLUDE         '../data/PB_LCA_DATA_CCS_%IAM_Scenario%.inc';
$if not EXIST '../data/PB_LCA_DATA_CCS_%IAM_Scenario%.inc' $INCLUDE '../../base/data/PB_LCA_DATA_CCS_%IAM_Scenario%.inc';
$offmulti
$label No_CCS 

$onmulti
$if     EXIST '../data/PB_THRESHOLDS_DATA.inc' $INCLUDE         '../data/PB_THRESHOLDS_DATA.inc';
$if not EXIST '../data/PB_THRESHOLDS_DATA.inc' $INCLUDE '../../base/data/PB_THRESHOLDS_DATA.inc';
$offmulti



