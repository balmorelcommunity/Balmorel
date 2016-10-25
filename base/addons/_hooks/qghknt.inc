* File qghknt.inc for handling Balmorel addons relevant for equation QGHKNT

$ifi %BB4%==yes $goto beginbb4

$ifi %combtech%==yes  $include   "../../base/addons/combtech/combtech_qghknt.inc";

$ifi not %BB4%==yes $goto endbb4




$label  beginbb4

$ifi %combtech%==yes  $include   "../../base/addons/combtech/bb4/combtech_qghknt.inc";

$label endbb4