* Latest revision 20180418 (hr)


$ifi %TRANSPORT%==yes       $include   "../../base/addons/transport/bb4/transport_qhydrogen_eq.inc";
$ifi %OPTIFLOW%==yes   $include   "../../base/addons/optiflow/bb4/optiflow_qh2eq_region.inc"

$ifi %vqdebug%==yes   $setglobal equation qhydrogen_eq
$ifi %vqdebug%==yes   $include   "../../base/addons/vqdebug/bb4/vqdebug_equations.inc";

$label endoffile
