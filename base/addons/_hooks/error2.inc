* File error2.inc for Balmorel addons, holding check of input data for obvious errors or dubious information
* Last revision 20160614(hr)

$ifi %BB4%==yes $goto beginbb4

$ifi %COMBTECH%==yes $include "../../base/addons/combtech/combtech_error2.inc"

$ifi not %BB4%==yes $goto endoffile

$label  beginbb4


$ifi %COMBTECH%==yes $include "../../base/addons/combtech/bb4/combtech_error2.inc"

$label endoffile
