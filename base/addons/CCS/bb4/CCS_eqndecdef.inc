* CCS add-on. Added by Juan Gea Bermudez

* Thise file is a further development tying together captured carbon from the CCS addon to CO2 used in the OptiFlow addon.
* Made by Theis Madsen

$ifi not %OPTIFLOW%==yes $goto NO_OPTIFLOW
*$ifi not %baloptCCU%==yes $goto NO_OPTIFLOW_CO2_CONNECTION

EQUATION QFLOWCO2LIM(Y,AAA,PROCSOURCE,FLOW,S,T)			"This equation limits the CO2 used in an OptiFlow production pathway by what is captured (ton/h)";

QFLOWCO2LIM(IY411,IA,PROCSOURCE,FLOW,S,T)$(ICO2(PROCSOURCE,FLOW)) ..
  VFLOWSOURCE(IY411,IA,PROCSOURCE,FLOW,S,T)
    =L=
$ifi %baloptCCU%==yes + SUM(G$(IAGK_HASORPOT(IY411,IA,G) AND IGPROC(PROCSOURCE,G)),(IM_CO2(G) + IM_CO2RE(G)) * IOF0001 * IOF3P6 * VGF_T(IY411,IA,G,S,T) * CCS_CO2CAPTEFF_G(G))
$ifi not %baloptCCU%==yes + EPS
;


$label NO_OPTIFLOW
*$label NO_OPTIFLOW_CO2_CONNECTION