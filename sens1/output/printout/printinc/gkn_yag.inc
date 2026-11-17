* File: gkn_yag.inc

* Modified last time: 20150214(hr)

* This file will print a table containing endogenous investments.


* -----------------------------------------------------------------------------

PUT gkn_yag;

* First print headings:

if ((gkn_yag.pw LT 32000),
gkn_yag.pw = 32000;
PUT "Version:              " "%PRINTSEPARATOR%" SYSTEM.TITLE /;
PUT "Printed from file:    " "%PRINTSEPARATOR%" "gkn_yag.inc" /;
PUT "Time-stamp:           " "%PRINTSEPARATOR%" SYSTEM.DATE " " SYSTEM.TIME  /;
$ifi %BB1%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE1"/;
$ifi %BB2%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE2"/;
$ifi %BB3%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE3"/;
$ifi %BB4%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE4"/;
PUT "Case-identification:  " "%PRINTSEPARATOR%" OCASEID.TS   //;

PUT "Endogenous investments for each Area and technology, all years in each BB4 model." /;
PUT "Units: "  "MW" //;
);

* End of file headings.
* -----------------------------------------------------------------------------


* OGKN_YYAG(IY411FIRST,IY411,IA,G)         = VGKN.L(IY411,IA,G);         !! Mainly for debugging. Comment in to see the values in Balmorel.lst. Declared in print1.inc.
* OGKNACCUMNET_YYAG(IY411FIRST,IY411,IA,G) = VGKNACCUMNET.L(IY411,IA,G); !! Mainly for debugging. Comment in to see the values in Balmorel.lst. Declared in print1.inc.* option  VGKN:3:0:1,  OGKN_YYAG:3:0:1 , VGKNACCUMNET:3:0:1,  OGKNACCUMNET_YYAG:3:0:1;
* display "printfil",IY411FIRST ,VGKN.L,  OGKN_YYAG ,OGKNACCUMNET_YAG, VGKNACCUMNET.L,  OGKNACCUMNET_YYAG;

LOOP(IY411FIRST,

PUT "BB4 model starting year "  IY411FIRST.TL:4  " ....................................................................:" /;
LOOP(Y$(IY411PREVY(IY411FIRST,Y)),
  PUT "From previous BB4 model's first year (" Y.TL:4 "), available at beginning of this BB4 model's first year (" IY411FIRST.TL:4 "):" /;
    LOOP((IA,G)$VGKNACCUMNET.L(Y,IA,G),
* Weiming: check this
    PUT "      ", "%PRINTSEPARATOR%", IA.TL:OTLWCRA, "%PRINTSEPARATOR%",   G.TL:OTLWG, "%PRINTSEPARATOR%", "%PRINTSEPARATOR%", VGKNACCUMNET.L(Y,IA,G):40:2 /;
  );
  PUT /;
);

PUT "%PRINTSEPARATOR%", "%PRINTSEPARATOR%", "%PRINTSEPARATOR%", "                                                       This year's investment",  "%PRINTSEPARATOR%" ,"       Accumulated at end of year" /;
*PUT  "                                                     This year's investment"  "%PRINTSEPARATOR%", "       Accumulated at end of year" /;
LOOP(IY411,
  PUT IY411.TL:6, "%PRINTSEPARATOR%",  "%PRINTSEPARATOR%", "%PRINTSEPARATOR%", "%PRINTSEPARATOR%" /;
    LOOP((IA,G)$VGKNACCUMNET.L(IY411,IA,G),
      PUT "      ", "%PRINTSEPARATOR%", IA.TL:OTLWCRA, "%PRINTSEPARATOR%",  G.TL:OTLWG, "%PRINTSEPARATOR%", VGKN.L(IY411,IA,G):20:2 "%PRINTSEPARATOR%", VGKNACCUMNET.L(IY411,IA,G):20:2 /;
    );
);PUT /;


);PUT /;

* -----------------------------------------------------------------------------
