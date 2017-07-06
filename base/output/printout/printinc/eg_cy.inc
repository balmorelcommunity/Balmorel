* File: eg_cy.inc
* This file is part of the Balmorel model.

* Modified last time: 01-02-2002 by (rus), 16-02-2004 (sns,ld), 20060328(hr), 200804xx(hr), 20110508(hr), 20151120(hr), 20151210(hr)

* This file will print a table containing annnual netto electricity generation
* from all technologies in each country.
* (Incl. the negative electricity generation for heat pumps)


* ------------------------------------------------------------------------------

PUT eg_cy;

* First print headings:

if ((eg_cy.pw LT 32000),
eg_cy.pw = 32000;

PUT "Version:              " "%PRINTSEPARATOR%" SYSTEM.TITLE /;
PUT "File name:            " "%PRINTSEPARATOR%" "eg_cy.out" /;
PUT "Time-stamp:           " "%PRINTSEPARATOR%" SYSTEM.DATE " " SYSTEM.TIME  /;
$ifi %BB1%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE1"/;
$ifi %BB2%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE2"/;
$ifi %BB3%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE3"/;

PUT "Case-identification:  " "%PRINTSEPARATOR%" OCASEID.TS   //;

$ifi %BB1%==yes PUT / "Annual net electricity generation, old and new technologies, (incl. negative electricity generation for heat pumps)." //;
$ifi %BB2%==yes PUT / "Annual net electricity generation, old and new technologies, (incl. negative electricity generation for heat pumps)." //;
$ifi %BB3%==yes PUT / "Annual net electricity generation, old and new technologies, (incl. negative electricity generation for heat pumps)." //;

PUT "Units: GWh" //;

);

* End of file headings.

* -----------------------------------------------------------------------------

eg_cy.LJ = 1;
*                         |<------ OTLW characters ----->|
PUT Y.TL:OTLWY:0;    PUT "                                " ; LOOP(C, PUT   "%PRINTSEPARATOR%"  C.TL:OTLW) ;
*                         |<------ OTLW characters ----->|                        |<------ OTLW characters ----->|
PUT  "%PRINTSEPARATOR%"  "                 Technology type"  "%PRINTSEPARATOR%"  "                            Fuel" /;
eg_cy.LJ = 2;

LOOP(G,

if(ignotetoh(g),
if( SUM(C,EGqCY(C,G)) NE 0,

  PUT OTLWY.ts  G.TL:OTLW ;
  LOOP(C, PUT   "%PRINTSEPARATOR%" (EGqCY(C,G)*IOF0001):OTLW:0 ;) ;  PUT     "%PRINTSEPARATOR%"  GDATA(G,'GDTYPE'):OTLW:0  "%PRINTSEPARATOR%"  GDATA(G,'GDFUEL'):OTLW:0 /;
*  PUT "    Technology type:  " GDATA(G,'GDTYPE');
*  LOOP(FFF$IGF(G,FFF), PUT "    Fuel:  " FFF.TL);
);

ELSE

if( SUM(C,EGqCY(C,G)) NE 0,

  PUT OTLWY.ts  G.TL:OTLW ;
  LOOP(C, PUT  "%PRINTSEPARATOR%" (-EGqCY(C,G) *IOF0001):OTLW:0 ;) ;  PUT     "%PRINTSEPARATOR%"  GDATA(G,'GDTYPE'):OTLW:0  "%PRINTSEPARATOR%"  GDATA(G,'GDFUEL'):OTLW:0 /;
);
);
);


PUT OTLWY.ts  "TOTAL (note any minus sign)     " ; LOOP(C, PUT  "%PRINTSEPARATOR%"  ( sum(ignotetoh,EGqCY(C,ignotetoh)*IOF0001) + sum(igetoh,-EGqCY(C,igetoh)*IOF0001)):OTLW:0 ; ); PUT //;

