* File balbase4.inc for handling additions of equations an addon in the definition of Balmorel model balbase4

$ifi not %bb4%==yes $goto endoffile

$ifi %X3V%==yes    $include   "../../base/addons/x3v/bb4/x3v_balbase4.inc";
$ifi %HYDROGEN%==yes  $include   "../../base/addons/hydrogen/bb4/hydrogen_balbase4.inc";
$ifi %UnitComm%==yes      $include   "../../base/addons/unitcommitment/bb4/uc_balbase4.inc";
$ifi %COMBTECH%==yes  $include   "../../base/addons/combtech/bb4/combtech_balbase4.inc";
$ifi %AGKNDISC%==yes  $include   "../../base/addons/agkndisc/bb4/agkndisc_balbase4.inc";

$ifi %STEPWISEPRICE%==yes  $include   "../../base/addons/stepwiseprice/stepwiseprice_balbase4.inc";
$ifi %LIMITSFORFUELS%==yes  $include   "../../base/addons/limitsforfuels/bb4/limitsforfuels_balbase4.inc";
$ifi %ramping_stepwise%==yes  $include "../../base/addons/ramping_stepwise/bb4/ramping_stepwise_balbase4.inc";   

$label endoffile
