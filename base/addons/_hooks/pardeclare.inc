* Location of parameter declarations used in add-ons

* Example of a generic line for addon integration (replace ADDONNAME for a specific add-on):
* $ifi %ADDONNAME%==yes    $include "../../base/addons/ADDONNAME/ADDONNAME_pardeclare.inc";


$ifi %FlowBased%==yes    $include "../../base/addons/flowbased/flowbased_pardeclare.inc";

$ifi %BB4%==yes $goto beginbb4

$ifi %HYDROGEN%==yes  $include   "../../base/addons/hydrogen/hydrogen_pardeclare.inc";

$ifi not %BB4%==yes $goto endoffile

$label  beginbb4

$ifi %HYDROGEN%==yes  $include   "../../base/addons/hydrogen/bb4/hydrogen_pardeclare.inc";
$ifi %LIMITSFORFUELS%==yes  $include   "../../base/addons/limitsforfuels/bb4/limitsforfuels_pardeclare.inc";

$label endoffile
