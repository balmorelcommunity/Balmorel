* Location of parameter definitions used in add-ons


$ifi %dflexquant%==yes             $include "../../base/addons/demandflexquant/dflexquant_par.inc";

$ifi %FLOWBASED%==yes $include    "../../base/addons/flowbased/flowbased_pardefine.inc";
*$ifi not %forcedoutage%==''    $include "../../base/addons/forcedoutage/forcedoutage_par.inc";



$ifi %HYDROGEN%==yes  $include   "../../base/addons/hydrogen/hydrogen_pardefine.inc";
