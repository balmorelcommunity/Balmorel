* File setdefine.inc for handling SET definitions for Balmorel addons

*NOTE: Hydrogen add-on is loaded first as some technologies used in combtech comes from the hydrogen add-on.
$ifi %HYDROGEN%==yes  $include   "../../base/addons/hydrogen/hydrogen_setdefine.inc";
$ifi %COMBTECH%==yes  $include   "../../base/addons/combtech/combtech_setdefine.inc";


$ifi %FLOWBASED%==yes  $include   "../../base/addons/flowbased/flowbased_setdefine.inc";