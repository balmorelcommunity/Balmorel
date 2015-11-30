* File: ehf_gay.inc

* Modified last time: 01-02-2002 (rus), 16-02-2004 (ld), 20060328(hr), 20110508(hr)

* This file will print a table containing annnual fuel consumption by technologies and areas.

* -----------------------------------------------------------------------------

PUT ehf_gay;

* First print headings:

if ((ehf_gay.pw LT 32000),
ehf_gay.pw = 32000;
PUT "Version:              " "%PRINTSEPARATOR%" SYSTEM.TITLE /;
PUT "File name:            " "%PRINTSEPARATOR%" "ehf_gay.out" /;
PUT "Time-stamp:           " "%PRINTSEPARATOR%" SYSTEM.DATE " " SYSTEM.TIME  /;
$ifi %BB1%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE1"/;
$ifi %BB2%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE2"/;
$ifi %BB3%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE3"/;
PUT "Case-identification:  " "%PRINTSEPARATOR%" OCASEID.TS   //;

$ifi %BB1%==yes PUT / "Annual fuel consumption by technologies and areas, old technologies." //;
$ifi %BB2%==yes PUT / "Annual fuel consumption by technologies and areas, old plus new technologies." //;
$ifi %BB3%==yes PUT / "Annual fuel consumption by technologies and areas, old technologies." //;

PUT "Units: GWh" //;

);

* End of file headings.


* -----------------------------------------------------------------------------

ehf_gay.LJ = 1;
PUT Y.TL:OTLWY   OTLW.ts  ; LOOP(IA, PUT "%PRINTSEPARATOR%" IA.TL:OTLW) ;
*                         |<------ OTLW characters ----->|                        |<------ OTLW characters ----->|
PUT  "%PRINTSEPARATOR%"  "                 Technology type"  "%PRINTSEPARATOR%"  "                            Fuel" /;

ehf_gay.LJ = 2;

LOOP(ignotetoh,

if( sum(IA,EHFqAY(IA,ignotetoh)) ne 0,

*  PUT ignotetoh.TL:12 ;
*  LOOP(IA, PUT (EHFqAY(IA,ignotetoh) *IOF0001):12:0 ;) ;
*   PUT /; );
  PUT OTLWY.ts ignotetoh.TL:OTLW ;
  LOOP(IA, PUT  "%PRINTSEPARATOR%" (EHFqAY(IA,ignotetoh) *IOF0001):OTLW:0);   PUT  "%PRINTSEPARATOR%" GDATA(ignotetoh,'GDTYPE'):OTLW:0  "%PRINTSEPARATOR%"  GDATA(ignotetoh,'GDFUEL'):OTLW:0     /;  );
 );

LOOP(igetoh,

if( sum(IA,EHFqAY(IA,igetoh)) ne 0,

*  PUT igetoh.TL:12 ;
*  LOOP(IA, PUT (EHFqAY(IA,igetoh) *IOF0001):12:0 ;) ;
*   PUT /; );
  PUT  OTLWY.ts igetoh.TL:OTLW ;
  LOOP(IA, PUT  "%PRINTSEPARATOR%" (EHFqaY(IA,igetoh) *IOF0001):OTLW:0);   PUT  "%PRINTSEPARATOR%" GDATA(igetoh,'GDTYPE'):OTLW:0  "%PRINTSEPARATOR%"  GDATA(igetoh,'GDFUEL'):OTLW:0     /;  );


 );

PUT /;
                /*

PUT Y.TL:OTLWY   OTLW.ts  ; LOOP(C, PUT "%PRINTSEPARATOR%" C.TL:OTLW) ;
*                         |<------ OTLW characters ----->|                        |<------ OTLW characters ----->|
PUT  "%PRINTSEPARATOR%"  "                 Technology type"  "%PRINTSEPARATOR%"  "                            Fuel" /;
ehf_cy.LJ = 2;

LOOP(ignotetoh,

if( sum(C,EHFqCY(C,ignotetoh)) ne 0,

  PUT OTLWY.ts ignotetoh.TL:OTLW ;
  LOOP(C, PUT  "%PRINTSEPARATOR%" (EHFqCY(C,ignotetoh) *IOF0001):OTLW:0);   PUT  "%PRINTSEPARATOR%" GDATA(ignotetoh,'GDTYPE'):OTLW:0  "%PRINTSEPARATOR%"  GDATA(ignotetoh,'GDFUEL'):OTLW:0     /;  );
 );

LOOP(igetoh,

if( sum(C,EHFqCY(C,igetoh)) ne 0,

  PUT  OTLWY.ts igetoh.TL:OTLW ;
  LOOP(C, PUT  "%PRINTSEPARATOR%" (EHFqCY(C,igetoh) *IOF0001):OTLW:0);   PUT  "%PRINTSEPARATOR%" GDATA(igetoh,'GDTYPE'):OTLW:0  "%PRINTSEPARATOR%"  GDATA(igetoh,'GDFUEL'):OTLW:0     /;  );
 );

PUT /;
                   */
