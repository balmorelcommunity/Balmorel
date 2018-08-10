* File qgfeq.inc for Balmorel addons that are relevant for equation QGFEQ
* Latest revision 20180614 (idje)
$ifi %BB4%==yes $goto beginbb4

$ifi not %BB4%==yes $goto endoffile

$label  beginbb4

$ifi %HYDROGEN%==yes   $include   "../../base/addons/hydrogen/bb4/hydrogen_qgfeq.inc";

$label endoffile
