*Initializing the set IFPROC and IFFLOW if OPTIFLOW is enabled and the bridge of biomass usage between models, TMAD
$ifi not %baloptfuelbridge%==yes $goto nofuelbridge

SET IFFLOW(FFF,FLOW)	"Fuel in Balmorel that corresponds to a flow in OptiFlow";
IFFLOW(FFF,FLOW)=0;

IFFLOW('STRAW','STRAW_GEN_FLOW')=YES;
IFFLOW('WOODCHIPS','WOOD_GEN_FLOW')=YES;
*IFFLOW('WOODPELLETS','WOOD_PELLETS_GEN_FLOW')=YES;

SET IFPROC(FFF,PROC)	"Fuel in Balmorel that corresponds to a flow in OptiFlow";
IFPROC(FFF,PROC)=0;

IFPROC('STRAW','Straw_Gen')=YES;
IFPROC('WOODCHIPS','Wood_Gen')=YES;
*IFPROC('WOODPELLETS','Wood_Pellets_Gen')=YES;

$label nofuelbridge

*Initializing the set IFPROC and IFFLOW if OPTIFLOW is enabled and the bridge of biogas between models

$ifi not %baloptgasbridge%==yes $goto nogasbridge

*IFFLOW('STRAW','STRAW_FLOW_BIOGAS')=YES;
IFFLOW('BIOGAS','SNG_FLOW')=YES;
IFPROC('BIOGAS','Gas_Buffer')=YES;

$label nogasbridge

*Initializing CO2 sources

$ifi not %baloptCCU%==yes $goto noCCUopti

*Constrain CO2 point source flow based on what is captured in Balmorel

SET ICO2(PROCSOURCE,FLOW)		"Set of CO2 SOURCE/FLOW linked to point sources in Balmorel";
ICO2(PROCSOURCE,FLOW)=0;
ICO2('CO2_Source_Biogen','CO2_SOURCE_FLOW_BIOGEN') = YES;
ICO2('CO2_Source_Fossil','CO2_SOURCE_FLOW_FOSSIL') = YES;

*Subtract CO2 captured in OptiFlow from carbon balance

SET ICO2_CC(PROC,FLOW)			"Set of PROC/FLOW pairs that deliver CO2 captured in OptiFlow to a pool for CS/CU";
ICO2_CC(PROC,FLOW)=0;
ICO2_CC('CO2_DAC','CO2_FLOW_DAC') = YES;
ICO2_CC('CO2_Biogas','CO2_FLOW_BIOGAS') = YES;
ICO2_CC('CO2_Biochar_Sum','CO2_FLOW_BIOCHAR') = YES;

***MDO emissions are added in SOSIBU2INDIC. OCC captured share is subtracted here, yielding a net reduction in residual emissions. 
***For fossil drop-in fuels, OCC captured share is simply subtracted. This yields carbon neutral cycling for CCU and net removal for CCS. 
ICO2_CC('OCC_30','CO2_FLOW_OCC') = YES;
ICO2_CC('OCC_35','CO2_FLOW_OCC') = YES;
ICO2_CC('OCC_40','CO2_FLOW_OCC') = YES;
ICO2_CC('OCC_45','CO2_FLOW_OCC') = YES;
ICO2_CC('OCC_50','CO2_FLOW_OCC') = YES;

*Re-ad CO2 used for CU in OptiFlow
SET ICO2_CU(PROC,FLOW)			"Set of PROC/FLOW pairs that deliver CO2 for CU";
ICO2_CU(PROC,FLOW)=0;
ICO2_CU('CO2_CU_Split','CO2_FLOW_EME') = YES;
ICO2_CU('CO2_CU_Split','CO2_FLOW_FT') = YES;

$label noCCUopti

$label endoffile