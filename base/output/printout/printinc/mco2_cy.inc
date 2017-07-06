* File: mco2_cy.inc

* Modified last time: 4-1-2001 by (rus), 16-02-2004 (ld), 20051217 (hr), 20060328(hr)

* This file prints the national CO2 emission values



* -----------------------------------------------------------------------------

PUT mco2_cy;

* First print headings:

if ((mco2_cy.pw LT 32000),
mco2_cy.pw = 32000;
PUT "Version:              " SYSTEM.TITLE /;
PUT "File name:            mco2_cy.out" /;
PUT "Time-stamp:          '" SYSTEM.DATE " " SYSTEM.TIME "'" /;
PUT "Case-identification: '" OCASEID.TS "'" //;

PUT "Annual CO2 emissions" //;

PUT "Units: tonnes" //;

mco2_cy.LJ = 1;

PUT "CO2     "; LOOP(C, PUT C.TL:12) ; PUT   "       Total "/;

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


mco2_cy.LJ = 2;


ISCALAR1=0;
ISCALAR2=0;

PUT Y.TL:4:0; PUT "    ";
LOOP(C,

ISCALAR1= (
               SUM((G,S,T), IHOURSINST(S,T) * (IM_CO2(G)/1000) * IOF3P6 *
               SUM(IA$(ICA(C,IA) AND (GDATA(G,'GDFE')* GEFFDERATE(IA,G))),(VGE_T.L(IA,G,S,T) + VGEN_T.L(IA,G,S,T)
             + GDATA(G,'GDCV')*(VGH_T.L(IA,G,S,T) + VGHN_T.L(IA,G,S,T))) /
               (GDATA(G,'GDFE')* GEFFDERATE(IA,G))))
         );


 PUT ISCALAR1:12:0 ;
 ISCALAR2=ISCALAR2+ISCALAR1;
);
 PUT ISCALAR2:12:0 /;

*PUT "CO2 max level (ton)        " ; LOOP(C, PUT LIM_CO2_Y(C):12:0 ); PUT /;
*PUT "CO2 shadowprice (USD/ton)  " ; LOOP(C, PUT QLIMCO2.M(C):12:0 ); PUT /;