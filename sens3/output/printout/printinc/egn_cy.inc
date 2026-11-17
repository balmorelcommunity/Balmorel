* File: egn_cy.inc

* Modified last time: 4-1-2001 by (rus), 16-02-2004 (ld), 20060328(hr), 200804xx(hr), 20110508(hr)

* This file will print a table containing annual net electricity generation (MWh)
* on new power plants in each country.
* (Incl. the negative electricity generation for heat pumps).
* Also new capacities (MW) are printed.


* -----------------------------------------------------------------------------

PUT egn_cy;

* First print headings:

if ((egn_cy.pw LT 32000),
egn_cy.pw = 32000;
PUT "Version:              " "%PRINTSEPARATOR%" SYSTEM.TITLE /;
PUT "File name:            " "%PRINTSEPARATOR%" "egn_cy.out" /;
PUT "Time-stamp:           " "%PRINTSEPARATOR%" SYSTEM.DATE " " SYSTEM.TIME  /;
$ifi %BB1%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE1"/;
$ifi %BB2%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE2"/;
$ifi %BB3%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE3"/;
PUT "Case-identification:  " "%PRINTSEPARATOR%" OCASEID.TS   /;

$ifi %BB1%==yes PUT / "Not relevant for model Balbase1." //;
$ifi %BB2%==yes PUT / "Annual net electricity generation at new technologies (incl. negative electricity generation for heat pumps), and new generation capacities." //;
$ifi %BB3%==yes PUT / "Not relevant for model Balbase3." //;

PUT "Units: generation: GWh, capacities MW."//;
);

* End of headings.

* ------------------------------------------------------------------------------------

* -----------------------------------------------------------------------------

put "Generation on new technologies (GWh):" //;
egn_cy.LJ = 1;
*                         |<------ OTLW characters ----->|
PUT Y.TL:OTLWY:0;    PUT "                                " ; LOOP(C, PUT   "%PRINTSEPARATOR%"  C.TL:OTLW) ;
*                         |<------ OTLW characters ----->|                        |<------ OTLW characters ----->|
PUT  "%PRINTSEPARATOR%"  "                 Technology type"  "%PRINTSEPARATOR%"  "                            Fuel" /;

egn_cy.LJ = 2;

LOOP(G,
if(ignotetoh(g),
if( sum(C,EGNqCY(C,G)) ne 0,
  PUT OTLWY.ts  G.TL:OTLW;
  LOOP(C, PUT   "%PRINTSEPARATOR%"  (EGNqCY(C,G) *IOF0001):OTLW:0 ;) ;    PUT     "%PRINTSEPARATOR%"  GDATA(G,'GDTYPE'):OTLW:0  "%PRINTSEPARATOR%"  GDATA(G,'GDFUEL'):OTLW:0 /;
);
ELSE
if( sum(C,EGNqCY(C,G)) ne 0,
  PUT PUT OTLWY.ts  G.TL:OTLW;
  LOOP(C, PUT  "%PRINTSEPARATOR%" (-EGNqCY(C,G) *IOF0001):OTLW:0  ;) ;    PUT     "%PRINTSEPARATOR%"  GDATA(G,'GDTYPE'):OTLW:0  "%PRINTSEPARATOR%"  GDATA(G,'GDFUEL'):OTLW:0 / ;
 );
));
*              |<------ OTLW characters ----->|
PUT OTLWY.ts  "TOTAL (note any minus sign)     " ; LOOP(C, PUT  "%PRINTSEPARATOR%"  ( sum(ignotetoh,EGNqCY(C,ignotetoh)*IOF0001)+ sum(igetoh,-EGNqCY(C,igetoh)*IOF0001)):OTLW:0 ; ); PUT //;


* ------------------------------------------------------------------------------
* ------------------------------------------------------------------------------

PUT  "New capacities (MW) "    / /;

egn_cy.LJ = 1;
*                      |<------ OTLW characters ----->|
PUT Y.TL:OTLWY:0; PUT "                                " ; LOOP(C, PUT  "%PRINTSEPARATOR%" C.TL:OTLW) ;PUT /;
egn_cy.LJ = 2;

LOOP(G,
ISCALAR1=SUM(C,SUM(IA$ICA(C,IA), VGKN.L(IA,G)));
if( ISCALAR1 GT 0,
  PUT PUT OTLWY.ts  G.TL:OTLW;
  LOOP(C, PUT   "%PRINTSEPARATOR%"  (SUM(IA$ICA(C,IA), VGKN.L(IA,G))):OTLW:0 ;) ;  PUT     "%PRINTSEPARATOR%"  GDATA(G,'GDTYPE'):OTLW:0  "%PRINTSEPARATOR%"  GDATA(G,'GDFUEL'):OTLW:0 /;
   );
);
*              |<------ OTLW characters ----->|
PUT OTLWY.ts  "TOTAL                           " ; LOOP(C, PUT  "%PRINTSEPARATOR%"  (SUM(IA$ICA(C,IA), SUM(G, VGKN.L(IA,G)))):OTLW:0 ;); PUT //;

PUT ///;
