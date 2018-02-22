* Location of parameter definitions used in add-ons

* Example of a generic line for addon integration (replace ADDONNAME for a specific add-on):
* $ifi %ADDONNAME%==yes $include    "../../base/addons/ADDONNAME/ADDONNAME_pardefine.inc";

$ifi %FLOWBASED%==yes $include    "../../base/addons/flowbased/flowbased_pardefine.inc";

$ifi %HYDROGEN%==yes  $include   "../../base/addons/hydrogen/hydrogen_pardefine.inc";
