* File: mco2_cy.inc

* Modified last time: 4-1-2001 by (rus), 16-02-2004 (ld), 20051217 (hr), 20060328(hr)

* This file prints the national CO2 emission values



* -----------------------------------------------------------------------------

PUT mco2_cy;

* First print headings:

if ((mco2_cy.pw LT 32000),
mco2_cy.pw = 32000;
PUT "Version:              " "%PRINTSEPARATOR%" SYSTEM.TITLE /;
PUT "File name:            " "%PRINTSEPARATOR%" "mco2_cy.out" /;
PUT "Time-stamp:           " "%PRINTSEPARATOR%" SYSTEM.DATE " " SYSTEM.TIME  /;
$ifi %BB1%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE1"/;
$ifi %BB2%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE2"/;
$ifi %BB3%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE3"/;
PUT "Case-identification:  " "%PRINTSEPARATOR%" OCASEID.TS   //;

PUT "Annual CO2 emissions" //;

PUT "Units: tonnes" //;

mco2_cy.LJ = 1;

PUT "CO2     "; LOOP(C, PUT C.TL:12) ; PUT   "       Total "/;

);

* End of file headings.
* ------------------------------------------------------------------------------------

* -----------------------------------------------------------------------------


mco2_cy.LJ = 2;

$ontext
ISCALAR1=0;
ISCALAR2=0;

PUT Y.TL:4:0; PUT "    ";
LOOP(C,

ISCALAR1= (
               SUM((IA,G,S,T)$((IAGK_Y(IA,G) or IAGKN(IA,G)) and ICA(C,IA)), IHOURSINST(S,T) * (IM_CO2(G)/IOF1000) * IOF3P6 *
                  VGF_T.l(IA,G,S,T)$IAGK_Y(IA,G)
                 +VGF_T.l(IA,G,S,T)$(VGKN.l(IA,G) and IAGKN(IA,G)) )
         );


 PUT ISCALAR1:12:0 ;
 ISCALAR2=ISCALAR2+ISCALAR1;
);
 PUT ISCALAR2:12:0 /;


*PUT "CO2 max level (ton)        " ; LOOP(C, PUT LIM_CO2_Y(C):12:0 ); PUT /;
*PUT "CO2 shadowprice (USD/ton)  " ; LOOP(C, PUT QLIMCO2.M(C):12:0 ); PUT /;

(GDATA(ignotetoh,'GDFUEL') EQ FDATA(FFF,'FDNB'))
$offtext



