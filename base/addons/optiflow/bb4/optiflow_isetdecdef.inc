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

*Initializing the set IFPROC and IFFLOW if OPTIFLOW is enabled and the bridge of biogas between models
*OBS FF
$ifi not %baloptgasbridge%==yes $goto nogasbridge


IFFLOW('STRAW','STRAW_FLOW_BIOGAS')=YES;

IFFLOW('BIOGAS','SNG_FLOW_FOR_USE')=YES;
IFPROC('BIOGAS','Gas_Buffer')=YES;

$label nogasbridge

*Initializing CO2 sources

$ifi not %baloptCCU%==yes $goto noCCUopti

*OBS FF

*Constrain CO2 point source flow based on what is captured in Balmorel

SET ICO2(PROCSOURCE,FLOW)		"Set of CO2 SOURCE/FLOW linked to point sources in Balmorel";
ICO2(PROCSOURCE,FLOW)=0;
ICO2('CO2_Source_Biogen','CO2_SOURCE_FLOW_BIOGEN') = YES;
ICO2('CO2_Source_Fossil','CO2_SOURCE_FLOW_FOSSIL') = YES;

*Subtract CO2 captured in OptiFlow from carbon balance

SET ICO2_CC(PROC,FLOW)			"Set of PROC/FLOW pairs that deliver CO2 captured in OptiFlow to a pool for CS/CU";
ICO2_CC(PROC,FLOW)=0;
ICO2_CC('CO2_DAC','CO2_FLOW_DAC') = YES;
ICO2_CC('CO2_Biochar_Sum','CO2_FLOW_BIOCHAR') = YES;

*Re-ad CO2 used for CU in OptiFlow

SET ICO2_CU(PROC,FLOW)			"Set of PROC/FLOW pairs that deliver CO2 for CU";
ICO2_CU(PROC,FLOW)=0;
ICO2_CU('CO2_BIOGEN','CO2_FLOW_BIOGEN') = YES;
ICO2_CU('CO2_FOS','CO2_FLOW_FOSSIL') = YES;
ICO2_CU('CO2_DAC_Total','CO2_FLOW_DAC') = YES;

$label noCCUopti

$label endoffile