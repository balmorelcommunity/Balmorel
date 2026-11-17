* File: ehf_gry.inc

* Modified last time: 01-02-2002 (rus), 16-02-2004 (sns,ld), 20060328(hr), 20110508(hr)

* This file will print a table containing annnual fuel consumption on technologies in regions.



* -----------------------------------------------------------------------------

PUT ehf_gry;

* First print headings:

if ((ehf_gry.pw LT 32000),
ehf_gry.pw = 32000;

PUT "Version:              " "%PRINTSEPARATOR%" SYSTEM.TITLE /;
PUT "File name:            " "%PRINTSEPARATOR%" "ehf_gry.out" /;
PUT "Time-stamp:           " "%PRINTSEPARATOR%" SYSTEM.DATE " " SYSTEM.TIME  /;
$ifi %BB1%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE1"/;
$ifi %BB2%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE2"/;
$ifi %BB3%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE3"/;
PUT "Case-identification:  " "%PRINTSEPARATOR%" OCASEID.TS   //;

$ifi %BB1%==yes PUT / "Annual fuel consumption by technologies and regions." //;
$ifi %BB2%==yes PUT / "Annual fuel consumption by technologies and regions, old plus new technologies." //;
$ifi %BB3%==yes PUT / "Annual fuel consumption by technologies and regions." //;


PUT "Units: GWh" //;

);

* End of file headings.

* ------------------------------------------------------------------------------------

* -----------------------------------------------------------------------------

ehf_gry.LJ = 1;
PUT Y.TL:OTLWY   OTLW.ts  ; LOOP(IR, PUT "%PRINTSEPARATOR%" IR.TL:OTLW) ;
*                         |<------ OTLW characters ----->|                        |<------ OTLW characters ----->|
PUT  "%PRINTSEPARATOR%"  "                 Technology type"  "%PRINTSEPARATOR%"  "                            Fuel" /;
ehf_gry.LJ = 2;

LOOP(ignotetoh,

if( sum(IR,EHFqRY(IR,ignotetoh)) ne 0,

  PUT OTLWY.ts ignotetoh.TL:OTLW ;
  LOOP(IR, PUT  "%PRINTSEPARATOR%" (EHFqRY(IR,ignotetoh) *IOF0001):OTLW:0);   PUT  "%PRINTSEPARATOR%" GDATA(ignotetoh,'GDTYPE'):OTLW:0  "%PRINTSEPARATOR%"  GDATA(ignotetoh,'GDFUEL'):OTLW:0     /;  );
);



LOOP(igetoh,

if( sum(IR,EHFqRY(IR,igetoh)) ne 0,

  PUT  OTLWY.ts igetoh.TL:OTLW ;
  LOOP(IR, PUT  "%PRINTSEPARATOR%" (EHFqRY(IR,igetoh) *IOF0001):OTLW:0);   PUT  "%PRINTSEPARATOR%" GDATA(igetoh,'GDTYPE'):OTLW:0  "%PRINTSEPARATOR%"  GDATA(igetoh,'GDFUEL'):OTLW:0     /;  );
);


PUT /;
