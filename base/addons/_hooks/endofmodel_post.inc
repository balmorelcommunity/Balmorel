* To be done immediately after $label ENDOFMODEL in Balmorel.gms
* Compare with endofmodel_pre.inc


$ifi %all_endofmodelgdx%==yes  $include "../../base/addons/all_endofmodelgdx/all_endofmodelgdx.inc";

$ifi %BB4%==yes $ifi %GRIDTARIFFS%==yes EXECUTE_UNLOAD "%relpathoutput%temp/GR_OUT.GDX", GR_FC_OUTPUT_TECH, GR_EC_OUTPUT_TECH, GR_DC_OUTPUT_TECH, GR_EC_OUTPUT_USER, GR_DC_OUTPUT_USER;
