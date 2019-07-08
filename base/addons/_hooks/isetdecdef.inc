* Location of internal set delarations and definitions used in addons  (for any addon where declarations and definitions are in the same file)


$ifi %BB4%==yes $goto beginbb4

$ifi %HYDROGEN%==yes  $include   "../../base/addons/hydrogen/hydrogen_isetdecdef.inc";
$ifi %COMBTECH%==yes  $include   "../../base/addons/combtech/combtech_isetdecdef.inc";

$ifi not %BB4%==yes $goto endoffile

$label  beginbb4

$ifi %HYDROGEN%==yes  $include   "../../base/addons/hydrogen/bb4/hydrogen_isetdecdef.inc";
$ifi %UnitComm%==yes  $include   "../../base/addons/unitcommitment/bb4/uc_isetdecdef.inc";
$ifi %STEPWISE_RAMPING%==yes  $include   "../../base/addons/STEPWISE_RAMPING/stepwise_ramping_isetdecdef.inc";
$ifi %AGKNDISC%==yes  $include   "../../base/addons/AGKNdisc/bb4/agkndisc_isetdecdef.inc";
$ifi %COMBTECH%==yes  $include   "../../base/addons/combtech/bb4/combtech_isetdecdef.inc";
$ifi %STEPWISEPRICE%==yes  $include   "../../base/addons/stepwiseprice/stepwiseprice_isetdecdef.inc";
$ifi %LIMITSFORFUELS%==yes  $include   "../../base/addons/limitsforfuels/bb4/limitsforfuels_isetdecdef.inc";
$ifi %GRIDTARIFFS%==yes  $include   "../../base/addons/GridTariffs/bb4/GridTariffs_isetdecdef.inc";
$ifi %DECOM%==yes  $include   "../../base/addons/DECOM/DECOM_isetdecdef.inc";


$label endoffile
