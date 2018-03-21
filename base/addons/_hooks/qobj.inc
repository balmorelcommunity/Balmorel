* Location of contributions to QOBJ by add-ons

$ifi %BB3%==yes     $ifi %HYRSBB123%==price      $include  "../../base/addons/hyrsbb123/hyrsbb123addobj.inc";
$ifi %BB3%==yes     $ifi %HYRSBB123%==quantprice $include  "../../base/addons/hyrsbb123/hyrsbb123addobj.inc";

$ifi %dflexquant%==yes   $include "../../base/addons/demandflexquant/dflexquant_qobj.inc";

$ifi %BB4%==yes $goto beginbb4

$ifi %HYDROGEN%==yes   $include   "../../base/addons/hydrogen/hydrogen_qobj.inc";
$ifi %MAXFOR3FUELS%==yes  $include   "../../base/addons/maxfor3fuels/maxfor3fuels_qobj.inc";

$ifi not %BB4%==yes $goto endoffile

$label  beginbb4

$ifi not %bb4%==yes $goto endoffile

$ifi %HYDROGEN%==yes   $include   "../../base/addons/hydrogen/bb4/hydrogen_qobj.inc";
$ifi %MAXFOR3FUELS%==yes  $include   "../../base/addons/maxfor3fuels/bb4/maxfor3fuels_qobj.inc";
$ifi %STEPWISEPRICE%==yes  $include   "../../base/addons/stepwiseprice/stepwiseprice_qobj.inc";

$label endoffile
