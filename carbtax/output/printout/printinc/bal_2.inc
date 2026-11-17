* File: bal_2.out
* Printing to bal_1.out

* Modified last time: 20070306 (lb), 20151210(hr)

* Note: presently there are errors in the file, has to be recoded for version 3.03 or later. Therefore it is not included, cf. prt4-bb2.inc

* This file will print a table containing an energy balance for each country




* -----------------------------------------------------------------------------

PUT bal_1;

* First print file headings:

if ((bal_1.pw LT 32000),
bal_1.pw = 32000;
PUT "Version:              " "%PRINTSEPARATOR%" SYSTEM.TITLE /;
PUT "File name:            " "%PRINTSEPARATOR%" "bal_1.out" /;
PUT "Time-stamp:           " "%PRINTSEPARATOR%" SYSTEM.DATE " " SYSTEM.TIME  /;
PUT "Case-identification:  " "%PRINTSEPARATOR%" OCASEID.TS   /;
$ifi %BB1%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE1"/;
$ifi %BB2%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE2"/;
$ifi %BB3%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE3"/;


PUT "Energy balance" //;
PUT "Units: GWh" //;

);

* End of file headings.


bal_1.LJ = 1;
PUT "Electricity balance for "PUT Y.TL:4:0; PUT "                     ;" ; LOOP(C, PUT C.TL:12 PUT ";";) ;PUT /;
bal_1.LJ = 2;

PUT "Total electricity generation (excl. heat pumps)  ;" ; LOOP(C, PUT ( EZGqCY(C)*IOF0001):12:0 ; PUT ";";); PUT /;
PUT " - nuclear                                       ;" ; LOOP(C, PUT ( SUM((IA,G,S,T)$(IGF(G,'NUCLEAR') and (IAGK_Y(IA,G) or AGKN(IA,G)) and ICA(C,IA)),(VGE_T.l(IA,G,S,T)+VGEN_T.l(IA,G,S,T))*IHOURSINST(S,T))*IOF0001):12:0 ; PUT ";";); PUT /;
PUT " - other thermal                                 ;" ; LOOP(C, PUT ( SUM((IA,IGE,S,T)$((IAGK_Y(IA,IGE) or AGKN(IA,IGE)) and ICA(C,IA) and not (GDATA(IGE,'GDTYPE')=5) and not IGWND(IGE) and not IGHYRR(IGE) and not IGHYRS(IGE) and not IGF(IGE,'NUCLEAR')),(VGE_T.l(IA,IGE,S,T)+VGEN_T.l(IA,IGE,S,T))*IHOURSINST(S,T))*IOF0001):12:0 ; PUT ";";); PUT /;
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
PUT "District heating balance for "PUT Y.TL:4:0; PUT "                ;" ; LOOP(C, PUT C.TL:12 PUT ";";) ;PUT /;
bal_1.LJ = 2;

PUT "Total heat generation                            ;" ; LOOP(C, PUT ( HZGqCY(C)*IOF0001):12:0 ; PUT ";";); PUT /;
PUT " - CHP                                           ;" ; LOOP(C, PUT ( SUM((IA,IGH,S,T)$((IGBPR(IGH) or IGEXT(IGH)) and(IAGK_Y(IA,IGH) or AGKN(IA,IGH)) and ICA(C,IA)),(VGH_T.l(IA,IGH,S,T)+VGHN_T.l(IA,IGH,S,T))*IHOURSINST(S,T))*IOF0001):12:0 ; PUT ";";); PUT /;
PUT " - electricity to heat                           ;" ; LOOP(C, PUT ( SUM((IA,IGETOH,S,T)$((IAGK_Y(IA,IGETOH) or AGKN(IA,IGETOH)) and ICA(C,IA)),(VGH_T.l(IA,IGETOH,S,T)+VGHN_T.l(IA,IGETOH,S,T))*IHOURSINST(S,T))*IOF0001):12:0 ; PUT ";";); PUT /;
PUT " - other                                         ;" ; LOOP(C, PUT ( SUM((IA,IGHOB,S,T)$((IAGK_Y(IA,IGHOB) or AGKN(IA,IGHOB)) and ICA(C,IA)),(VGH_T.l(IA,IGHOB,S,T)+VGHN_T.l(IA,IGHOB,S,T))*IHOURSINST(S,T))*IOF0001):12:0 ; PUT ";";); PUT /;
PUT "Distribution loss                                ;" ; LOOP(C, PUT ( HLqCY(C)*IOF0001):12:0 ; PUT ";";)PUT /;
PUT "Heat demand                                      ;" ; LOOP(C, PUT ( HDqCY(C)*IOF0001):12:0 ; PUT ";";); PUT //;



*-----------------------------------
* Investments:
*-----------------------------------

$ifi not %BB2%==yes $goto BAL2_INVEST_END


PUT "Investments" //;

* End of file headings.

* ------------------------------------------------------------------------------------

bal_1.LJ = 1;
PUT "Electricity generation and infrastructure MW el "PUT Y.TL:4:0; PUT "  ;" ; LOOP(C, PUT C.TL:12 PUT ";";) ;PUT /;
bal_1.LJ = 2;

PUT "Total electricity generation (excl. heat pumps)       ;" ; LOOP(C, PUT ( SUM((IA,IGE)$((not IGETOH(IGE)) and IAGKN(IA,IGE) and ICA(C,IA)), VGKN.l(IA,IGE))):12:0 ;PUT ";"; ); PUT /;
PUT " - nuclear                                            ;" ; LOOP(C, PUT ( SUM((IA,IGNUC)$(IAGKN(IA,IGNUC) and ICA(C,IA)),VGKN.l(IA,IGNUC))):12:0 ; PUT ";";); PUT /;
PUT " - other thermal                                      ;" ; LOOP(C, PUT ( SUM((IA,IGE)$(IAGKN(IA,IGE) and ICA(C,IA) and not (GDATA(IGE,'GDTYPE')=5) and not IGWND(IGE) and not IGHYRR(IGE) and not IGHYRS(IGE) and not IGNUC(IGE)),VGKN.l(IA,IGE))):12:0 ; PUT ";";); PUT /;
PUT " - hydro                                              ;" ; LOOP(C, PUT ( SUM((IA,G)$(IAGKN(IA,G) and (IGHYRR(G) or IGHYRS(G)) and ICA(C,IA)),VGKN.l(IA,G))):12:0 ; PUT ";";); PUT /;
PUT " - wind                                               ;" ; LOOP(C, PUT ( SUM((IA,IGWND)$(IAGKN(IA,IGWND) and ICA(C,IA)),VGKN.l(IA,IGWND))):12:0 ; PUT ";";); PUT /;
PUT " (hereof CHP)                                         ;" ; LOOP(C, PUT ( SUM((IA,G)$(IAGKN(IA,G) and (IGEXT(G) or IGBPR(G)) and ICA(C,IA)),VGKN.l(IA,G))):12:0 ; PUT ";";); PUT /;
PUT "Electric heating                                      ;" ; LOOP(C, PUT ( SUM((IA,IGETOH)$(IAGKN(IA,IGETOH) and ICA(C,IA)), VGKN.l(IA,IGETOH))):12:0 ; PUT ";";); PUT /;
*PUT "Transmission capacity                                 ;" ; LOOP(C, PUT ( SUM(IRE$CCCRRR(C,IRE), SUM(VXKN.l(IRE,IRE) ))):12:0 ; PUT ";";)PUT /;

PUT //;

bal_1.LJ = 1;
PUT "District heating capacity gained from investments     "PUT Y.TL:4:0; PUT "  ;" ; LOOP(C, PUT C.TL:12 PUT ";";) ;PUT /;
bal_1.LJ = 2;

PUT "Total heat generation capacity from investments             ;" ; LOOP(C, PUT ( SUM(IAGKN(IA,IGH(G))$ICA(C,IA),   VGKN.l(IA,G)/(1+(GDATA(G,'GDCB')$(IGBPR(G) or IGEXT(G)) )  )) ):12:0 ; PUT ";";); PUT /;
PUT " - CHP                                                      ;" ; LOOP(C, PUT ( SUM(IAGKN(IA,G)$(ICA(C,IA) and (IGEXT(G) or IGBPR(G))),  VGKN.l(IA,G)/GDATA(G,'GDCB'))   ):12:0  ; PUT ";";); PUT /;
PUT " - electric heating                                         ;" ; LOOP(C, PUT ( SUM(IAGKN(IA,IGETOH(G))$(ICA(C,IA)),  VGKN.l(IA,G) )   ):12:0  ; PUT ";";); PUT /;
PUT " - heat only                                                       ;" ; LOOP(C, PUT ( SUM(IAGKN(IA,IGHOB(G))$ICA(C,IA), VGKN.l(IA,G)   )     ):12:0 ; PUT ";";); PUT /;
PUT //;

PUT "*==============================================================================="//;


bal_1.LJ = 1;
PUT "Currency: Mio " OMONEY.TS "  with exchange rate to input currency: "  OMONEY:7:3  " ("OMONEY.TS"/"OIMONEY.TS")." /;
PUT "Currency: " OMONEY.TS "  with exchange rate to input currency: "  OMONEY:7:3  " ("OMONEY.TS"/"OIMONEY.TS")." /;
bal_1.LJ = 2;

PUT "Total electricity generation (excl. heat pumps)            ;" ; LOOP(C, PUT ( OMONEY*SUM((IA,IGE)$((not IGETOH(IGE)) and IAGKN(IA,IGE) and ICA(C,IA)), GDATA(IGE,'GDINVCOST0')*VGKN.l(IA,IGE))):12:0 ; PUT ";";); PUT /;
PUT " - nuclear                                                 ;" ; LOOP(C, PUT ( OMONEY*SUM((IA,IGNUC)$(IAGKN(IA,IGNUC) and ICA(C,IA)),GDATA(IGNUC,'GDINVCOST0')*VGKN.l(IA,IGNUC))):12:0 ; PUT ";";); PUT /;
PUT " - other thermal                                           ;" ; LOOP(C, PUT ( OMONEY*SUM((IA,IGE)$(IAGKN(IA,IGE) and ICA(C,IA) and not (GDATA(IGE,'GDTYPE')=5) and not IGWND(IGE) and not IGHYRR(IGE) and not IGHYRS(IGE) and not IGNUC(IGE)),GDATA(IGE,'GDINVCOST0')*VGKN.l(IA,IGE))):12:0 ; PUT ";";); PUT /;
PUT " - hydro                                                   ;" ; LOOP(C, PUT ( OMONEY*SUM((IA,G)$(IAGKN(IA,G) and (IGHYRR(G) or IGHYRS(G)) and ICA(C,IA)),GDATA(G,'GDINVCOST0')*VGKN.l(IA,G))):12:0 ; PUT ";";); PUT /;
PUT " - wind                                                    ;" ; LOOP(C, PUT ( OMONEY*SUM((IA,IGWND)$(IAGKN(IA,IGWND) and ICA(C,IA)),GDATA(IGWND,'GDINVCOST0')*VGKN.l(IA,IGWND))):12:0 ; PUT ";";); PUT /;
PUT " (hereof CHP)                                              ;" ; LOOP(C, PUT ( OMONEY*SUM((IA,G)$(IAGKN(IA,G) and (IGEXT(G) or IGBPR(G)) and ICA(C,IA)),GDATA(G,'GDINVCOST0')*VGKN.l(IA,G))):12:0 ; PUT ";";); PUT /;
PUT "Electric heating                                           ;" ; LOOP(C, PUT ( OMONEY*SUM((IA,IGETOH)$(IAGKN(IA,IGETOH) and ICA(C,IA)), GDATA(IGETOH,'GDINVCOST0')*VGKN.l(IA,IGETOH))):12:0 ; PUT ";";); PUT /;
*PUT "Transmission capacity                                     ;" ; LOOP(C, PUT ( OMONEY*SUM(IRE$CCCRRR(C,IRE), SUM(VXKN.l(IRE,IRE) ))):12:0 ; PUT ";";)PUT /; MANGLER INVCOST

PUT //;

bal_1.LJ = 1;
PUT "Investments in capacity for district heating     "PUT Y.TL:4:0; PUT "  ;" ; LOOP(C, PUT C.TL:12 PUT ";";) ;PUT /;
bal_1.LJ = 2;

PUT "Total heat generation capacity from investments        ;" ; LOOP(C, PUT ( OMONEY*SUM(IAGKN(IA,IGH(G))$ICA(C,IA),  GDATA(G,'GDINVCOST0')*VGKN.l(IA,G) )     ):12:0 ; PUT ";";); PUT /;
PUT " - CHP                                                 ;" ; LOOP(C, PUT ( OMONEY*SUM(IAGKN(IA,G)$(ICA(C,IA) and (IGEXT(G) or IGBPR(G))),   GDATA(G,'GDINVCOST0')*VGKN.l(IA,G)  )):12:0  ; PUT ";";); PUT /;
PUT " - electric heating                                    ;" ; LOOP(C, PUT ( OMONEY*SUM(IAGKN(IA,IGETOH(G))$(ICA(C,IA)),   GDATA(G,'GDINVCOST0')*VGKN.l(IA,G)  )    ):12:0  ; PUT ";";); PUT /;
PUT " - heat only                                           ;" ; LOOP(C, PUT ( OMONEY*SUM(IAGKN(IA,IGHOB(G))$ICA(C,IA),  GDATA(G,'GDINVCOST0')*VGKN.l(IA,G)     )  ):12:0 ; PUT ";";); PUT /;
PUT //;

$label BAL2_INVEST_END








































