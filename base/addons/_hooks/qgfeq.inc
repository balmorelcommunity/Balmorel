* Location of contributions to the RHS of QGFEQ by add-ons
* Latest revision 20180920 (ida)


$ifi %BB4%==yes $goto beginbb4


$ifi not %BB4%==yes $goto endoffile

$label  beginbb4

$ifi %HYDROGEN%==yes   $include   "../../base/addons/hydrogen/bb4/hydrogen_qgfeq.inc";
$ifi %UnitComm%==yes  $include   "../../base/addons/unitcommitment/bb4/uc_qgfeq.inc";

$ifi not %bb4%==yes $goto endoffile




$label endoffile
