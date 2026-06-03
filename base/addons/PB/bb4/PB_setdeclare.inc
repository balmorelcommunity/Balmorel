*-------------------------------------------------------------------------------
* PB_setdeclare.inc  --  Populate PB set elements from per-scenario data files
*-------------------------------------------------------------------------------
* Part of the Balmorel Planetary Boundaries (PB) add-on.
*
* Loads the actual elements of the three PB sets (declared in PB_setdefine.inc).
* Each set is loaded with the standard scenario-overrides-base pattern:
*     if  ../data/<file> exists in the active scenario, use that;
*     else fall back to the canonical copy in ../../base/data/<file>.
*
* The $onmulti / $offmulti pair lets the set be (re)populated without raising
* a "set redeclared" error -- needed because the bare SET <name>; statements
* in PB_setdefine.inc create empty sets that we now fill.
*
* Authors: Theo Balanza & Dhruv Sharma
*-------------------------------------------------------------------------------

* --- PB_LCA_DATASET (LCA impact-category x suffix labels) ---------------------
$onmulti
$if     EXIST '../data/PB_LCA_DATASET.inc' $INCLUDE         '../data/PB_LCA_DATASET.inc';
$if not EXIST '../data/PB_LCA_DATASET.inc' $INCLUDE '../../base/data/PB_LCA_DATASET.inc';
$offmulti

* --- PB_THRESHOLDS_SET (sector SOS threshold keys) ----------------------------
$onmulti
$if     EXIST '../data/PB_THRESHOLDS_SET.inc' $INCLUDE         '../data/PB_THRESHOLDS_SET.inc';
$if not EXIST '../data/PB_THRESHOLDS_SET.inc' $INCLUDE '../../base/data/PB_THRESHOLDS_SET.inc';
$offmulti

* --- PB_GDTYPE_SET (generator-type labels for PB_LCA_DATA) --------------------
$onmulti
$if     EXIST '../data/PB_GDTYPE_SET.inc' $INCLUDE         '../data/PB_GDTYPE_SET.inc';
$if not EXIST '../data/PB_GDTYPE_SET.inc' $INCLUDE '../../base/data/PB_GDTYPE_SET.inc';
$offmulti

* --- PB_RULE_CONFIG (rolling-foresight: threshold-type classification + scalar) -
* Declares+populates PB_THRESHOLD_TYPE_CUMULATIVE, PB_THRESHOLD_TYPE_STEADY_STATE
* subsets of PB_THRESHOLDS_SET and the scalar PB_RF_FLOOR_FRAC. Must come AFTER
* the PB_THRESHOLDS_SET block above. Gated by PB_ROLLING_FORESIGHT (balopt.opt).
$ifi %PB_ROLLING_FORESIGHT%==yes $if     EXIST '../data/PB_RULE_CONFIG.inc' $INCLUDE         '../data/PB_RULE_CONFIG.inc';
$ifi %PB_ROLLING_FORESIGHT%==yes $if not EXIST '../data/PB_RULE_CONFIG.inc' $INCLUDE '../../base/data/PB_RULE_CONFIG.inc';
