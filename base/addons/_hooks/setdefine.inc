* File setdefine.inc for handling SET definitions for Balmorel addons

$ifi %BB4%==yes $goto bb4_begin 


$ifi %COMBTECH%==yes  $include   "../../base/addons/combtech/combtech_setdefine.inc";

$ifi %FLOWBASED%==yes  $include   "../../base/addons/flowbased/flowbased_setdefine.inc";



$ifi not %BB4%==yes $goto endoffile


$label bb4_begin

$ifi %COMBTECH%==yes  $include   "../../base/addons/combtech/bb4/combtech_setdefine.inc";



$label endoffile 