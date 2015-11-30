* File: mso2_cy.inc

* Modified last time: 08-03-2002 by (mhd), 16-02-2004 (ld), 20051217 (hr), 20060328(hr)

* This file prints the national SO2 emission values




* -----------------------------------------------------------------------------

PUT mso2_cy;

* First print headings:

if ((mso2_cy.pw LT 32000),
mso2_cy.pw = 32000;
PUT "Version:              " "%PRINTSEPARATOR%" SYSTEM.TITLE /;
PUT "File name:            " "%PRINTSEPARATOR%" "mso2_cy.out" /;
PUT "Time-stamp:           " "%PRINTSEPARATOR%" SYSTEM.DATE " " SYSTEM.TIME  /;
$ifi %BB1%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE1"/;
$ifi %BB2%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE2"/;
$ifi %BB3%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE3"/;
PUT "Case-identification:  " "%PRINTSEPARATOR%" OCASEID.TS   //;

PUT "Annual SO2 emissions" //;

PUT "Units: tonnes" //;

mso2_cy.LJ = 1;

PUT "SO2     "; LOOP(C, PUT C.TL:12) ; PUT /;

);

* End of file headings.

* -----------------------------------------------------------------------------

mso2_cy.LJ = 2;

PUT Y.TL:4:0; PUT "    "; LOOP(C, PUT (

      SUM((IA,G,S,T)$((IAGK_Y(IA,G) or IAGKN(IA,G)) and ICA(C,IA)), IHOURSINST(S,T) * (IM_SO2(G)/IOF1000) * IOF3P6 *(
       VGF_T.l(IA,G,S,T)$IAGK_Y(IA,G)
      +VGF_T.l(IA,G,S,T)$(VGKN.l(IA,G) and IAGKN(IA,G))    )
      )

):12:0 ); PUT /;
