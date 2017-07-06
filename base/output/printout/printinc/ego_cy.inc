* File: ego_cy.inc

* Modified last time: 4-1-2001 by (rus), 16-02-2004(sns,ld), 2005.07.31(hr), 20060328(hr), 200804xx(hr), 20110508(hr)

* This file will print a table containing annnual net electricity generation
* on old power plants in each country.
* (Incl. the negative electricity generation for heat pumps)


* -----------------------------------------------------------------------------

PUT ego_cy;

* First print headings:

if ((ego_cy.pw LT 32000),
ego_cy.pw = 32000;

PUT "Version:              " "%PRINTSEPARATOR%" SYSTEM.TITLE /;
PUT "File name:            " "%PRINTSEPARATOR%" "ego_cy.out" /;
PUT "Time-stamp:           " "%PRINTSEPARATOR%" SYSTEM.DATE " " SYSTEM.TIME  /;
$ifi %BB1%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE1"/;
$ifi %BB2%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE2"/;
$ifi %BB3%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE3"/;
PUT "Case-identification:  " "%PRINTSEPARATOR%" OCASEID.TS   /;
$ifi %BB1%==yes PUT / "Annual net electricity generation at old (existing at the beginning of the year) technologies (incl. negative electricity generation for heat pumps)." //;
$ifi %BB2%==yes PUT / "Annual net electricity generation at old (existing at the beginning of the year) technologies (incl. negative electricity generation for heat pumps)." //;
$ifi %BB3%==yes PUT / "Annual net electricity generation at old (existing at the beginning of the year) technologies (incl. negative electricity generation for heat pumps)." //;

PUT "Units: GWh" //;
);


* -----------------------------------------------------------------------------

ego_cy.LJ = 1;
*                         |<------ OTLW characters ----->|
PUT Y.TL:OTLWY:0;    PUT "                                " ; LOOP(C, PUT   "%PRINTSEPARATOR%"  C.TL:OTLW) ;
*                         |<------ OTLW characters ----->|                        |<------ OTLW characters ----->|
PUT  "%PRINTSEPARATOR%"  "                 Technology type"  "%PRINTSEPARATOR%"  "                            Fuel" /;
ego_cy.LJ = 2;

LOOP(G,

if(ignotetoh(g),
if( SUM(C,EGOqCY(C,G)) NE 0,

  PUT OTLWY.ts  G.TL:OTLW ;
  LOOP(C, PUT  "%PRINTSEPARATOR%" ( EGOqCY(C,G) *IOF0001):OTLW:0 ;);    PUT     "%PRINTSEPARATOR%"  GDATA(G,'GDTYPE'):OTLW:0  "%PRINTSEPARATOR%"  GDATA(G,'GDFUEL'):OTLW:0 /;
);
ELSE

if( SUM(C,EGOqCY(C,G)) NE 0,

  PUT OTLWY.ts  G.TL:OTLW ;
  LOOP(C, PUT  "%PRINTSEPARATOR%" (-EGOqCY(C,G) *IOF0001):OTLW:0 ;);    PUT     "%PRINTSEPARATOR%"  GDATA(G,'GDTYPE'):OTLW:0  "%PRINTSEPARATOR%"  GDATA(G,'GDFUEL'):OTLW:0 /;
 );
);
);




*              |<------ OTLW characters ----->|
PUT OTLWY.ts  "TOTAL (note any minus sign)     " ; LOOP(C, PUT "%PRINTSEPARATOR%" ( sum(ignotetoh,EGOqCY(C,ignotetoh)*IOF0001)+ sum(igetoh,-EGOqCY(C,igetoh)*IOF0001)):OTLW:0 ; ); PUT //;
