* File balbase1.inc for handling additions of equations an addon in the definition of Balmorel model balbase1

$ifi not %bb1%==yes $goto endoffile

$ifi %COMBTECH%==yes  $include   "../../base/addons/combtech/combtech_balbase1.inc";
$ifi %HYDROGEN%==yes  $include   "../../base/addons/hydrogen/hydrogen_balbase1.inc";

$ifi %FLOWBASED%==yes  $include   "../../base/addons/flowbased/flowbased_balbase1.inc";

$label endoffile

