*IEQFLOW_Y(CCCRRRAAA,PROC,FLOW)=EQFLOW(Y,CCCRRRAAA,PROC,FLOW);
*IMAXFLOW_Y(CCCRRRAAA,PROC,FLOW)=MAXFLOW(Y,CCCRRRAAA,PROC,FLOW);
*IMINFLOW_Y(CCCRRRAAA,PROC,FLOW)=MINFLOW(Y,CCCRRRAAA,PROC,FLOW);

*Initializing the set IFPROC and IFFLOW if OPTIFLOW is enabled and the bridge of biomass usage between models, TMAD
$ifi not %baloptfuelbridge%==yes $goto nofuelbridge

SET IFFLOW(FFF,FLOW)	"Fuel in Balmorel that corresponds to a flow in OptiFlow";
IFFLOW(FFF,FLOW)=0;

IFFLOW('STRAW','STRAW_GEN_FLOW')=YES;
IFFLOW('WOODCHIPS','WOOD_GEN_FLOW')=YES;
IFFLOW('WOODPELLETS','WOOD_PELLETS_GEN_FLOW')=YES;

SET IFPROC(FFF,PROC)	"Fuel in Balmorel that corresponds to a flow in OptiFlow";
IFPROC(FFF,PROC)=0;

IFPROC('STRAW','Straw_Gen')=YES;
IFPROC('WOODCHIPS','Wood_Gen')=YES;
IFPROC('WOODPELLETS','Wood_Pellets_Gen')=YES;

$label nofuelbridge

*Initializing the set IFPROC and IFFLOW if OPTIFLOW is enabled and the bridge of biogas between models, TMAD
$ifi not %baloptgasbridge%==yes $goto nogasbridge
IFFLOW('BIOGAS','GASFLOW')=YES;
IFPROC('BIOGAS','GasBuffer')=YES;

$label nogasbridge

*Initializing CO2 sources
*$ifi not %baloptCCU%==yes $goto noCCUopti
SET ICO2(PROCSOURCE,FLOW)		"Set of CO2 source and flows";
ICO2(PROCSOURCE,FLOW)=0;
ICO2('CO2_Source_Biogen','CO2_SOURCE_FLOW_BIOGEN') = YES;
ICO2('CO2_Source_Fossil','CO2_SOURCE_FLOW_FOSSIL') = YES;

$label noCCUopti

$label endoffile