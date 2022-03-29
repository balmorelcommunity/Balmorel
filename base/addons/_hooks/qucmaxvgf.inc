
$ifi %SEASONALCOP%==yes  $include   "../../base/addons/seasonalCOP/bb4/seasonalCOP_qucmaxvgf.inc";
$ifi %ANC_SERV%==yes  $include   "../../base/addons/ancilliary_services/ancilliary_services_qucmaxvgf.inc";

$ifi %vqdebug%==yes   $setglobal equation qucmaxvgf
$ifi %vqdebug%==yes   $include   "../../base/addons/vqdebug/bb4/vqdebug_equations.inc";


