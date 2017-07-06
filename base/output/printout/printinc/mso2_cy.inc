* File: mso2_cy.inc

* Modified last time: 08-03-2002 by (mhd), 16-02-2004 (ld), 20051217 (hr), 20060328(hr)

* This file prints the national SO2 emission values




* -----------------------------------------------------------------------------

PUT mso2_cy;

* First print headings:

if ((mso2_cy.pw LT 32000),
mso2_cy.pw = 32000;
PUT "Version:              " SYSTEM.TITLE /;
PUT "File name:            mso2_cy.out" /;
PUT "Time-stamp:          '" SYSTEM.DATE " " SYSTEM.TIME "'" /;
PUT "Case-identification: '" OCASEID.TS "'" //;

PUT "Annual SO2 emissions" //;

PUT "Units: tonnes" //;

mso2_cy.LJ = 1;

PUT "SO2     "; LOOP(C, PUT C.TL:12) ; PUT /;

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

mso2_cy.LJ = 2;

PUT Y.TL:4:0; PUT "    "; LOOP(C, PUT (

      SUM((G,S,T), IHOURSINST(S,T) * (IM_SO2(G)/1000) * IOF3P6 *
      SUM(IA$(ICA(C,IA) AND (GDATA(G,'GDFE')* GEFFDERATE(IA,G))),(VGE_T.L(IA,G,S,T) + VGEN_T.L(IA,G,S,T)
      + GDATA(G,'GDCV')*(VGH_T.L(IA,G,S,T) + VGHN_T.L(IA,G,S,T))) /
      (GDATA(G,'GDFE')* GEFFDERATE(IA,G)) ))

):12:0 ); PUT /;