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
$INCLUDE      '../../sensitivity_analysis/morris_screening/scenarios.inc';
%semislash%;


*Change of the parameters for the different scenarios
$INCLUDE      '../../sensitivity_analysis/morris_screening/scenarios_parameters.inc';

*step 2 save data
$INCLUDE      '../../sensitivity_analysis/morris_screening/saved_data.inc';

$INCLUDE      '../../sensitivity_analysis/morris_screening/parameters_output.inc';



SET scenariosrunning(scenarios) /Scenario1*Scenario5/;

loop(scenarios$scenariosrunning(scenarios),


**Reseting .fx variables
*upper bound
$ifi %TechInvest%==yes         VGKN.UP(Y,IA,G)$IAGKNY(Y,IA,G) = INF;
$ifi %TechInvest%==yes         VGKNACCUMNET.UP(Y,IA,G)$SUM(IYALIAS$(IYALIAS.VAL LE Y.VAL),IAGKNY(IYALIAS,IA,G)) = INF;
$ifi %TransInvest%==yes        VXKN.UP(Y,IRE,IRI)$IXKN(Y,IRE,IRI)= INF;
$ifi %TransInvest%==yes        VXKNACCUMNET.UP(Y,IRE,IRI)$SUM(IYALIAS$(IYALIAS.VAL LE Y.VAL),IXKN(IYALIAS,IRE,IRI))= INF;
$ifi %DECOM%==yes              VDECOM_EXO.UP(Y,IA,G)$IGDECOMEXOPOT(Y,IA,G)=INF;
$ifi %DECOM%==yes              VDECOM_EXO_ACCUM.UP(Y,IA,G)$IGDECOMEXOPOT(Y,IA,G)=INF;
$ifi %DECOM%==yes              VDECOM_EXO_BACK.UP(Y,IA,G)$IGDECOMEXOPOT(Y,IA,G)=INF;
*lower bound
$ifi %TechInvest%==yes         VGKN.LO(Y,IA,G)$IAGKNY(Y,IA,G) = 0;
$ifi %TechInvest%==yes         VGKNACCUMNET.LO(Y,IA,G)$SUM(IYALIAS$(IYALIAS.VAL LE Y.VAL),IAGKNY(IYALIAS,IA,G)) = 0;
$ifi %TransInvest%==yes        VXKN.LO(Y,IRE,IRI)$IXKN(Y,IRE,IRI)= 0;
$ifi %TransInvest%==yes        VXKNACCUMNET.LO(Y,IRE,IRI)$SUM(IYALIAS$(IYALIAS.VAL LE Y.VAL),IXKN(IYALIAS,IRE,IRI))= 0;
$ifi %DECOM%==yes              VDECOM_EXO.LO(Y,IA,G)$IGDECOMEXOPOT(Y,IA,G)=0;
$ifi %DECOM%==yes              VDECOM_EXO_ACCUM.LO(Y,IA,G)$IGDECOMEXOPOT(Y,IA,G)=0;
$ifi %DECOM%==yes              VDECOM_EXO_BACK.LO(Y,IA,G)$IGDECOMEXOPOT(Y,IA,G)=0;

$ifi not %LIFETIME_DECOM_ENDO_G%==yes $ifi not %ECONOMIC_DECOM_ENDO_G%==yes  $goto DECOMMISSIONING_ENDOGENOUS_GENERATION2
VDECOM_ENDO.UP(Y,IA,G)=INF;
VDECOM_ENDO_ACCUM.UP(Y,IA,G)=INF;
$ifi %REVERT_DECOM_ENDO_G%==yes VDECOM_ENDO_BACK.UP(Y,IA,G)=INF;

VDECOM_ENDO.LO(Y,IA,G)=0;
VDECOM_ENDO_ACCUM.LO(Y,IA,G)=0;
$ifi %REVERT_DECOM_ENDO_G%==yes VDECOM_ENDO_BACK.LO(Y,IA,G)=0;
$label  DECOMMISSIONING_ENDOGENOUS_GENERATION2

*step 3 reestablish data to base level
TAX_F_HEAT(Y,C,IGETOH)=sav_TAX_F_HEAT(Y,C,IGETOH);
TAX_F(Y,C,G)=sav_TAX_F(Y,C,G);
ANNUITYCG(C,G)=sav_ANNUITYCG(C,G);
IGR_PRICE_TECH(Y,IR,'GRDECW')=sav_IGR_PRICE_TECH(Y,IR,'GRDECW');
*SUBTECHGROUPKPOT(IA,TECH_GROUP,SUBTECH_GROUP)=sav_SUBTECHGROUPKPOT(IA,TECH_GROUP,SUBTECH_GROUP);
ICBYPASS(C)=sav_ICBYPASS(C);
IGKRATE(IA,G,S,T)=sav_IGKRATE(IA,G,S,T);


*step 4 change data to levels needed in scenario
TAX_F_HEAT(Y,'DENMARK',IGETOH)=P2H_TAX_Scenarios(scenarios);
TAX_F(Y,'DENMARK',G)$(GDATA(G,'GDFUEL') EQ STRAW OR GDATA(G,'GDFUEL') EQ WOODPELLETS OR GDATA(G,'GDFUEL') EQ WOODCHIPS OR GDATA(G,'GDFUEL') EQ WOODWASTE OR GDATA(G,'GDFUEL') EQ WOOD)=SOS_TAX_BIOMASS_Scenarios(scenarios);
ANNUITYCG('DENMARK',G)$(GDATA(G,'GDKVARIABL') EQ 1)= ((1-DEBT_SHARE_G(G))*DISCOUNT_RATE_Scenarios(scenarios) + DISCOUNT_RATE_Scenarios(scenarios) * DEBT_SHARE_G (G)* (1 - (1 + DISCOUNT_RATE_Scenarios(scenarios)) ** (-PAYBACK_TIME_G(G))) / (1 - (1 + DISCOUNT_RATE_Scenarios(scenarios)) **( -PAYBACK_TIME_G(G)))) / (1 - (1 + DISCOUNT_RATE_Scenarios(scenarios)) ** (-GDATA(G,'GDLIFETIME')));
IGR_PRICE_TECH(Y,IR,'GRDECW')$CCCRRR('DENMARK',IR)=VOL_GRID_TARIFF_Scenarios(scenarios);
*SUBTECHGROUPKPOT(IA,'BOILER','BIOMASS_BOILER')$(INVDATA(IA,'SDH') EQ 1 AND ICA('DENMARK',IA) AND NOT (BOILER_POT_Scenarios(scenarios) EQ 1))=EPS;
*SUBTECHGROUPKPOT(IA,'HEATPUMP','AIR')$(INVDATA(IA,'LDH') EQ 1 AND ICA('DENMARK',IA) AND NOT (HP_POT_Scenarios(scenarios) EQ 1))=EPS;
*SUBTECHGROUPKPOT(IA,'HEAT_STORAGE','HEAT_STORAGE')$(ICA('DENMARK',IA) AND NOT (HEAT_STO_POT_Scenarios(scenarios) EQ 1))=EPS;
ICBYPASS('DENMARK')$(NOT (BYPASS_Scenarios(scenarios) EQ 1))= NO;
IGKRATE(IA,G,S,T)$(INVDATA(IA,'SDH') EQ 1 AND ICA('DENMARK',IA) AND NOT (BOILER_POT_Scenarios(scenarios) EQ 1) AND GDATA(G,'GDTECHGROUP') EQ BOILER AND GDATA(G,'GDSUBTECHGROUP') EQ BIOMASS_BOILER)=EPS;
IGKRATE(IA,G,S,T)$(INVDATA(IA,'LDH') EQ 1 AND ICA('DENMARK',IA) AND NOT (HP_POT_Scenarios(scenarios) EQ 1) AND GDATA(G,'GDTECHGROUP') EQ HEATPUMP AND GDATA(G,'GDSUBTECHGROUP') EQ AIR)=EPS;
IGKRATE(IA,G,S,T)$(ICA('DENMARK',IA) AND NOT (HEAT_STO_POT_Scenarios(scenarios) EQ 1) AND GDATA(G,'GDTECHGROUP') EQ HEAT_STORAGE AND GDATA(G,'GDSUBTECHGROUP') EQ HEAT_STORAGE)=EPS;

*step 5 -- solve model

$ifi     exist 'Balmorelbb4.sim'  $include                  'Balmorelbb4.sim';
$ifi not exist 'Balmorelbb4.sim'  $include '../../base/model/Balmorelbb4.sim';


*step 6 cross scenario report writing

$INCLUDE      '../../sensitivity_analysis/morris_screening/Loop_output.inc';


*step 7 end of loop
);

*step 8 Create a Report
*step 9 compute and display final results


execute_unload "../../sensitivity_analysis/morris_screening/output_analysis/input/ScenarioResults.gdx"

G_CAP_YCRAF_scenarios
G_STO_YCRAF_scenarios
PRO_YCRAGF_scenarios
F_CONS_YCRA_scenarios
X_CAP_YCR_scenarios
X_FLOW_YCR_scenarios
ECO_G_YCRAG_scenarios
ECO_X_YCR_scenarios
ECO_XH_YCRA_scenarios
OBJ_YCR_scenarios
EL_PRICE_YCR_scenarios
EL_PRICE_YCRST_scenarios
H_PRICE_YCRA_scenarios
H_PRICE_YCRAST_scenarios
EL_DEMAND_YCR_scenarios
H_DEMAND_YCRA_scenarios
EMI_YCRAG_scenarios
XH_CAP_YCA_scenarios
XH_FLOW_YCA_scenarios
;





*End of the Balmorel scenario file



