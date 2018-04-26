* Latest revision 20171023(hr)


$ifi %testbb1234%==yes    $include "../../base/addons/bb1234compare/bb1234_vardeclare.inc";
$ifi %FLOWBASED%==yes  $include   "../../base/addons/flowbased/flowbased_vardeclare.inc";
$ifi %HYRSBB123%==quantprice      $include "../../base/addons/hyrsbb123/hyrsbb123variables.inc";
$ifi %dflexquant%==yes            $include "../../base/addons/demandflexquant/dflexquant_vardeclare.inc";

$ifi %BB4%==yes $goto beginbb4

$ifi %HYDROGEN%==yes  $include   "../../base/addons/hydrogen/hydrogen_vardeclare.inc";

$ifi not %BB4%==yes $goto endoffile

$label  beginbb4

$ifi not %bb4%==yes $goto endoffile

$ifi %HYDROGEN%==yes  $include   "../../base/addons/hydrogen/bb4/hydrogen_vardeclare.inc";
$ifi %STEPWISEPRICE%==yes  $include   "../../base/addons/stepwiseprice/stepwiseprice_vardeclare.inc";

$label endoffile
