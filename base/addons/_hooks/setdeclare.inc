* File setdeclare.inc for handling SET declarations for Balmorel addons
*HYDROGEN not checked for BB4
$ifi %HYDROGEN%==yes  $include   "../../base/addons/hydrogen/hydrogen_setdeclare.inc";

$ifi %BB4%==yes $goto beginbb4

$ifi %COMBTECH%==yes  $include   "../../base/addons/combtech/combtech_setdeclare.inc";

$ifi not %HYRSBB123%==none   $include   "../../base/addons/hyrsbb123/hyrsbb123internals.inc";

$ifi %dflexquant%==yes       $include "../../base/addons/demandflexquant/dflexquant_set.inc";

$ifi %FLOWBASED%==yes  $include   "../../base/addons/flowbased/flowbased_setdeclare.inc";
$ifi not %BB4%==yes $goto endoffile

$label  beginbb4

$ifi %COMBTECH%==yes  $include   "../../base/addons/combtech/bb4/combtech_setdeclare.inc";

$ifi %dflexquant%==yes       $include "../../base/addons/demandflexquant/dflexquant_set.inc";

$label endoffile
