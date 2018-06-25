* File sim.inc for handling SET definitions for Balmorel addons



$ifi %BB4%==yes $goto bb4_begin

*NOTE: Hydrogen add-on is loaded first as some technologies used in combtech comes from the hydrogen add-on.
$ifi %HYDROGEN%==yes  $include   "../../base/addons/hydrogen/hydrogen_sim.inc";

$ifi %COMBTECH%==yes  $include   "../../base/addons/combtech/combtech_sim.inc";



$ifi not %BB4%==yes $goto endoffile


$label bb4_begin

*NOTE: Hydrogen add-on is loaded first as some technologies used in combtech comes from the hydrogen add-on.
$ifi %HYDROGEN%==yes  $include   "../../base/addons/hydrogen/bb4/hydrogen_sim.inc";
$ifi %UnitComm%==yes      $include   "../../base/addons/unitcommitment/bb4/uc_annual_update.inc";
$ifi %X3V%==yes  $include   "../../base/addons/x3v/bb4/x3v_sim.inc";
$ifi %AGKNDISC%==yes  $include   "../../base/addons/agkndisc/bb4/agkndisc_sim.inc";

$label endoffile
