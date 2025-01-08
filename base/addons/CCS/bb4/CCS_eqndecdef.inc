* CCS add-on. Added by Juan Gea Bermudez

* Thise file is a further development tying together captured carbon from the CCS addon to CO2 used in the OptiFlow addon.
* Made by Theis Madsen

$ifi not %OPTIFLOW%==yes $goto NO_OPTIFLOW
*$ifi not %baloptCCU%==yes $goto NO_OPTIFLOW_CO2_CONNECTION

EQUATION QFLOWCO2LIM(Y,RRR,PROCSOURCE,FLOW,S,T)			"This equation limits the CO2 used in an OptiFlow production pathway by what is captured (ton/h)";
*EQUATION QCCSLIM(Y)                                 "This equation limits the amount of CO2 that can be dequestrated yearly";

QFLOWCO2LIM(IY411,IR,PROCSOURCE,FLOW,S,T)$(ICO2(PROCSOURCE,FLOW)) ..
  SUM(IA$(RRRAAA(IR,IA) AND AAAOPTIFLOW(IA)),VFLOWSOURCE(IY411,IA,PROCSOURCE,FLOW,S,T))
    =L=
$ifi %baloptCCU%==yes + SUM(IA$(RRRAAA(IR,IA)),SUM(G$(IAGK_HASORPOT(IY411,IA,G) AND IGPROC(PROCSOURCE,G)), (IM_CO2(G) + IM_CO2RE(G)) * IOF0001 * IOF3P6 * VGF_T(IY411,IA,G,S,T) * CCS_CO2CAPTEFF_G(G)))
$ifi not %baloptCCU%==yes + EPS
;

*QCCSLIM(IY411)..
*  SUM(C,SUM((IA,G)$(IAGK_HASORPOT(IY411,IA,G) AND ICA(C,IA) AND GROUP_AAA(GROUP,IA)), SUM((IS3,T), IHOURSINST(IS3,T) * IHOURFRAC * (IM_CO2(G) + IM_CO2RE(G)) * IOF0001 * IOF3P6 * VGF_T(IY411,IA,G,IS3,T)*CCS_CO2CAPTEFF_G(G))))
*$ifi %OPTIFLOW%==yes $ifi %baloptCCU%==yes - SUM(IA, SUM((IS3,T), SUM((PROCSOURCE,FLOW)$(ICO2(PROCSOURCE,FLOW)),IHOURSINST(IS3,T) * VFLOWSOURCE(IY411,IA,PROCSOURCE,FLOW,IS3,T))))
*  =L=
*  CCSLIM
*;


$label NO_OPTIFLOW
*$label NO_OPTIFLOW_CO2_CONNECTION