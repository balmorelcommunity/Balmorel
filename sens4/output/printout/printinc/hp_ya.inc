* File hp_ya.inc.

* Modified last time: 01-02-2002 (rus), ... ,  20150130(hr),20150312(Weiming). 20161024 (hr): Guading against division-by-zero (search NA). Todo: detect the source for division-by-0, at do something about that.

* This file will print a table containing
* the annual weighted average marginal heat generation price by IA.



* -----------------------------------------------------------------------------

PUT hp_ya;

* First print headings:

if ((hp_ya.pw LT 32000),
hp_ya.pw = 32000;
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
hp_ya.LJ = 1;
PUT "YEAR        " ; LOOP(IA, PUT IA.TL:OTLWCRA); PUT /;
hp_ya.LJ = 2;
LOOP(IY411,
  PUT IY411.TL ;

         LOOP(IA,
                 OSCALAR1=0;  /* To become accounter of total consumption */
                 OSCALAR3=0;  /* To become total cost       */
                 OSCALAR2=0;  /* To become total consumption */
           LOOP(DHUSER,
                 LOOP(IS3,  LOOP(T,
                         OSCALAR1 = (IDH_T(IY411,IA,DHUSER,IS3,T)
$ifi %dflexquant%==yes   + SUM(DHF_U1,VDHF_T.L(IY411,IA,DHUSER,IS3,T,DHF_U1) )
$ifi %dflexquant%==yes   - SUM(DHF_D1,VDHF_T.L(IY411,IA,DHUSER,IS3,T,DHF_D1) )
$ifi %dflexquant%==yes   + SUM(DHF_U2,VDHF_T.L(IY411,IA,DHUSER,IS3,T,DHF_U2) )
$ifi %dflexquant%==yes   - SUM(DHF_D2,VDHF_T.L(IY411,IA,DHUSER,IS3,T,DHF_D2) )
$ifi %dflexquant%==yes   + SUM(DHF_U3,VDHF_T.L(IY411,IA,DHUSER,IS3,T,DHF_U3) )
$ifi %dflexquant%==yes   - SUM(DHF_D3,VDHF_T.L(IY411,IA,DHUSER,IS3,T,DHF_D3) )

                                     ) / (1-DISLOSS_H(IA));


                         OSCALAR2 = OSCALAR2 + OSCALAR1 * IHOURSINST(IS3,T);
                         OSCALAR3 = OSCALAR3 + OSCALAR1 * OHP_YAT(IY411FIRST,IY411,IA,IS3,T)*IHOURSINST(IS3,T);
      ));


      OHP_YA(IY411FIRST,IY411,IA)$(DH(IY411,IA,DHUSER) > 0)= OSCALAR3/(OSCALAR2$(OSCALAR2 NE 0) + NA$(OSCALAR2 EQ 0))
      PUT OHP_YA(IY411FIRST,IY411,IA):OTLWCRA:2;

    );PUT /;
    );PUT /;
  );PUT /;
);PUT /;





$ontext

OHP_YA(IY411FIRST,IY411,IA) = SUM((IS3,T),OHP_YAT(IY411FIRST,IY411,IA,IS3,T));

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
        PUT ((OMONEY*IOF1_/IOF8760)*SUM((IS3,T), QHEQ.M(IA,IS3,T))):OTLW:2 ;
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


       LOOP(IS3,  LOOP(T,
*            OSCALAR1 = SUM(IGH, VGH_T.L(IA,IGH,IS3,T)+VGHN_T.L(IA,IGH,IS3,T));
* Note: The expression for OSCALAR1 is identical to the left hand side of heat equation:
            OSCALAR1 =
                  SUM(IGBPR$IAGK_Y(IA,IGBPR),VGH_T.L(IA,IGBPR,IS3,T))
               + SUM(IGBPR$IAGKN(IA,IGBPR),VGHN_T.L(IA,IGBPR,IS3,T))
               + SUM(IGEXT$IAGK_Y(IA,IGEXT),VGH_T.L(IA,IGEXT,IS3,T))
               + SUM(IGEXT$IAGKN(IA,IGEXT),VGHN_T.L(IA,IGEXT,IS3,T))
               + SUM(IGHH$IAGK_Y(IA,IGHH),VGH_T.L(IA,IGHH,IS3,T))
               + SUM(IGHH$IAGKN(IA,IGHH),VGHN_T.L(IA,IGHH,IS3,T))
               + SUM(IGETOH$IAGK_Y(IA,IGETOH),VGH_T.L(IA,IGETOH,IS3,T))
               + SUM(IGETOH$IAGKN(IA,IGETOH),VGHN_T.L(IA,IGETOH,IS3,T))
               - VHSTOLOADT.L(IA,IS3,T)
               + SUM(IGESTO$((IGKFX_Y(IA,IGESTO) GT 0) AND (GDATA(IGESTO,'GDCB') GT 0)), VGE_T.L(IA,IGESTO,IS3,T)/GDATA(IGESTO,'GDCB'));

            OSCALAR2 = OSCALAR2 + OSCALAR1 * IHOURSINST(IS3,T);
            OSCALAR3 = OSCALAR3 + OSCALAR1 * IHOURSINST(IS3,T) * QHEQ.M(IA,IS3,T);


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

       LOOP(IS3,  LOOP(T,
            OSCALAR1 = (IDH_T_Y(IA,IS3,T)
                      + SUM(DHF_U1,VDHF_T.L(IA,IS3,T,DHF_U1) )
                      - SUM(DHF_D1,VDHF_T.L(IA,IS3,T,DHF_D1) )) / (1-DISLOSS_H(IA));
            OSCALAR2 = OSCALAR2 + OSCALAR1 * IHOURSINST(IS3,T);
            OSCALAR3 = OSCALAR3 + OSCALAR1 * QHEQ.M(IA,IS3,T);
      ));

     IF((OSCALAR2 GT 0),
      PUT (OMONEY*(IOF1_*OSCALAR3 / OSCALAR2)):OTLW:2 ;

    ELSE
      PUT " '(No dem.)'" ;
      ); );
  PUT //;



$offtext
* -----------------------------------------------------------------------------
