* File: mpco2_yc.inc

* Modified last time: 20150422(Weiming)

* This file prints the national CO2 emission values



* -----------------------------------------------------------------------------

PUT mpco2_yc;

* First print headings:

if ((mpco2_yc.pw LT 32000),
mpco2_yc.pw = 32000;
PUT "Version:              " "%PRINTSEPARATOR%" SYSTEM.TITLE /;
PUT "File name:            " "%PRINTSEPARATOR%" "mpco2_yc.out" /;
PUT "Time-stamp:           " "%PRINTSEPARATOR%" SYSTEM.DATE " " SYSTEM.TIME  /;
$ifi %BB1%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE1"/;
$ifi %BB2%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE2"/;
$ifi %BB3%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE3"/;
$ifi %BB4%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE4"/;
PUT "Case-identification:  " "%PRINTSEPARATOR%" OCASEID.TS   //;

PUT "CO2 shadowprice (RMB/ton)" //;



);

* End of file headings.
* ------------------------------------------------------------------------------------

* -----------------------------------------------------------------------------
LOOP(IY411FIRST,
PUT "BB4 model starting year "  IY411FIRST.TL:4 "..............................:" //;
mpco2_yc.LJ = 1;
PUT "YEAR        " ; LOOP(C, PUT C.TL:OTLWCRA); PUT /;
mpco2_yc.LJ = 2;
  LOOP(IY411,
    PUT IY411.TL ;

       LOOP(C,
       PUT QLIMCO2.M(IY411,C):OTLWCRA:2;

       )PUT /;
  )PUT /;
)








