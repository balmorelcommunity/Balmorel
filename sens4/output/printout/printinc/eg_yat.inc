* File: EG_YAT.INC

* Modified last time: 16.02.2004 (ld), 200804xx(hr),20150313(Weiming)

* This file will print a table containing electricity generation from all
* technologies in each time period in each season in each region.
* (Incl. the negative electricity generation for heat pumps)


* -----------------------------------------------------------------------------

PUT EG_YAT;

* First print headings:

if ((eg_yat.pw LT 32000),
eg_yat.pw = 32000;
PUT "Version:              " "%PRINTSEPARATOR%" SYSTEM.TITLE /;
PUT "File name:            " "%PRINTSEPARATOR%" "eg_gat.out" /;
PUT "Time-stamp:           " "%PRINTSEPARATOR%" SYSTEM.DATE " " SYSTEM.TIME  /;
$ifi %BB1%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE1"/;
$ifi %BB2%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE2"/;
$ifi %BB3%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE3"/;
$ifi %BB4%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE4"/;
PUT "Case-identification:  " "%PRINTSEPARATOR%" OCASEID.TS   //;
PUT '"Electricity production (GWh) on units during each time segment"'//;
);

* End of headings.

* -----------------------------------------------------------------------------

*OEG_YAT(IY411FIRST,IY411,IA,G,S,T)=VGE_T(Y,IA,G,S,T);






LOOP(IY411FIRST,
EG_YAT.LJ = 2;
PUT "BB4 model starting year "  IY411FIRST.TL:4  " ....................................................................:" /;PUT /;
  LOOP(IY411, PUT IY411.TL:4;PUT /;
    LOOP(S,
    PUT S.TL:12;PUT /; FOR(ISCALAR1=1 TO (OTLWG+OTLWCRA+1) BY 1, PUT " ");EG_YAT.LJ = 1; LOOP(T,PUT T.TL:12); PUT /; EG_YAT.LJ = 2;
      LOOP(IA,
        LOOP(G,
        PUT IA.TL:OTLWCRA, "%PRINTSEPARATOR%",G.TL:OTLWG;
          LOOP(T,
          ISCALAR2=VGE_T.L(IY411,IA,G,S,T)*IHOURSINST(S,T)*IOF0001;
          PUT ISCALAR2:12:0;
          );
        PUT /;
        );
      );




    );
  );
);
PUT //;


$ontext
    LOOP(IA,
                                 LOOP(G$IGNOTETOH(G),PUT IA.TL:OTLWCRA, "%PRINTSEPARATOR%",G.TL:OTLWG; PUT /;

                              );


        LOOP(S, PUT S.TL:12;PUT /;
                 FOR(ISCALAR1=1 TO (OTLWG+OTLWCRA+6) BY 1, PUT " ";);
                 LOOP(T,PUT T.TL:OTLWCRA); PUT /;)

                         LOOP(IA,
                                 LOOP(G$IGNOTETOH(G),
                                         PUT IA.TL:OTLWCRA, "%PRINTSEPARATOR%",G.TL:OTLWG,
                                         PUT VGE_T.L(IY411,IA,G,S,T);PUT /;
                                     );
                     );
             );
         );

$offtext









$ontext
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

$offtext
