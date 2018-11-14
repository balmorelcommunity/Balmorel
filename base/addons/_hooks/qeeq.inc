* File qeeq.inc for Balmorel addons that are relevant for equation QEEQ
* Latest revision 20170419 (hr)
$ifi %BB4%==yes $goto beginbb4

$ifi %HYDROGEN%==yes   $include   "../../base/addons/hydrogen/hydrogen_qeeq.inc";

$ifi not %BB4%==yes $goto endoffile

$label  beginbb4

$ifi %HYDROGEN%==yes   $include   "../../base/addons/hydrogen/bb4/hydrogen_qeeq.inc";
* The following implemented only for bb4

$ifi %X3V%==yes      $include "../../base/addons/x3v/bb4/x3v_qeeq.inc"; 
$ifi %dflexquant%==yes   $include "../../base/addons/demandflexquant/dflexquant_qeeq.inc";

$ifi %dflextime%==yes    $include "../../base/addons/demandflextime/dflextime_qeeq.inc";
$ifi %DEMANDRESPONSE%==yes 	$include 	"../../base/addons/demandresponse/bb4/dr_qeeq.inc";

$ifi %vqdebug%==yes   $setglobal equation qeeq
$ifi %vqdebug%==yes   $include   "../../base/addons/vqdebug/bb4/vqdebug_equations.inc";


$label endoffile
