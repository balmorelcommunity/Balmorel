*Code created for running different scenarios (Amalia, 05-09-2016)
*Adapted to BB4 (Juan Gea Bermudez,12-02-2019)

*Call the balmorel mode, which will be solved through a loop in order to calculate all the marginal values
$ifi     exist 'Balmorel.gms'  $include  'Balmorel.gms';
$ifi not exist 'Balmorel.gms'  $include  '../../base/model/Balmorel.gms';

* Turn off the listing of the input file */
$offlisting

* Turn off the listing and cross-reference of the symbols used */
$offsymxref offsymlist

Option solprint=off;
Option sysout=off;



*step 1 - setup scenarios

Set scenarios  'Scenarios' %semislash%
$INCLUDE      '../../sensitivity_analysis/montecarlo_simulations/scenarios.inc';
%semislash%;


*Change of the parameters for the different scenarios
$INCLUDE      '../../sensitivity_analysis/montecarlo_simulations/scenarios_parameters.inc';

*step 2 save data
$INCLUDE      '../../sensitivity_analysis/montecarlo_simulations/saved_data.inc';

$INCLUDE      '../../sensitivity_analysis/montecarlo_simulations/parameters_output.inc';

SET scenariosrunning(scenarios) /Scenario1,Scenario100/;

loop(scenarios$scenariosrunning(scenarios),

**Reseting .fx variables
*upper bound
$ifi %TechInvest%==yes         VGKN.UP(Y,IA,G)$IAGKNY(Y,IA,G) = INF;
$ifi %TechInvest%==yes         VGKNACCUMNET.UP(Y,IA,G)$SUM(IYALIAS$(IYALIAS.VAL LE Y.VAL),IAGKNY(IYALIAS,IA,G)) = INF;
$ifi %TransInvest%==yes        VXKN.UP(Y,IRE,IRI)$IXKN(Y,IRE,IRI)= INF;
$ifi %TransInvest%==yes        VXKNACCUMNET.UP(Y,IRE,IRI)$SUM(IYALIAS$(IYALIAS.VAL LE Y.VAL),IXKN(IYALIAS,IRE,IRI))= INF;
$ifi %DECOM%==yes              VDECOM_EXO.UP(Y,IA,G)$IGDECOMEXOPOT(Y,IA,G)=INF;
$ifi %DECOM%==yes              VDECOM_EXO_ACCUM.UP(Y,IA,G)$IGDECOMEXOPOT(Y,IA,G)=INF;
*lower bound
$ifi %TechInvest%==yes         VGKN.LO(Y,IA,G)$IAGKNY(Y,IA,G) = 0;
$ifi %TechInvest%==yes         VGKNACCUMNET.LO(Y,IA,G)$SUM(IYALIAS$(IYALIAS.VAL LE Y.VAL),IAGKNY(IYALIAS,IA,G)) = 0;
$ifi %TransInvest%==yes        VXKN.LO(Y,IRE,IRI)$IXKN(Y,IRE,IRI)= 0;
$ifi %TransInvest%==yes        VXKNACCUMNET.LO(Y,IRE,IRI)$SUM(IYALIAS$(IYALIAS.VAL LE Y.VAL),IXKN(IYALIAS,IRE,IRI))= 0;
$ifi %DECOM%==yes              VDECOM_EXO.LO(Y,IA,G)$IGDECOMEXOPOT(Y,IA,G)=0;
$ifi %DECOM%==yes              VDECOM_EXO_ACCUM.LO(Y,IA,G)$IGDECOMEXOPOT(Y,IA,G)=0;


*step 3 reestablish data to base level
*GKFX(Y,IA,G)=sav_GKFX(Y,IA,G);
WNDFLH(IA)=sav_WNDFLH(IA);
SOLEFLH(IA)=sav_SOLEFLH(IA);
WTRRSFLH(IA)=sav_WTRRSFLH(IA);
IHYINF_S(IA,S)=sav_IHYINF_S(IA,S);
FUELPRICE(Y,IA,FFF)=sav_FUELPRICE(Y,IA,FFF);
IXKRATE(IRE,IRI,S,T)=sav_IXKRATE(IRE,IRI,S,T);
*GINVCOST(IA,G)=sav_GINVCOST(IA,G);
*DE(Y,IR)=sav_DE(Y,IR);
*DH(Y,IA)=sav_DH(Y,IA);
M_POL(Y,MPOLSET,C)=sav_M_POL(Y,MPOLSET,C);

*step 4 change data to levels needed in scenario
*GKFX(Y,IA,G)$(GKFX_Scenario(scenarios,Y,IA,G))=GKFX_Scenario(scenarios,Y,IA,G);
WNDFLH(IA)$(WNDFLH_Scenarios(scenarios,IA))=WNDFLH_Scenarios(scenarios,IA);
SOLEFLH(IA)$(SOLEFLH_Scenarios(scenarios,IA))=SOLEFLH_Scenarios(scenarios,IA);
WTRRSFLH(IA)$(WTRRSFLH_Scenarios(scenarios,IA))=WTRRSFLH_Scenarios(scenarios,IA);
IHYINF_S(IA,S)$(IHYINF_S_Scenarios(scenarios,IA,S))=IHYINF_S_Scenarios(scenarios,IA,S);
FUELPRICE(Y,IA,FFF)$(FUELPRICE_Scenario(scenarios,Y,IA,FFF))=FUELPRICE_Scenario(scenarios,Y,IA,FFF);
IXKRATE(IRE,IRI,S,T)$(IXKRATE_Scenario(scenarios,IRE,IRI,S,T))=IXKRATE_Scenario(scenarios,IRE,IRI,S,T);
*GINVCOST(IA,G)$(GINVCOST_Scenario(scenarios,IA,G))=GINVCOST_Scenario(scenarios,IA,G);
*DE(Y,IR)$(DE_Scenario(scenarios,Y,IR))=DE_Scenario(scenarios,Y,IR);
*DH(Y,IA)$(DH_Scenario(scenarios,Y,IA))=DH_Scenario(scenarios,Y,IA);
M_POL(Y,MPOLSET,C)$(M_POL_Scenarios(scenarios,Y,MPOLSET,C))=M_POL_Scenarios(scenarios,Y,MPOLSET,C);

*step 5 -- solve model

$ifi     exist 'Balmorelbb4.sim'  $include                  'Balmorelbb4.sim';
$ifi not exist 'Balmorelbb4.sim'  $include '../../base/model/Balmorelbb4.sim';


*step 6 cross scenario report writing


$INCLUDE      '../../sensitivity_analysis/montecarlo_simulations/Loop_output.inc';




*step 7 end of loop
);

*step 8 Create a Report
*step 9 compute and display final results


execute_unload "../../sensitivity_analysis/montecarlo_simulations/output_analysis/input/ScenarioResults.gdx"
EPrice_YRST_scen,EPrice_YRST_scen_average,CO2_emissions_scen,Investments_scen,Production_scen;



*End of the Balmorel scenario file







