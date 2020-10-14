* Location of GDATA additions used in add-ons

$ifi %BB4%==yes $goto beginbb4

$ifi %COMBTECH%==yes  $include   "../../base/addons/combtech/combtech_gdataadditions.inc";
$ifi %HYDROGEN%==yes  $include   "../../base/addons/hydrogen/hydrogen_gdataadditions.inc";

$ifi not %BB4%==yes $goto endoffile

$label  beginbb4

$ifi %COMBTECH%==yes  $include   "../../base/addons/combtech/bb4/combtech_gdataadditions.inc";
$ifi %HYDROGEN%==yes  $include   "../../base/addons/hydrogen/bb4/hydrogen_gdataadditions.inc";
$ifi %CCS%==yes  $include   "../../base/addons/CCS/bb4/CCS_gdataadditions.inc";   
$ifi %HYDROCAS%==YES     $include   "../../base/addons/hydrocas/hydrocas_gdataadditions.inc";
$ifi %HYDROCAS_FLH%==YES     $include   "../../base/addons/hydrocas/hydrocas_gdataadditions_FLH.inc";    

$label endoffile

