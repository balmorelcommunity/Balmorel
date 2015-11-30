* File: EG2_CY.INC

* Modified last time: 01-02-2002 by (rus), 20060328(hr)

* This file will print a table containing annnual net electricity generation
* from all technologies in each country.
* (Incl. the negative electricity generation for heat pumps)


* -----------------------------------------------------------------------------

PUT EG2_CY;

if ((EG2_CY.PW LT 32000),
EG2_CY.PW = 32000;
PUT "Version:              " "%PRINTSEPARATOR%" SYSTEM.TITLE /;
PUT "File name:            " "%PRINTSEPARATOR%" "eg2_cy.out" /;
PUT "Time-stamp:           " "%PRINTSEPARATOR%" SYSTEM.DATE " " SYSTEM.TIME  /;
$ifi %BB1%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE1"/;
$ifi %BB2%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE2"/;
$ifi %BB3%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE3"/;
PUT "Case-identification:  " "%PRINTSEPARATOR%" OCASEID.TS   //;
PUT '"Electricity production (MWh and MW) on units during each time segment"'//;
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

* -----------------------------------------------------------------------------

EG2_CY.LJ = 2;
PUT Y.TL:6:0; PUT "                        ";

EG2_CY.LJ = 1;
LOOP(C, PUT C.TL:12) ;PUT "      NORDEL" PUT /;

EG2_CY.LJ = 2;

PUT "TOTAL                         " ; LOOP(C, PUT ( sum(G,EGqCY(C,G)/1000)):12:0 ; ); PUT ( SUM((C,G),EGqCY(C,G)/1000)):12:0 ; PUT //;
PUT "Hydropower with reservoir     " ; LOOP(C, PUT ( sum(IGHYRS(G),EGqCY(C,G)/1000)):12:0 ; ); PUT ( SUM((C,IGHYRS(G)),EGqCY(C,G)/1000)):12:0 ; PUT /;
PUT "Hydropower run-of-river       " ; LOOP(C, PUT ( sum(IGHYRR(G),EGqCY(C,G)/1000)):12:0 ; ); PUT ( SUM((C,IGHYRR(G)),EGqCY(C,G)/1000)):12:0 ; PUT /;
PUT "Nuclear power technologies    " ; LOOP(C, PUT ( sum(INUCLEAR(G),EGqCY(C,G)/1000)):12:0 ; ); PUT ( SUM((C,INUCLEAR(G)),EGqCY(C,G)/1000)):12:0 ; PUT /;
PUT "Other electricity power       " , LOOP(C, PUT ( sum(IGCND(G),EGqCY(C,G)/1000)+ sum(IGEXT(G),EGqCY(C,G)/1000)+ sum(IGBPR(G),EGqCY(C,G)/1000)):12:0 ; ); PUT ( SUM((C,IGBPR(G)),EGqCY(C,G)/1000)+SUM((C,IGCND(G)),EGqCY(C,G)/1000)+SUM((C,IGEXT(G)),EGqCY(C,G)/1000)):12:0 ; PUT /;
PUT " -Condensing technologies     " ; LOOP(C, PUT ( sum(IGCND(G),EGqCY(C,G)/1000)):12:0 ; ); PUT ( SUM((C,IGCND(G)),EGqCY(C,G)/1000)):12:0 ; PUT /;
PUT " -Extraction technologies     " ; LOOP(C, PUT ( sum(IGEXT(G),EGqCY(C,G)/1000)):12:0 ; ); PUT ( SUM((C,IGEXT(G)),EGqCY(C,G)/1000)):12:0 ; PUT /;
PUT " -Back pressure technologies  " ; LOOP(C, PUT ( sum(IGBPR(G),EGqCY(C,G)/1000)):12:0 ; ); PUT ( SUM((C,IGBPR(G)),EGqCY(C,G)/1000)):12:0 ; PUT /;
PUT "Other Renewable power         " , PUT /;
PUT "Wind power technologies       " ; LOOP(C, PUT ( sum(IGWND(G),EGqCY(C,G)/1000)):12:0 ; ); PUT ( SUM((C,IGWND(G)),EGqCY(C,G)/1000)):12:0 ; PUT /;
PUT "Solar power technologies      " ; LOOP(C, PUT ( sum(IGSOL(G),EGqCY(C,G)/1000)):12:0 ; ); PUT ( SUM((C,IGSOL(G)),EGqCY(C,G)/1000)):12:0 ; PUT /;
PUT "Electric heaters or heatpumps " ; LOOP(C, PUT ( sum(IGETOH(G),EGqCY(C,G)/1000)):12:0 ; ); PUT ( SUM((C,IGETOH(G)),EGqCY(C,G)/1000)):12:0 ; PUT ///;


/*
PUT "Production capacity"//;
OSCALAR1=0;OSCALAR2=0;
LOOP(YYY$(ORD(YYY) EQ 1), PUT "Production capacity:"
YYY.tl //;
PUT " Technology         Area      El(MW)    Heat(MW)        Fuel     Fuel     eff.     Desulph       Denox     Referring to "/;
LOOP(IA$RRRAAA(IR,IA),
LOOP(G$GKFX(YYY,IA,G),
PUT G.TL:12
IA.TL:12;
* OBS: DE FOLGENDE BETINGELSER SKAL KONTROLLERES - JEG HUSKER DEM IKKE HELT
LIGE NU...
IF(IGKE(G), OSCALAR1=OSCALAR1+GKFX(YYY,IA,G); PUT
GKFX(YYY,IA,G):12:0 ELSE PUT "            ");
IF(IGEE(G), PUT "            "
ELSE
IF(IGHOB(G),  OSCALAR2=OSCALAR2+GKFX(YYY,IA,G); PUT
GKFX(YYY,IA,G):12:0);
IF(IGETOH(G), OSCALAR2=OSCALAR2+GKFX(YYY,IA,G); PUT
GKFX(YYY,IA,G):12:0);
IF(IGBPR(G),  OSCALAR2=OSCALAR2+GKFX(YYY,IA,G); PUT
(GKFX(YYY,IA,G)/GDATA(G,'GDCB')):12:0);
IF(IGEXT(G),  OSCALAR2=OSCALAR2+GKFX(YYY,IA,G); PUT
(GKFX(YYY,IA,G)/(GDATA(G,'GDCB')+GDATA(G,'GDCV'))):12:0);
IF(IGHSTO(G), OSCALAR2=OSCALAR2+GKFX(YYY,IA,G); PUT
GKFX(YYY,IA,G):12:0);
);

*/
