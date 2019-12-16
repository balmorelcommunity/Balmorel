******Create output file

*SET UNITS /GW,TWh,MWh,Money_per_MWh,Mmoney,kton/;
*SET PRICE_CATEGORY /AVERAGE,AVERAGE_WEIGHTED_BY_CONSUMPTION,AVERAGE_WEIGHTED_BY_PRODUCTION/;
*SET VARIABLE_CATEGORY /EXOGENOUS,ENDOGENOUS,DECOMMISSIONING/;


***** ELECTRICITY PRICES

*---HOURLY ELECTRICITY PRICE
PARAMETER EL_PRICE_YCRST(Y,C,RRR,SSS,TTT,UNITS) "Hourly Electricity Prices for each region (money/MWh)";
EL_PRICE_YCRST(Y,C,IR,S,T,'Money_per_MWh')$CCCRRR(C,IR)=OMONEY*QEEQ.M(Y,IR,S,T)/IDISCOUNTFACTOR(Y)/IWEIGHTY(Y)/IHOURSINST(S,T);

*AVERAGE ELECTRICITY PRICE
PARAMETER EL_PRICE_YCR(Y,C,RRR,PRICE_CATEGORY,UNITS) "Average Electricity Prices for each region (money/MWh)";
EL_PRICE_YCR(Y,C,IR,'AVERAGE','Money_per_MWh')$CCCRRR(C,IR)=OMONEY/IOF8760/IDISCOUNTFACTOR(Y)/IWEIGHTY(Y)*SUM((S,T),QEEQ.M(Y,IR,S,T));




*****DISTRICT HEATING PRICES

*---HOURLY DISTRICT HEATING PRICE

PARAMETER DH_PRICE_YCRAST(Y,C,RRR,AAA,SSS,TTT,UNITS) "Hourly District Heating Prices for each area (money(MWh)";
DH_PRICE_YCRAST(Y,C,IR,IA,S,T,'Money_per_MWh')$(CCCRRR(C,IR) AND RRRAAA(IR,IA) AND SUM(DHUSER, IDH_SUMST(IA,DHUSER)))=OMONEY*QHEQ.M(Y,IA,S,T)/IDISCOUNTFACTOR(Y)/IWEIGHTY(Y)/IHOURSINST(S,T);

*AVERAGE DISTRICT HEATING PRICE
PARAMETER DH_PRICE_YCRA(Y,C,RRR,AAA,PRICE_CATEGORY,UNITS) "Average District Heating Prices for each area(money/MWh)";
DH_PRICE_YCRA(Y,C,IR,IA,'AVERAGE','Money_per_MWh')$(CCCRRR(C,IR) AND RRRAAA(IR,IA) AND SUM(DHUSER, IDH_SUMST(IA,DHUSER)))= OMONEY/IOF8760/IDISCOUNTFACTOR(Y)/IWEIGHTY(Y)*SUM((S,T),QHEQ.M(Y,IA,S,T));


* ------------------------ ELECTRICITY PRODUCTION ---------------------
** ELECTRICITY PRODUCTION HOURLY
*** OTHER SECTOR
PRO_YCRAGFST(Y,C,IR,IA,IGE,FFF,S,T,'ELECTRICITY',TECH_TYPE,'MWh')$((not IGETOH(IGE)) AND CCCRRR(C,IR) and RRRAAA(IR,IA) and IAGK_HASORPOT(Y,IA,IGE) AND IGF(IGE,FFF) AND GTECH_TYPE(IGE,TECH_TYPE) AND NOT INDUSTRY_AREAS(IA))=
       VGE_T.L(Y,IA,IGE,S,T);

** ELECTRICITY PRODUCTION ANNUALLY
*** OTHER SECTOR
PRO_YCRAGF(Y,C,IR,IA,IGE,FFF,'ELECTRICITY',TECH_TYPE,'TWh')$((not IGETOH(IGE)) AND CCCRRR(C,IR) and RRRAAA(IR,IA) and IAGK_HASORPOT(Y,IA,IGE) AND IGF(IGE,FFF) AND GTECH_TYPE(IGE,TECH_TYPE) AND NOT INDUSTRY_AREAS(IA))=
       SUM((S,T),IHOURSINST(S,T)*VGE_T.L(Y,IA,IGE,S,T))/IOF1000000;

* ------------------------ END OF ELECTRICITY PRODUCTION --------------

* ------------------------ HEAT PRODUCTION ---------------------
** HEAT PRODUCTION HOURLY

PARAMETER PRO_YCRAGFST(Y,C,RRR,*,*,FFF,SSS,TTT,COMMODITY,TECH_TYPE,UNITS) "Energy Production for each year, country, region, area, technology, fuel, season, hour, commodity, technology type (MWh)" ;
*** DISTRICT HEAT
PRO_YCRAGFST(Y,C,IR,IA,IGH,FFF,S,T,'DISTRICT_HEAT',TECH_TYPE,'MWh')$(CCCRRR(C,IR) and RRRAAA(IR,IA) and IAGK_HASORPOT(Y,IA,IGH) AND IGF(IGH,FFF) AND GTECH_TYPE(IGH,TECH_TYPE) AND NOT INDUSTRY_AREAS(IA))=
       VGH_T.L(Y,IA,IGH,S,T);

*** INDHEAT
PRO_YCRAGFST(Y,C,IR,INDHEAT_AAA,INDHEAT_G,FFF,S,T,'IND_HEAT',TECH_TYPE,'MWh')$(CCCRRR(C,IR) and RRRAAA(IR,INDHEAT_AAA) and (INDHEAT_GDATA(INDHEAT_G,'GDFUEL') EQ FDATA(FFF,'FDACRONYM')) AND INDHEAT_GTECH_TYPE(INDHEAT_G,TECH_TYPE))=
      sum((INDHEAT_DHUSER,INDHEAT_GROUP),INDHEAT_VGH_T.L(Y,INDHEAT_AAA,INDHEAT_DHUSER,INDHEAT_G,INDHEAT_GROUP,S,T));

*** PROCESS HEAT
PRO_YCRAGFST(Y,C,IR,IA,IGH,FFF,S,T,'PROCESS_HEAT',TECH_TYPE,'MWh')$(CCCRRR(C,IR) and RRRAAA(IR,IA) and IAGK_HASORPOT(Y,IA,IGH) AND IGF(IGH,FFF) AND GTECH_TYPE(IGH,TECH_TYPE) AND INDUSTRY_AREAS(IA))=
       VGH_T.L(Y,IA,IGH,S,T);


** HEAT PRODUCTION ANNUAL
PARAMETER PRO_YCRAGF(Y,C,RRR,*,*,FFF,COMMODITY,TECH_TYPE,UNITS) "Annual Energy Production for each year, country, region, area, technology, fuel, commodity, technology type (TWh)";
*** DISTRICT HEAT
PRO_YCRAGF(Y,C,IR,IA,IGH,FFF,'DISTRICT_HEAT',TECH_TYPE,'TWh')$(CCCRRR(C,IR) and RRRAAA(IR,IA) and IAGK_HASORPOT(Y,IA,IGH) AND IGF(IGH,FFF) AND GTECH_TYPE(IGH,TECH_TYPE) AND NOT INDUSTRY_AREAS(IA))=
       SUM((S,T),IHOURSINST(S,T)*VGH_T.L(Y,IA,IGH,S,T))/IOF1000000;

*** INDHEAT
PRO_YCRAGF(Y,C,IR,INDHEAT_AAA,INDHEAT_G,FFF,'IND_HEAT',TECH_TYPE,'TWh')$(CCCRRR(C,IR) and RRRAAA(IR,INDHEAT_AAA) and (INDHEAT_GDATA(INDHEAT_G,'GDFUEL') EQ FDATA(FFF,'FDACRONYM')) AND INDHEAT_GTECH_TYPE(INDHEAT_G,TECH_TYPE))=
      SUM((S,T,INDHEAT_DHUSER,INDHEAT_GROUP),IHOURSINST(S,T)*INDHEAT_VGH_T.L(Y,INDHEAT_AAA,INDHEAT_DHUSER,INDHEAT_G,INDHEAT_GROUP,S,T))/IOF1000000;

*** PROCESS HEAT
PRO_YCRAGF(Y,C,IR,IA,IGH,FFF,'PROCESS_HEAT',TECH_TYPE,'TWh')$(CCCRRR(C,IR) and RRRAAA(IR,IA) and IAGK_HASORPOT(Y,IA,IGH) AND IGF(IGH,FFF) AND GTECH_TYPE(IGH,TECH_TYPE) AND INDUSTRY_AREAS(IA))=
       SUM((S,T),IHOURSINST(S,T)*VGH_T.L(Y,IA,IGH,S,T))/IOF1000000;


Parameter Hproduction_AST_Opti(Y,AAA,TECH_GROUP,SSS,TTT) 'Heat production at an area level (GJ)';
Hproduction_AST_Opti(Y,IA,TECH_GROUP,S,T)=SUM(IPROCFROM$PROCTECHTYPE(IPROCFROM,TECH_GROUP),VFLOW.L(Y,IA,IPROCFROM,'Heat_Opti_to_Bal_conv','HEATFLOW_GJ',S,T));

Parameter Hproduction_A_Opti(Y,AAA,TECH_GROUP) 'Heat production at an area level (GJ)';
Hproduction_A_Opti(Y,IA,TECH_GROUP) = SUM((S,T),Hproduction_AST_Opti(Y,IA,TECH_GROUP,S,T));


* ------------------------ END OF HEAT PRODUCTION --------------

;






















*mason
$ontext

SET ELECTRADE /Import, Export, "Net Export"/;


SET RRROFFSHORE(RRR);
RRROFFSHORE(IR)$SUM(IA,RRRAAA(IR,IA)$AAAOFFSHORE(IA))=YES;
RRROFFSHORE("DK_E")=NO;
RRROFFSHORE("DK_W")=NO;
RRROFFSHORE("DK_KF")=NO;
RRROFFSHORE("DE_KF")=NO;



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


Parameter ETrade_RST(RRR,ELECTRADE,SSS,TTT) 'Electricity trade at a regional level (MW)';

*electricity import, do not consider import from offshore regions
ETrade_RST(IR,"Import",S,T)$((NOT RETRANS(IR)) AND (NOT RINDUS(IR)))=SUM(IRE$((IXKINI_Y(IRE,IR) OR IXKN(IRE,IR) OR IXKN(IR,IRE)) AND (NOT RRROFFSHORE(IRE))), VX_T.L(IRE,IR,S,T)*(1-XLOSS(IRE,IR)));

*electricity export, do not consider export towards EV region or industrial region
ETrade_RST(IR,"Export",S,T)$(NOT RRROFFSHORE(IR))= SUM(IRI$((IXKINI_Y(IR,IRI) OR IXKN(IR,IRI) OR IXKN(IRI,IR)) AND ((NOT RETRANS(IRI)) AND (NOT RINDUS(IRI)))),VX_T.L(IR,IRI,S,T));

ETrade_RST(IR,"Net Export",S,T)=ETrade_RST(IR,"Export",S,T)-ETrade_RST(IR,"Import",S,T);


Parameter ETrade_CST(CCC,ELECTRADE,SSS,TTT) 'Electricity trade at a country level (MW)';
ETrade_CST(C,"Import",S,T)=SUM((IR,IRE)$(CCCRRR(C,IR) AND (NOT CCCRRR(C,IRE))AND (IXKINI_Y(IRE,IR) OR IXKN(IR,IRE) OR IXKN(IRE,IR)) AND (IXKINI_Y(IRE,IR) NE INF)), VX_T.L(IRE,IR,S,T)*(1-XLOSS(IRE,IR)));
ETrade_CST(C,"Export",S,T)=SUM((IR,IRI)$(CCCRRR(C,IR) AND (NOT CCCRRR(C,IRI))AND (IXKINI_Y(IR,IRI) OR IXKN(IRI,IR) OR IXKN(IR,IRI)) AND (IXKINI_Y(IR,IRI) NE INF)), VX_T.L(IR,IRI,S,T));
ETrade_CST(C,"Net Export",S,T)=ETrade_CST(C,"Export",S,T)-ETrade_CST(C,"Import",S,T);



Parameter Eproduction_C(CCC,TECH_GROUP) 'Electricity production at a country level (PJ/year)';
EProduction_C(C,TECH_GROUP)= (SUM((S,T),EProduction_CST(C,TECH_GROUP,S,T)*IHOURSINST(S,T)))*IOF0000001*IOF3P6;

Parameter ETrade_R(RRR,ELECTRADE) 'Electricity trade at a regional level (PJ/year)';
ETrade_R(IR,ELECTRADE)=(SUM((S,T),ETrade_RST(IR,ELECTRADE,S,T)*IHOURSINST(S,T)))*IOF0000001*IOF3P6;

Parameter ETrade_C(CCC,ELECTRADE) 'Electricity trade at a regional level (PJ/year)';
ETrade_C(C,ELECTRADE)=(SUM((S,T),ETrade_CST(C,ELECTRADE,S,T)*IHOURSINST(S,T)))*IOF0000001*IOF3P6;


Parameter FuelConsumption_C(CCC,TECH_GROUP)  'Fuel Consumption at a country level per type of technology (PJ/year)';
FuelConsumption_C(C,TECH_GROUP)=SUM((IA,G,S,T)$(ICA(C,IA) AND GTECH_GROUP(G,TECH_GROUP)),IHOURSINST(S,T)*(VGF_T.L(IA,G,S,T)+VGFN_T.L(IA,G,S,T)))*IOF0000001*IOF3P6
$if     EXIST '../addons/_hooks/FuelConsumption_C.inc' $INCLUDE      '../addons/_hooks/FuelConsumption_C.inc';
$if not EXIST '../addons/_hooks/FuelConsumption_C.inc' $INCLUDE '../../base/addons/_hooks/FuelConsumption_C.inc';

;

Parameter FuelConsumption_TOTAL(TECH_GROUP)  'Fuel Consumption in all the simulated countryes per type of technology (PJ/year)';
FuelConsumption_TOTAL(TECH_GROUP)=SUM(C,FuelConsumption_C(C,TECH_GROUP));

$offtext

*****************************************************************
*OptiFlow



Parameter RE_GasFuel_AST_Opti(Y,AAA,TECH_GROUP,SSS,TTT) 'RE-gas and fuels production at an area level (GJ)';
RE_GasFuel_AST_Opti(Y,IA,TECH_GROUP,S,T)=        SUM(IPROCFROM$PROCTECHTYPE(IPROCFROM,TECH_GROUP),VFLOW.L(Y,IA,IPROCFROM,'BioJet_Eff','BIOJETFLOW',S,T)$FLOWFROMTOPROC(Y,IA,IPROCFROM,'BioJet_Eff','BIOJETFLOW'))
                                            +SUM(IPROCFROM$PROCTECHTYPE(IPROCFROM,TECH_GROUP),VFLOW.L(Y,IA,IPROCFROM,'Bio_SNG_OUT','BIO_SNG_FLOW',S,T)$FLOWFROMTOPROC(Y,IA,IPROCFROM,'BIO_SNG_OUT','BIO_SNG_FLOW'))
                                            +SUM(IPROCFROM$PROCTECHTYPE(IPROCFROM,TECH_GROUP),VFLOW.L(Y,IA,IPROCFROM,'BioSyngasBuffer','BIO_SYNGAS_FLOW',S,T)$FLOWFROMTOPROC(Y,IA,IPROCFROM,'BioSyngasBuffer','BIO_SYNGAS_FLOW'))
                                            +SUM(IPROCFROM$PROCTECHTYPE(IPROCFROM,TECH_GROUP),VFLOW.L(Y,IA,IPROCFROM,'BIO_TG_GRID_OUT','BIO_TG_FLOW',S,T)$FLOWFROMTOPROC(Y,IA,IPROCFROM,'BIO_TG_GRID_OUT','BIO_TG_FLOW'))
                                            +SUM(IPROCFROM$PROCTECHTYPE(IPROCFROM,TECH_GROUP),VFLOW.L(Y,IA,IPROCFROM,'Biogas_Grid_SUM','BIOGAS_MANURE_WB_1_FLOW',S,T)$FLOWFROMTOPROC(Y,IA,IPROCFROM,'BIOGAS_GRID_SUM','BIOGAS_MANURE_WB_1_FLOW'))
                                            +SUM(IPROCFROM$PROCTECHTYPE(IPROCFROM,TECH_GROUP),VFLOW.L(Y,IA,IPROCFROM,'Biogas_Grid_SUM','BIOGAS_MIX_FLOW',S,T)$FLOWFROMTOPROC(Y,IA,IPROCFROM,'BIOGAS_GRID_SUM','BIOGAS_MIX_FLOW'))
*                                            +SUM(IPROCFROM$PROCTECHTYPE(IPROCFROM,TECH_GROUP),VFLOW.L(Y,IA,IPROCFROM,'BiogasBuffer','BIOGAS_FLOW',S,T)$FLOWFROMTOPROC(Y,IA,IPROCFROM,'BiogasBuffer','BIOGAS_FLOW'))
                                            +SUM(IPROCFROM$PROCTECHTYPE(IPROCFROM,TECH_GROUP),VFLOW.L(Y,IA,IPROCFROM,'Hydrogen_Grid_IN','HYDROGEN_FLOW',S,T)$FLOWFROMTOPROC(Y,IA,IPROCFROM,'Hydrogen_GRID_IN','HYDROGEN_FLOW'))
                                            +SUM(IPROCFROM$PROCTECHTYPE(IPROCFROM,TECH_GROUP),VFLOW.L(Y,IA,IPROCFROM,'GasBuffer','GASFLOW',S,T)$FLOWFROMTOPROC(Y,IA,IPROCFROM,'GasBuffer','GASFLOW'))
                                            +SUM(IPROCFROM$PROCTECHTYPE(IPROCFROM,TECH_GROUP),VFLOW.L(Y,IA,IPROCFROM,'Other_Gas_Proc','OTHER_GAS_FLOW',S,T)$FLOWFROMTOPROC(Y,IA,IPROCFROM,'Other_Gas_Proc','OTHER_GAS_FLOW'))
                                            +SUM(IPROCFROM$PROCTECHTYPE(IPROCFROM,TECH_GROUP),VFLOW.L(Y,IA,IPROCFROM,'Ethanol_Eff','Ethanol_FLOW',S,T)$FLOWFROMTOPROC(Y,IA,IPROCFROM,'Ethanol_Eff','Ethanol_FLOW'))
                                            +SUM(IPROCFROM$PROCTECHTYPE(IPROCFROM,TECH_GROUP),VFLOW.L(Y,IA,IPROCFROM,'Biodiesel_Eff','BIODIESELFLOW',S,T)$FLOWFROMTOPROC(Y,IA,IPROCFROM,'Biodiesel_Eff','BIODIESELFLOW'))
                                            +SUM(IPROCFROM$PROCTECHTYPE(IPROCFROM,TECH_GROUP),VFLOW.L(Y,IA,IPROCFROM,'Methanol_Eff','METHANOLFLOW',S,T)$FLOWFROMTOPROC(Y,IA,IPROCFROM,'Methanol_Eff','METHANOLFLOW'))
                                            +SUM(IPROCFROM$PROCTECHTYPE(IPROCFROM,TECH_GROUP),VFLOW.L(Y,IA,IPROCFROM,'BioGasoline_Eff','BIOGASOLINEFLOW',S,T)$FLOWFROMTOPROC(Y,IA,IPROCFROM,'BioGasoline_Eff','BIOGASOLINEFLOW'))
                                            +SUM(IPROCFROM$PROCTECHTYPE(IPROCFROM,TECH_GROUP),VFLOW.L(Y,IA,IPROCFROM,'EMethanol_Eff','EMETHANOLFLOW',S,T)$FLOWFROMTOPROC(Y,IA,IPROCFROM,'EMethanol_Eff','EMETHANOLFLOW'))
                                            +SUM(IPROCFROM$PROCTECHTYPE(IPROCFROM,TECH_GROUP),VFLOW.L(Y,IA,IPROCFROM,'Ammonia_Eff','AMMONIA_FLOW',S,T)$FLOWFROMTOPROC(Y,IA,IPROCFROM,'Ammonia_Eff','AMMONIA_FLOW'))
                                            +SUM(IPROCFROM$PROCTECHTYPE(IPROCFROM,TECH_GROUP),VFLOW.L(Y,IA,IPROCFROM,'EME_Gasoline_Eff','EME_GASOLINE_FLOW',S,T)$FLOWFROMTOPROC(Y,IA,IPROCFROM,'EME_Gasoline_Eff','EME_GASOLINE_FLOW'))
                                            +SUM(IPROCFROM$PROCTECHTYPE(IPROCFROM,TECH_GROUP),VFLOW.L(Y,IA,IPROCFROM,'EME_LPG_Eff','EME_LPG_FLOW',S,T)$FLOWFROMTOPROC(Y,IA,IPROCFROM,'EME_LPG_Eff','EME_LPG_FLOW'))
                                            +SUM(IPROCFROM$PROCTECHTYPE(IPROCFROM,TECH_GROUP),VFLOW.L(Y,IA,IPROCFROM,'E_FT_Diesel_Eff','E_FT_DIESEL_FLOW',S,T)$FLOWFROMTOPROC(Y,IA,IPROCFROM,'E_FT_Diesel_Eff','E_FT_DIESEL_FLOW'))
                                            +SUM(IPROCFROM$PROCTECHTYPE(IPROCFROM,TECH_GROUP),VFLOW.L(Y,IA,IPROCFROM,'EME_Jet_Eff','EME_JET_FLOW',S,T)$FLOWFROMTOPROC(Y,IA,IPROCFROM,'EME_Jet_Eff','EME_JET_FLOW'))
                                            +SUM(IPROCFROM$PROCTECHTYPE(IPROCFROM,TECH_GROUP),VFLOW.L(Y,IA,IPROCFROM,'E_FT_Jet_Eff','E_FT_JET_FLOW',S,T)$FLOWFROMTOPROC(Y,IA,IPROCFROM,'E_FT_Jet_Eff','E_FT_JET_FLOW'))
                                            +SUM(IPROCFROM$PROCTECHTYPE(IPROCFROM,TECH_GROUP),VFLOW.L(Y,IA,IPROCFROM,'HTL_Eff','HTLFLOW',S,T)$FLOWFROMTOPROC(Y,IA,IPROCFROM,'HTL_Eff','HTLFLOW'))
;


*******************

*RE-fuel

Parameter RE_Fuel_AST_Opti(Y,AAA,TECH_GROUP,SSS,TTT) 'Final RE-fuel production at an area level (GJ)';
RE_Fuel_AST_Opti(Y,IA,TECH_GROUP,S,T)=           SUM(IPROCFROM$PROCTECHTYPE(IPROCFROM,TECH_GROUP),VFLOW.L(Y,IA,IPROCFROM,'BioJet_Eff','BIOJETFLOW',S,T)$FLOWFROMTOPROC(Y,IA,IPROCFROM,'BioJet_Eff','BIOJETFLOW'))
                                            +SUM(IPROCFROM$PROCTECHTYPE(IPROCFROM,TECH_GROUP),VFLOW.L(Y,IA,IPROCFROM,'Ethanol_Eff','Ethanol_FLOW',S,T)$FLOWFROMTOPROC(Y,IA,IPROCFROM,'Ethanol_Eff','Ethanol_FLOW'))
                                            +SUM(IPROCFROM$PROCTECHTYPE(IPROCFROM,TECH_GROUP),VFLOW.L(Y,IA,IPROCFROM,'Biodiesel_Eff','BIODIESELFLOW',S,T)$FLOWFROMTOPROC(Y,IA,IPROCFROM,'Biodiesel_Eff','BIODIESELFLOW'))
                                            +SUM(IPROCFROM$PROCTECHTYPE(IPROCFROM,TECH_GROUP),VFLOW.L(Y,IA,IPROCFROM,'Methanol_Eff','METHANOLFLOW',S,T)$FLOWFROMTOPROC(Y,IA,IPROCFROM,'Methanol_Eff','METHANOLFLOW'))
                                            +SUM(IPROCFROM$PROCTECHTYPE(IPROCFROM,TECH_GROUP),VFLOW.L(Y,IA,IPROCFROM,'BioGasoline_Eff','BIOGASOLINEFLOW',S,T)$FLOWFROMTOPROC(Y,IA,IPROCFROM,'BioGasoline_Eff','BIOGASOLINEFLOW'))
                                            +SUM(IPROCFROM$PROCTECHTYPE(IPROCFROM,TECH_GROUP),VFLOW.L(Y,IA,IPROCFROM,'EMethanol_Eff','EMETHANOLFLOW',S,T)$FLOWFROMTOPROC(Y,IA,IPROCFROM,'EMethanol_Eff','EMETHANOLFLOW'))
                                            +SUM(IPROCFROM$PROCTECHTYPE(IPROCFROM,TECH_GROUP),VFLOW.L(Y,IA,IPROCFROM,'Ammonia_Eff','AMMONIA_FLOW',S,T)$FLOWFROMTOPROC(Y,IA,IPROCFROM,'Ammonia_Eff','AMMONIA_FLOW'))
                                            +SUM(IPROCFROM$PROCTECHTYPE(IPROCFROM,TECH_GROUP),VFLOW.L(Y,IA,IPROCFROM,'EME_Gasoline_Eff','EME_GASOLINE_FLOW',S,T)$FLOWFROMTOPROC(Y,IA,IPROCFROM,'EME_Gasoline_Eff','EME_GASOLINE_FLOW'))
                                            +SUM(IPROCFROM$PROCTECHTYPE(IPROCFROM,TECH_GROUP),VFLOW.L(Y,IA,IPROCFROM,'EME_LPG_Eff','EME_LPG_FLOW',S,T)$FLOWFROMTOPROC(Y,IA,IPROCFROM,'EME_LPG_Eff','EME_LPG_FLOW'))
                                            +SUM(IPROCFROM$PROCTECHTYPE(IPROCFROM,TECH_GROUP),VFLOW.L(Y,IA,IPROCFROM,'E_FT_Diesel_Eff','E_FT_DIESEL_FLOW',S,T)$FLOWFROMTOPROC(Y,IA,IPROCFROM,'E_FT_Diesel_Eff','E_FT_DIESEL_FLOW'))
                                            +SUM(IPROCFROM$PROCTECHTYPE(IPROCFROM,TECH_GROUP),VFLOW.L(Y,IA,IPROCFROM,'EME_Jet_Eff','EME_JET_FLOW',S,T)$FLOWFROMTOPROC(Y,IA,IPROCFROM,'EME_Jet_Eff','EME_JET_FLOW'))
                                            +SUM(IPROCFROM$PROCTECHTYPE(IPROCFROM,TECH_GROUP),VFLOW.L(Y,IA,IPROCFROM,'E_FT_Jet_Eff','E_FT_JET_FLOW',S,T)$FLOWFROMTOPROC(Y,IA,IPROCFROM,'E_FT_Jet_Eff','E_FT_JET_FLOW'))
                                            +SUM(IPROCFROM$PROCTECHTYPE(IPROCFROM,TECH_GROUP),VFLOW.L(Y,IA,IPROCFROM,'HTL_Eff','HTLFLOW',S,T)$FLOWFROMTOPROC(Y,IA,IPROCFROM,'HTL_Eff','HTLFLOW'))
*
*
                                            +SUM(IPROCFROM$PROCTECHTYPE(IPROCFROM,TECH_GROUP),VFLOW.L(Y,IA,IPROCFROM,'Demand','SumDemand',S,T)$FLOWFROMTOPROC(Y,IA,IPROCFROM,'Demand','SumDemand'))
;

Parameter RE_Fuel_AST_Opti_A(Y,AAA,TECH_GROUP) 'Final RE-fuel production at an area level per year (PJ/year)';
RE_Fuel_AST_Opti_A(Y,IA,TECH_GROUP)=SUM((S,T),RE_Fuel_AST_Opti(Y,IA,TECH_GROUP,S,T)*IHOURSINST(S,T))*IOF0000001;

Parameter RE_Fuel_AST_Opti_C(Y,CCC,TECH_GROUP) 'RE-fuel production at a country level per year (PJ/year)';
RE_Fuel_AST_Opti_C(Y,C,TECH_GROUP)=SUM(IA$ICA(C,IA),RE_Fuel_AST_Opti_A(Y,IA,TECH_GROUP));


*******************
*RE-gas
Parameter RE_Gas_AST_Opti(Y,AAA,TECH_GROUP,SSS,TTT) 'RE-gas production at an area level (GJ)';
RE_Gas_AST_Opti(Y,IA,TECH_GROUP,S,T)=            SUM(IPROCFROM$PROCTECHTYPE(IPROCFROM,TECH_GROUP),VFLOW.L(Y,IA,IPROCFROM,'GasBuffer','GASFLOW',S,T)$FLOWFROMTOPROC(Y,IA,IPROCFROM,'GasBuffer','GASFLOW'))
*                                            +SUM(IPROCFROM$PROCTECHTYPE(IPROCFROM,TECH_GROUP),VFLOW.L(Y,IA,IPROCFROM,'Biogas_Grid_SUM','BIOGAS_MANURE_WB_1_FLOW',S,T)$FLOWFROMTOPROC(Y,IA,IPROCFROM,'BIOGAS_GRID_SUM','BIOGAS_MANURE_WB_1_FLOW'))
                                            +SUM(IPROCFROM$PROCTECHTYPE(IPROCFROM,TECH_GROUP),VFLOW.L(Y,IA,IPROCFROM,'Biogas_Grid_SUM','BIOGAS_MIX_FLOW',S,T)$FLOWFROMTOPROC(Y,IA,IPROCFROM,'BIOGAS_GRID_SUM','BIOGAS_MIX_FLOW'))
*                                            +SUM(IPROCFROM$PROCTECHTYPE(IPROCFROM,TECH_GROUP),VFLOW.L(Y,IA,IPROCFROM,'BiogasBuffer','BIOGAS_FLOW',S,T)$FLOWFROMTOPROC(Y,IA,IPROCFROM,'BiogasBuffer','BIOGAS_FLOW'))
                                            +SUM(IPROCFROM$PROCTECHTYPE(IPROCFROM,TECH_GROUP),VFLOW.L(Y,IA,IPROCFROM,'Hydrogen_Grid_IN','HYDROGEN_FLOW',S,T)$FLOWFROMTOPROC(Y,IA,IPROCFROM,'Hydrogen_GRID_IN','HYDROGEN_FLOW'))
                                            +SUM(IPROCFROM$PROCTECHTYPE(IPROCFROM,TECH_GROUP),VFLOW.L(Y,IA,IPROCFROM,'Bio_SNG_OUT','BIO_SNG_FLOW',S,T)$FLOWFROMTOPROC(Y,IA,IPROCFROM,'BIO_SNG_OUT','BIO_SNG_FLOW'))
                                            +SUM(IPROCFROM$PROCTECHTYPE(IPROCFROM,TECH_GROUP),VFLOW.L(Y,IA,IPROCFROM,'BioSyngasBuffer','BIO_SYNGAS_FLOW',S,T)$FLOWFROMTOPROC(Y,IA,IPROCFROM,'BioSyngasBuffer','BIO_SYNGAS_FLOW'))
                                            +SUM(IPROCFROM$PROCTECHTYPE(IPROCFROM,TECH_GROUP),VFLOW.L(Y,IA,IPROCFROM,'Other_Gas_Proc','OTHER_GAS_FLOW',S,T)$FLOWFROMTOPROC(Y,IA,IPROCFROM,'Other_Gas_Proc','OTHER_GAS_FLOW'))


;


Parameter RE_Gas_AST_Opti_A(Y,AAA,TECH_GROUP) 'Final RE-Gas production at an area level per year (PJ/year)';
RE_Gas_AST_Opti_A(Y,IA,TECH_GROUP)=SUM((S,T),RE_Gas_AST_Opti(Y,IA,TECH_GROUP,S,T)*IHOURSINST(S,T))*IOF0000001;

Parameter RE_Gas_AST_Opti_C(Y,CCC,TECH_GROUP) 'RE-gas production at a country level per year (PJ/year)';
RE_Gas_AST_Opti_C(Y,C,TECH_GROUP)=SUM(IA$ICA(C,IA),RE_Gas_AST_Opti_A(Y,IA,TECH_GROUP));



*******************
*Resources used


Parameter Resource_use_AST_Opti(Y,AAA,TECH_GROUP,SSS,TTT) 'Resource use for RE-gas and fuel production at an area level (GJ)';
Resource_use_AST_Opti(Y,IA,TECH_GROUP,S,T)=      SUM(IPROCFROM$PROCTECHTYPE(IPROCFROM,TECH_GROUP),VFLOW.L(Y,IA,IPROCFROM,'Wood','WOOD_GEN_FLOW',S,T)$FLOWFROMTOPROC(Y,IA,IPROCFROM,'Wood','WOOD_GEN_FLOW'))
                                            +SUM(IPROCFROM$PROCTECHTYPE(IPROCFROM,TECH_GROUP),VFLOW.L(Y,IA,IPROCFROM,'Straw','STRAW_GEN_FLOW',S,T)$FLOWFROMTOPROC(Y,IA,IPROCFROM,'Straw','STRAW_GEN_FLOW'))
                                            +SUM(IPROCFROM$PROCTECHTYPE(IPROCFROM,TECH_GROUP),VFLOW.L(Y,IA,IPROCFROM,'Muni_Waste','MUNI_WASTE_GEN_FLOW',S,T)$FLOWFROMTOPROC(Y,IA,IPROCFROM,'Muni_Waste','MUNI_WASTE_GEN_FLOW'))
                                            +SUM(IPROCFROM$PROCTECHTYPE(IPROCFROM,TECH_GROUP),VFLOW.L(Y,IA,IPROCFROM,'Wood_Pellets','WOOD_PELLETS_GEN_FLOW',S,T)$FLOWFROMTOPROC(Y,IA,IPROCFROM,'Wood_Pellets','WOOD_PELLETS_GEN_FLOW'))
                                            +SUM(IPROCFROM$PROCTECHTYPE(IPROCFROM,TECH_GROUP),VFLOW.L(Y,IA,IPROCFROM,'Manure','MANURE_GEN_FLOW',S,T)$FLOWFROMTOPROC(Y,IA,IPROCFROM,'Manure','MANURE_GEN_FLOW'))
                                            +SUM(IPROCFROM$PROCTECHTYPE(IPROCFROM,TECH_GROUP),VFLOW.L(Y,IA,IPROCFROM,'CO2_PH','CO2_SOURCE_FLOW_PH',S,T)$FLOWFROMTOPROC(Y,IA,IPROCFROM,'CO2_PH','CO2_SOURCE_FLOW_PH'))
                                            +SUM(IPROCFROM$PROCTECHTYPE(IPROCFROM,TECH_GROUP),VFLOW.L(Y,IA,IPROCFROM,'CO2_IND','CO2_SOURCE_FLOW_IND',S,T)$FLOWFROMTOPROC(Y,IA,IPROCFROM,'CO2_IND','CO2_SOURCE_FLOW_IND'))
                                            +SUM(IPROCFROM$PROCTECHTYPE(IPROCFROM,TECH_GROUP),VFLOW.L(Y,IA,IPROCFROM,'CO2_DAC','CO2_SOURCE_FLOW_DAC',S,T)$FLOWFROMTOPROC(Y,IA,IPROCFROM,'CO2_DAC','CO2_SOURCE_FLOW_DAC'))
                                            +SUM(IPROCFROM$PROCTECHTYPE(IPROCFROM,TECH_GROUP),VFLOW.L(Y,IA,IPROCFROM,'CO2_Bio','CO2_SOURCE_FLOW_BIO',S,T)$FLOWFROMTOPROC(Y,IA,IPROCFROM,'CO2_Bio','CO2_SOURCE_FLOW_BIO'))
*
*
                                            +SUM(IPROCFROM$PROCTECHTYPE(IPROCFROM,TECH_GROUP),VFLOW.L(Y,IA,IPROCFROM,'ResA','ResProA',S,T)$FLOWFROMTOPROC(Y,IA,IPROCFROM,'ResA','ResProA'))
                                            +SUM(IPROCFROM$PROCTECHTYPE(IPROCFROM,TECH_GROUP),VFLOW.L(Y,IA,IPROCFROM,'ResB','ResProB',S,T)$FLOWFROMTOPROC(Y,IA,IPROCFROM,'ResB','ResProB'))
                                            +SUM(IPROCFROM$PROCTECHTYPE(IPROCFROM,TECH_GROUP),VFLOW.L(Y,IA,IPROCFROM,'ResC','ResSumC',S,T)$FLOWFROMTOPROC(Y,IA,IPROCFROM,'ResC','ResSumC'))
                                            +SUM(IPROCFROM$PROCTECHTYPE(IPROCFROM,TECH_GROUP),VFLOW.L(Y,IA,IPROCFROM,'ResD','ResProD',S,T)$FLOWFROMTOPROC(Y,IA,IPROCFROM,'ResD','ResProD'))

;

Parameter Resource_use_Opti_A(Y,AAA,TECH_GROUP) 'Resource_use at an area level per year (PJ/year)';
Resource_use_Opti_A(Y,IA,TECH_GROUP)=SUM((S,T),Resource_use_AST_Opti(Y,IA,TECH_GROUP,S,T)*IHOURSINSTWWT(S,T))*IOF0000001;

Parameter Resource_use_Opti_C(Y,CCC,TECH_GROUP) 'Resource_use at a country level per year (PJ/year)';
Resource_use_Opti_C(Y,C,TECH_GROUP)=SUM(IA$ICA(C,IA),Resource_use_Opti_A(Y,IA,TECH_GROUP));





*FLOWS
Parameter VFLOW_Opti_A(Y,AAA,IPROCFROM,IPROCTO,FLOW)   'FLOWS at an area level per year (PJ/year)';
VFLOW_Opti_A(Y,IA,IPROCFROM,IPROCTO,FLOW)=   SUM((S,T),VFLOW.L(Y,IA,IPROCFROM,IPROCTO,FLOW,S,T)*IHOURSINST(S,T))*IOF0000001;


Parameter VFLOW_Opti_C(Y,CCC,IPROCFROM,IPROCTO,FLOW) 'FLOWS at a country level per year (PJ/year)';
VFLOW_Opti_C(Y,C,IPROCFROM,IPROCTO,FLOW)=SUM(IA$ICA(C,IA),VFLOW_Opti_A(Y,IA,IPROCFROM,IPROCTO,FLOW));


*FLOWS source
Parameter VFLOWSOURCE_Opti_A(Y,AAA,PROCSOURCE,FLOW)   'Source FLOWS at an area level per year (ton/year)';
VFLOWSOURCE_Opti_A(Y,IA,PROCSOURCE,FLOW)=   SUM((S,T),VFLOWSOURCE.L(Y,IA,PROCSOURCE,FLOW,S,T)*IHOURSINSTWWT(S,T));


Parameter VFLOWSOURCE_Opti_C(Y,CCC,PROCSOURCE,FLOW) 'Source FLOWS at a country level per year (ton/year)';
VFLOWSOURCE_Opti_C(Y,C,PROCSOURCE,FLOW)=SUM(IA$ICA(C,IA),VFLOWSOURCE_Opti_A(Y,IA,PROCSOURCE,FLOW));


*FLOWS Buffer
Parameter VFLOWBUFFER_Opti_A(Y,AAA,PROCBUFFER,FLOW)   'BUFFER FLOWS at an area level per year (u/year)';
VFLOWBUFFER_Opti_A(Y,IA,PROCBUFFER,FLOW)=   SUM((S,T),VFLOWBUFFER.L(Y,IA,PROCBUFFER,FLOW,S,T)*IHOURSINST(S,T));


Parameter VFLOWBUFFER_Opti_C(Y,CCC,PROCBUFFER,FLOW) 'BUFFER FLOWS at a country level per year (u/year)';
VFLOWBUFFER_Opti_C(Y,C,PROCBUFFER,FLOW)=SUM(IA$ICA(C,IA),VFLOWBUFFER_Opti_A(Y,IA,PROCBUFFER,FLOW));


*FLOWS Storage
Parameter VFLOWSTORAGE_Opti_A(Y,AAA,PROC,FLOW)   'Storage FLOWS at an area level per year (u/year)';
VFLOWSTORAGE_Opti_A(Y,IA,PROCSTORAGE,FLOW)=   SUM((S,T),VSTORAGEVOL.L(Y,IA,PROCSTORAGE,FLOW,S,T)*IHOURSINST(S,T));

Parameter VFLOWSTORAGE_Opti_C(Y,CCC,PROC,FLOW)   'Storage FLOWS at an area level per year (u/year)';
VFLOWSTORAGE_Opti_C(Y,C,PROCSTORAGE,FLOW)=    SUM(IA$ICA(C,IA),VFLOWSTORAGE_Opti_A(Y,IA,PROCSTORAGE,FLOW));



* RE-fuel prices
Parameter RE_fuel_Price(Y,C,PROC,FLOW)'RE-fuel price (€ 2015/GJ)';
RE_fuel_Price(Y,C,PROC,FLOW)=QMINFLOW_C.M(Y,C,PROC,FLOW) / IWEIGHTY(Y);



*_______________________________________________________________________________________________________________________________________________________________________________________________________________________________________
*----Original
$ontext
execute_unload "Optiflow_MainResults.gdx" EPrice_RST, HPrice_AST, EDemand_RST, EDemand_R, Edemand_CST, Edemand_C, Hdemand_AST, EPrice_R, EPrice_CST, EPrice_C, HPrice_AS, HPrice_A, HPrice_C, EProduction_RST, ETrade_RST,
Eproduction_CST, ETrade_CST, EProduction_R, EProduction_C, ETrade_R, ETrade_C, Hproduction_AST, Hproduction_AS, Hproduction_A, Hproduction_CST, Hproduction_CS, Hproduction_C, FuelConsumption_C, FuelConsumption_TOTAL,
Elec_Capacity,Heat_Capacity,VOBJ,VGKN,VX_T,VXKN,
VFLOW,VFLOWTRANS,VPROCKAPNEW,Hproduction_AST_Opti,
RE_GasFuel_AST_Opti,RE_Fuel_AST_Opti_A,RE_Fuel_AST_Opti_C,RE_Gas_AST_Opti,RE_Gas_AST_Opti_A,RE_Gas_AST_Opti_C,
Resource_use_Opti_C,Resource_use_AST_Opti,Resource_use_Opti_A,
VFLOW_Opti_A,VFLOW_Opti_C,VFLOWSOURCE_Opti_A,VFLOWSOURCE_Opti_C,VFLOWTRANS_Opti_A,VFLOWBUFFER_Opti_C
RE_fuel_Price
$offtext

execute_unload "Optiflow_MainResults.gdx" VOBJ,VGKN,VX_T,VXKN,
VFLOW,VFLOWTRANS,VPROCKAPNEW,
RE_GasFuel_AST_Opti,RE_Fuel_AST_Opti_A,RE_Fuel_AST_Opti_C,RE_Gas_AST_Opti,RE_Gas_AST_Opti_A,RE_Gas_AST_Opti_C,
Resource_use_Opti_C,Resource_use_AST_Opti,Resource_use_Opti_A,
VFLOW_Opti_A,VFLOW_Opti_C,VFLOWSOURCE_Opti_A,VFLOWSOURCE_Opti_C,VFLOWBUFFER_Opti_C
RE_fuel_Price
EL_PRICE_YCRST, EL_PRICE_YCR
DH_PRICE_YCRAST, DH_PRICE_YCRA
PRO_YCRAGFST, PRO_YCRAGF
Hproduction_AST_Opti, Hproduction_A_Opti
VFLOWSTORAGE_Opti_A,VFLOWSTORAGE_Opti_C
*MASON

$ONTEXT
$if     EXIST '../addons/_hooks/Outputgdx.inc' $INCLUDE      '../addons/_hooks/Outputgdx.inc';
$if not EXIST '../addons/_hooks/Outputgdx.inc' $INCLUDE '../../base/addons/_hooks/Outputgdx.inc';
$OFFTEXT

;


*End of the output file
