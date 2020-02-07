* Location of contributions to OUTPUT_SUMMARY_obj by add-ons

$ifi %GRIDTARIFFS%==yes  $include   "../../base/addons/GridTariffs/GridTariffs_outputs_obj.inc";
$ifi %TAXES%==yes  $include   "../../base/addons/taxes/tax_outputs_obj.inc";
$ifi %DEMANDRESPONSE%==yes      $include        "../../base/addons/demandresponse/bb4/dr_outputs_obj.inc";
$ifi %EV%==yes      $include        "../../base/addons/EV/bb4/EV_outputs_obj.inc";
