* File balbase3.inc for handling additions of equations an addon in the definition of Balmorel model balbase3

$ifi not %bb3%==yes $goto endoffile

$ifi %COMBTECH%==yes  $include   "../../base/addons/combtech/combtech_balbase3.inc";
$ifi %HYDROGEN%==yes  $include   "../../base/addons/hydrogen/hydrogen_balbase3.inc";

$ifi %FLOWBASED%==yes  $include   "../../base/addons/flowbased/flowbased_balbase3.inc";
$ifi not %HYRSBB123%==none $include  "../../base/addons/hyrsbb123/hyrsbb123balbase3.inc";

$label endoffile
