* File setdeclare.inc for handling SET declarations for Balmorel addons

$ifi %BB4%==yes $goto beginbb4

$ifi %COMBTECH%==yes  $include   "../../base/addons/combtech/combtech_setdeclare.inc";

$ifi not %HYRSBB123%==none   $include   "../../base/addons/hyrsbb123/hyrsbb123internals.inc";

$ifi %dflexquant%==yes       $include "../../base/addons/demandflexquant/dflexquant_set.inc";

$ifi %FLOWBASED%==yes  $include   "../../base/addons/flowbased/flowbased_setdeclare.inc";

$ifi not %BB4%==yes $goto endoffile

$label  beginbb4

$ifi %COMBTECH%==yes  $include   "../../base/addons/combtech/bb4/combtech_setdeclare.inc";

$ifi %AGKNDISC%==yes  $include   "../../base/addons/AGKNdisc/bb4/agkndisc_setdeclare.inc";

$ifi %X3V%==yes  $include   "../../base/addons/x3v/bb4/x3v_setdeclare.inc";

$ifi %dflexquant%==yes       $include "../../base/addons/demandflexquant/dflexquant_set.inc";

$ifi %STEPWISEPRICE%==yes  $include   "../../base/addons/stepwiseprice/stepwiseprice_setdeclare.inc";

$ifi %LIMITSFORFUELS%==yes  $include   "../../base/addons/limitsforfuels/bb4/limitsforfuels_setdeclare.inc";

$ifi %UnitComm%==yes  $include   "../../base/addons/unitcommitment/bb4/uc_setdeclare.inc";

$ifi %STEPWISE_RAMPING%==yes  $include   "../../base/addons/STEPWISE_RAMPING/stepwise_ramping_setdeclare.inc";

$ifi %DEMANDRESPONSE%==yes      $include        "../../base/addons/demandresponse/bb4/dr_setdeclare.inc";


$label endoffile
