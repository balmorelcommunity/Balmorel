* Location of GDATA additions used in add-ons

$ifi %BB4%==yes $goto beginbb4

$ifi %COMBTECH%==yes  $include   "../../base/addons/combtech/combtech_gdataadditions.inc";
$ifi %HYDROGEN%==yes  $include   "../../base/addons/hydrogen/hydrogen_gdataadditions.inc";

$ifi not %BB4%==yes $goto endoffile

$label  beginbb4

$ifi %COMBTECH%==yes  $include   "../../base/addons/combtech/bb4/combtech_gdataadditions.inc";
$ifi %HYDROGEN%==yes  $include   "../../base/addons/hydrogen/bb4/hydrogen_gdataadditions.inc";
$ifi %DATACENTERS%==yes     $include   "../../base/addons/datacenters/bb4/datacenters_gdataadditions.inc";

$label endoffile

$ifi %INDIVUSERS%==yes  $ifi %GROUP_DEMAND_SHIFT%==yes  $include   "../../base/addons/indivusers/bb4/indivusers_gdataadditions.inc";
