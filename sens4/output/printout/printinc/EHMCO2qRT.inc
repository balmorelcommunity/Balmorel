* File: EHMCO2qRT.INC

* Modified last time: 20150620 (ap)

* This file will print a table containing the total CO2 emissions by (R,S,T).
* The output will not print nicely if CARD(T) is large.

* -----------------------------------------------------------------------------

PUT EHMCO2qRT;

* First print headings:

if ((EHMCO2qRT.pw LT 32000),
EHMCO2qRT.pw = 32000;
PUT "Version:              " "%PRINTSEPARATOR%" SYSTEM.TITLE /;
PUT "File name:            " "%PRINTSEPARATOR%" "ep_rt.out" /;
PUT "Time-stamp:           " "%PRINTSEPARATOR%" SYSTEM.DATE " " SYSTEM.TIME  /;
$ifi %BB1%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE1"/;
$ifi %BB2%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE2"/;
$ifi %BB3%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE3"/;
PUT "Case-identification:  " "%PRINTSEPARATOR%" OCASEID.TS   //;

PUT "Emissions to satisfy all the energy demand in a given region" /;
PUT "Units:    ton CO2/h" //;
);

* End of file headings.
* ------------------------------------------------------------------------------------
* If scenarios (i.e., more than base case) print scenario heading:
* ------------------------------------------------------------------------------------

* -----------------------------------------------------------------------------


LOOP(IR,
EHMCO2qRT.LJ = 2;
  PUT  Y.TL:6:0 "   "; PUT IR.TL:12;
EHMCO2qRT.LJ = 1;
LOOP(T, PUT T.TL:12 ); PUT /;

  LOOP(S,
    PUT "         " S.TL:12  ;
      LOOP(T,
        PUT (IOF0001*EHM1qRT(IR,S,T)))
    PUT /; ) PUT /;
) PUT //;
