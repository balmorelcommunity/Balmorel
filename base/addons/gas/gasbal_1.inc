* File: bal_1.out

* Modified last time: 29-05-2002 by (rus), 2003.08.07 (hrv), 16-02-2004 (ld), 20060328(hr)

* This file will print a table containing a energy balance for each country




* -----------------------------------------------------------------------------

PUT bal_1;

* First print file headings:

if ((bal_1.pw LT 32000),
bal_1.pw = 32000;
PUT "Version:              " SYSTEM.TITLE /;
PUT "File name:            bal_1.out" /;
PUT "Time-stamp:          '" SYSTEM.DATE " " SYSTEM.TIME "'" /;
PUT "Case-identification: '" OCASEID.TS "'" //;


PUT "Energy balance" //;
PUT "Units: GWh" //;

);

* End of file headings.

* ------------------------------------------------------------------------------------
* If scenarios (i.e., more than base case) print scenario heading:
IF((CARD(SCENARIO) GT 1),
PUT /"*==============================================================================="/;
PUT "*       "   SCENARIO.TL "      " SCENARIO.TE(SCENARIO) /;
PUT "*==============================================================================="//;
);
* End of scenario heading
* ------------------------------------------------------------------------------------

bal_1.LJ = 1;
PUT "Electricity balance for "PUT Y.TL:4:0; PUT "                          ;" ; LOOP(C, PUT C.TL:12 PUT ";";) ;PUT /;
bal_1.LJ = 2;

PUT "Total electricity generation (excl. heat pumps)  ;" ; LOOP(C, PUT ( EZGqCY(C)*IOF0001):12:0 ; PUT ";";); PUT /;
PUT " - nuclear                                       ;" ; LOOP(C, PUT ( SUM((IA,IGNUC,S,T)$((IAGK_Y(IA,IGNUC) or AGKN(IA,IGNUC)) and ICA(C,IA)),(VGE_T.l(IA,IGNUC,S,T)+VGEN_T.l(IA,IGNUC,S,T))*IHOURSINST(S,T))*IOF0001):12:0 ; PUT ";";); PUT /;
PUT " - natural gas                                   ;" ; LOOP(C, PUT ( SUM((IA,IGE,S,T)$((IAGK_Y(IA,IGE) or AGKN(IA,IGE)) and ICA(C,IA) and GDATA(IGE,'GDFUEL')=2),(VGE_T.l(IA,IGE,S,T)+VGEN_T.l(IA,IGE,S,T))*IHOURSINST(S,T))*IOF0001):12:0 ; PUT ";";); PUT /;
PUT " - other thermal                                 ;" ; LOOP(C, PUT ( SUM((IA,IGE,S,T)$((IAGK_Y(IA,IGE) or AGKN(IA,IGE)) and ICA(C,IA) and not (GDATA(IGE,'GDTYPE')=5) and not (GDATA(IGE,'GDFUEL')=2) and not IGWND(IGE) and not IGHYRR(IGE) and not IGHYRS(IGE) and not IGNUC(IGE)),(VGE_T.l(IA,IGE,S,T)+VGEN_T.l(IA,IGE,S,T))*IHOURSINST(S,T))*IOF0001):12:0 ; PUT ";";); PUT /;
PUT " - hydro                                         ;" ; LOOP(C, PUT ( SUM((IA,G,S,T)$((IAGK_Y(IA,G) or AGKN(IA,G)) and (IGHYRR(G) or IGHYRS(G)) and ICA(C,IA)),(VGE_T.l(IA,G,S,T)+VGEN_T.l(IA,G,S,T))*IHOURSINST(S,T))*IOF0001):12:0 ; PUT ";";); PUT /;
PUT " - wind                                          ;" ; LOOP(C, PUT ( SUM((IA,IGWND,S,T)$((IAGK_Y(IA,IGWND) or AGKN(IA,IGWND)) and ICA(C,IA)),(VGE_T.l(IA,IGWND,S,T)+VGEN_T.l(IA,IGWND,S,T))*IHOURSINST(S,T))*IOF0001):12:0 ; PUT ";";); PUT /;
PUT " (hereof CHP)                                    ;" ; LOOP(C, PUT ( SUM((IA,G,S,T)$((IAGK_Y(IA,G) or AGKN(IA,G)) and (IGEXT(G) or IGBPR(G)) and ICA(C,IA)),(VGE_T.l(IA,G,S,T)+VGEN_T.l(IA,G,S,T))*IHOURSINST(S,T))*IOF0001):12:0 ; PUT ";";); PUT /;
PUT "Consumption for heat pumps                       ;" ; LOOP(C, PUT (-EZG13qCY(C)*IOF0001):12:0 ; PUT ";";)PUT /;       /*sarah*/
PUT "Net import from other Nordic countries           ;" ; LOOP(C, PUT ( SUM((IRE,S,T)$CCCRRR(C,IRE), SUM(IRI$(not CCCRRR(C,IRI)), (VX_T.l(IRI,IRE,S,T)-VX_T.l(IRE,IRI,S,T))*IHOURSINST(S,T)))*IOF0001 ):12:0 ; PUT ";";)PUT /;
PUT "Net import from other countries                  ;" ; LOOP(C, PUT ( EX3qCY(C)*IOF0001):12:0 ; PUT ";";)PUT /;
PUT "Transmission loss                                ;" ; LOOP(C, PUT ( EXLqCY(C)*IOF0001):12:0 ; PUT ";";)PUT /;
PUT "Distribution loss                                ;" ; LOOP(C, PUT ( ELqCY(C)*IOF0001):12:0 ; PUT ";";)PUT /;
PUT "Electricity demand                               ;" ; LOOP(C, PUT ( EDqCY(C)*IOF0001):12:0 ; PUT ";";); PUT //;


bal_1.LJ = 1;
PUT "Natural gas balance for "PUT Y.TL:4:0; PUT "                          ;" ; LOOP(C, PUT C.TL:12 PUT ";";) ;PUT /;
bal_1.LJ = 2;

PUT "Total endogenous gas production                  ;" ; LOOP(C, PUT ( 0+IOF0001*SUM((S,T), VSUP.l('Nybro',s,t)*IHOURSINST(S,T))$SAMEAS(C,'Denmark')    ):12:0 ; PUT ";";); PUT /;
PUT "Consumption of natural gas                       ;" ; LOOP(C, PUT ( IOF0001*SUM((IA,S,T), VGUD.l(IA,s,t)*IHOURSINST(S,T))$SAMEAS(C,'Denmark')+IOF0001*SUM((TRANSIT,S,T), VTRANSIT.l(TRANSIT,s,t)*IHOURSINST(S,T))$SAMEAS(C,'Sweden')    ):12:0 ; PUT ";";); PUT /;
PUT " - for electricity and district heating          ;" ; LOOP(C, PUT ( IOF0001*SUM((IA,S,T)$ICA(C,IA),
          IHOURSINST(S,T)*sum(IGE$(IAGKN(IA,IGE) and GDATA(IGE,'GDFUEL') EQ 2), VGEN_T.l(IA,IGE,S,T)/(GDATA(IGE,'GDFE')* (1-GEFFDERATE(IGE,IA))) )
         +IHOURSINST(S,T)*sum(IGH$(IAGKN(IA,IGH) and GDATA(IGH,'GDFUEL') EQ 2), GDATA(IGH,'GDCV')*VGHN_T.l(IA,IGH,S,T)/(GDATA(IGH,'GDFE')* (1-GEFFDERATE(IGH,IA))) )
         +IHOURSINST(S,T)*sum(IGE$(IAGK_Y(IA,IGE) and GDATA(IGE,'GDFUEL') EQ 2),VGE_T.l(IA,IGE,S,T)/(GDATA(IGE,'GDFE')* (1-GEFFDERATE(IGE,IA))) )
         +IHOURSINST(S,T)*sum(IGH$(IAGK_Y(IA,IGH) and GDATA(IGH,'GDFUEL') EQ 2),GDATA(IGH,'GDCV')*VGH_T.l(IA,IGH,S,T) /(GDATA(IGH,'GDFE')* (1-GEFFDERATE(IGH,IA))) ) )  ):12:0 ; PUT ";";); PUT /;
PUT " - other consumption                             ;" ; LOOP(C, PUT ( IOF0001*SUM((IA,S,T)$ICA(C,IA), (IDGRES_Y(IA,S,T)+IDGOTH_Y(IA,S,T))*IHOURSINST(S,T)) ):12:0 ; PUT ";";); PUT /;
PUT "Exports of natural gas                           ;" ; LOOP(C, PUT ( 0+IOF0001*SUM((SOURCE,S,T), VEXP.l(SOURCE,S)*IHOURSINST(S,T))$SAMEAS(C,'Denmark')+IOF0001*SUM((TRANSIT,S,T), VTRANSIT.l(TRANSIT,S,T)*IHOURSINST(S,T))$SAMEAS(C,'Denmark')    ):12:0 ; PUT ";";); PUT /;
PUT "Imports of natural gas                           ;" ; LOOP(C, PUT ( 0+IOF0001*SUM((SOURCE,S,T)$(not SAMEAS(SOURCE,'Nybro')), VSUP.l(SOURCE,S,T)*IHOURSINST(S,T))$SAMEAS(C,'Denmark')+IOF0001*SUM((TRANSIT,S,T), VTRANSIT.l(TRANSIT,S,T)*IHOURSINST(S,T))$SAMEAS(C,'Sweden')    ):12:0 ; PUT ";";); PUT /;

PUT /;

bal_1.LJ = 1;
PUT "District heating balance for "PUT Y.TL:4:0; PUT "                          ;" ; LOOP(C, PUT C.TL:12 PUT ";";) ;PUT /;
bal_1.LJ = 2;

PUT "Total heat generation                            ;" ; LOOP(C, PUT ( HZGqCY(C)*IOF0001):12:0 ; PUT ";";); PUT /;
PUT " - natural gas                                   ;" ; LOOP(C, PUT ( SUM((IA,IGH,S,T)$((IAGK_Y(IA,IGH) or AGKN(IA,IGH)) and ICA(C,IA) and (GDATA(IGH,'GDFUEL')=2)),(VGH_T.l(IA,IGH,S,T)+VGHN_T.l(IA,IGH,S,T))*IHOURSINST(S,T))*IOF0001):12:0 ; PUT ";";); PUT /;
PUT " - other                                         ;" ; LOOP(C, PUT ( SUM((IA,IGH,S,T)$((IAGK_Y(IA,IGH) or AGKN(IA,IGH)) and ICA(C,IA) and not (GDATA(IGH,'GDFUEL')=2) and not (GDATA(IGH,'GDTYPE')=6)),(VGH_T.l(IA,IGH,S,T)+VGHN_T.l(IA,IGH,S,T))*IHOURSINST(S,T))*IOF0001):12:0 ; PUT ";";); PUT /;
PUT "Distribution loss                                ;" ; LOOP(C, PUT ( HLqCY(C)*IOF0001):12:0 ; PUT ";";)PUT /;
PUT "Heat demand                                      ;" ; LOOP(C, PUT ( HDqCY(C)*IOF0001):12:0 ; PUT ";";); PUT //;



*-----------------------------------
* Investments:
*-----------------------------------

$ifi not %BB2%==yes $goto BAL1_INVEST_END


PUT "Investments" //;
PUT "Units:  Mio EURO6" //;



* End of file headings.

* ------------------------------------------------------------------------------------
* If scenarios (i.e., more than base case) print scenario heading:
IF((CARD(SCENARIO) GT 1),
PUT /"*==============================================================================="/;
PUT "*       "   SCENARIO.TL "      " SCENARIO.TE(SCENARIO) /;
PUT "*==============================================================================="//;
);
* End of scenario heading
* ------------------------------------------------------------------------------------

bal_1.LJ = 1;
PUT "Electricity generation and infrastructure MW el "PUT Y.TL:4:0; PUT "  ;" ; LOOP(C, PUT C.TL:12 PUT ";";) ;PUT /;
bal_1.LJ = 2;

PUT "Total electricity generation (excl. heat pumps)  ;" ; LOOP(C, PUT ( SUM((IA,IGE)$((not IGETOH(IGE)) and IAGKN(IA,IGE) and ICA(C,IA)), VGKN.l(IA,IGE))):12:0 ;PUT ";"; ); PUT /;
PUT " - nuclear                                       ;" ; LOOP(C, PUT ( SUM((IA,IGNUC)$(IAGKN(IA,IGNUC) and ICA(C,IA)),VGKN.l(IA,IGNUC))):12:0 ; PUT ";";); PUT /;
PUT " - natural gas                                   ;" ; LOOP(C, PUT ( SUM((IA,IGE)$(IAGKN(IA,IGE) and ICA(C,IA) and GDATA(IGE,'GDFUEL')=2),VGKN.l(IA,IGE))):12:0 ; PUT ";";); PUT /;
PUT " - other thermal                                 ;" ; LOOP(C, PUT ( SUM((IA,IGE)$(IAGKN(IA,IGE) and ICA(C,IA) and not (GDATA(IGE,'GDTYPE')=5) and not (GDATA(IGE,'GDFUEL')=2) and not IGWND(IGE) and not IGHYRR(IGE) and not IGHYRS(IGE) and not IGNUC(IGE)),VGKN.l(IA,IGE))):12:0 ; PUT ";";); PUT /;
PUT " - hydro                                         ;" ; LOOP(C, PUT ( SUM((IA,G)$(IAGKN(IA,G) and (IGHYRR(G) or IGHYRS(G)) and ICA(C,IA)),VGKN.l(IA,G))):12:0 ; PUT ";";); PUT /;
PUT " - wind                                          ;" ; LOOP(C, PUT ( SUM((IA,IGWND)$(IAGKN(IA,IGWND) and ICA(C,IA)),VGKN.l(IA,IGWND))):12:0 ; PUT ";";); PUT /;
PUT " (hereof CHP)                                    ;" ; LOOP(C, PUT ( SUM((IA,G)$(IAGKN(IA,G) and (IGEXT(G) or IGBPR(G)) and ICA(C,IA)),VGKN.l(IA,G))):12:0 ; PUT ";";); PUT /;
PUT "Electric heating                                 ;" ; LOOP(C, PUT ( SUM((IA,IGETOH)$(IAGKN(IA,IGETOH) and ICA(C,IA)), VGKN.l(IA,IGETOH))):12:0 ; PUT ";";); PUT /;
*PUT "Transmission capacity                            ;" ; LOOP(C, PUT ( SUM(IRE$CCCRRR(C,IRE), SUM(VXKN.l(IRE,IRE) ))):12:0 ; PUT ";";)PUT /;

PUT //;

bal_1.LJ = 1;
PUT "Natural gas capacity gained from investments     "PUT Y.TL:4:0; PUT "  ;" ; LOOP(C, PUT C.TL:12 PUT ";";) ;PUT /;
bal_1.LJ = 2;

PUT "Total new supply capacity (MWh/h)                ;" ; LOOP(C, PUT ( sum((NGINV,SOURCE),SUPEFFECT(NGINV,SOURCE)*VGINFINV.l(NGINV))$SAMEAS(C,'Denmark')    ):12:0 ; PUT ";";); PUT /;
PUT "Total new delivery capacity (MWh/h)              ;" ; LOOP(C, PUT ( sum((GNETSTEPS,SYSEXIT), GNET_DEV_EFFECT(C,SYSEXIT)*VGNETINV.l(C,GNETSTEPS))+ sum((NGINV,SYSEXIT),DEVEFFECT(NGINV,SYSEXIT)*VGINFINV.l(NGINV))$SAMEAS(C,'Denmark')      ):12:0 ; PUT ";";); PUT /;
PUT " - onshore gas transmission network              ;" ; LOOP(C, PUT ( sum((GNETSTEPS,SYSEXIT), GNET_DEV_EFFECT(C,SYSEXIT)*VGNETINV.l(C,GNETSTEPS))  ):12:0 ; PUT ";";); PUT /;
PUT " - compressors and interconnectors               ;" ; LOOP(C, PUT ( sum((NGINV,SYSEXIT),DEVEFFECT(NGINV,SYSEXIT)*VGINFINV.l(NGINV))$SAMEAS(C,'Denmark')       ):12:0 ; PUT ";";); PUT /;
PUT "Total new export/transit capacity (MWh/h)        ;" ; LOOP(C, PUT ( sum((GNETSTEPS,SOURCE), GNET_EXP_EFFECT(C,SOURCE)*VGNETINV.l(C,GNETSTEPS))   +     sum((NGINV,SOURCE),EXPEFFECT(NGINV,SOURCE)*VGINFINV.l(NGINV))$SAMEAS(C,'Denmark')      ):12:0 ;PUT ";"; ); PUT /;
PUT " - onshore gas transmission network              ;" ; LOOP(C, PUT ( sum((GNETSTEPS,SOURCE), GNET_EXP_EFFECT(C,SOURCE)*VGNETINV.l(C,GNETSTEPS))  ):12:0 ; PUT ";";); PUT /;
PUT " - compressors and interconnectors               ;" ; LOOP(C, PUT ( sum((NGINV,SOURCE),EXPEFFECT(NGINV,SOURCE)*VGINFINV.l(NGINV))$SAMEAS(C,'Denmark')       ):12:0 ; PUT ";";); PUT /;
PUT "Gas storage capacity                             ;" ; LOOP(C, PUT  "-" ; ); PUT /;
PUT " - volumetric capacity (MWh)                     ;" ; LOOP(C, PUT ( sum((STORE,STORETYPE)$ICA(C,STORE),VGINVSTORE.l(STORE,STORETYPE))   ):12:0 ; PUT ";";); PUT /;
PUT " - injection capacity  (MWh/h)                   ;" ; LOOP(C, PUT ( sum((STORE,STORETYPE)$ICA(C,STORE),GSTOREDATA(STORETYPE,'Injeffect')*VGINVSTORE.l(STORE,STORETYPE)+VGINVINJ.l(STORE,STORETYPE))   ):12:0 ; PUT ";";); PUT /;
PUT " - extraction capacity (MWh/h)                   ;" ; LOOP(C, PUT ( sum((STORE,STORETYPE)$ICA(C,STORE),GSTOREDATA(STORETYPE,'Exteffect')*VGINVSTORE.l(STORE,STORETYPE)+VGINVEXT.l(STORE,STORETYPE))   ):12:0 ; PUT ";";); PUT /;
PUT "Total gas consumption capacity (MWh/h)           ;" ; LOOP(C, PUT ( SUM(IAGKN(IA,IGCND)$(ICA(C,IA) and GDATA(IGCND,'GDFUEL')=2), VGKN.l(IA,IGCND)/GDATA(IGCND,'GDFE') )     +   SUM(IAGKN(IA,IGE)$(ICA(C,IA) and (IGBPR(IGE) or IGEXT(IGE)) and GDATA(IGE,'GDFUEL')=2), ( (VGKN.l(IA,IGE)+VGKN.l(IA,IGE)/GDATA(IGE,'GDCB'))$IGBPR(IGE) + VGKN.l(IA,IGE)$IGEXT(IGE) )/GDATA(IGE,'GDFE') )   + SUM(IAGKN(IA,IGHH)$(ICA(C,IA) and GDATA(IGHH,'GDFUEL')=2), VGKN.l(IA,IGHH)/GDATA(IGHH,'GDFE')  )    ):12:0 ; PUT ";";); PUT /;
PUT " - condensing gas-fired electricity generation   ;" ; LOOP(C, PUT ( SUM(IAGKN(IA,IGCND)$(ICA(C,IA) and GDATA(IGCND,'GDFUEL')=2), VGKN.l(IA,IGCND)/GDATA(IGCND,'GDFE') )  ):12:0 ; PUT ";";); PUT /;
PUT " - combined heat and power (gas-fired)           ;" ; LOOP(C, PUT ( SUM(IAGKN(IA,IGE)$(ICA(C,IA) and (IGBPR(IGE) or IGEXT(IGE)) and GDATA(IGE,'GDFUEL')=2), ( (VGKN.l(IA,IGE)+VGKN.l(IA,IGE)/GDATA(IGE,'GDCB'))$IGBPR(IGE) + VGKN.l(IA,IGE)$IGEXT(IGE) )/GDATA(IGE,'GDFE') )  ):12:0 ; PUT ";";); PUT /;
PUT " - heat boilers (gas-fired)                      ;" ; LOOP(C, PUT ( SUM(IAGKN(IA,IGHH)$(ICA(C,IA) and GDATA(IGHH,'GDFUEL')=2), VGKN.l(IA,IGHH)/GDATA(IGHH,'GDFE') )   ):12:0 ; PUT ";";); PUT /;

PUT //;

bal_1.LJ = 1;
PUT "District heating capacity gained from investments     "PUT Y.TL:4:0; PUT "  ;" ; LOOP(C, PUT C.TL:12 PUT ";";) ;PUT /;
bal_1.LJ = 2;

PUT "Total heat generation capacity from investments  ;" ; LOOP(C, PUT ( SUM(IAGKN(IA,G)$(ICA(C,IA) and (IGEXT(G) or IGBPR(G))),   VGKN.l(IA,G)/GDATA(G,'GDCB') )    +  SUM(IAGKN(IA,IGHH),  VGKN.l(IA,IGHH))       ):12:0 ; PUT ";";); PUT /;
PUT " - CHP (natural gas-fired)                       ;" ; LOOP(C, PUT ( SUM(IAGKN(IA,G)$(ICA(C,IA) and (IGEXT(G) or IGBPR(G)) and (GDATA(G,'GDFUEL') =2)),   VGKN.l(IA,G)/GDATA(G,'GDCB')   )    ):12:0  ; PUT ";";); PUT /;
PUT " - CHP (other fuels)                             ;" ; LOOP(C, PUT ( SUM(IAGKN(IA,G)$(ICA(C,IA) and (IGEXT(G) or IGBPR(G)) and (not GDATA(G,'GDFUEL') =2) ),  VGKN.l(IA,G)/GDATA(G,'GDCB'))   ):12:0  ; PUT ";";); PUT /;
PUT " - heat only (natural gas-fired)                 ;" ; LOOP(C, PUT ( SUM(IAGKN(IA,IGHH)$(ICA(C,IA) and GDATA(IGHH,'GDFUEL') =2),  VGKN.l(IA,IGHH)     )  ):12:0 ; PUT ";";); PUT /;
PUT " - heat only (other fuels)                       ;" ; LOOP(C, PUT ( SUM(IAGKN(IA,IGHH)$(ICA(C,IA) and not GDATA(IGHH,'GDFUEL') =2), VGKN.l(IA,IGHH)   )     ):12:0 ; PUT ";";); PUT /;
PUT //;

PUT "*==============================================================================="//;


bal_1.LJ = 1;
PUT "Electricity generation and infrastructure Mio EURO06 "PUT Y.TL:4:0; PUT "  ;" ; LOOP(C, PUT C.TL:12 PUT ";";) ;PUT /;
bal_1.LJ = 2;

PUT "Total electricity generation (excl. heat pumps)  ;" ; LOOP(C, PUT ( OMONEY*SUM((IA,IGE)$((not IGETOH(IGE)) and IAGKN(IA,IGE) and ICA(C,IA)), GDATA(IGE,'GDINVCOST0')*VGKN.l(IA,IGE))):12:0 ; PUT ";";); PUT /;
PUT " - nuclear                                       ;" ; LOOP(C, PUT ( OMONEY*SUM((IA,IGNUC)$(IAGKN(IA,IGNUC) and ICA(C,IA)),GDATA(IGNUC,'GDINVCOST0')*VGKN.l(IA,IGNUC))):12:0 ; PUT ";";); PUT /;
PUT " - natural gas                                   ;" ; LOOP(C, PUT ( OMONEY*SUM((IA,IGE)$(IAGKN(IA,IGE) and ICA(C,IA) and GDATA(IGE,'GDFUEL')=2),GDATA(IGE,'GDINVCOST0')*VGKN.l(IA,IGE))):12:0 ; PUT ";";); PUT /;
PUT " - other thermal                                 ;" ; LOOP(C, PUT ( OMONEY*SUM((IA,IGE)$(IAGKN(IA,IGE) and ICA(C,IA) and not (GDATA(IGE,'GDTYPE')=5) and not (GDATA(IGE,'GDFUEL')=2) and not IGWND(IGE) and not IGHYRR(IGE) and not IGHYRS(IGE) and not IGNUC(IGE)),GDATA(IGE,'GDINVCOST0')*VGKN.l(IA,IGE))):12:0 ; PUT ";";); PUT /;
PUT " - hydro                                         ;" ; LOOP(C, PUT ( OMONEY*SUM((IA,G)$(IAGKN(IA,G) and (IGHYRR(G) or IGHYRS(G)) and ICA(C,IA)),GDATA(G,'GDINVCOST0')*VGKN.l(IA,G))):12:0 ; PUT ";";); PUT /;
PUT " - wind                                          ;" ; LOOP(C, PUT ( OMONEY*SUM((IA,IGWND)$(IAGKN(IA,IGWND) and ICA(C,IA)),GDATA(IGWND,'GDINVCOST0')*VGKN.l(IA,IGWND))):12:0 ; PUT ";";); PUT /;
PUT " (hereof CHP)                                    ;" ; LOOP(C, PUT ( OMONEY*SUM((IA,G)$(IAGKN(IA,G) and (IGEXT(G) or IGBPR(G)) and ICA(C,IA)),GDATA(G,'GDINVCOST0')*VGKN.l(IA,G))):12:0 ; PUT ";";); PUT /;
PUT "Electric heating                                 ;" ; LOOP(C, PUT ( OMONEY*SUM((IA,IGETOH)$(IAGKN(IA,IGETOH) and ICA(C,IA)), GDATA(IGETOH,'GDINVCOST0')*VGKN.l(IA,IGETOH))):12:0 ; PUT ";";); PUT /;
*PUT "Transmission capacity                           ;" ; LOOP(C, PUT ( OMONEY*SUM(IRE$CCCRRR(C,IRE), SUM(VXKN.l(IRE,IRE) ))):12:0 ; PUT ";";)PUT /; MANGLER INVCOST

PUT //;

bal_1.LJ = 1;
PUT "Natural gas infrastructure Mio EURO06 "PUT Y.TL:4:0; PUT "  ;" ; LOOP(C, PUT C.TL:12 PUT ";";) ;PUT /;
bal_1.LJ = 2;

PUT "Total investments in transmision infrastructure  ;" ; LOOP(C, PUT ( OMONEY*IOF0000001*( sum(GNETSTEPS, GNET_COST(C,GNETSTEPS)*VGNETINV.l(C,GNETSTEPS)) + sum(NGINV,COST_NGINV(NGINV)*VGINFINV.l(NGINV))$SAMEAS(C,'Denmark')   )    ):12:0 ; PUT ";";); PUT /;
PUT " - onshore gas transmission network              ;" ; LOOP(C, PUT ( OMONEY*IOF0000001* sum(GNETSTEPS, GNET_COST(C,GNETSTEPS)*VGNETINV.l(C,GNETSTEPS))   ):12:0 ; PUT ";";); PUT /;
PUT " - compressors and interconnectors               ;" ; LOOP(C, PUT ( OMONEY*IOF0000001* sum(NGINV,COST_NGINV(NGINV)*VGINFINV.l(NGINV))$SAMEAS(C,'Denmark')   ):12:0 ; PUT ";";); PUT /;
PUT "Total investments in natural gas storage         ;" ; LOOP(C, PUT ( OMONEY*IOF0000001* sum((STORE,STORETYPE)$ICA(C,STORE),GSTOREDATA(STORETYPE,'MargExtInvCost')*VGINVEXT.l(STORE,STORETYPE)+GSTOREDATA(STORETYPE,'MargInjInvCost')*VGINVINJ.l(STORE,STORETYPE)+GSTOREDATA(STORETYPE,'INVCOST')*VGINVSTORE.l(STORE,STORETYPE))/GASANNUITY   ):12:0 ; PUT ";";); PUT /;
PUT " - gas storage facilities                        ;" ; LOOP(C, PUT ( OMONEY*IOF0000001* sum((STORE,STORETYPE)$ICA(C,STORE),GSTOREDATA(STORETYPE,'INVCOST')*VGINVSTORE.l(STORE,STORETYPE))/GASANNUITY   ):12:0 ; PUT ";";); PUT /;
PUT " - injection capacity upgrades                   ;" ; LOOP(C, PUT ( OMONEY*IOF0000001* sum((STORE,STORETYPE)$ICA(C,STORE),GSTOREDATA(STORETYPE,'MargInjInvCost')*VGINVINJ.l(STORE,STORETYPE))/GASANNUITY   ):12:0 ; PUT ";";); PUT /;
PUT " - extraction capacity expansion                 ;" ; LOOP(C, PUT ( OMONEY*IOF0000001* sum((STORE,STORETYPE)$ICA(C,STORE),GSTOREDATA(STORETYPE,'MargExtInvCost')*VGINVEXT.l(STORE,STORETYPE))/GASANNUITY   ):12:0 ; PUT ";";); PUT /;
PUT "Total gas consumption capacity                   ;" ; LOOP(C, PUT ( OMONEY* SUM(IAGKN(IA,G)$(ICA(C,IA) and GDATA(G,'GDFUEL')=2), GDATA(G,'GDINVCOST0')*VGKN.l(IA,G))    ):12:0 ; PUT ";";); PUT /;
PUT " - condensing gas-fired electricity generation   ;" ; LOOP(C, PUT ( OMONEY* SUM(IAGKN(IA,IGCND)$(ICA(C,IA) and GDATA(IGCND,'GDFUEL')=2), GDATA(IGCND,'GDINVCOST0')*VGKN.l(IA,IGCND) ) ):12:0 ; PUT ";";); PUT /;
PUT " - combined heat and power (gas-fired)           ;" ; LOOP(C, PUT ( OMONEY* SUM(IAGKN(IA,IGE)$(ICA(C,IA) and (IGBPR(IGE) or IGEXT(IGE)) and GDATA(IGE,'GDFUEL')=2), GDATA(IGE,'GDINVCOST0')*VGKN.l(IA,IGE) ) ):12:0 ; PUT ";";); PUT /;
PUT " - heat boilers (gas-fired)                      ;" ; LOOP(C, PUT ( OMONEY* SUM(IAGKN(IA,IGHH)$(ICA(C,IA) and GDATA(IGHH,'GDFUEL')=2), GDATA(IGHH,'GDINVCOST0')*VGKN.l(IA,IGHH)  )   ):12:0 ; PUT ";";); PUT /;

PUT //;

bal_1.LJ = 1;
PUT "Investments in capacity for district heating     "PUT Y.TL:4:0; PUT "  ;" ; LOOP(C, PUT C.TL:12 PUT ";";) ;PUT /;
bal_1.LJ = 2;

PUT "Total heat generation capacity from investments  ;" ; LOOP(C, PUT ( OMONEY*SUM(IAGKN(IA,G)$(ICA(C,IA) and (IGEXT(G) or IGBPR(G))),  GDATA(G,'GDINVCOST0')*VGKN.l(IA,G) )    +  SUM(IAGKN(IA,IGHH),  GDATA(IGHH,'GDINVCOST0')*VGKN.l(IA,IGHH))       ):12:0 ; PUT ";";); PUT /;
PUT " - CHP (natural gas-fired)                       ;" ; LOOP(C, PUT ( OMONEY*SUM(IAGKN(IA,G)$(ICA(C,IA) and (IGEXT(G) or IGBPR(G)) and (GDATA(G,'GDFUEL') =2)),   GDATA(G,'GDINVCOST0')*VGKN.l(IA,G)  )    ):12:0  ; PUT ";";); PUT /;
PUT " - CHP (other fuels)                             ;" ; LOOP(C, PUT ( OMONEY*SUM(IAGKN(IA,G)$(ICA(C,IA) and (IGEXT(G) or IGBPR(G)) and (not GDATA(G,'GDFUEL') =2) ),  GDATA(G,'GDINVCOST0')*VGKN.l(IA,G)  )   ):12:0  ; PUT ";";); PUT /;
PUT " - heat only (natural gas-fired)                 ;" ; LOOP(C, PUT ( OMONEY*SUM(IAGKN(IA,IGHH)$(ICA(C,IA) and GDATA(IGHH,'GDFUEL') =2),  GDATA(IGHH,'GDINVCOST0')*VGKN.l(IA,IGHH)     )  ):12:0 ; PUT ";";); PUT /;
PUT " - heat only (other fuels)                       ;" ; LOOP(C, PUT ( OMONEY*SUM(IAGKN(IA,IGHH)$(ICA(C,IA) and not GDATA(IGHH,'GDFUEL') =2), GDATA(IGHH,'GDINVCOST0')*VGKN.l(IA,IGHH)   )     ):12:0 ; PUT ";";); PUT /;
PUT //;

$label BAL1_INVEST_END










































