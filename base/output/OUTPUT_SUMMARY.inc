*Create output file

SET CATEGORY /COSTS,INCOME/;
SET SUBCATEGORY /ELECTRICITY_SALE,GENERATION_CAPITAL_COSTS, GENERATION_FIXED_COSTS, GENERATION_OPERATIONAL_COSTS, GENERATION_FUEL_COSTS,TRANSMISSION_CAPITAL_COSTS, TRANSMISSION_OPERATIONAL_COSTS,GENERATION_CO2_COSTS/;
SET COMMODITY /ELECTRICITY,DISTRICT_HEAT/;
SET TECH_TYPE /CONDENSING,CHP-BACK-PRESSURE,CHP-EXTRACTION,BOILERS,ELECT-TO-HEAT,INTERSEASONAL-HEAT-STORAGE,INTERSEASONAL-ELECT-STORAGE,INTRASEASONAL-HEAT-STORAGE,INTRASEASONAL-ELECT-STORAGE,HYDRO-RESERVOIRS,HYDRO-RUN-OF-RIVER,WIND-TURBINES,SOLAR-PV,SOLAR-HEATING,HYDRO-WAVE/;
SET GTECH_TYPE(GGG,TECH_TYPE);
SET PRICE_CATEGORY /AVERAGE,AVERAGE_WEIGHTED_BY_CONSUMPTION,AVERAGE_WEIGHTED_BY_PRODUCTION/;
SET VARIABLE_CATEGORY /EXOGENOUS,ENDOGENOUS,DECOMMISSIONING/;
SET UNITS /GW,TWh,MWh,Money_per_MWh,Mmoney,kton/;


   GTECH_TYPE(G,'CONDENSING')                     = YES$((GDATA(G,'GDTYPE') EQ 1)  OR (GDATA(G,'GDTYPE') EQ GCND));
   GTECH_TYPE(G,'CHP-BACK-PRESSURE')              = YES$((GDATA(G,'GDTYPE') EQ 2)  OR (GDATA(G,'GDTYPE') EQ GBPR));
   GTECH_TYPE(G,'CHP-EXTRACTION')                 = YES$((GDATA(G,'GDTYPE') EQ 3)  OR (GDATA(G,'GDTYPE') EQ GEXT));
   GTECH_TYPE(G,'BOILERS')                        = YES$((GDATA(G,'GDTYPE') EQ 4)  OR (GDATA(G,'GDTYPE') EQ GHOB));
   GTECH_TYPE(G,'ELECT-TO-HEAT')                  = YES$((GDATA(G,'GDTYPE') EQ 5)  OR (GDATA(G,'GDTYPE') EQ GETOH));
   GTECH_TYPE(G,'INTRASEASONAL-HEAT-STORAGE')     = YES$((GDATA(G,'GDTYPE') EQ 6)  OR (GDATA(G,'GDTYPE') EQ GHSTO));
   GTECH_TYPE(G,'INTERSEASONAL-HEAT-STORAGE')     = YES$(GDATA(G,'GDTYPE') EQ GHSTOS);
   GTECH_TYPE(G,'INTRASEASONAL-ELECT-STORAGE')    = YES$((GDATA(G,'GDTYPE') EQ 7)  OR (GDATA(G,'GDTYPE') EQ GESTO));
   GTECH_TYPE(G,'INTERSEASONAL-ELECT-STORAGE')    = YES$(GDATA(G,'GDTYPE') EQ GESTOS);
   GTECH_TYPE(G,'HYDRO-RESERVOIRS')               = YES$((GDATA(G,'GDTYPE') EQ 8)  OR (GDATA(G,'GDTYPE') EQ GHYRS));
   GTECH_TYPE(G,'HYDRO-RUN-OF-RIVER')             = YES$((GDATA(G,'GDTYPE') EQ 9)  OR (GDATA(G,'GDTYPE') EQ GHYRR));
   GTECH_TYPE(G,'WIND-TURBINES')                  = YES$((GDATA(G,'GDTYPE') EQ 10) OR (GDATA(G,'GDTYPE') EQ GWND));
   GTECH_TYPE(G,'SOLAR-PV')                       = YES$((GDATA(G,'GDTYPE') EQ 11) OR (GDATA(G,'GDTYPE') EQ GSOLE));
   GTECH_TYPE(G,'SOLAR-HEATING')                  = YES$((GDATA(G,'GDTYPE') EQ 12) OR (GDATA(G,'GDTYPE') EQ GSOLH));
   GTECH_TYPE(G,'HYDRO-WAVE')                     = YES$((GDATA(G,'GDTYPE') EQ 22) OR (GDATA(G,'GDTYPE') EQ GWAVE));


PARAMETER G_CAP_YCRAF(Y,C,RRR,AAA,G,FFF,COMMODITY,TECH_TYPE,VARIABLE_CATEGORY,UNITS) "Generation capacity for each year, country, region, area, technology, fuel, commodity, technology type and variable type (GW)";
PARAMETER PRO_YCRAGFST(Y,C,RRR,AAA,G,FFF,SSS,TTT,COMMODITY,TECH_TYPE,UNITS) "Energy Production for each year, country, region, area, technology, fuel, season, hour, commodity and technology type (MWh)" ;
PARAMETER PRO_YCRAGF(Y,C,RRR,AAA,G,FFF,COMMODITY,TECH_TYPE,UNITS) "Annual Energy Production for each year, country, region, area, technology, fuel, commodity and technology type (TWh)";
PARAMETER F_CONS_YCRAST(Y,C,RRR,AAA,G,FFF,SSS,TTT,TECH_TYPE,UNITS) "Fuel consumption for each year, country, region, area, technology, fuel, season, hour and technology type (MWh)";
PARAMETER F_CONS_YCRA(Y,C,RRR,AAA,G,FFF,TECH_TYPE,UNITS) "Fuel consumption for each year, country, region, area, technology, fuel and technology type (TWh)";
PARAMETER X_CAP_YCR(Y,C,IRRRE,IRRRI,VARIABLE_CATEGORY,UNITS) "Transmission capacity for each year, country, from region to region (GW)";
PARAMETER X_FLOW_YCRST(Y,C,IRRRE,IRRRI,SSS,TTT,UNITS) "Transmission flow for each year, country, from region to region, for each season and hour (MWh)";
PARAMETER X_FLOW_YCR(Y,C,IRRRE,IRRRI,UNITS) "Transmission flow for each year, country, from region to region (TWh)";
PARAMETER ECO_G_YCRAG(Y,C,RRR,AAA,G,CATEGORY,SUBCATEGORY,UNITS) "Generation Economic Output for each year, country, region, area and technology (Mmoney)";
PARAMETER ECO_X_OUTPUT_YCR(Y,C,RRR,CATEGORY,SUBCATEGORY,UNITS) "Transmission Economic Output for each year, country and region (Mmoney)";
PARAMETER OBJ_YCR(Y,C,RRR,SUBCATEGORY,UNITS) "Objective function (Mmoney)";
PARAMETER EL_PRICE_YCR(Y,C,RRR,PRICE_CATEGORY,UNITS) "Average Electricity Prices for each region (money/MWh)";
PARAMETER EL_PRICE_YCRST(Y,C,RRR,SSS,TTT,UNITS) "Hourly Electricity Prices for each region (money/MWh)";
PARAMETER DH_PRICE_YCRA(Y,C,RRR,AAA,PRICE_CATEGORY,UNITS) "Average District Heating Prices for each area(money/MWh)";
PARAMETER DH_PRICE_YCRAST(Y,C,RRR,AAA,SSS,TTT,UNITS) "Hourly District Heating Prices for each area (money(MWh)";
PARAMETER EL_DEMAND_YCRST(Y,C,RRR,SSS,TTT,VARIABLE_CATEGORY,UNITS) "Aggregated Hourly Electricity Demand (MWh)";
PARAMETER DH_DEMAND_YCRAST(Y,C,RRR,AAA,SSS,TTT,VARIABLE_CATEGORY,UNITS) "Aggregated Hourly DH Demand (MWh)";
PARAMETER EMI_YCRAG(Y,C,RRR,AAA,G,FFF,TECH_TYPE,UNITS) "Annual CO2 emissions(ktons)";

*Modification of IHOURSINST
IWEIGHSUMS = SUM(S, WEIGHT_S(S));
IWEIGHSUMT = SUM(T, WEIGHT_T(T));
IHOURSINST(SSS,TTT)=0;
IHOURSINST(S,T)=IOF8760*WEIGHT_S(S)*WEIGHT_T(T)/(IWEIGHSUMS*IWEIGHSUMT);

* -------------------- ENERGY CAPACITY ---------------------

* ------------- ELECTRICITY CAPACITY --------------

** EXOGENOUS ELECTRICITY CAPACITY

G_CAP_YCRAF(Y,C,IR,IA,IGE,FFF,'ELECTRICITY',TECH_TYPE,'EXOGENOUS','GW')$((not IGETOH(IGE)) AND CCCRRR(C,IR) and RRRAAA(IR,IA) and IAGK_HASORPOT(Y,IA,IGE) AND IGF(IGE,FFF) AND GTECH_TYPE(IGE,TECH_TYPE))=
IOF0001*(GKFX(Y,IA,IGE)/(1$((NOT IGESTO(IGE)) AND (NOT IGESTOS(IGE)))+GDATA(IGE,'GDSTOHUNLD')$((IGESTO(IGE)) OR IGESTOS(IGE))))
;


** ENDOGENOUS ELECTRIC CAPACITY ACCUMULATED INVESTMENTS
G_CAP_YCRAF(Y,C,IR,IA,IGE,FFF,'ELECTRICITY',TECH_TYPE,'ENDOGENOUS','GW')$((not IGETOH(IGE)) AND CCCRRR(C,IR) and RRRAAA(IR,IA) and IAGK_HASORPOT(Y,IA,IGE) AND IGF(IGE,FFF) AND GTECH_TYPE(IGE,TECH_TYPE))=
IOF0001*(VGKNACCUMNET.L(Y,IA,IGE)/(1$((NOT IGESTO(IGE)) AND (NOT IGESTOS(IGE)))+GDATA(IGE,'GDSTOHUNLD')$((IGESTO(IGE)) OR IGESTOS(IGE))))
;

** ENDOGENOUS ELECTRICITY CAPACITY ACCUMULATED DECOMMISSIONING
$ifi %DECOM%==yes G_CAP_YCRAF(Y,C,IR,IA,IGE,FFF,'ELECTRICITY',TECH_TYPE,'DECOMMISSIONING','GW')$((not IGETOH(IGE)) AND CCCRRR(C,IR) and RRRAAA(IR,IA) and IAGK_HASORPOT(Y,IA,IGE) AND IGF(IGE,FFF) AND GTECH_TYPE(IGE,TECH_TYPE) AND IGDECOMEXOPOT(Y,IA,IGE))=
$ifi %DECOM%==yes -IOF0001*(VDECOM_EXO_ACCUM.L(Y,IA,IGE)/(1$((NOT IGESTO(IGE)) AND (NOT IGESTOS(IGE)))+GDATA(IGE,'GDSTOHUNLD')$((IGESTO(IGE)) OR IGESTOS(IGE))))
;


* ------------- END OF ELECTRICITY CAPACITY --------------

* ------------- HEAT CAPACITY --------------

** EXOGENOUS HEAT CAPACITY

G_CAP_YCRAF(Y,C,IR,IA,IGH,FFF,'DISTRICT_HEAT',TECH_TYPE,'EXOGENOUS','GW')$(CCCRRR(C,IR) and RRRAAA(IR,IA) and IAGK_HASORPOT(Y,IA,IGH) AND IGF(IGH,FFF) AND GTECH_TYPE(IGH,TECH_TYPE))=
IOF0001*(GKFX(Y,IA,IGH)/(1$((NOT IGHSTO(IGH)) AND (NOT IGHSTOS(IGH)))+GDATA(IGH,'GDSTOHUNLD')$((IGHSTO(IGH)) OR IGHSTOS(IGH))))
;


** ENDOGENOUS HEAT CAPACITY ACCUMULATED INVESTMENTS
G_CAP_YCRAF(Y,C,IR,IA,IGH,FFF,'DISTRICT_HEAT',TECH_TYPE,'ENDOGENOUS','GW')$(CCCRRR(C,IR) and RRRAAA(IR,IA) and IAGK_HASORPOT(Y,IA,IGH) AND IGF(IGH,FFF) AND GTECH_TYPE(IGH,TECH_TYPE))=
IOF0001*(VGKNACCUMNET.L(Y,IA,IGH)/(1$((NOT IGHSTO(IGH)) AND (NOT IGHSTOS(IGH)))+GDATA(IGH,'GDSTOHUNLD')$((IGHSTO(IGH)) OR IGHSTOS(IGH))))
;

** ENDOGENOUS HEAT CAPACITY ACCUMULATED DECOMMISSIONING
$ifi %DECOM%==yes G_CAP_YCRAF(Y,C,IR,IA,IGH,FFF,'DISTRICT_HEAT',TECH_TYPE,'DECOMMISSIONING','GW')$(CCCRRR(C,IR) and RRRAAA(IR,IA) and IAGK_HASORPOT(Y,IA,IGH) AND IGF(IGH,FFF) AND GTECH_TYPE(IGH,TECH_TYPE) AND IGDECOMEXOPOT(Y,IA,IGH))=
$ifi %DECOM%==yes -IOF0001*(VDECOM_EXO_ACCUM.L(Y,IA,IGH)/(1$((NOT IGHSTO(IGH)) AND (NOT IGHSTOS(IGH)))+GDATA(IGH,'GDSTOHUNLD')$((IGHSTO(IGH)) OR IGHSTOS(IGH))))
;

* ------------- END OF HEAT CAPACITY --------------

* ---------------- END OF ENERGY CAPACITY -----------------

* -------------------- ENERGY PRODUCTION ---------------------

** ELECTRICITY PRODUCTION HOURLY
PRO_YCRAGFST(Y,C,IR,IA,IGE,FFF,S,T,'ELECTRICITY',TECH_TYPE,'MWh')$((not IGETOH(IGE)) AND CCCRRR(C,IR) and RRRAAA(IR,IA) and IAGK_HASORPOT(Y,IA,IGE) AND IGF(IGE,FFF) AND GTECH_TYPE(IGE,TECH_TYPE))=
       VGE_T.L(Y,IA,IGE,S,T);

** ELECTRICITY PRODUCTION ANNUALLY
PRO_YCRAGF(Y,C,IR,IA,IGE,FFF,'ELECTRICITY',TECH_TYPE,'TWh')$((not IGETOH(IGE)) AND CCCRRR(C,IR) and RRRAAA(IR,IA) and IAGK_HASORPOT(Y,IA,IGE) AND IGF(IGE,FFF) AND GTECH_TYPE(IGE,TECH_TYPE))=
       SUM((S,T),IHOURSINST(S,T)*VGE_T.L(Y,IA,IGE,S,T))/IOF1000000;

** DISTRICT HEAT PRODUCTION HOURLY
PRO_YCRAGFST(Y,C,IR,IA,IGH,FFF,S,T,'DISTRICT_HEAT',TECH_TYPE,'MWh')$(CCCRRR(C,IR) and RRRAAA(IR,IA) and IAGK_HASORPOT(Y,IA,IGH) AND IGF(IGH,FFF) AND GTECH_TYPE(IGH,TECH_TYPE))=
       VGH_T.L(Y,IA,IGH,S,T);

** DISTRICT HEAT PRODUCTION ANNUALY
PRO_YCRAGF(Y,C,IR,IA,IGH,FFF,'DISTRICT_HEAT',TECH_TYPE,'TWh')$(CCCRRR(C,IR) and RRRAAA(IR,IA) and IAGK_HASORPOT(Y,IA,IGH) AND IGF(IGH,FFF) AND GTECH_TYPE(IGH,TECH_TYPE))=
       SUM((S,T),IHOURSINST(S,T)*VGH_T.L(Y,IA,IGH,S,T))/IOF1000000;

* ---------------- END OF ENERGY PRODUCTION -----------------


* -------------------- FUEL CONSUMPTION ---------------------

** HOURLY FUEL CONSUMPTION
F_CONS_YCRAST(Y,C,IR,IA,G,FFF,S,T,TECH_TYPE,'MWh')$(CCCRRR(C,IR) and RRRAAA(IR,IA) and IAGK_HASORPOT(Y,IA,G) AND IGF(G,FFF) AND GTECH_TYPE(G,TECH_TYPE))=
       VGF_T.L(Y,IA,G,S,T);

** ANNUAL FUEL CONSUMPTION
F_CONS_YCRA(Y,C,IR,IA,G,FFF,TECH_TYPE,'TWh')$(CCCRRR(C,IR) and RRRAAA(IR,IA) and IAGK_HASORPOT(Y,IA,G) AND IGF(G,FFF) AND GTECH_TYPE(G,TECH_TYPE))=
       SUM((S,T),IHOURSINST(S,T)*VGF_T.L(Y,IA,G,S,T))/IOF1000000;


* ---------------- END OF FUEL CONSUMPTION -----------------


* ------------------------- ENERGY DEMAND ----------------------

* ------------- ELECTRICITY DEMAND --------------

** EXOGENOUS DEMAND

EL_DEMAND_YCRST(Y,C,IR,S,T,'EXOGENOUS','MWh')$CCCRRR(C,IR)=
         SUM(DEUSER,IDE_T(Y,IR,DEUSER,S,T))/(1-DISLOSS_E(IR));

** ENDOGENOUS DEMAND

EL_DEMAND_YCRST(Y,C,IR,S,T,'ENDOGENOUS','MWh')$CCCRRR(C,IR)=


* HEAT PUMPS CONSUMPTION
         SUM(IA$RRRAAA(IR,IA), SUM(IGETOH$IAGK_HASORPOT(Y,IA,IGETOH), VGE_T.L(Y,IA,IGETOH,S,T)))


* INTRASEASONAL ELECTRICITY STORAGE
         +SUM(IA$RRRAAA(IR,IA),SUM(IGESTO$IAGK_HASORPOT(Y,IA,IGESTO),VESTOLOADT.L(Y,IA,IGESTO,S,T)))
* INTERSEASONAL ELECTRICITY STORAGE
         +SUM(IA$RRRAAA(IR,IA),SUM(IGESTOS$IAGK_HASORPOT(Y,IA,IGESTOS),VESTOLOADTS.L(Y,IA,IGESTOS,S,T)))

;

* ----------- END OF ELECTRICITY DEMAND --------------

* ------------- HEAT DEMAND --------------

** EXOGENOUS DEMAND

DH_DEMAND_YCRAST(Y,C,IR,IA,S,T,'EXOGENOUS','MWh')$(CCCRRR(C,IR) AND RRRAAA(IR,IA))=
         SUM(DHUSER,IDH_T(Y,IA,DHUSER,S,T))/(1-DISLOSS_H(IA));

** ENDOGENOUS DEMAND

DH_DEMAND_YCRAST(Y,C,IR,IA,S,T,'ENDOGENOUS','MWh')$(CCCRRR(C,IR) AND RRRAAA(IR,IA))=

* INTRASEASONAL HEAT STORAGE
        SUM(IGHSTO$IAGK_HASORPOT(Y,IA,IGHSTO),VHSTOLOADT.L(Y,IA,IGHSTO,S,T))
* INTERSEASONAL HEAT STORAGE
        + SUM(IGHSTOS$IAGK_HASORPOT(Y,IA,IGHSTOS),VHSTOLOADTS.L(Y,IA,IGHSTOS,S,T))
;

* ----------- END OF HEAT DEMAND --------------

* -------------------- END OF ENERGY DEMAND -----------------------



* -------------------- TRANSMISSION CAPACITY -----------------------

** EXOGENOUS ELECTRICITY CAPACITY

X_CAP_YCR(Y,C,IR,IRI,'EXOGENOUS','GW')$(CCCRRR(C,IR) AND IXK_HASORPOT(Y,IR,IRI))=
IOF0001*XKFX(Y,IR,IRI)
;


** ENDOGENOUS ELECTRIC CAPACITY

$ifi not %TransInvest%==yes $goto Transmission_investments_end
X_CAP_YCR(Y,C,IR,IRI,'ENDOGENOUS','GW')$(CCCRRR(C,IR) AND IXK_HASORPOT(Y,IR,IRI))=
IOF0001*VXKNACCUMNET.L(Y,IR,IRI)
;
$label  Transmission_investments_end


* -------------------- END OF TRANSMISSION CAPACITY -----------------------

* -------------------- TRANSMISSION FLOW -----------------------

** HOURLY TRANSMISSION FLOW

X_FLOW_YCRST(Y,C,IR,IRI,S,T,'MWh')$(CCCRRR(C,IR) AND IXK_HASORPOT(Y,IR,IRI))=
VX_T.L(Y,IR,IRI,S,T);
;


** ANNUAL TRANSMISSION FLOW
X_FLOW_YCR(Y,C,IR,IRI,'TWh')$(CCCRRR(C,IR) AND IXK_HASORPOT(Y,IR,IRI))=
SUM((S,T),IHOURSINST(S,T)*VX_T.L(Y,IR,IRI,S,T))/IOF1000000;
;



* -------------------- END OF TRANSMISSION FLOW -----------------------



* ---------------------- ECONOMIC OUTPUT ----------------------

* ------------- COSTS --------------

* -- GENERATION COSTS -----

** GENERATION INVESTMENTS

ECO_G_YCRAG(Y,C,IR,IA,G,'COSTS','GENERATION_CAPITAL_COSTS','Mmoney')$(CCCRRR(C,IR) and RRRAAA(IR,IA) and  VGKN.L(Y,IA,G))=
         OMONEY*VGKN.L(Y,IA,G)*GINVCOST(IA,G)*ANNUITYCG(C,G);

** GENEARTION FIXED COSTS

ECO_G_YCRAG(Y,C,IR,IA,G,'COSTS','GENERATION_FIXED_COSTS','Mmoney')$(CCCRRR(C,IR) and RRRAAA(IR,IA) and IAGK_HASORPOT(Y,IA,G))=
         OMONEY/IOF1000*(GKFX(Y,IA,G)+VGKNACCUMNET.L(Y,IA,G))*GOMFCOST(IA,G);

** GENERATION O&M COSTS

ECO_G_YCRAG(Y,C,IR,IA,G,'COSTS','GENERATION_OPERATIONAL_COSTS','Mmoney')$(CCCRRR(C,IR) and RRRAAA(IR,IA) and IAGK_HASORPOT(Y,IA,G))=
   OMONEY/IOF1000000*
     ((GOMVCOSTO(IA,G)*
      (
   +   SUM((S,T), IHOURSINST(S,T) * VGE_T.L(Y,IA,G,S,T))$IAGK_HASORPOT(Y,IA,G)))$IGKE(G)

   +  (GOMVCOSTO(IA,G) * GDATA(G,'GDCV') *
      (
   +   SUM((S,T), IHOURSINST(S,T) * VGH_T.L(Y,IA,G,S,T))$IAGK_HASORPOT(Y,IA,G)))$IGKH(G)

   +  (GOMVCOSTIN(IA,G)*
      (
   +   SUM((S,T), IHOURSINST(S,T) * VGF_T.L(Y,IA,G,S,T))$IAGK_HASORPOT(Y,IA,G)))
     ) ;

** GENERATION FUEL COSTS

ECO_G_YCRAG(Y,C,IR,IA,G,'COSTS','GENERATION_FUEL_COSTS','Mmoney')$(CCCRRR(C,IR) and RRRAAA(IR,IA) and IAGK_HASORPOT(Y,IA,G))=
   OMONEY*IOF3P6/IOF1000000*
    SUM(FFF$(GDATA(G,'GDFUEL') EQ FDATA(FFF,'FDACRONYM')),
                 FUELPRICE(Y,IA,FFF)*(
                 SUM((S,T), IHOURSINST(S,T) * VGF_T.L(Y,IA,G,S,T) )$IAGK_HASORPOT(Y,IA,G)
                )
    )$(IGNOTETOH(G) and (not IGESTO(G)) and (not IGHSTO(G)) and (not IGESTOS(G)) and (not IGHSTOS(G)))

$ONTEXT
*NOT RELEVANT
* Electricity storages:
    +OMONEY/IOF1000000*SUM((S,T), QEEQ.M(Y,IR,S,T)/IDISCOUNTFACTOR(Y)/IWEIGHTY(Y)*VESTOLOADT.L(Y,IA,G,S,T))$IGESTO(G)
    +OMONEY/IOF1000000*SUM((S,T), QEEQ.M(Y,IR,S,T)/IDISCOUNTFACTOR(Y)/IWEIGHTY(Y)*VESTOLOADTS.L(Y,IA,G,S,T))$IGESTOS(G)
* Heat storages:
    +OMONEY/IOF1000000*SUM((S,T), QHEQ.M(Y,IA,S,T)/IDISCOUNTFACTOR(Y)/IWEIGHTY(Y)*VHSTOLOADT.L(Y,IA,G,S,T))$IGHSTO(G)
    +OMONEY/IOF1000000*SUM((S,T), QHEQ.M(Y,IA,S,T)/IDISCOUNTFACTOR(Y)/IWEIGHTY(Y)*VHSTOLOADTS.L(Y,IA,G,S,T))$IGHSTOS(G)
* Electricity to heat:
    +OMONEY/IOF1000000*SUM((S,T), QEEQ.M(Y,IR,S,T)/IDISCOUNTFACTOR(Y)/IWEIGHTY(Y)*VGE_T.L(Y,IA,G,S,T))$(IAGK_HASORPOT(Y,IA,G) and IGETOH(G))
$OFFTEXT
;

** CO2 EMISSIONS COST

ECO_G_YCRAG(Y,C,IR,IA,G,'COSTS','GENERATION_CO2_COSTS','Mmoney')$(CCCRRR(C,IR) and RRRAAA(IR,IA) and IAGK_HASORPOT(Y,IA,G))=
         OMONEY/IOF1000000*IM_CO2(G)*IOF0001 * IOF3P6 *M_POL(Y,"TAX_CO2",C) * SUM((S,T), IHOURSINST(S,T)*VGF_T.L(Y,IA,G,S,T))$IAGK_HASORPOT(Y,IA,G);

* -- TRANSMISSION COSTS -----

** TRANSMISSION INVESTMENTS
ECO_X_OUTPUT_YCR(Y,C,IR,'COSTS','TRANSMISSION_CAPITAL_COSTS','Mmoney')$CCCRRR(C,IR)=
          OMONEY*IOF0000001*SUM(IRI$IXK_HASORPOT(Y,IR,IRI),
                                    (IOF05*VXKN.L(Y,IR,IRI))*XINVCOST(Y,IR,IRI)*(IOF05*ANNUITYCX(C))
                                );

** TRANSMISSION FLOW

ECO_X_OUTPUT_YCR(Y,C,IR,'COSTS','TRANSMISSION_OPERATIONAL_COSTS','Mmoney')$CCCRRR(C,IR)=
OMONEY*IOF0000001*SUM(IRI$IXK_HASORPOT(Y,IR,IRI), SUM((S,T), IHOURSINST(S,T) * (VX_T.L(Y,IR,IRI,S,T) * XCOST(IR,IRI))));

* ------------- END OF COSTS --------------

* ------------- OBJECTIVE FUNCTION --------------

OBJ_YCR(Y,C,IR,SUBCATEGORY,'Mmoney')$CCCRRR(C,IR)=

*GENERATION COSTS
SUM((IA,G)$(RRRAAA(IR,IA)AND IAGK_HASORPOT(Y,IA,G)),ECO_G_YCRAG(Y,C,IR,IA,G,'COSTS',SUBCATEGORY,'Mmoney'))

*TRANSMISSION COSTS
+ ECO_X_OUTPUT_YCR(Y,C,IR,'COSTS',SUBCATEGORY,'Mmoney');

* ------------- END OF OBJECTIVE FUNCTION --------------

* ------------- INCOME --------------

** ELECTRICITY SALES
ECO_G_YCRAG(Y,C,IR,IA,G,'INCOME','ELECTRICITY_SALE','Mmoney')$(CCCRRR(C,IR) and RRRAAA(IR,IA) and IAGK_HASORPOT(Y,IA,G) and IGE(G))=
 OMONEY*IOF0000001*
   (SUM((S,T), VGE_T.L(Y,IA,G,S,T)*QEEQ.M(Y,IR,S,T)/IDISCOUNTFACTOR(Y)/IWEIGHTY(Y)))*(1-2$(IGETOH(G)));

* ------------- END OF INCOME --------------

* ------------- COMMODITY PRICES --------------

** ELECTRICITY PRICES

*HOURLY ELECTRICITY PRICE

EL_PRICE_YCRST(Y,C,IR,S,T,'Money_per_MWh')$CCCRRR(C,IR)=OMONEY*QEEQ.M(Y,IR,S,T)/IDISCOUNTFACTOR(Y)/IWEIGHTY(Y)/IHOURSINST(S,T);

*AVERAGE ELECTRICITY PRICE

EL_PRICE_YCR(Y,C,IR,'AVERAGE','Money_per_MWh')$CCCRRR(C,IR)=
OMONEY/IOF8760/IDISCOUNTFACTOR(Y)/IWEIGHTY(Y)*SUM((S,T),QEEQ.M(Y,IR,S,T));

$ontext
*EXCLUDED SO FAR
*AVERAGE ELECTRICITY PRICE WEIGTHED BY CONSUMPTION

EL_PRICE_YCR(Y,C,IR,'AVERAGE_WEIGHTED_BY_CONSUMPTION','Money_per_MWh')$CCCRRR(C,IR)=
               SUM((VARIABLE_CATEGORY,S,T),
                         EL_PRICE_YCRST(Y,C,IR,S,T,'Money_per_MWh')*EL_DEMAND_YCRST(Y,C,IR,S,T,VARIABLE_CATEGORY,'MWh')
                         )
               /SUM((VARIABLE_CATEGORY,S,T),EL_DEMAND_YCRST(Y,C,IR,S,T,VARIABLE_CATEGORY,'MWh'))
;

*AVERAGE ELECTRICITY PRICE WEIGTHED BY PRODUCTION

EL_PRICE_YCR(Y,C,IR,'AVERAGE_WEIGHTED_BY_PRODUCTION','Money_per_MWh')$CCCRRR(C,IR)=
               SUM((IGE,IA,FFF,S,T,TECH_TYPE)$(RRRAAA(IR,IA) AND IAGK_HASORPOT(Y,IA,IGE)),
                         EL_PRICE_YCRST(Y,C,IR,S,T,'Money_per_MWh')*PRO_YCRAGFST(Y,C,IR,IA,IGE,FFF,S,T,'ELECTRICITY',TECH_TYPE,'MWh')
                         )
               /SUM((IGE,IA,FFF,S,T,TECH_TYPE)$(RRRAAA(IR,IA) AND IAGK_HASORPOT(Y,IA,IGE)),PRO_YCRAGFST(Y,C,IR,IA,IGE,FFF,S,T,'ELECTRICITY',TECH_TYPE,'MWh'))
;
$offtext

** END OF ELECTRICITY PRICES

** DISTRICT HEATING PRICES

*HOURLY DISTRICT HEATING PRICE

DH_PRICE_YCRAST(Y,C,IR,IA,S,T,'Money_per_MWh')$(CCCRRR(C,IR) AND RRRAAA(IR,IA) AND SUM(DHUSER, IDH_SUMST(IA,DHUSER)))=OMONEY*QHEQ.M(Y,IA,S,T)/IDISCOUNTFACTOR(Y)/IWEIGHTY(Y)/IHOURSINST(S,T);

*AVERAGE DISTRICT HEATING PRICE

DH_PRICE_YCRA(Y,C,IR,IA,'AVERAGE','Money_per_MWh')$(CCCRRR(C,IR) AND RRRAAA(IR,IA) AND SUM(DHUSER, IDH_SUMST(IA,DHUSER)))=
OMONEY/IOF8760/IDISCOUNTFACTOR(Y)/IWEIGHTY(Y)*SUM((S,T),QHEQ.M(Y,IA,S,T));

$ontext
*EXCLUDED SO FAR
*AVERAGE DISTRICT HEATING PRICE WEIGTHED BY CONSUMPTION

DH_PRICE_YCRA(Y,C,IR,IA,'AVERAGE_WEIGHTED_BY_CONSUMPTION','Money_per_MWh')$(CCCRRR(C,IR) AND RRRAAA(IR,IA) AND SUM(DHUSER, IDH_SUMST(IA,DHUSER)))=
               SUM((VARIABLE_CATEGORY,S,T),
                         DH_PRICE_YCRAST(Y,C,IR,IA,S,T,'Money_per_MWh')*DH_DEMAND_YCRAST(Y,C,IR,IA,S,T,VARIABLE_CATEGORY,'MWh')
                         )
               /SUM((VARIABLE_CATEGORY,S,T),DH_DEMAND_YCRAST(Y,C,IR,IA,S,T,VARIABLE_CATEGORY,'MWh'))
;

*AVERAGE DISTRICT HEATING PRICE WEIGTHED BY PRODUCTION

DH_PRICE_YCRA(Y,C,IR,IA,'AVERAGE_WEIGHTED_BY_PRODUCTION','Money_per_MWh')$(CCCRRR(C,IR) AND RRRAAA(IR,IA) AND SUM(DHUSER, IDH_SUMST(IA,DHUSER)))=
               SUM((IGH,FFF,S,T,TECH_TYPE)$IAGK_HASORPOT(Y,IA,IGH),
                         DH_PRICE_YCRAST(Y,C,IR,IA,S,T,'Money_per_MWh')*PRO_YCRAGFST(Y,C,IR,IA,IGH,FFF,S,T,'DISTRICT_HEAT',TECH_TYPE,'MWh')
                         )
               /SUM((IGH,FFF,S,T,TECH_TYPE)$IAGK_HASORPOT(Y,IA,IGH),PRO_YCRAGFST(Y,C,IR,IA,IGH,FFF,S,T,'DISTRICT_HEAT',TECH_TYPE,'MWh'))
;
$offtext

** END OF DISTRICT HEATING PRICES


* ------------- END OF COMMODITY PRICES --------------


* --------- END OF ECONOMIC OUTPUT -----------

* ---------------------- ENVIRONMENT ----------------------

* ------------- CO2 EMISSIONS -------------

EMI_YCRAG(Y,C,IR,IA,G,FFF,TECH_TYPE,'kton')$(F_CONS_YCRA(Y,C,IR,IA,G,FFF,TECH_TYPE,'TWh'))=
F_CONS_YCRA(Y,C,IR,IA,G,FFF,TECH_TYPE,'TWh')*IM_CO2(G)*IOF3P6;

* ------------- END OF CO2 EMISSIONS -------------

* ---------------------- END OF ENVIRONMENT ----------------------




execute_unload "MainResults.gdx" ECO_G_YCRAG,ECO_X_OUTPUT_YCR,OBJ_YCR,EL_PRICE_YCR,EL_PRICE_YCRST,PRO_YCRAGFST,EL_DEMAND_YCRST,
DH_DEMAND_YCRAST,PRO_YCRAGF,DH_PRICE_YCRAST,DH_PRICE_YCRA,G_CAP_YCRAF,X_CAP_YCR,X_FLOW_YCRST,X_FLOW_YCR,F_CONS_YCRAST,F_CONS_YCRA,EMI_YCRAG;























** ----------------------- AMALIAS OUTPUT (FOR INSPIRATION) --------------------------

$ontext
* MODELING OF THE ELECTRICITY GENERATION

SET EDemand_type /classic, transport, "individual heating", "process heating", DH, H2/;


SET TECHTYPE  'Type of technologies for calculation of marginals' %semislash%
$if     EXIST '../data/TECHTYPE.inc' $INCLUDE      '../data/TECHTYPE.inc';
$if not EXIST '../data/TECHTYPE.inc' $INCLUDE '../../base/data/TECHTYPE.inc';
%semislash%;

SET GTECHTYPE(GGG,TECHTYPE) 'Type of technology aggrupated'%semislash%
$if     EXIST '../data/GTECHTYPE.inc' $INCLUDE      '../data/GTECHTYPE.inc';
$if not EXIST '../data/GTECHTYPE.inc' $INCLUDE '../../base/data/GTECHTYPE.inc';
%semislash%;

SET ELECTRADE /Import, Export, "Net Export"/;


SET RRROFFSHORE(RRR);
RRROFFSHORE(IR)$SUM(IA,RRRAAA(IR,IA)$AAAOFFSHORE(IA))=YES;
RRROFFSHORE("DK_E")=NO;
RRROFFSHORE("DK_W")=NO;
RRROFFSHORE("DK_KF")=NO;
RRROFFSHORE("DE_KF")=NO;

SET CAPACITIES /New, Existing, TOTAL/;






Parameter EPrice_RST(RRR,SSS,TTT)  'Electricity price per hour at a regional level - cost of producing one unit more of electricity for own consumption or for export (€ 2015/MWh)';
EPrice_RST(IR,S,T)=QEEQ.M(IR,S,T)*MONEYCONVERT/IHOURSINST(S,T);

Parameter HPrice_AST(AAA,SSS,TTT)'Heat price per hour at an area level - cost of producing one unit more of heat(€ 2015/MWh)';
HPrice_AST(IA,S,T)=QHEQ.M(IA,S,T)*MONEYCONVERT/IHOURSINST(S,T);

$if     EXIST '../addons/_hooks/OutputCalculation.inc' $INCLUDE      '../addons/_hooks/OutputCalculation.inc';
$if not EXIST '../addons/_hooks/OutputCalculation.inc' $INCLUDE '../../base/addons/_hooks/OutputCalculation.inc';


* MODELING OF THE ELECTRICITY DEMAND

Parameter EDemand_RST(EDemand_type,RRR,SSS,TTT) 'Electricity Demand (MW)';

EDemand_RST("classic",IR,S,T)$(NOT (RETRANS(IR) OR RINDUS(IR)))=IDE_T_Y(IR,S,T);

EDemand_RST("transport",IR,S,T)=SUM(RETRANS$IXKINI_Y(IR,RETRANS),IDE_T_Y(RETRANS,S,T));

EDemand_RST("individual heating",IR,S,T)=SUM(IAGK_Y(IA,IGE)$((RRRAAA(IR,IA) AND (AINDHEAT(IA))) AND IGETOH(IGE)), VGE_T.L(IA,IGE,S,T))
$ifi %bb2%==yes                         +SUM(IAGKN(IA,IGE)$((RRRAAA(IR,IA) AND (AINDHEAT(IA))) AND IGETOH(IGE)), VGEN_T.L(IA,IGE,S,T));

EDemand_RST("process heating",IR,S,T)=SUM(RINDUS$IXKINI_Y(IR,RINDUS),IDE_T_Y(RINDUS,S,T));

EDemand_RST("DH",IR,S,T)=SUM(IAGK_Y(IA,IGE)$((RRRAAA(IR,IA) AND (NOT AINDHEAT(IA))) AND IGETOH(IGE)), VGE_T.L(IA,IGE,S,T))
$ifi %bb2%==yes         +SUM(IAGKN(IA,IGE)$((RRRAAA(IR,IA) AND (NOT AINDHEAT(IA))) AND IGETOH(IGE)), VGEN_T.L(IA,IGE,S,T));

$ifi %H2%==yes  EDemand_RST("H2",IR,S,T)=SUM(IAGK_Y(IA,IGETOH2)$(RRRAAA(IR,IA)), VGE_T.L(IA,IGETOH2,S,T))
$ifi %bb2%==yes                         +SUM(IAGKN(IA,IGETOH2)$(RRRAAA(IR,IA)), VGEN_T.L(IA,IGETOH2,S,T));


Parameter Edemand_CST(EDemand_type,CCC,SSS,TTT) 'Electricity Demand (MW)';
Edemand_CST(EDemand_type,C,S,T)=SUM(IR$CCCRRR(C,IR),EDemand_RST(EDemand_type,IR,S,T));


Parameter Edemand_R(EDemand_type,RRR) 'Electricity Demand (PJ/year)';
Edemand_R(EDemand_type,IR)=SUM((S,T),EDemand_RST(EDemand_type,IR,S,T)*IHOURSINST(S,T))*IOF0000001*IOF3P6;


Parameter Edemand_C(EDemand_type,CCC) 'Electricity Demand (PJ/year)';
Edemand_C(EDemand_type,C)=SUM((S,T),EDemand_CST(EDemand_type,C,S,T)*IHOURSINST(S,T))*IOF0000001*IOF3P6;

Parameter Hdemand_AST(AAA,SSS,TTT) 'District Heating Demand (MW)';
Hdemand_AST(IA,S,T)$(NOT AINDHEAT(IA))=IDH_T_Y(IA,S,T);


*Weighted average electricity price by consumption quantity (€ 2015/MWh)

Parameter EPrice_R(RRR) 'Weighted average electricity price by consumption quantity per year at a regional level (€ 2015/MWh)';
EPrice_R(IR)$(SUM((EDemand_type,S,T),EDemand_RST(EDemand_type,IR,S,T)*IHOURSINST(S,T)))=SUM((EDemand_type,S,T),EDemand_RST(EDemand_type,IR,S,T)*IHOURSINST(S,T)*EPrice_RST(IR,S,T))/SUM((EDemand_type,S,T),EDemand_RST(EDemand_type,IR,S,T)*IHOURSINST(S,T));

Parameter EPrice_CST(CCC,SSS,TTT) 'Weighted average electricity price by consumption quantity at a country level(€ 2015/MWh)';
EPrice_CST(C,S,T)=SUM((EDemand_type,IR)$CCCRRR(C,IR),EDemand_RST(EDemand_type,IR,S,T)*EPrice_RST(IR,S,T))/SUM((EDemand_type,IR)$CCCRRR(C,IR),EDemand_RST(EDemand_type,IR,S,T));

Parameter EPrice_C(CCC) 'Weighted average electricity price by consumption quantity per year at a country level (€ 2015/MWh)';
EPrice_C(C)=SUM((EDemand_type,S,T),EDemand_CST(EDemand_type,C,S,T)*IHOURSINST(S,T)*EPrice_CST(C,S,T))/SUM((EDemand_type,S,T),EDemand_CST(EDemand_type,C,S,T)*IHOURSINST(S,T));

*Weighted average heat price by consumption quantity (€ 2012/MWh)
Parameter HPrice_AS(AAA,SSS) 'Weighted average heat price by consumption quantity per week at an area level (€ 2015/MWh)';
HPrice_AS(IA,S)$(SUM(T,Hdemand_AST(IA,S,T)))=SUM(T,HPrice_AST(IA,S,T)*Hdemand_AST(IA,S,T)*IHOURSINST(S,T))/SUM(T,Hdemand_AST(IA,S,T)*IHOURSINST(S,T));

Parameter HPrice_A(AAA) 'Weighted average heat price by consumption quantity per year at an area level (€ 2015/MWh)';
HPrice_A(IA)$(SUM((S,T),Hdemand_AST(IA,S,T)))=SUM((S,T),HPrice_AST(IA,S,T)*Hdemand_AST(IA,S,T)*IHOURSINST(S,T))/SUM((S,T),Hdemand_AST(IA,S,T)*IHOURSINST(S,T));

Parameter HPrice_C(CCC) 'Weighted average heat price by consumption quantity per year at an country level (€ 2015/MWh)';
HPrice_C(CCC)$(SUM((S,T,IA)$ICA(CCC,IA),Hdemand_AST(IA,S,T)))=SUM((S,T,IA)$ICA(CCC,IA),HPrice_AST(IA,S,T)*Hdemand_AST(IA,S,T)*IHOURSINST(S,T))/SUM((S,T,IA)$ICA(CCC,IA),Hdemand_AST(IA,S,T)*IHOURSINST(S,T));



Parameter EProduction_RST(RRR,TECHTYPE,SSS,TTT) 'Electricity production at a regional level (MW)';
EProduction_RST(IR,TECHTYPE,S,T)= SUM(IAGK_Y(IA,IGE)$((RRRAAA(IR,IA) AND (NOT AAAOFFSHORE(IA))) AND IGNOTETOH(IGE) AND GTECHTYPE(IGE,TECHTYPE)), VGE_T.L(IA,IGE,S,T))
$ifi %bb2%==yes                  +SUM(IAGKN(IA,IGE)$((RRRAAA(IR,IA) AND (NOT AAAOFFSHORE(IA))) AND IGNOTETOH(IGE) AND GTECHTYPE(IGE,TECHTYPE)), VGEN_T.L(IA,IGE,S,T))
                                 +SUM(RRROFFSHORE$IXKINI_Y(RRROFFSHORE,IR),(SUM(IAGK_Y(IA,IGE)$((RRRAAA(RRROFFSHORE,IA) AND (AAAOFFSHORE(IA))) AND IGNOTETOH(IGE) AND GTECHTYPE(IGE,TECHTYPE)), VGE_T.L(IA,IGE,S,T)))*(1-XLOSS(RRROFFSHORE,IR)))
$ifi %bb2%==yes                  +SUM(RRROFFSHORE$IXKINI_Y(RRROFFSHORE,IR),(SUM(IAGKN(IA,IGE)$((RRRAAA(RRROFFSHORE,IA) AND (AAAOFFSHORE(IA))) AND IGNOTETOH(IGE) AND GTECHTYPE(IGE,TECHTYPE)), VGEN_T.L(IA,IGE,S,T)))*(1-XLOSS(RRROFFSHORE,IR)))

$if     EXIST '../addons/_hooks/EProduction_RST.inc' $INCLUDE      '../addons/_hooks/EProduction_RST.inc';
$if not EXIST '../addons/_hooks/EProduction_RST.inc' $INCLUDE '../../base/addons/_hooks/EProduction_RST.inc';

;

Parameter ETrade_RST(RRR,ELECTRADE,SSS,TTT) 'Electricity trade at a regional level (MW)';

*electricity import, do not consider import from offshore regions
ETrade_RST(IR,"Import",S,T)$((NOT RETRANS(IR)) AND (NOT RINDUS(IR)))=SUM(IRE$((IXKINI_Y(IRE,IR) OR IXKN(IRE,IR) OR IXKN(IR,IRE)) AND (NOT RRROFFSHORE(IRE))), VX_T.L(IRE,IR,S,T)*(1-XLOSS(IRE,IR)));

*electricity export, do not consider export towards EV region or industrial region
ETrade_RST(IR,"Export",S,T)$(NOT RRROFFSHORE(IR))= SUM(IRI$((IXKINI_Y(IR,IRI) OR IXKN(IR,IRI) OR IXKN(IRI,IR)) AND ((NOT RETRANS(IRI)) AND (NOT RINDUS(IRI)))),VX_T.L(IR,IRI,S,T));

ETrade_RST(IR,"Net Export",S,T)=ETrade_RST(IR,"Export",S,T)-ETrade_RST(IR,"Import",S,T);

Parameter Eproduction_CST(CCC,TECHTYPE,SSS,TTT) 'Electricity production at a country level (MW)';
Eproduction_CST(C,TECHTYPE,S,T)=SUM(IR$CCCRRR(C,IR),EProduction_RST(IR,TECHTYPE,S,T));

Parameter ETrade_CST(CCC,ELECTRADE,SSS,TTT) 'Electricity trade at a country level (MW)';
ETrade_CST(C,"Import",S,T)=SUM((IR,IRE)$(CCCRRR(C,IR) AND (NOT CCCRRR(C,IRE))AND (IXKINI_Y(IRE,IR) OR IXKN(IR,IRE) OR IXKN(IRE,IR)) AND (IXKINI_Y(IRE,IR) NE INF)), VX_T.L(IRE,IR,S,T)*(1-XLOSS(IRE,IR)));
ETrade_CST(C,"Export",S,T)=SUM((IR,IRI)$(CCCRRR(C,IR) AND (NOT CCCRRR(C,IRI))AND (IXKINI_Y(IR,IRI) OR IXKN(IRI,IR) OR IXKN(IR,IRI)) AND (IXKINI_Y(IR,IRI) NE INF)), VX_T.L(IR,IRI,S,T));
ETrade_CST(C,"Net Export",S,T)=ETrade_CST(C,"Export",S,T)-ETrade_CST(C,"Import",S,T);


*Energy production and trade at a yearly level in (PJ/year) units:
Parameter Eproduction_R(RRR,TECHTYPE) 'Electricity production at a regional level (PJ/year)';
EProduction_R(IR,TECHTYPE)=(SUM((S,T),EProduction_RST(IR,TECHTYPE,S,T)*IHOURSINST(S,T)))*IOF0000001*IOF3P6;

Parameter Eproduction_C(CCC,TECHTYPE) 'Electricity production at a country level (PJ/year)';
EProduction_C(C,TECHTYPE)= (SUM((S,T),EProduction_CST(C,TECHTYPE,S,T)*IHOURSINST(S,T)))*IOF0000001*IOF3P6;

Parameter ETrade_R(RRR,ELECTRADE) 'Electricity trade at a regional level (PJ/year)';
ETrade_R(IR,ELECTRADE)=(SUM((S,T),ETrade_RST(IR,ELECTRADE,S,T)*IHOURSINST(S,T)))*IOF0000001*IOF3P6;

Parameter ETrade_C(CCC,ELECTRADE) 'Electricity trade at a regional level (PJ/year)';
ETrade_C(C,ELECTRADE)=(SUM((S,T),ETrade_CST(C,ELECTRADE,S,T)*IHOURSINST(S,T)))*IOF0000001*IOF3P6;

EProduction_RST(IR,"Net Trade",S,T)=-ETrade_RST(IR,"Net Export",S,T);
Eproduction_CST(C,"Net Trade",S,T)=-ETrade_CST(C,"Net Export",S,T);


*HEAT GENERATION

Parameter Hproduction_AST(AAA,TECHTYPE,SSS,TTT) 'Heat production at an area level (MW)';

Hproduction_AST(IA,TECHTYPE,S,T)$(NOT AINDHEAT(IA))=
                                  SUM(IGBPR$(IAGK_Y(IA,IGBPR) AND GTECHTYPE(IGBPR,TECHTYPE)),VGH_T.L(IA,IGBPR,S,T))
$ifi %bb2%==yes                 + SUM(IGBPR$(IAGKN(IA,IGBPR) AND GTECHTYPE(IGBPR,TECHTYPE)),VGHN_T.L(IA,IGBPR,S,T))
                                + SUM(IGEXT$(IAGK_Y(IA,IGEXT) AND GTECHTYPE(IGEXT,TECHTYPE)),VGH_T.L(IA,IGEXT,S,T))
$ifi %bb2%==yes                 + SUM(IGEXT$(IAGKN(IA,IGEXT) AND GTECHTYPE(IGEXT,TECHTYPE)),VGHN_T.L(IA,IGEXT,S,T))
                                + SUM(IGHH$(IAGK_Y(IA,IGHH) AND GTECHTYPE(IGHH,TECHTYPE)),VGH_T.L(IA,IGHH,S,T))
$ifi %bb2%==yes                 + SUM(IGHH$(IAGKN(IA,IGHH) AND GTECHTYPE(IGHH,TECHTYPE)),VGHN_T.L(IA,IGHH,S,T))
                                + SUM(IGETOH$(IAGK_Y(IA,IGETOH) AND GTECHTYPE(IGETOH,TECHTYPE)),VGH_T.L(IA,IGETOH,S,T))
$ifi %bb2%==yes                 + SUM(IGETOH$(IAGKN(IA,IGETOH) AND GTECHTYPE(IGETOH,TECHTYPE)),VGHN_T.L(IA,IGETOH,S,T))
$ifi %H2%==yes                  +SUM(IGETOH2$(IAGK_Y(IA,IGETOH2) AND GTECHTYPE(IGETOH2,TECHTYPE)), VGH_T.L(IA,IGETOH2,S,T))
$ifi %H2%==yes                  +SUM(IGETOH2$(IAGKN(IA,IGETOH2) AND GTECHTYPE(IGETOH2,TECHTYPE)), VGHN_T.L(IA,IGETOH2,S,T))

$if     EXIST '../addons/_hooks/Hproduction_AST.inc' $INCLUDE      '../addons/_hooks/Hproduction_AST.inc';
$if not EXIST '../addons/_hooks/Hproduction_AST.inc' $INCLUDE '../../base/addons/_hooks/Hproduction_AST.inc';
;

Hproduction_AST(IA,"Heat to Storage",S,T)=VHSTOLOADT.L(IA,S,T)$SUM(IGHSTO$(IAGK_Y(IA,IGHSTO) or IAGKN(IA,IGHSTO)),1);
Hproduction_AST(IA,"Heat cool down",S,T)=VCOOLDOWN.L(IA,S,T);

Parameter Hproduction_AS(AAA,TECHTYPE,SSS) 'Heat production at an area level per week (MWh)';
Hproduction_AS(IA,TECHTYPE,S)=SUM(T,Hproduction_AST(IA,TECHTYPE,S,T)*WEIGHT_T(T)*SUM(TTT,WEIGHT_T(TTT))/IWEIGHSUMT);

Parameter Hproduction_A(AAA,TECHTYPE) 'Heat production at an area level per year (PJ/year)';
Hproduction_A(IA,TECHTYPE)=(SUM((S,T),Hproduction_AST(IA,TECHTYPE,S,T)*IHOURSINST(S,T)))*IOF0000001*IOF3P6;

Parameter Hproduction_CST(CCC,TECHTYPE,SSS,TTT) 'Heat production at a country level (MW)';
Hproduction_CST(C,TECHTYPE,S,T)=SUM(IA$ICA(C,IA),Hproduction_AST(IA,TECHTYPE,S,T));

Parameter Hproduction_CS(CCC,TECHTYPE,SSS) 'Heat production at a country level per week (MWh)';
Hproduction_CS(C,TECHTYPE,S)=SUM(IA$ICA(C,IA),Hproduction_AS(IA,TECHTYPE,S));

Parameter Hproduction_C(CCC,TECHTYPE) 'Heat production at a country level per year (PJ/year)';
Hproduction_C(C,TECHTYPE)=SUM(IA$ICA(C,IA),Hproduction_A(IA,TECHTYPE));

Parameter FuelConsumption_C(CCC,TECHTYPE)  'Fuel Consumption at a country level per type of technology (PJ/year)';
FuelConsumption_C(C,TECHTYPE)=SUM((IA,G,S,T)$(ICA(C,IA) AND GTECHTYPE(G,TECHTYPE)),IHOURSINST(S,T)*(VGF_T.L(IA,G,S,T)+VGFN_T.L(IA,G,S,T)))*IOF0000001*IOF3P6
$if     EXIST '../addons/_hooks/FuelConsumption_C.inc' $INCLUDE      '../addons/_hooks/FuelConsumption_C.inc';
$if not EXIST '../addons/_hooks/FuelConsumption_C.inc' $INCLUDE '../../base/addons/_hooks/FuelConsumption_C.inc';

;

Parameter FuelConsumption_TOTAL(TECHTYPE)  'Fuel Consumption in all the simulated countryes per type of technology (PJ/year)';
FuelConsumption_TOTAL(TECHTYPE)=SUM(C,FuelConsumption_C(C,TECHTYPE));

*_______________________________________________________________________________________________________________________________________________________________________________________________________________________________________

*New Installed Capacity per country for electricity and District Heating production

Parameter Elec_Capacity(CCC,CAPACITIES,TECHTYPE) 'Installed capacity for electricity production (MW)';

Elec_Capacity(C,'New',TECHTYPE)=SUM((IA,IGE)$(ICA(C,IA) AND IGNOTETOH(IGE) AND GTECHTYPE(IGE,TECHTYPE)
$ifi %COMBTECH%==yes  AND (NOT IGCOMB2(IGE))
),VGKN.L(IA,IGE));

Elec_Capacity(C,'Existing',TECHTYPE)=SUM((IA,IGE)$(ICA(C,IA) AND IGNOTETOH(IGE) AND GTECHTYPE(IGE,TECHTYPE) AND IAGK_Y(IA,IGE)
$ifi %COMBTECH%==yes  AND (NOT IGCOMB2(IGE))
),IGKFX_Y(IA,IGE));

Elec_Capacity(C,'TOTAL',TECHTYPE)=Elec_Capacity(C,'New',TECHTYPE)+Elec_Capacity(C,'Existing',TECHTYPE);



Parameter Heat_Capacity(CCC,CAPACITIES,TECHTYPE) 'Installed capacity for heat production (MW)';

Heat_Capacity(C,'New',TECHTYPE)=SUM(IA$(ICA(C,IA) AND (NOT AINDHEAT(IA))),
SUM(IGBPR$(GTECHTYPE(IGBPR,TECHTYPE)
$ifi %COMBTECH%==yes  AND (NOT IGCOMB2(IGBPR))
),VGKN.L(IA,IGBPR)/GDATA(IGBPR,'GDCB'))
+SUM(IGEXT$(GTECHTYPE(IGEXT,TECHTYPE)
$ifi %COMBTECH%==yes  AND (NOT IGCOMB2(IGEXT))
),VGKN.L(IA,IGEXT)/GDATA(IGEXT,'GDCB'))
+SUM(IGHHNOSTO$(GTECHTYPE(IGHHNOSTO,TECHTYPE)
$ifi %COMBTECH%==yes  AND (NOT IGCOMB2(IGHHNOSTO))
),VGKN.L(IA,IGHHNOSTO ))
+SUM(IGETOH$(GTECHTYPE(IGETOH,TECHTYPE)
$ifi %COMBTECH%==yes  AND (NOT IGCOMB2(IGETOH))
),VGKN.L(IA,IGETOH)));

Heat_Capacity(C,'Existing',TECHTYPE)=SUM(IA$(ICA(C,IA) AND (NOT AINDHEAT(IA))),
SUM(IGBPR$(GTECHTYPE(IGBPR,TECHTYPE) AND IAGK_Y(IA,IGBPR)
$ifi %COMBTECH%==yes  AND (NOT IGCOMB2(IGBPR))
),IGKFX_Y(IA,IGBPR)/GDATA(IGBPR,'GDCB'))
+SUM(IGEXT$(GTECHTYPE(IGEXT,TECHTYPE) AND IAGK_Y(IA,IGEXT)
$ifi %COMBTECH%==yes  AND (NOT IGCOMB2(IGEXT))
),IGKFX_Y(IA,IGEXT)/GDATA(IGEXT,'GDCB'))
+SUM(IGHHNOSTO$(GTECHTYPE(IGHHNOSTO,TECHTYPE) AND IAGK_Y(IA,IGHHNOSTO)
$ifi %COMBTECH%==yes  AND (NOT IGCOMB2(IGHHNOSTO))
),IGKFX_Y(IA,IGHHNOSTO ))
+SUM(IGETOH$(GTECHTYPE(IGETOH,TECHTYPE) AND IAGK_Y(IA,IGETOH)
$ifi %COMBTECH%==yes  AND (NOT IGCOMB2(IGETOH))
),IGKFX_Y(IA,IGETOH)));

Heat_Capacity(C,'TOTAL',TECHTYPE)=Heat_Capacity(C,'New',TECHTYPE)+Heat_Capacity(C,'Existing',TECHTYPE);




*_______________________________________________________________________________________________________________________________________________________________________________________________________________________________________

execute_unload "MainResults.gdx" EPrice_RST, HPrice_AST, EDemand_RST, EDemand_R, Edemand_CST, Edemand_C, Hdemand_AST, EPrice_R, EPrice_CST, EPrice_C, HPrice_AS, HPrice_A, HPrice_C, EProduction_RST, ETrade_RST,
Eproduction_CST, ETrade_CST, EProduction_R, EProduction_C, ETrade_R, ETrade_C, Hproduction_AST, Hproduction_AS, Hproduction_A, Hproduction_CST, Hproduction_CS, Hproduction_C, FuelConsumption_C, FuelConsumption_TOTAL,
Elec_Capacity,Heat_Capacity,VOBJ,VGKN

$if     EXIST '../addons/_hooks/Outputgdx.inc' $INCLUDE      '../addons/_hooks/Outputgdx.inc';
$if not EXIST '../addons/_hooks/Outputgdx.inc' $INCLUDE '../../base/addons/_hooks/Outputgdx.inc';


;


*End of the output file
$offtext
