* File: gkn_ynaf.inc

* Modified last time: 20150430(Weiming)

* This file will print a table containing total capacity including endogenous investments


* -----------------------------------------------------------------------------

PUT gkn_ynaf;

* First print headings:

if ((gkn_ynaf.pw LT 32000),
gkn_ynaf.pw = 32000;
PUT "Version:              " "%PRINTSEPARATOR%" SYSTEM.TITLE /;
PUT "Printed from file:    " "%PRINTSEPARATOR%" "gk_ynaf.inc" /;
PUT "Time-stamp:           " "%PRINTSEPARATOR%" SYSTEM.DATE " " SYSTEM.TIME  /;
$ifi %BB1%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE1"/;
$ifi %BB2%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE2"/;
$ifi %BB3%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE3"/;
$ifi %BB4%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE4"/;
PUT "Case-identification:  " "%PRINTSEPARATOR%" OCASEID.TS   //;

PUT "New investments capacity for aggregated countries by fuel, all years in each BB4 model." /;
PUT "Units: "  "MW" //;
);

* End of file headings.
* -----------------------------------------------------------------------------
*PARAMETER OGKN_YNAF(Y,Y,FFF) "Electricity capacity by aggregated countries(MW)";

LOOP(IY411FIRST,
GKN_YNAF.LJ=1;
PUT "BB4 model starting year "  IY411FIRST.TL:4  " ....................................................................:" /;PUT /;
GKN_YNAF.LJ=2;
  LOOP(IY411,PUT IY411.TL ; PUT /;


      LOOP(FFF,
      PUT FFF.TL:OTLWG;PUT "    ";
      OGKN_YNAF(IY411FIRST,IY411,FFF)=SUM(C,
                                         SUM(IA$ICA(C,IA),
                                                SUM(G$IGF(G,FFF),(VGKN.L(IY411,IA,G)))
                                            )
                                       );
      PUT OGKN_YNAF(IY411FIRST,IY411,FFF):40:2 /;
      )
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
