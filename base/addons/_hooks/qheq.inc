* Location of contributions to the RHS of QHEQ by add-ons
* Latest revision 20170419 (hr)

$ifi %dflexquant%==yes    $include "../../base/addons/demandflexquant/dflexquant_qheq.inc";

$ifi %BB4%==yes $goto beginbb4

$ifi %HYDROGEN%==yes   $include   "../../base/addons/hydrogen/hydrogen_qheq.inc";

$ifi not %BB4%==yes $goto endoffile

$label  beginbb4

$ifi not %bb4%==yes $goto endoffile

$ifi %HYDROGEN%==yes   $include   "../../base/addons/hydrogen/bb4/hydrogen_qheq.inc";

$label endoffile
