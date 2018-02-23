* File setdefine.inc for handling SET definitions for Balmorel addons

*NOTE: Hydrogen add-on is loaded first as some technologies used in combtech comes from the hydrogen add-on.
$ifi %HYDROGEN%==yes  $include   "../../base/addons/hydrogen/hydrogen_setdefine.inc";

$ifi %BB4%==yes $goto bb4_begin


$ifi %COMBTECH%==yes  $include   "../../base/addons/combtech/combtech_setdefine.inc";

$ifi %FLOWBASED%==yes  $include   "../../base/addons/flowbased/flowbased_setdefine.inc";



$ifi not %BB4%==yes $goto endoffile


$label bb4_begin

$ifi %COMBTECH%==yes  $include   "../../base/addons/combtech/bb4/combtech_setdefine.inc";

$label endoffile
