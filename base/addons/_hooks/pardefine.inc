* Location of parameter definitions used in add-ons

%ONOFFDATALISTING%

$ifi %dflexquant%==yes             $include "../../base/addons/demandflexquant/dflexquant_par.inc";

$ifi %FLOWBASED%==yes $include    "../../base/addons/flowbased/flowbased_pardefine.inc";
*$ifi not %forcedoutage%==''    $include "../../base/addons/forcedoutage/forcedoutage_par.inc";

$ifi %BB4%==yes $goto beginbb4

$ifi %HYDROGEN%==yes  $include   "../../base/addons/hydrogen/hydrogen_pardefine.inc";
*This is only tested for BB1 and BB2:
$ifi %COMBTECH%==yes  $include   "../../base/addons/combtech/combtech_pardefine.inc";

$ifi not %BB4%==yes $goto endoffile

$label  beginbb4

$ifi %X3V%==yes  $include   "../../base/addons/x3v/bb4/x3v_pardefine.inc";
$ifi %HYDROGEN%==yes  $include   "../../base/addons/hydrogen/bb4/hydrogen_pardefine.inc";
$ifi %AGKNDISC%==yes  $include   "../../base/addons/agkndisc/bb4/agkndisc_pardefine.inc";
$ifi %COMBTECH%==yes  $include   "../../base/addons/combtech/bb4/combtech_pardefine.inc";
$ifi %STEPWISEPRICE%==yes  $include   "../../base/addons/stepwiseprice/stepwiseprice_pardefine.inc";
$ifi %LIMITSFORFUELS%==yes  $include   "../../base/addons/limitsforfuels/bb4/limitsforfuels_pardefine.inc";
$ifi %ramping_stepwise%==yes  $include "../../base/addons/ramping_stepwise/bb4/ramping_stepwise_pardefine.inc"; 

$label endoffile


