* Latest revision 20180418 (hr)


$ifi %BB4%==yes $goto beginbb4


$ifi not %BB4%==yes $goto endoffile

$label  beginbb4

$ifi %vqdebug%==yes  $include   "../../base/addons/vqdebug/bb4/vqdebug_m2zero.inc";
$ifi  not %RollingSeasons%==yes $ifi %GRIDTARIFFS%==yes $include "../../base/addons/GridTariffs/GridTariffs_postsolve.inc";
$ifi %TAXES%==yes  $include   "../../base/addons/taxes/tax_postsolve.inc";

$ifi not %bb4%==yes $goto endoffile


$label endoffile
