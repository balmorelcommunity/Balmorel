* File qeeq.inc for Balmorel addons that are relevant for equation QEEQ
* Latest revision 20170419 (hr)

$ifi %HYDROGEN%==yes   $include   "../../base/addons/hydrogen/hydrogen_qeeq.inc";
$ifi not %bb4%==yes $goto bb4end

* The following implemented only for bb4

$ifi %dflexquant%==yes   $include "../../base/addons/demandflexquant/dflexquant_qeeq.inc";


$ifi %dflextime%==yes    $include "../../base/addons/demandflextime/dflextime_qeeq.inc";



$label  bb4end
