* File: EP_YRT.INC

* Modified last time: 08-03-2002 by (mhd), ... ,  20150130(hr),20150311(Weiming)

* This file will print a table containing the marginal electricity generation
* price by (R,S,T). This quantity is here derived as
* the marginal value (shadow price) to equation QEEQ.


* -----------------------------------------------------------------------------

PUT EP_YRT;

* First print headings:

if ((ep_yrt.pw LT 32000),
ep_yrt.pw = 32000;
PUT "Version:              " "%PRINTSEPARATOR%" SYSTEM.TITLE /;
PUT "Printed from file:    " "%PRINTSEPARATOR%" "ep_yrt.inc" /;
PUT "Time-stamp:           " "%PRINTSEPARATOR%" SYSTEM.DATE " " SYSTEM.TIME  /;
$ifi %BB1%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE1"/;
$ifi %BB2%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE2"/;
$ifi %BB3%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE3"/;
$ifi %BB4%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE4"/;
PUT "Case-identification:  " "%PRINTSEPARATOR%" OCASEID.TS   //;

PUT "Electricity price for each (S,T) - each Region, all years in each BB4 model." /;
PUT "Currency: " OMONEY.TS "  with exchange rate to input currency: "  OMONEY:7:3  " ("OMONEY.TS"/"OIMONEY.TS").";
PUT "   (The output currency and its relation to input currency is specified in input data file OMONEY.inc. The input currency is specified in file print1.inc.)" /;
PUT "Units: "; PUT OMONEY.ts "/MWh" //;
$ifi %BB4%==yes PUT "Electricity prices are in undiscounted values." //;
);

* End of file headings.
* ------------------------------------------------------------------------------------
* If scenarios (i.e., more than base case) print scenario heading:
* ------------------------------------------------------------------------------------
                                                                                          
* -----------------------------------------------------------------------------

OEP_YRT(IY411FIRST,IY411,IR,S,T) = OMONEY*IOF1_*QEEQ.M(IY411,IR,S,T)/(IHOURSINST(S,T)*IDISCOUNTFACTOR(IY411)*IWEIGHTY(IY411));

LOOP(IY411FIRST,
PUT "BB4 model starting year "  IY411FIRST.TL:4 "..............................:" //;
LOOP(IY411,
LOOP(IR,
  EP_YRT.LJ = 2;
  PUT  IY411.TL:9:0; PUT IR.TL:OTLWCRA;
  EP_YRT.LJ = 1;
  LOOP(T, PUT T.TL:12 ); PUT /;
    LOOP(S,
      FOR(ISCALAR1=1 TO (OTLWCRA-3) BY 1, PUT " ";);
      PUT S.TL:12;
      LOOP(T,
        PUT OEP_YRT(IY411FIRST,IY411,IR,S,T):12:4
      )
      PUT /;
    );PUT /;
) PUT //;
) PUT //;
);
