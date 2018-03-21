* Location of equation declarations and definitions used in addons (for any addon where declarations and definitions are in the same file)

$ifi %BB4%==yes $goto beginbb4

$ifi %COMBTECH%==yes $include "../../base/addons/combtech/combtech_eqndecdef.inc"
$ifi %HYDROGEN%==yes $include "../../base/addons/hydrogen/hydrogen_eqndecdef.inc"

$ifi %FLOWBASED%==yes $include "../../base/addons/flowbased/flowbased_eqndecdef.inc"
$ifi %BB3%==yes $ifi not %HYRSBB123%==none     $include "../../base/addons/hyrsbb123/hyrsbb123equations.inc";
$ifi %MAXFOR3FUELS%==yes  $include   "../../base/addons/maxfor3fuels/maxfor3fuels_eqndecdef.inc";

$ifi not %BB4%==yes $goto endoffile

$label  beginbb4

$ifi %COMBTECH%==yes $include "../../base/addons/combtech/bb4/combtech_eqndecdef.inc"
$ifi %HYDROGEN%==yes $include "../../base/addons/hydrogen/bb4/hydrogen_eqndecdef.inc"
$ifi %MAXFOR3FUELS%==yes  $include   "../../base/addons/maxfor3fuels/bb4/maxfor3fuels_eqndecdef.inc";
$ifi %STEPWISEPRICE%==yes  $include   "../../base/addons/stepwiseprice/stepwiseprice_eqndecdef.inc";

$label endoffile
