* Latest revision 20180924 (hr)


$ifi %BB4%==yes $goto beginbb4

$ifi not %BB4%==yes $goto endoffile

$label  beginbb4

$ifi %heattrans%==yes  $include   "../../base/addons/heattrans/bb4/heattrans_qdecdef.inc";



$label endoffile
