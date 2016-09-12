* File balbase3.inc for handling additions of equations an addon in the definition of Balmorel model balbase3

$ifi not %bb3%==yes $goto endoffile

$ifi %COMBTECH%==yes  $include   "../../base/addons/combtech/combtech_balbase3.inc";

$ifi %FLOWBASED%==yes  $include   "../../base/addons/flowbased/FB_AddModel.inc";


$label endoffile