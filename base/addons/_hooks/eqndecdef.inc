* Location of equation declarations and definitions used in addons (for any addon where declarations and definitions are in the same file)

$ifi %BB4%==yes $goto beginbb4

$ifi %COMBTECH%==yes $include "..\..\base\addons\combtech\combtech_eqndecdef.inc"
$ifi %HYDROGEN%==yes $include "../../base/addons/hydrogen/hydrogen_eqndecdef.inc"



$ifi not %BB4%==yes $goto endoffile

$label  beginbb4

$ifi %COMBTECH%==yes $include "..\..\base\addons\combtech\bb4\combtech_eqndecdef.inc"


$label endoffile
