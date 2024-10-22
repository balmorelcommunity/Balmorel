

*Initializing CO2 sources
$ifi not %baloptCCU%==yes $goto noCCUopti

*Initializing set if a flow is for biogenic or fossil CO2
SET IGPROC(PROCSOURCE,G)		"Connection of CO2 flow and technology with CCS";
IGPROC(PROCSOURCE,G)=0;
IGPROC('CO2_Source_Biogen',G)$(CCS_G(G) AND IM_CO2RE(G)) = YES;
IGPROC('CO2_Source_Fossil',G)$(CCS_G(G) AND IM_CO2(G)) = YES;

$label noCCUopti

$label endoffile