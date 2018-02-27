* File balbase4.inc for handling additions of equations an addon in the definition of Balmorel model balbase4

$ifi not %bb4%==yes $goto endoffile

$ifi %HYDROGEN%==yes  $include   "../../base/addons/hydrogen/bb4/hydrogen_balbase4.inc";
$ifi %COMBTECH%==yes  $include   "../../base/addons/combtech/bb4/combtech_balbase4.inc";



$label endoffile
