* File balbase4.inc for handling additions of equations an addon in the definition of Balmorel model balbase4

$ifi not %bb4%==yes $goto endoffile

$ifi %X3V%==yes    $include   "../../base/addons/x3v/bb4/x3v_balbase4.inc";
$ifi %HYDROGEN%==yes  $include   "../../base/addons/hydrogen/bb4/hydrogen_balbase4.inc";
$ifi %UnitComm%==yes      $include   "../../base/addons/unitcommitment/bb4/uc_balbase4.inc";
$ifi %COMBTECH%==yes  $include   "../../base/addons/combtech/bb4/combtech_balbase4.inc";
$ifi %AGKNDISC%==yes  $include   "../../base/addons/AGKNdisc/bb4/agkndisc_balbase4.inc";

$ifi %STEPWISEPRICE%==yes  $include   "../../base/addons/stepwiseprice/stepwiseprice_balbase4.inc";
$ifi %LIMITSFORFUELS%==yes  $include   "../../base/addons/limitsforfuels/bb4/limitsforfuels_balbase4.inc";
$ifi %GRIDTARIFFS%==yes  $include   "../../base/addons/GridTariffs/GridTariffs_balbase4.inc";
$ifi %DEMANDRESPONSE%==yes      $include        "../../base/addons/demandresponse/bb4/dr_balbase4.inc";
$ifi %EV%==yes      $include        "../../base/addons/EV/bb4/EV_balbase4.inc";
$ifi %FBEU%==yes      $include        "../../base/addons/FlowBased_EU/bb4/flowbased_eu_balbase4.inc";
$ifi %STEPWISEKPOT%==YES    $include   "../../base/addons/stepwisekpot/steppot_balbase4.inc";
$ifi %INDHEAT%==yes  $include   "../../base/addons/indheat/indheat_balbase4.inc";


$label endoffile
