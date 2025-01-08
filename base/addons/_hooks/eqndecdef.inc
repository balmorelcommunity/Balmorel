* Location of equation declarations and definitions used in addons (for any addon where declarations and definitions are in the same file)

$ifi %BB4%==yes $goto beginbb4

$ifi %COMBTECH%==yes $include "../../base/addons/combtech/combtech_eqndecdef.inc"
$ifi %HYDROGEN%==yes $include "../../base/addons/hydrogen/hydrogen_eqndecdef.inc"

$ifi %FLOWBASED%==yes $include "../../base/addons/flowbased/flowbased_eqndecdef.inc"
$ifi %BB3%==yes $ifi not %HYRSBB123%==none     $include "../../base/addons/hyrsbb123/hyrsbb123equations.inc";

$ifi not %BB4%==yes $goto endoffile

$label  beginbb4


$ifi %import_results%==yes  $include   "../../base/addons/import_results/import_results_eqndecdef.inc";

$ifi %OFFSHOREGRID%==yes  $include   "../../base/addons/offshoregrid/bb4/offshoregrid_eqndecdef.inc";
$ifi %TRANSPORT%==yes       $include   "../../base/addons/transport/bb4/transport_eqndecdef.inc";
$ifi %X3V%==yes $include "../../base/addons/x3v/bb4/x3v_eqndecdef.inc";
$ifi %UnitComm%==yes      $include   "../../base/addons/unitcommitment/bb4/uc_eqndecdef.inc";
$ifi %AGKNDISC%==yes $include "../../base/addons/AGKNdisc/bb4/agkndisc_eqndecdef.inc";
$ifi %COMBTECH%==yes $include "../../base/addons/combtech/bb4/combtech_eqndecdef.inc";
$ifi %HYDROGEN%==yes $include "../../base/addons/hydrogen/bb4/hydrogen_eqndecdef.inc";
$ifi %EV%==yes      $include        "../../base/addons/EV/bb4/EV_eqndecdef.inc";
$ifi %STEPWISEPRICE%==yes  $include   "../../base/addons/stepwiseprice/stepwiseprice_eqndecdef.inc";
$ifi %LIMITSFORFUELS%==yes  $include   "../../base/addons/limitsforfuels/bb4/limitsforfuels_eqndecdef.inc";
$ifi %STEPWISE_RAMPING%==yes  $include "../../base/addons/STEPWISE_RAMPING/stepwise_ramping_eqndecdef.inc";
$ifi %GRIDTARIFFS%==yes  $include   "../../base/addons/GridTariffs/bb4/GridTariffs_eqndecdef.inc";
$ifi %DEMANDRESPONSE%==yes      $include        "../../base/addons/demandresponse/bb4/dr_eqndecdef.inc";
$ifi %HEATTRANS%==yes  $include   "../../base/addons/heattrans/bb4/heattrans_eqndecdef.inc";
$ifi %DECOM%==yes  $include   "../../base/addons/DECOM/DECOM_eqndecdef.inc";
$ifi %FlowBased%==yes      $include        "../../base/addons/FlowBased/bb4/flowbased_eqndecdef.inc";
$ifi %TRANS_RAMP%==yes  $include   "../../base/addons/transmission_ramping/transmission_ramping_eqndecdef.inc";
$ifi %ANC_SERV%==yes  $include   "../../base/addons/ancilliary_services/ancilliary_services_eqndecdef.inc";
$ifi %BalancingMarket%==yes       $include   "../../base/addons/balancing_market/balancing_market_eqndecdef.inc";
$ifi %INDIVUSERS%==yes       $include   "../../base/addons/indivusers/bb4/indivusers_eqndecdef.inc";
$ifi %OPTIFLOW%==yes $include "../../base/addons/optiflow/bb4/optiflow_eqndecdef.inc";
$ifi %CCS%==yes $include "../../base/addons/CCS/bb4/CCS_eqndecdef.inc";

$label endoffile
