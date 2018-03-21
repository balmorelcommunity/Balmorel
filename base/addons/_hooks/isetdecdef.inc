* Location of internal set delarations and definitions used in addons  (for any addon where declarations and definitions are in the same file)


$ifi %BB4%==yes $goto beginbb4

$ifi %HYDROGEN%==yes  $include   "../../base/addons/hydrogen/hydrogen_isetdecdef.inc";
$ifi %COMBTECH%==yes  $include   "../../base/addons/combtech/combtech_isetdecdef.inc";

$ifi not %BB4%==yes $goto endoffile

$label  beginbb4

$ifi %HYDROGEN%==yes  $include   "../../base/addons/hydrogen/bb4/hydrogen_isetdecdef.inc";
$ifi %COMBTECH%==yes  $include   "../../base/addons/combtech/bb4/combtech_isetdecdef.inc";
$ifi %STEPWISEPRICE%==yes  $include   "../../base/addons/stepwiseprice/stepwiseprice_isetdecdef.inc";

$label endoffile
