* Location of internal parameter delarations used in add-ons
$ifi %BB4%==yes $goto beginbb4

$ifi %HYDROGEN%==yes   $include   "../../base/addons/hydrogen/hydrogen_ipardecdef.inc";

$ifi not %BB4%==yes $goto endoffile

$label  beginbb4

$ifi %HYDROGEN%==yes   $include   "../../base/addons/hydrogen/bb4/hydrogen_ipardecdef.inc";
$ifi %X3V%==yes $include '../../base/addons/x3v/bb4/x3v_ipardecdef.inc';


$label endoffile


