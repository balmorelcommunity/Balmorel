* File EPNXT_RT.INC

* Modified last time: 17-03-2003 (hrv), 16-02-2004 (ld), 2005.10.29 (hr), 20060328(hr), 20080305(hr)

* This file prints the marginal cost of electricity generation of 'the next' unit in each region.
* This means... (explanation avaiting .. )
* The file contains printing at regional level.
* The file contains priting of values at time segment (S,T) level.

* -----------------------------------------------------------------------------

PUT EPNXT_RT;

* First print headings:

if ((epnxt_rt.pw LT 32000),
epnxt_rt.pw = 32000;
PUT "Version:              " "%PRINTSEPARATOR%" SYSTEM.TITLE /;
PUT "File name:            " "%PRINTSEPARATOR%" "epnxt_rt.out" /;
PUT "Time-stamp:           " "%PRINTSEPARATOR%" SYSTEM.DATE " " SYSTEM.TIME  /;
$ifi %BB1%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE1"/;
$ifi %BB2%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE2"/;
$ifi %BB3%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE3"/;
PUT "Case-identification:  " "%PRINTSEPARATOR%" OCASEID.TS   //;

PUT "Marginal electricity generation cost of 'the next' unit." /
PUT "Currency: " OMONEY.TS "  with exchange rate to input currency: "  OMONEY:7:3  " ("OMONEY.TS"/EUR90)." /;
PUT "The output of the table is in (" OMONEY.ts "/MWh)" //;

);

* End of file headings.
* ------------------------------------------------------------------------------------

* -----------------------------------------------------------------------------

PUT "The marginal cost of electricity generation of 'the next' unit in " /;
PUT "each region. If the marginal unit is the most expensive one, the " /;
PUT "marginal cost of this one is shown, marked with a '*'. " //;

LOOP(IR,
  PUT  Y.TL:6:0 "   "; PUT IR.TL  /;
  LOOP(S,
    PUT "    Season  " S.TL:12  ;     LOOP(T, PUT T.TL:12 );   PUT /;
    PUT "               " ;
    LOOP(T,
      OSCALAR1 = INF;
      OSCALAR2 = QEEQ.M(IR,S,T);

      LOOP(IA$RRRAAA(IR,IA),
        LOOP(IGEE$((IGKVACCTOY(IA,IGEE) + IGKFX_Y(IA,IGEE) + VGKN.L(IA,IGEE)) GT 0),
          IF(((VGE_T.M(IA,IGEE,S,T) GT 0) OR (VGEN_T.M(IA,IGEE,S,T) GT 0)),
            IF(((VGE_T.M(IA,IGEE,S,T) LT OSCALAR1) AND (VGE_T.M(IA,IGEE,S,T) GT 0)),
              OSCALAR1=VGE_T.M(IA,IGEE,S,T);
            );
            IF(((VGEN_T.M(IA,IGEE,S,T) LT OSCALAR1) AND (VGEN_T.M(IA,IGEE,S,T) GT 0)),
              OSCALAR1=VGEN_T.M(IA,IGEE,S,T);
            );
          );
        );
      );

      IF((OSCALAR1 LT INF),
        PUT (OMONEY*IOF1_*( OSCALAR1 + OSCALAR2 )/(IHOURSINST(S,T))):11:3 " "
      ELSE
        PUT (OMONEY*IOF1_*( OSCALAR2 )/(IHOURSINST(S,T))):11:3 "*" ;
      );
    );
    PUT /;
  );
);
PUT //;





$ONTEXT  This part is not intended for printing, but may be printed for control.
PUT "............................................................................"/;
PUT "Details begin ... (This part is not intended for normal printing ...) " Y.TL /;
LOOP((S,T),
  PUT S.TL T.TL ":"/;
  LOOP(IR,
    PUT IR.TL /;
    PUT "Marginal cost of region's electricity production: "
        (OMONEY*1e6*QEEQ.M(IR,S,T)/(IDAYSIN_S(S)*IHOURSIN24(T))):12:3  /;
    PUT "Unit's marginal relative generation cost (MRGC),"
        "  unit's MRGC+region's 'electricity price',  unit's generation "
        "  and unit's derated capacity ":/;
    LOOP(IA$RRRAAA(IR,IA),
      LOOP(IGEE$((IGKVACCTOY(IA,IGEE) + IGKFX_Y(IA,IGEE) + VGKN.L(IA,IGEE)) GT 0),
        PUT IGEE.TL
            (OMONEY*IOF1_*(MAX(VGE_T.M(IA,IGEE,S,T),VGEN_T.M(IA,IGEE,S,T)))/(IDAYSIN_S(S)*IHOURSIN24(T))):12:3
            (OMONEY*IOF1_*((MAX(VGE_T.M(IA,IGEE,S,T),VGEN_T.M(IA,IGEE,S,T)))+QEEQ.M(IR,S,T))/(IDAYSIN_S(S)*IHOURSIN24(T))):12:3
            (VGE_T.L(IA,IGEE,S,T)+VGEN_T.L(IA,IGEE,S,T)):12:3
             ((IGKVACCTOY(IA,IGEE) + IGKFX_Y(IA,IGEE) + VGKN.L(IA,IGEE))*(1-GKDERATE(IGEE,IA,S))):12:3;
        PUT /;
      )
    )
  )
  PUT /;
);

PUT "Details end " Y.TL /;
PUT ".........................................................................."//;
$OFFTEXT  End of 'This part is not intended for printing, but may be printed for control.'
