*File created by Juan Gea Bermudez


$ifi %import_results%==yes  $include   "../../base/addons/import_results/import_results_sim_rollingseasons.inc";
$ifi %STEPWISE_RAMPING%==yes $ifi %SEASONALLINKRAMPING%==yes   $include   "../../base/addons/STEPWISE_RAMPING/stepwise_ramping_sim_rollingseasons.inc";
$ifi %UnitComm%==yes $ifi %SEASONALLINKUC%==yes                $include   "../../base/addons/unitcommitment/bb4/uc_sim_rollingseasons.inc";



