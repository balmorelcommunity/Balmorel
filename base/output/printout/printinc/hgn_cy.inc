* File: hgn_cy.inc

* Modified last time: 01-02-2002 (rus), 16-02-2004 (ld), 20060338(hr)

* This file will print a table containing annnual heat generation at new
* technologies in each country.



* -----------------------------------------------------------------------------

PUT hgn_cy;

* First print headings:

if ((hgn_cy.pw LT 32000),
hgn_cy.pw = 32000;
PUT "Version:              " "%PRINTSEPARATOR%" SYSTEM.TITLE /;
PUT "File name:            " "%PRINTSEPARATOR%" "hgn_cy.out" /;
PUT "Time-stamp:           " "%PRINTSEPARATOR%" SYSTEM.DATE " " SYSTEM.TIME  /;
$ifi %BB1%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE1"/;
$ifi %BB2%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE2"/;
$ifi %BB3%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE3"/;
PUT "Case-identification:  " "%PRINTSEPARATOR%" OCASEID.TS   /;

PUT "Annual heat generation from new technologies" //;

PUT "Units: GWh" //;

);

* End of file headings.
* ------------------------------------------------------------------------------------

* -----------------------------------------------------------------------------

hgn_cy.LJ = 1;
PUT Y.TL:4:0; PUT "        " ; LOOP(C, PUT C.TL:12) ;PUT /;
hgn_cy.LJ = 2;

LOOP(G,

if( sum(C,HGNqCY(C,G)) ne 0,

  PUT G.TL:32 ;
  LOOP(C, PUT (HGNqCY(C,G) *IOF0001):12:0 ;) ;
  PUT /;
   );
 );

PUT "TOTAL       " ; LOOP(C, PUT ( HZGNqCY(C)*IOF0001):12:0 ; ); PUT //;
