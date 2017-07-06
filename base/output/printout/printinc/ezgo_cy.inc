* File: ezgo_cy.inc

* Modified last time: 01-02-2002 by (rus), 16-02-2004 (ld), 20060328(hr)

* This file will print a table containing the total annnual electricity
* generation from old power technologies in each country.
* Electricity consumption for heat pumps are NOT included.


* -----------------------------------------------------------------------------

PUT ezgo_cy;

* First print headings:

if ((ezgo_cy.pw LT 32000),
ezgo_cy.pw = 32000;
PUT "Version:              " SYSTEM.TITLE /;
PUT "File name:            ezgo_cy.out" /;
PUT "Time-stamp:          '" SYSTEM.DATE " " SYSTEM.TIME "'" /;
PUT "Case-identification: '" OCASEID.TS "'" //;

PUT "Total annual electricity generation from old technologies" /;
PUT "(Excl. electricity consumption at heat pumps)"/;
PUT "Units: GWh" //;

ezgo_cy.LJ = 1;

PUT "YEAR        " ; LOOP(C, PUT C.TL:12) ;PUT /;

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


ezgo_cy.LJ = 2;

PUT Y.TL:4:0; PUT "        " ; LOOP(C, PUT ( EZGOqCY(C)*IOF0001):12:0 ; ); PUT /;