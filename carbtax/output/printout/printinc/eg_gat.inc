* File: EG_GAT.INC

* Modified last time: 16.02.2004 (ld), 2005.10.29 (hr), 20060328(hr), 200804xx(hr)

* This file will print a table containing electricity generation from all
* technologies in each time period in each season in each region.
* (Incl. the negative electricity generation for heat pumps)


* -----------------------------------------------------------------------------

PUT EG_GAT;

* First print headings:
put / /  "Hallodo"//;

if ((eg_gat.pw LT 32000),
eg_gat.pw = 32000;
PUT "Version:              " "%PRINTSEPARATOR%" SYSTEM.TITLE /;
PUT "File name:            " "%PRINTSEPARATOR%" "eg_gat.out" /;
PUT "Time-stamp:           " "%PRINTSEPARATOR%" SYSTEM.DATE " " SYSTEM.TIME  /;
$ifi %BB1%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE1"/;
$ifi %BB2%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE2"/;
$ifi %BB3%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE3"/;
PUT "Case-identification:  " "%PRINTSEPARATOR%" OCASEID.TS   //;
PUT '"Electricity production (MWh and MW) on units during each time segment"'//;
);

* End of headings.

* -----------------------------------------------------------------------------


PUT '"Electricity production (MWh) on units during each time segment:"'//;
EG_GAT.LJ = 2;
PUT  "    "; put OTLW.TS  OTLW.TS;
EG_GAT.LJ = 1;
LOOP(S, OSCALAR1=0;  PUT S.TL:12;
   LOOP(T, IF((OSCALAR1 GT 0), PUT "            " ); OSCALAR1=1) PUT "   "); PUT /;
PUT Y.TL:4 "";  put OTLW.TS   OTLW.TS;
LOOP(S,  LOOP(T, PUT T.TL:12 ) PUT "   "); PUT /;

LOOP(IA,
EG_GAT.LJ = 2;
LOOP(G,
IF(IGNOTETOH(G),
IF((EGqAY(IA,G) NE 0),
  PUT IA.TL:OTLW  G.TL:OTLW
  LOOP(S,
  LOOP(T,
     PUT EGqAT(IA,G,S,T):12:0;
) PUT "   "; );  PUT /;
)
Else
IF((EGqAY(IA,G) NE 0),
  PUT IA.TL:OTLW  G.TL:OTLW
  LOOP(S,
  LOOP(T,
    PUT (-EGqAT(IA,G,S,T)):12:0
) PUT "   "; );  PUT /;
)
)
))
PUT //;


PUT '"Electricity production (MW) on units during each time segment:"'//;
EG_GAT.LJ = 2;
PUT  "    "; put OTLW.TS  OTLW.TS;
EG_GAT.LJ = 1;
LOOP(S, OSCALAR1=0;  PUT S.TL:12;
   LOOP(T, IF((OSCALAR1 GT 0), PUT "            " ); OSCALAR1=1) PUT "   "); PUT /;
PUT Y.TL:4 ""   OTLW.TS   OTLW.TS;
LOOP(S,  LOOP(T, PUT T.TL:12 ) PUT "   "); PUT /;


LOOP(IA,
EG_GAT.LJ = 2;
LOOP(G,
IF(IGNOTETOH(G),
IF(( sum((S,T),vge_t.L(ia,g,S,t)) NE 0),
  PUT IA.TL:OTLW  G.TL:OTLW
  LOOP(S,
  LOOP(T,
    PUT ( EGqAT(IA,G,S,T)/ihoursinst(S,t)    ):12:0
) PUT "   "; );  PUT /;
)
ELSE
IF(( sum((S,T),vge_t.L(ia,g,S,t)) NE 0),
  PUT IA.TL:OTLW  G.TL:OTLW
  LOOP(S,
  LOOP(T,
    PUT ( -EGqAT(IA,G,S,T)/ihoursinst(S,t)    ):12:0
) PUT "   "; );  PUT /;
)

)
))
PUT //;
put "''''''''"//;

loop(ia, loop(igwnd,
 put ia.tl igwnd.tl vgkn.l(ia,igwnd), vgkn.m(ia,igwnd) /;
));
