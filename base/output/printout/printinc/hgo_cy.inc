* File: hgo_cy.inc

* Modified last time: 01-02-2002 (rus) , 20060328(hr)

* This file will print a table containing annnual heat generation at old
* technologies in each country.



* -----------------------------------------------------------------------------

PUT hgo_cy;

* First print headings:

if ((hgo_cy.pw LT 32000),
hgo_cy.pw = 32000;
PUT "Version:              " "%PRINTSEPARATOR%" SYSTEM.TITLE /;
PUT "File name:            " "%PRINTSEPARATOR%" "hgo_cy.out" /;
PUT "Time-stamp:           " "%PRINTSEPARATOR%" SYSTEM.DATE " " SYSTEM.TIME  /;
$ifi %BB1%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE1"/;
$ifi %BB2%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE2"/;
$ifi %BB3%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE3"/;
PUT "Case-identification:  " "%PRINTSEPARATOR%" OCASEID.TS   //;

PUT "Annual heat generation from existing technologies" //;

PUT "Units: GWh" //;

);

* End of file headings.
* ------------------------------------------------------------------------------------

* -----------------------------------------------------------------------------

hgo_cy.LJ = 1;
PUT Y.TL:4:0; PUT "        " ; LOOP(C, PUT C.TL:12) ;PUT /;
hgo_cy.LJ = 2;

LOOP(G,

if( sum(C,HGOqCY(C,G)) ne 0,

  PUT G.TL:12 ;
  LOOP(C, PUT (HGOqCY(C,G) *IOF0001):12:0 ;) ;
  PUT /;
   );
 );

PUT "TOTAL       " ; LOOP(C, PUT ( HZGOqCY(C)*IOF0001):12:0 ; ); PUT //;
