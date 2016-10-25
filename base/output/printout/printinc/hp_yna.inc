* File hp_yna.inc.

* Modified last time: 20150422(Weiming)

* This file will print a table containing
* the annual weighted average marginal heat generation price by C.



* -----------------------------------------------------------------------------

PUT hp_yna;

* First print headings:

if ((hp_yna.pw LT 32000),
hp_yna.pw = 32000;
PUT "Version:              " "%PRINTSEPARATOR%" SYSTEM.TITLE /;
PUT "File name:            " "%PRINTSEPARATOR%" "hp_ay.out" /;
PUT "Time-stamp:           " "%PRINTSEPARATOR%" SYSTEM.DATE " " SYSTEM.TIME  /;
$ifi %BB1%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE1"/;
$ifi %BB2%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE2"/;
$ifi %BB3%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE3"/;
$ifi %BB4%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE4"/;

PUT "Case-identification:  " "%PRINTSEPARATOR%" OCASEID.TS   //;

PUT "Annual average heat price., in each BB4 model" /;
PUT "Currency: " OMONEY.TS "  with exchange rate to input currency: "  OMONEY:7:3  " ("OMONEY.TS"/"OIMONEY.TS")." /;
PUT "Units: "; PUT OMONEY.ts "/MWh" //;
$ifi %BB4%==yes PUT "Heat prices are in undiscounted values." //;

PUT "Annual average heat price, weighted by production quantity: NOT IMPLEMENTED YET"/;

);

* End of file headings.

* -----------------------------------------------------------------------------
PUT "Annual average heat price, weighted by consumption quantity "//;

LOOP(IY411FIRST,
PUT "BB4 model starting year "  IY411FIRST.TL:4 "..............................:" //;
hp_yna.LJ = 1;
PUT "YEAR        " ; PUT /;
hp_yna.LJ = 2;
LOOP(IY411,
  PUT IY411.TL ;

  OSCALAR1=0;  /* To become accounter of total consumption */
  OSCALAR3=0;  /* To become total cost       */
  OSCALAR2=0;  /* To become total consumption */
  LOOP(C,

         LOOP(IA$ICA(C,IA),


                 LOOP(S,  LOOP(T,
                         OSCALAR1 = (IDH_T(IY411,IA,S,T)
                                         + SUM(DHF_U1,VDHF_T.L(IY411,IA,S,T,DHF_U1) )
                                         - SUM(DHF_D1,VDHF_T.L(IY411,IA,S,T,DHF_D1) )
                                         + SUM(DHF_U2,VDHF_T.L(IY411,IA,S,T,DHF_U2) )
                                         - SUM(DHF_D2,VDHF_T.L(IY411,IA,S,T,DHF_D2) )
                                         + SUM(DHF_U3,VDHF_T.L(IY411,IA,S,T,DHF_U3) )
                                         - SUM(DHF_D3,VDHF_T.L(IY411,IA,S,T,DHF_D3) )
                                     ) / (1-DISLOSS_H(IA));

                         OSCALAR2 = OSCALAR2 + OSCALAR1 * IHOURSINST(S,T);
                         OSCALAR3 = OSCALAR3 + OSCALAR1 * OHP_YAT(IY411FIRST,IY411,IA,S,T)*IHOURSINST(S,T);
                 ));

        );

  );
  OHP_YNA(IY411FIRST,IY411)$(OSCALAR2 > 0)= OSCALAR3/OSCALAR2;
  PUT OHP_YNA(IY411FIRST,IY411):OTLWCRA:2;
  PUT /;
  );PUT /;
);PUT /;










$ontext

OHP_YA(IY411FIRST,IY411,IA) = SUM((S,T),OHP_YAT(IY411FIRST,IY411,IA,S,T));

PUT "Annual average heat price, simple time weighted average:" /;

LOOP(IY411FIRST,
PUT "BB4 model starting year "  IY411FIRST.TL:4 "..............................:" //;
hp_ya.LJ = 1;
PUT "YEAR        " ; LOOP(IA, PUT IA.TL:OTLWCRA); PUT /;
hp_ya.LJ = 2;
LOOP(IY411,
  PUT IY411.TL ;
    LOOP(IA,
      PUT OHP_YA(IY411FIRST,IY411,IA):OTLWCRA:2;
    );PUT /;
  );PUT /;
);PUT /;

$offtext


$ontext

PUT "Annual average heat price, simple time weighted average:, NOT IMPLEMENTED YET"/;
hp_ay.LJ = 1;
PUT "YEAR        " ; LOOP(IA,  PUT IA.TL:OTLW) ; PUT/;
hp_ay.LJ = 2;

PUT Y.TL:4:0; PUT "        "; LOOP(IA,
     if(DH(Y,IA),       /* Note: using DH(Y,IA) may not always be perfect ... */
        PUT ((OMONEY*IOF1_/IOF8760)*SUM((S,T), QHEQ.M(IA,S,T))):OTLW:2 ;
     ELSE
        PUT OTLW.ts;
     )
);
PUT //;


* -----------------------------------------------------------------------------

PUT "Annual average heat price, weighted by production quantity:"/;
hp_ay.LJ = 1;
PUT "YEAR        " ; LOOP(IA,  PUT IA.TL:OTLW) ; PUT  "     Average" /;
hp_ay.LJ = 2;

     ISCALAR3=0;  /* To become total cost over all IA  */
     ISCALAR2=0;  /* To become total production over all IA  */

PUT Y.TL:4:0; PUT "        "; LOOP(IA,
     OSCALAR3=0;  /* To become total cost       */
     OSCALAR2=0;  /* To become total production */


       LOOP(S,  LOOP(T,
*            OSCALAR1 = SUM(IGH, VGH_T.L(IA,IGH,S,T)+VGHN_T.L(IA,IGH,S,T));
* Note: The expression for OSCALAR1 is identical to the left hand side of heat equation:
            OSCALAR1 =
                  SUM(IGBPR$IAGK_Y(IA,IGBPR),VGH_T.L(IA,IGBPR,S,T))
               + SUM(IGBPR$IAGKN(IA,IGBPR),VGHN_T.L(IA,IGBPR,S,T))
               + SUM(IGEXT$IAGK_Y(IA,IGEXT),VGH_T.L(IA,IGEXT,S,T))
               + SUM(IGEXT$IAGKN(IA,IGEXT),VGHN_T.L(IA,IGEXT,S,T))
               + SUM(IGHH$IAGK_Y(IA,IGHH),VGH_T.L(IA,IGHH,S,T))
               + SUM(IGHH$IAGKN(IA,IGHH),VGHN_T.L(IA,IGHH,S,T))
               + SUM(IGETOH$IAGK_Y(IA,IGETOH),VGH_T.L(IA,IGETOH,S,T))
               + SUM(IGETOH$IAGKN(IA,IGETOH),VGHN_T.L(IA,IGETOH,S,T))
               - VHSTOLOADT.L(IA,S,T)
               + SUM(IGESTO$((IGKFX_Y(IA,IGESTO) GT 0) AND (GDATA(IGESTO,'GDCB') GT 0)), VGE_T.L(IA,IGESTO,S,T)/GDATA(IGESTO,'GDCB'));

            OSCALAR2 = OSCALAR2 + OSCALAR1 * IHOURSINST(S,T);
            OSCALAR3 = OSCALAR3 + OSCALAR1 * IHOURSINST(S,T) * QHEQ.M(IA,S,T);


      ));
*TEST PUT  / IA.TL "  MMM PROD, COST =  " OSCALAR2    OSCALAR3  /;

     IF((OSCALAR2 GT 1),
      PUT (OMONEY*(IOF1_*OSCALAR3 / OSCALAR2)):OTLW:2 ;
            ISCALAR2 = ISCALAR2 + OSCALAR2 ;
            ISCALAR3 = ISCALAR3 + OSCALAR3 ;
    ELSE
      PUT " '(No gen.)'" ;
      ); );

     IF((ISCALAR2 GT 1),
      PUT (OMONEY*(IOF1_*ISCALAR3 / ISCALAR2)):OTLW:2 ;
     )
  PUT //;


* -----------------------------------------------------------------------------


PUT "Annual average heat price, weighted by consumption quantity:"/;
hp_ay.LJ = 1;
PUT "YEAR        " ; LOOP(IA,  PUT IA.TL:OTLW) ; PUT /;
hp_ay.LJ = 2;

PUT Y.TL:4:0; PUT "        "; LOOP(IA,
     OSCALAR3=0;  /* To become total cost        */
     OSCALAR2=0;  /* To become total consumption */

       LOOP(S,  LOOP(T,
            OSCALAR1 = (IDH_T_Y(IA,S,T)
                      + SUM(DHF_U1,VDHF_T.L(IA,S,T,DHF_U1) )
                      - SUM(DHF_D1,VDHF_T.L(IA,S,T,DHF_D1) )) / (1-DISLOSS_H(IA));
            OSCALAR2 = OSCALAR2 + OSCALAR1 * IHOURSINST(S,T);
            OSCALAR3 = OSCALAR3 + OSCALAR1 * QHEQ.M(IA,S,T);
      ));

     IF((OSCALAR2 GT 0),
      PUT (OMONEY*(IOF1_*OSCALAR3 / OSCALAR2)):OTLW:2 ;

    ELSE
      PUT " '(No dem.)'" ;
      ); );
  PUT //;



$offtext
* -----------------------------------------------------------------------------
