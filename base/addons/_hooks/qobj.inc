* Location of contributions to QOBJ by add-ons

$ifi %BB3%==yes     $ifi %HYRSBB123%==price      $include  "../../base/addons/hyrsbb123/hyrsbb123addobj.inc";
$ifi %BB3%==yes     $ifi %HYRSBB123%==quantprice $include  "../../base/addons/hyrsbb123/hyrsbb123addobj.inc";

$ifi %dflexquant%==yes   $include "../../base/addons/demandflexquant/dflexquant_qobj.inc";

$ifi %BB4%==yes $goto beginbb4

$ifi %HYDROGEN%==yes   $include   "../../base/addons/hydrogen/hydrogen_qobj.inc";

$ifi not %BB4%==yes $goto endoffile

$label  beginbb4

$ifi not %bb4%==yes $goto endoffile

$ifi %HYDROGEN%==yes   $include   "../../base/addons/hydrogen/bb4/hydrogen_qobj.inc";
$ifi %UnitComm%==yes   $include   "../../base/addons/unitcommitment/bb4/uc_qobj.inc";
$ifi %X3V%==yes $include "../../base/addons/x3v/bb4/x3v_qobj.inc";
$ifi %AGKNDISC%==yes $include "../../base/addons/agkndisc/bb4/agkndisc_qobj.inc";
$ifi %STEPWISEPRICE%==yes  $include   "../../base/addons/stepwiseprice/stepwiseprice_qobj.inc";
$ifi %LIMITSFORFUELS%==yes  $include   "../../base/addons/limitsforfuels/bb4/limitsforfuels_qobj.inc";
$ifi %ramping_stepwise%==yes  $include "../../base/addons/ramping_stepwise/bb4/ramping_stepwise_qobj.inc"; 

$ifi %vqdebug%==yes   $setglobal equation qobj
$ifi %vqdebug%==yes   $include   "../../base/addons/vqdebug/bb4/vqdebug_equations.inc";


$label endoffile
