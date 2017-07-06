* File: EP_RT.INC

* Modified last time: 08-03-2002 by (mhd), 16-02-2004 (ld), 2005.10.29 (hr), 20060328(hr), 20080305(hr)

* This file will print a table containing the marginal electricity generation
* price by (R,S,T). This quantity is here derived as the marginal
* value (shadow price) to equation QEEQ.
* The output will not print nicely if CARD(T) is large.

* -----------------------------------------------------------------------------

PUT EP_RT;

* First print headings:

if ((ep_rt.pw LT 32000),
ep_rt.pw = 32000;
PUT "Version:              " "%PRINTSEPARATOR%" SYSTEM.TITLE /;
PUT "File name:            " "%PRINTSEPARATOR%" "ep_rt.out" /;
PUT "Time-stamp:           " "%PRINTSEPARATOR%" SYSTEM.DATE " " SYSTEM.TIME  /;
$ifi %BB1%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE1"/;
$ifi %BB2%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE2"/;
$ifi %BB3%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE3"/;
PUT "Case-identification:  " "%PRINTSEPARATOR%" OCASEID.TS   //;

PUT "Electricity price for each S and T" /;
PUT "Currency: " OMONEY.TS "  with exchange rate to input currency: "  OMONEY:7:3  " ("OMONEY.TS"/"OIMONEY.TS")." /;
PUT "Units: "; PUT OMONEY.ts "/MWh" //;
);

* End of file headings.
* ------------------------------------------------------------------------------------
* If scenarios (i.e., more than base case) print scenario heading:
* ------------------------------------------------------------------------------------

* -----------------------------------------------------------------------------


LOOP(IR,
EP_RT.LJ = 2;
  PUT  Y.TL:6:0 "   "; PUT IR.TL:12;
EP_RT.LJ = 1;
LOOP(T, PUT T.TL:12 ); PUT /;

  LOOP(S,
    PUT "         " S.TL:12  ;
      LOOP(T,
        PUT (OMONEY*IOF1_*QEEQ.M(IR,S,T)/IHOURSINST(S,T)):12:4
)
    PUT /; ) PUT /;
) PUT //;
