* File: mnox_cy.inc

* Modified last time: 08-03-2002 by (mhd), 16-02-2004 (ld), 20051217 (hr), 20060328(hr)

* This file prints the national NOx emission values




* -----------------------------------------------------------------------------

PUT mnox_cy;

* First print headings:

if ((mnox_cy.pw LT 32000),
mnox_cy.pw = 32000;
PUT "Version:              " "%PRINTSEPARATOR%" SYSTEM.TITLE /;
PUT "File name:            " "%PRINTSEPARATOR%" "mnox_cy.out" /;
PUT "Time-stamp:           " "%PRINTSEPARATOR%" SYSTEM.DATE " " SYSTEM.TIME  /;
$ifi %BB1%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE1"/;
$ifi %BB2%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE2"/;
$ifi %BB3%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE3"/;
PUT "Case-identification:  " "%PRINTSEPARATOR%" OCASEID.TS   //;

PUT "Annual NOx emissions" //;

PUT "Units: tonnes" //;

mnox_cy.LJ = 1;

PUT "NOx     "; LOOP(C, PUT C.TL:12) ; PUT /;

);

* End of file headings.
* ------------------------------------------------------------------------------------

* ------------------------------------------------------------------------------------

* -----------------------------------------------------------------------------

mnox_cy.LJ = 2;

PUT Y.TL:4:0; PUT "    "; LOOP(C, PUT (

     SUM((IA,G,S,T)$((IAGK_Y(IA,G) or IAGKN(IA,G)) and ICA(C,IA)), IHOURSINST(S,T) * (GDATA(G,'GDNOX')/IOF1000000) * IOF3P6 *
       VGF_T.l(IA,G,S,T)$IAGK_Y(IA,G)
      +VGF_T.l(IA,G,S,T)$(VGKN.l(IA,G) and IAGKN(IA,G)))

):12:0 ); PUT /;
