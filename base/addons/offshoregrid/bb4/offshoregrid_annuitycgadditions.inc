* Annuities for the offshore grid add-on technologies (hub platforms and hub wind).
* Generate OFFSHOREGRID_ANNUITYCG.inc with base/auxils/annuity_calculation/annuity_calculation.gms
$onmulti
$if     EXIST '../data/OFFSHOREGRID_ANNUITYCG.inc' $INCLUDE         '../data/OFFSHOREGRID_ANNUITYCG.inc';
$if not EXIST '../data/OFFSHOREGRID_ANNUITYCG.inc' $INCLUDE '../../base/data/OFFSHOREGRID_ANNUITYCG.inc';
$offmulti
