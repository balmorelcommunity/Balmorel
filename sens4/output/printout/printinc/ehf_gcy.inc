* File: ehf_gcy.inc

* Modified last time: 01-02-2002 (rus), 16-02-2004 (sns,ld), 20060328(hr), 20110508(hr)

* This file will print a table containing annnual fuel consumption by technologies and countries.



* -----------------------------------------------------------------------------

PUT ehf_gcy;

* First print headings:

if ((ehf_gcy.pw LT 32000),
ehf_gcy.pw = 32000;
PUT "Version:              " "%PRINTSEPARATOR%" SYSTEM.TITLE /;
PUT "File name:            " "%PRINTSEPARATOR%" "ehf_gcy.out" /;
PUT "Time-stamp:           " "%PRINTSEPARATOR%" SYSTEM.DATE " " SYSTEM.TIME  /;
$ifi %BB1%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE1"/;
$ifi %BB2%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE2"/;
$ifi %BB3%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE3"/;
PUT "Case-identification:  " "%PRINTSEPARATOR%" OCASEID.TS   /;

$ifi %BB1%==yes PUT / "Annual fuel consumption by technologies and countries, old technologies." //;
$ifi %BB2%==yes PUT / "Annual fuel consumption by technologies and countries, old plus new technologies." //;
$ifi %BB3%==yes PUT / "Annual fuel consumption by technologies and countries, old technologies." //;


PUT "Units: GWh" //;

);

* End of file headings.
* ------------------------------------------------------------------------------------

* -----------------------------------------------------------------------------

ehf_gcy.LJ = 1;
PUT Y.TL:OTLWY   OTLW.ts  ; LOOP(C, PUT "%PRINTSEPARATOR%" C.TL:OTLW) ;
*                         |<------ OTLW characters ----->|                        |<------ OTLW characters ----->|
PUT  "%PRINTSEPARATOR%"  "                 Technology type"  "%PRINTSEPARATOR%"  "                            Fuel" /;
ehf_gcy.LJ = 2;

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
