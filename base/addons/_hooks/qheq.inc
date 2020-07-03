* Location of contributions to the RHS of QHEQ by add-ons
* Latest revision 20180418 (hr)

$ifi %dflexquant%==yes    $include "../../base/addons/demandflexquant/dflexquant_qheq.inc";

$ifi %BB4%==yes $goto beginbb4

$ifi %HYDROGEN%==yes   $include   "../../base/addons/hydrogen/hydrogen_qheq.inc";

$ifi not %BB4%==yes $goto endoffile

$label  beginbb4

$ifi not %bb4%==yes $goto endoffile

$ifi %HYDROGEN%==yes   $include   "../../base/addons/hydrogen/bb4/hydrogen_qheq.inc";
$ifi %HEATTRANS%==yes      $include        "../../base/addons/heattrans/bb4/heattrans_qheq.inc";

$ifi %INDHEAT%==yes      $include        "../../base/addons/indheat/indheat_qheq.inc";
$ifi %HEATSAVINGS%==yes         $include         "../../base/addons/heatsavings/heatsavings_qheq.inc";

$ifi %vqdebug%==yes   $setglobal equation qheq
$ifi %vqdebug%==yes   $include   "../../base/addons/vqdebug/bb4/vqdebug_equations.inc";

$ifi %OPTIFLOW%==yes   $include   "../../base/addons/optiflow/bb4/optiflow_qheq.inc";

$label endoffile
