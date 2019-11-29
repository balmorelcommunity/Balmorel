* File sim.inc for handling SET definitions for Balmorel addons



$ifi %BB4%==yes $goto bb4_begin

*NOTE: Hydrogen add-on is loaded first as some technologies used in combtech comes from the hydrogen add-on.
$ifi %HYDROGEN%==yes  $include   "../../base/addons/hydrogen/hydrogen_sim.inc";

$ifi %COMBTECH%==yes  $include   "../../base/addons/combtech/combtech_sim.inc";



$ifi not %BB4%==yes $goto endoffile


$label bb4_begin

$ifi %UnitComm%==yes  $include   "../../base/addons/unitcommitment/bb4/uc_sim.inc";
$ifi %X3V%==yes  $include   "../../base/addons/x3v/bb4/x3v_sim.inc";
$ifi %AGKNDISC%==yes  $include   "../../base/addons/AGKNdisc/bb4/agkndisc_sim.inc";
$ifi %VARIABLE_TRIMMING%==yes           $include       "../../base/addons/variable_trimming/bb4/vt_sim_agknytrim.inc";
$ifi %EV%==yes      $include        "../../base/addons/EV/bb4/EV_sim.inc";
$ifi %DEMANDRESPONSE%==yes      $include        "../../base/addons/demandresponse/bb4/dr_sim.inc";
$ifi %INDHEAT%==yes      $include        "../../base/addons/indheat/indheat_sim.inc"; 
$ifi %SCENARIO3OR4%==YES  $include        "../../base/addons/scenario3_4/scen34_sim.inc";
$ifi %import_results%==YES $include       "../../base/addons/import_results/import_results_sim.inc";

$ifi %DECOM%==yes  $include   "../../base/addons/DECOM/DECOM_sim.inc";
$label endoffile
