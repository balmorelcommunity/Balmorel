* File: mpco2_yna.inc

* Modified last time: 20150430(Weiming)

* This file prints the national CO2 emission values



* -----------------------------------------------------------------------------

PUT mpco2_yna;

* First print headings:

if ((mpco2_yna.pw LT 32000),
mpco2_yna.pw = 32000;
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
mpco2_yna.LJ = 1;
PUT "YEAR        " ;
mpco2_yna.LJ = 2; PUT /;

  LOOP(IY411,
    PUT IY411.TL ;

    PUT QLIMCO2NA.M(IY411):OTLWCRA:2;
    PUT /;

  )PUT /;
)

PUT /;






