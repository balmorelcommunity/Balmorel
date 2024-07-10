* File balbase4.inc for handling additions of equations an addon in the definition of Balmorel model balbase4

$ifi not %bb4%==yes $goto endoffile

$ifi %import_results%==yes  $include   "../../base/addons/import_results/import_results_balbase4.inc";

$ifi %OFFSHOREGRID%==yes  $include   "../../base/addons/offshoregrid/bb4/offshoregrid_balbase4.inc";
$ifi %TRANSPORT%==yes       $include   "../../base/addons/transport/bb4/transport_balbase4.inc";
$ifi %X3V%==yes    $include   "../../base/addons/x3v/bb4/x3v_balbase4.inc";
$ifi %HYDROGEN%==yes  $include   "../../base/addons/hydrogen/bb4/hydrogen_balbase4.inc";
$ifi %UnitComm%==yes      $include   "../../base/addons/unitcommitment/bb4/uc_balbase4.inc";
$ifi %STEPWISE_RAMPING%==yes      $include   "../../base/addons/STEPWISE_RAMPING/stepwise_ramping_balbase4.inc";
$ifi %COMBTECH%==yes  $include   "../../base/addons/combtech/bb4/combtech_balbase4.inc";
$ifi %AGKNDISC%==yes  $include   "../../base/addons/AGKNdisc/bb4/agkndisc_balbase4.inc";
$ifi %EV%==yes      $include        "../../base/addons/EV/bb4/EV_balbase4.inc";
$ifi %STEPWISEPRICE%==yes  $include   "../../base/addons/stepwiseprice/stepwiseprice_balbase4.inc";
$ifi %LIMITSFORFUELS%==yes  $include   "../../base/addons/limitsforfuels/bb4/limitsforfuels_balbase4.inc";
$ifi %GRIDTARIFFS%==yes  $include   "../../base/addons/GridTariffs/bb4/GridTariffs_balbase4.inc";
$ifi %DEMANDRESPONSE%==yes      $include        "../../base/addons/demandresponse/bb4/dr_balbase4.inc";
$ifi %HEATTRANS%==yes       $include   "../../base/addons/heattrans/bb4/heattrans_balbase4.inc";
$ifi %DECOM%==yes  $include   "../../base/addons/DECOM/DECOM_balbase4.inc";
$ifi %FlowBased%==yes      $include        "../../base/addons/FlowBased/bb4/flowbased_balbase4.inc";
$ifi %TRANS_RAMP%==yes  $include   "../../base/addons/transmission_ramping/transmission_ramping_balbase4.inc";
$ifi %ANC_SERV%==yes  $include   "../../base/addons/ancilliary_services/ancilliary_services_balbase4.inc";
$ifi %BalancingMarket%==yes       $include   "../../base/addons/balancing_market/balancing_market_balbase4.inc";
$ifi %INDIVUSERS%==yes       $include   "../../base/addons/indivusers/bb4/indivusers_balbase4.inc";
$ifi %OPTIFLOW%==yes         $include         "../../base/addons/optiflow/bb4/optiflow_balbase4.inc";
$ifi %CCS%==yes				$include         "../../base/addons/CCS/bb4/CCS_balbase4.inc";

$label endoffile
