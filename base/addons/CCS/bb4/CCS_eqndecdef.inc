* CCS add-on made by Juan Gea Bermudez
* OptiFlow/CCU connection made by Theis Madsen
* OptiFlow/CCS connection modified by Frederik Fristed (OBS FF)

* The updated file integrates captured CO2 from the CCS addon with CO2 use (CU) and sequestration (CS) in OptiFlow

$ifi not %OPTIFLOW%==yes $goto NO_OPTIFLOW

EQUATION QFLOWCO2LIM(Y,RRR,PROCSOURCE,FLOW,S,T) "Balance CO2 captured in Balmorel and used in OptiFlow (ton/h)";

QFLOWCO2LIM(IY411,IR,PROCSOURCE,FLOW,S,T)$(ICO2(PROCSOURCE,FLOW)) ..

*LHS: CO2 source flow into OptiFlow.
  SUM(IA$(RRRAAA(IR,IA) AND AAAOPTIFLOW(IA)),VFLOWSOURCE(IY411,IA,PROCSOURCE,FLOW,S,T)) 

*CO2 captured in Balmorel MUST be used for CU/CS in OptiFlow
$ifi     %baloptCCS%==yes  =E=
*CO2 for CU in OptiFlow is limited to what is captured in Balmorel
$ifi not %baloptCCS%==yes  =L=

*RHS: CO2 captured in Balmorel
$ifi %baloptCCU%==yes +SUM(IA$(RRRAAA(IR,IA)), SUM(G$(IAGK_HASORPOT(IY411,IA,G) AND IGPROC(PROCSOURCE,G)), (IM_CO2(G)+IM_CO2RE(G))*IOF0001*IOF3P6*VGF_T(IY411,IA,G,S,T)*CCS_CO2CAPTEFF_G(G)))+EPS
$ifi not %baloptCCU%==yes +EPS
;

$label NO_OPTIFLOW



