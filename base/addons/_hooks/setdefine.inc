* File setdefine.inc for handling SET definitions for Balmorel addons



$ifi %BB4%==yes $goto bb4_begin

*NOTE: Hydrogen add-on is loaded first as some technologies used in combtech comes from the hydrogen add-on.
$ifi %HYDROGEN%==yes  $include   "../../base/addons/hydrogen/hydrogen_setdefine.inc";

$ifi %COMBTECH%==yes  $include   "../../base/addons/combtech/combtech_setdefine.inc";

$ifi %FLOWBASED%==yes  $include   "../../base/addons/flowbased/flowbased_setdefine.inc";

$ifi not %BB4%==yes $goto endoffile


$label bb4_begin

*NOTE: Hydrogen add-on is loaded first as some technologies used in combtech comes from the hydrogen add-on.
$ifi %HYDROGEN%==yes  $include   "../../base/addons/hydrogen/bb4/hydrogen_setdefine.inc";

$ifi %AGKNDISC%==yes  $include   "../../base/addons/AGKNdisc/bb4/agkndisc_setdefine.inc";

$ifi %X3V%==yes  $include   "../../base/addons/x3v/bb4/x3v_setdefine.inc";

$ifi %COMBTECH%==yes  $include   "../../base/addons/combtech/bb4/combtech_setdefine.inc";

$ifi %STEPWISEPRICE%==yes  $include   "../../base/addons/stepwiseprice/stepwiseprice_setdefine.inc";

$ifi %LIMITSFORFUELS%==yes  $include   "../../base/addons/limitsforfuels/bb4/limitsforfuels_setdefine.inc";

$ifi %UnitComm%==yes  $include   "../../base/addons/unitcommitment/bb4/uc_setdefine.inc";

$ifi %STEPWISE_RAMPING%==yes  $include   "../../base/addons/STEPWISE_RAMPING/stepwise_ramping_setdefine.inc";

$ifi %GRIDTARIFFS%==yes  $include   "../../base/addons/GridTariffs/bb4/GridTariffs_setdefine.inc";


$label endoffile
