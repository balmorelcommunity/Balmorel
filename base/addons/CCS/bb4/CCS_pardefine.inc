* CCS add-on. Added by Juan Gea Bermudez

$onmulti
$if     EXIST '../data/CCS_CCS_DECO2COMP_G.inc' $INCLUDE         '../data/CCS_CCS_DECO2COMP_G.inc';
$if not EXIST '../data/CCS_CCS_DECO2COMP_G.inc' $INCLUDE '../../base/data/CCS_CCS_DECO2COMP_G.inc';
$offmulti

$onmulti
$if     EXIST '../data/CCS_CCS_CO2CAPTEFF_G.inc' $INCLUDE         '../data/CCS_CCS_CO2CAPTEFF_G.inc';
$if not EXIST '../data/CCS_CCS_CO2CAPTEFF_G.inc' $INCLUDE '../../base/data/CCS_CCS_CO2CAPTEFF_G.inc';
$offmulti

$onmulti
$if     EXIST '../data/CCS_CCS_TRANSPORTCOST.inc' $INCLUDE         '../data/CCS_CCS_TRANSPORTCOST.inc';
$if not EXIST '../data/CCS_CCS_TRANSPORTCOST.inc' $INCLUDE '../../base/data/CCS_CCS_TRANSPORTCOST.inc';
$offmulti

$onmulti
$if     EXIST '../data/CCS_CCS_CO2CAPTVAL_G.inc' $INCLUDE         '../data/CCS_CCS_CO2CAPTVAL_G.inc';
$if not EXIST '../data/CCS_CCS_CO2CAPTVAL_G.inc' $INCLUDE '../../base/data/CCS_CCS_CO2CAPTVAL_G.inc';
$offmulti