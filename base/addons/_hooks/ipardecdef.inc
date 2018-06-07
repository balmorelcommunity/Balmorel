* Location of internal parameter delarations used in add-ons
$ifi %BB4%==yes $goto beginbb4

$ifi %HYDROGEN%==yes   $include   "../../base/addons/hydrogen/hydrogen_ipardecdef.inc";

$ifi not %BB4%==yes $goto endoffile

$label  beginbb4

$ifi %HYDROGEN%==yes   $include   "../../base/addons/hydrogen/bb4/hydrogen_ipardecdef.inc";
$ifi %ramping_stepwise%==yes  $include "../../base/addons/ramping_stepwise/bb4/ramping_stepwise_ipardecdef.inc"; 

$label endoffile


