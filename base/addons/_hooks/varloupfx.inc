* Assingments of .lo, .up and .fx for variables used in add-ons

$ifi %dflexquant%==yes          $include "../../base/addons/demandflexquant/dflexquant_varloupfx.inc";
$ifi %OPTIFLOW%==yes            $include "../../base/addons/optiflow/bb4/optiflow_varloupfx.inc";


$ontext
*todo
$ifi not %forcedoutage%==''     $include "../../base/addons/forcedoutage/forcedoutage_code.inc";
$offtext
