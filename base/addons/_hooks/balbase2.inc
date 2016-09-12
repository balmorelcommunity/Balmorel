* File balbase2.inc for handling additions of equations an addon in the definition of Balmorel model balbase2

$ifi not %bb2%==yes $goto endoffile

$ifi %COMBTECH%==yes  $include   "../../base/addons/combtech/combtech_balbase2.inc";

$ifi %FLOWBASED%==yes  $include   "../../base/addons/flowbased/FB_AddModel.inc";


                
$label endoffile
