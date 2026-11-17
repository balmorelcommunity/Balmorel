* File: gk_ycg.inc

* Modified last time: 20150422(Weiming)

* This file will print a table containing total capacity including endogenous investments and exogenous capacities.


* -----------------------------------------------------------------------------

PUT gk_ycg;

* First print headings:

if ((gk_ycg.pw LT 32000),
gk_ycg.pw = 32000;
PUT "Version:              " "%PRINTSEPARATOR%" SYSTEM.TITLE /;
PUT "Printed from file:    " "%PRINTSEPARATOR%" "gk_yag.inc" /;
PUT "Time-stamp:           " "%PRINTSEPARATOR%" SYSTEM.DATE " " SYSTEM.TIME  /;
$ifi %BB1%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE1"/;
$ifi %BB2%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE2"/;
$ifi %BB3%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE3"/;
$ifi %BB4%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE4"/;
PUT "Case-identification:  " "%PRINTSEPARATOR%" OCASEID.TS   //;

PUT "Total capacity for each Country and technology, all years in each BB4 model." /;
PUT "Units: "  "MW" //;
);

* End of file headings.
* -----------------------------------------------------------------------------
*PARAMETER OGK_YCG(Y,Y,CCC,G) "Electricity capacity by Country(MW)";

LOOP(IY411FIRST,
GK_YCG.LJ=1;
PUT "BB4 model starting year "  IY411FIRST.TL:4  " ....................................................................:" /;PUT /;
GK_YCG.LJ=2;
  LOOP(IY411,PUT IY411.TL ; PUT /;
    LOOP(C, PUT C.TL:OTLWCRA ; PUT /;

      LOOP(G,
      PUT G.TL:OTLWG;PUT "    ";
      OGK_YCG(IY411FIRST,IY411,C,G)=SUM(IA$ICA(C,IA),VGKNACCUMNET.L(IY411,IA,G)+GKFX(IY411,IA,G));
      PUT OGK_YCG(IY411FIRST,IY411,C,G):40:2 /;
      )
    PUT /;

    );
  PUT /;
  );


);





$ontext


LOOP(IY411FIRST,

PUT "BB4 model starting year "  IY411FIRST.TL:4  " ....................................................................:" /;
LOOP(Y$(IY411PREVY(IY411FIRST,Y)),
  PUT "From previous BB4 model's first year (" Y.TL:4 "), available at beginning of this BB4 model's first year (" IY411FIRST.TL:4 "):" /;
    LOOP((IA,G)$VGKNACCUMNET.L(Y,IA,G),
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

$offtext

* -----------------------------------------------------------------------------
