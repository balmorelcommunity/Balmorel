* Location of parameter declarations used in add-ons


%ONOFFCODELISTING%

* Example of a generic line for addon integration (replace ADDONNAME for a specific add-on):
* $ifi %ADDONNAME%==yes    $include "../../base/addons/ADDONNAME/ADDONNAME_pardeclare.inc";


$ifi %FlowBased%==yes    $include "../../base/addons/flowbased/flowbased_pardeclare.inc";

$ifi %BB4%==yes $goto beginbb4

$ifi %HYDROGEN%==yes  $include   "../../base/addons/hydrogen/hydrogen_pardeclare.inc";

$ifi not %BB4%==yes $goto endoffile

$label  beginbb4

$ifi %X3V%==yes  $include   "../../base/addons/x3v/bb4/x3v_pardeclare.inc";
$ifi %AGKNDISC%==yes  $include   "../../base/addons/AGKNdisc/bb4/agkndisc_pardeclare.inc";
$ifi %HYDROGEN%==yes  $include   "../../base/addons/hydrogen/bb4/hydrogen_pardeclare.inc";
$ifi %STEPWISEPRICE%==yes  $include   "../../base/addons/stepwiseprice/stepwiseprice_pardeclare.inc";
$ifi %LIMITSFORFUELS%==yes  $include   "../../base/addons/limitsforfuels/bb4/limitsforfuels_pardeclare.inc";
$ifi %UnitComm%==yes  $include   "../../base/addons/unitcommitment/bb4/uc_pardeclare.inc"; 
$ifi %heattrans%==yes       $include   "../../base/addons/heattrans/bb4/heattrans_pardeclare.inc";

$label endoffile
