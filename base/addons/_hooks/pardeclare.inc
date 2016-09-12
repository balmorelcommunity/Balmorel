* Location of parameter declarations used in add-ons

* Example of a generic line for addon integration (replace ADDONNAME for a specific add-on):
* $ifi %ADDONNAME%==yes    $include "../../base/addons/ADDONNAME/ADDONNAME_pardeclare.inc";


$ifi %FlowBased%==yes    $include "../../base/addons/flowbased/FB_pardeclare.inc";