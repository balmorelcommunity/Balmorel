* File: hp_yat.INC

* Modified last time: 20150311(Weiming)

* This file will print a table containing the marginal heat generation
* price by (A,S,T). This quantity is here derives as the marginal
* value (shadow price) to equation QHEQ.
* The output will not print nicely if CARD(T) is large.

* -----------------------------------------------------------------------------


PUT HP_YAT;

* First print headings:

if ((hp_yat.pw LT 32000),
hp_yat.pw = 32000;
PUT "Version:              " "%PRINTSEPARATOR%" SYSTEM.TITLE /;
PUT "File name:            " "%PRINTSEPARATOR%" "hp_yat.out" /;
PUT "Time-stamp:           " "%PRINTSEPARATOR%" SYSTEM.DATE " " SYSTEM.TIME  /;
$ifi %BB1%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE1"/;
$ifi %BB2%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE2"/;
$ifi %BB3%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE3"/;
$ifi %BB4%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE4"/;
PUT "Case-identification:  " "%PRINTSEPARATOR%" OCASEID.TS   //;

PUT "Heat price for each (S,T) - each Region, all years in each BB4 model." /;
PUT "Currency: " OMONEY.TS "  with exchange rate to input currency: "  OMONEY:7:3  " ("OMONEY.TS"/"OIMONEY.TS")." /;
PUT "Units: "; PUT OMONEY.ts "/MWh" //;
$ifi %BB4%==yes PUT "Heat prices are in undiscounted values." //;
);

* End of file headings.
* ------------------------------------------------------------------------------------
* ------------------------------------------------------------------------------------

* -----------------------------------------------------------------------------
* ------------------------------------------------------------------------------
OHP_YAT(IY411FIRST,IY411,IA,S,T) = OMONEY*IOF1_*QHEQ.M(IY411,IA,S,T)/(IHOURSINST(S,T)*IDISCOUNTFACTOR(IY411)*IWEIGHTY(IY411));

LOOP(IY411FIRST,
PUT "BB4 model starting year "  IY411FIRST.TL:4 "..............................:" //;
LOOP(IY411,
LOOP(IA,
  LOOP(DHUSER,
  HP_YAT.LJ = 2;
  PUT  IY411.TL:9:0; PUT IA.TL:OTLWCRA;
  HP_YAT.LJ = 1;
  LOOP(T, PUT T.TL:12 ); PUT /;
    LOOP(S,
      FOR(ISCALAR1=1 TO (OTLWCRA-3) BY 1, PUT " ";);
      PUT S.TL:12;
      LOOP(T,
         IF(IDH_T(IY411,IA,DHUSER,S,T),
            PUT OHP_YAT(IY411FIRST,IY411,IA,S,T):12:4;
        ELSE
           PUT " '(No dem.)'";
           )
      )
      PUT /;
    );PUT /;
) PUT //;
) PUT //;
) PUT //;
);


