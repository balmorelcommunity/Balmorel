* Latest revision 20180418 (hr)


$ifi %BB4%==yes $goto beginbb4


$ifi not %BB4%==yes $goto endoffile

$label  beginbb4

$ifi %vqdebug%==yes  $include   "../../base/addons/vqdebug/bb4/vqdebug_m2zero.inc";


$ifi not %bb4%==yes $goto endoffile


$label endoffile
