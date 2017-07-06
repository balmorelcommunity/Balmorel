* File: ehf_fcy.inc

* Modified last time: 01-02-2002 (rus), 16-02-2004 (sns,ld),  20060328(hr), 20110508(hr)

* This file will print a table containing annual fuel consumption by (FFF,C)




* -----------------------------------------------------------------------------

PUT ehf_fcy;

* First print headings:

if ((ehf_fcy.pw LT 32000),
ehf_fcy.pw = 32000;

PUT "Version:              " "%PRINTSEPARATOR%" SYSTEM.TITLE /;
PUT "File name:            " "%PRINTSEPARATOR%" "ehf_fcy.out" /;
PUT "Time-stamp:           " "%PRINTSEPARATOR%" SYSTEM.DATE " " SYSTEM.TIME  /;
$ifi %BB1%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE1"/;
$ifi %BB2%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE2"/;
$ifi %BB3%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE3"/;
PUT "Case-identification:  " "%PRINTSEPARATOR%" OCASEID.TS   //;

$ifi %BB1%==yes PUT / "Annual fuel consumption by fuels and countries, old plus." //;
$ifi %BB2%==yes PUT / "Annual fuel consumption by fuels and countries, old plus new technologies." //;
$ifi %BB3%==yes PUT / "Annual fuel consumption by fuels and countries, old plus." //;

PUT "Units: GWh" //;

);

* End of file headings.
* ------------------------------------------------------------------------------------

* -----------------------------------------------------------------------------

ehf_fcy.LJ = 1;
PUT Y.TL:OTLWY   OTLW.ts  ; LOOP(C, PUT "%PRINTSEPARATOR%" C.TL:OTLW) ; PUT /;
ehf_fcy.LJ = 2;

LOOP(FFF,

  PUT  PUT OTLWY.ts FFF.TL:OTLW ;
  LOOP(C,
   OSCALAR1=0;
*  LOOP(ignotetoh$(GDATA(ignotetoh,'GDFUEL') EQ FDATA(FFF,'FDNB')),  OSCALAR1=OSCALAR1 + EHFqCY(C,ignotetoh) );
   LOOP(ignotetoh$IGF(ignotetoh,FFF),  OSCALAR1=OSCALAR1 + EHFqCY(C,ignotetoh) );
*  LOOP(igetoh$(GDATA(igetoh,'GDFUEL') EQ FDATA(FFF,'FDNB')),        OSCALAR1=OSCALAR1 + EHFqCY(C,igetoh) );
   LOOP(igetoh$IGF(igetoh,FFF),        OSCALAR1=OSCALAR1 + EHFqCY(C,igetoh) );
   PUT  "%PRINTSEPARATOR%" (OSCALAR1 *IOF0001):OTLW:0 ;
  ) ;
  PUT   /;
 );
PUT /;
