* File ep_ry.inc.

* Modified last time: 01-02-2002 (rus), 16-02-2004 (ld), 2005.11.20 (hr), 20060328(hr), 20080305(hr), 20120812(hr)

* This file will print a table containing
* the annual weighted average marginal electricity price by IR.
* Different weighting used.



* -----------------------------------------------------------------------------

PUT ep_ry;

* First print headings:

if ((ep_ry.pw LT 32000),
ep_ry.pw = 32000;
PUT "Version:              " "%PRINTSEPARATOR%" SYSTEM.TITLE /;
PUT "File name:            " "%PRINTSEPARATOR%" "ep_ry.out" /;
PUT "Time-stamp:           " "%PRINTSEPARATOR%" SYSTEM.DATE " " SYSTEM.TIME  /;
$ifi %BB1%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE1"/;
$ifi %BB2%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE2"/;
$ifi %BB3%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE3"/;
PUT "Case-identification:  " "%PRINTSEPARATOR%" OCASEID.TS   //;

PUT "Annual electricity price, several versions." /;
PUT "Currency: " OMONEY.TS "  with exchange rate to input currency: "  OMONEY:7:3  " ("OMONEY.TS"/"OIMONEY.TS")." /;
PUT "Units: "; PUT OMONEY.ts "/MWh" //;

);

* End of file headings.
* -----------------------------------------------------------------------------


PUT "Annual average electricity price, simple time weighted average:"/;
ep_ry.LJ = 1;
PUT "YEAR        " ; LOOP(IR,  PUT IR.TL:12) ; PUT /;
ep_ry.LJ = 2;

PUT Y.TL:4:0; PUT "        "; LOOP(IR,
     PUT ( (OMONEY*IOF1_/IOF8760) * SUM((S,T), QEEQ.M(IR,S,T))):12:2 ;
);
PUT //;

* -----------------------------------------------------------------------------

PUT "Annual average electricity price, weighted by production quantity:"/;
ep_ry.LJ = 1;
PUT "YEAR        " ; LOOP(IR,  PUT IR.TL:12) ; PUT /;
ep_ry.LJ = 2;

PUT Y.TL:4:0; PUT "        "; LOOP(IR,
     OSCALAR3=0;  /* To become total cost       */
     OSCALAR2=0;  /* To become total production */

       LOOP(S,  LOOP(T,
*            OSCALAR1 = SUM(IGH, VGH_T.L(IR,IGH,S,T)+VGHN_T.L(IR,IGH,S,T));
* Note: The expression for OSCALAR1 is identical to the left hand side of electricity equation:
            OSCALAR1 =
              SUM(IAGK_Y(IA,IGE)$((RRRAAA(IR,IA)) AND IGNOTETOH(IGE)), VGE_T.L(IA,IGE,S,T))
            - SUM(IAGK_Y(IA,IGE)$((RRRAAA(IR,IA)) AND IGETOH(IGE)), VGE_T.L(IA,IGE,S,T))
            + SUM(IAGKN(IA,IGE)$((RRRAAA(IR,IA)) AND IGNOTETOH(IGE)), VGEN_T.L(IA,IGE,S,T))
            - SUM(IAGKN(IA,IGE)$((RRRAAA(IR,IA)) AND IGETOH(IGE)), VGEN_T.L(IA,IGE,S,T))
            + SUM(IRE$(IXKINI_Y(IRE,IR) OR IXKN(IRE,IR) OR IXKN(IR,IRE)), VX_T.L(IRE,IR,S,T)*(1-XLOSS(IRE,IR)))
            - SUM(IA$RRRAAA(IR,IA),VESTOLOADT.L(IA,S,T))
$ifi "%X3V%"=="yes"     + SUM(X3VPLACE$X3VX(IR,X3VPLACE),SUM(X3VSTEP,VX3VIM_T.L(IR,X3VPLACE,X3VSTEP,S,T)))
;

            OSCALAR2 = OSCALAR2 + OSCALAR1 * IHOURSINST(S,T);
            OSCALAR3 = OSCALAR3 + OSCALAR1 * QEEQ.M(IR,S,T);
      ));

     IF((OSCALAR2 GT 0),
      PUT (OMONEY*(IOF1_*OSCALAR3 / OSCALAR2)):12:2 ;

    ELSE
      PUT " '(No gen.)'" ;
      ); );
  PUT //;


* -----------------------------------------------------------------------------


PUT "Annual average electricity price, weighted by consumption quantity:"/;

*TODO!!

$ontext
ep_ry.LJ = 1;
PUT "YEAR        " ; LOOP(IR,  PUT IR.TL:12) ; PUT /;
ep_ry.LJ = 2;

PUT Y.TL:4:0; PUT "        "; LOOP(IR,
     OSCALAR3=0;  /* To become total cost        */
     OSCALAR2=0;  /* To become total consumption */

       LOOP(S,  LOOP(T,
            OSCALAR1 =  (IDE_T_Y(IR,S,T)
                + SUM(DEF_U1,VDEF_T.L(IR,S,T,DEF_U1) )
                - SUM(DEF_D1,VDEF_T.L(IR,S,T,DEF_D1) )
                + SUM(DEF_U2,VDEF_T.L(IR,S,T,DEF_U2) )
                - SUM(DEF_D2,VDEF_T.L(IR,S,T,DEF_D2) )
                 )/(1-DISLOSS_E(IR));
            OSCALAR2 = OSCALAR2 + OSCALAR1 * IHOURSINST(S,T);
            OSCALAR3 = OSCALAR3 + OSCALAR1 * QEEQ.M(IR,S,T);
      ));


     IF((OSCALAR2 GT 0),
      PUT (OMONEY*(IOF1_*OSCALAR3 / OSCALAR2)):12:2 ;

    ELSE
      PUT " '(No dem.)'" ;
      ); );
  PUT //;

$offtext

* -----------------------------------------------------------------------------
