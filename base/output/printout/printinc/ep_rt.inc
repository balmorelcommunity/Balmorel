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
PUT "Version:              " SYSTEM.TITLE /;
PUT "File name:            EP_RT.OUT" /;
PUT "Time-stamp:          '" SYSTEM.DATE " " SYSTEM.TIME "'" /;
PUT "Case-identification: '" OCASEID.TS "'" //;

PUT "Electricity generation price for each S and T" /;
PUT "Currency: " OMONEY.TS "  with exchange rate to input currency: "  OMONEY:7:3  " ("OMONEY.TS"/EUR90)." /;
PUT "Units: "; PUT OMONEY.ts "/MWh" //;
);

* End of file headings.
* ------------------------------------------------------------------------------------
* If scenarios (i.e., more than base case) print scenario heading:
IF((CARD(SCENARIO) GT 1),
PUT /"*==============================================================================="/;
PUT "*       "   SCENARIO.TL "      " SCENARIO.TE(SCENARIO) /;
PUT "*==============================================================================="//;
);
* End of scenario heading
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