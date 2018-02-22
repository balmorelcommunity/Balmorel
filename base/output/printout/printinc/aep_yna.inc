* File aep_yna.inc.

* Modified last time:20150430(Weiming), 20151209(HR)

* This file will print a table containing
* the annual average electricity price by aggregated countries (annual system cost/annual consumption).
* Consumption weighting used.


DISPLAY INFODISPLAY, "SKIPPED PRINTING FROM %SYSTEM.INCNAME% ";
$GOTO ENDOFFILE

* -----------------------------------------------------------------------------

PUT aep_yna;

* First print headings:

if ((aep_yna.pw LT 32000),
aep_yna.pw = 32000;
PUT "Version:              " "%PRINTSEPARATOR%" SYSTEM.TITLE /;
PUT "Printed from file:    " "%PRINTSEPARATOR%" "aep_yna.inc" /;
PUT "Time-stamp:           " "%PRINTSEPARATOR%" SYSTEM.DATE " " SYSTEM.TIME  /;
$ifi %BB1%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE1"/;
$ifi %BB2%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE2"/;
$ifi %BB3%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE3"/;
$ifi %BB4%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE4"/;
PUT "Case-identification:  " "%PRINTSEPARATOR%" OCASEID.TS   //;

PUT "Annual averaged electricity price, several versions, all years in each BB4 model." /;
PUT "Currency: " OMONEY.TS "  with exchange rate to input currency: "  OMONEY:7:3  " ("OMONEY.TS"/"OIMONEY.TS").";
PUT "   (The output currency and its relation to input currency is specified in input data file OMONEY.inc. The input currency is specified in file print1.inc.)" /;
PUT "Units: "; PUT OMONEY.ts "/MWh" //;
$ifi %BB4%==yes PUT "Electricity prices are in undiscounted values." //;

PUT "Annual average electricity price(annual system cost/annual consumption, not marignal price), weighted by consumption quantity"//;

);

* End of file headings.
* -----------------------------------------------------------------------------



*OAEP_YNA(IY411FIRST,IY411)

LOOP(IY411FIRST,
PUT "BB4 model starting year "  IY411FIRST.TL:4 "..............................:" //;
aep_yna.LJ = 1;
PUT "YEAR        " ;  PUT /;
aep_yna.LJ = 2;
LOOP(IY411,
  PUT IY411.TL ;



OSCALAR1=0;  /* To become total cost        */
OSCALAR2=0;  /* To become total demand        */

OSCALAR1=
* Cost of fuel consumption during the year:

     SUM((IAGK_HASORPOT(IY411,IA,IGE),FFF)$IGF(IGE,FFF),
                 FUELPRICE(IY411,IA,FFF) * IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) *
                 VGE_T.L(IY411,IA,IGE,IS3,T)/(GDATA(IGE,"GDFE")*GEFFRATE(IA,IGE))))

* Operation and maintainance cost:

   + SUM(IAGK_HASORPOT(IY411,IA,IGE), GOMVCOST(IA,IGE) * SUM((IS3,T), IHOURSINST(IS3,T)*
     VGE_T.L(IY411,IA,IGE,IS3,T)))

   + IOF1000*(SUM((IA,G)$IAGK_HASORPOT(IY411,IA,G),(VGKNACCUMNET.L(IY411,IA,G) + GKFX(IY411,IA,G))*GOMFCOST(IA,G)))

*  Hydro with storage seasonal price profile:

   + SUM((IA,IGHYRS)$IAGK_HASORPOT(IY411,IA,IGHYRS), SUM((IS3,T), HYPPROFILS(IA,IS3)* IHOURSINST(IS3,T)
     * VGE_T.L(IY411,IA,IGHYRS,IS3,T)))

* Transmission cost:

*   + SUM((IRE,IRI)$(XKINI(IY411,IRE,IRI) OR IXKN(IRE,IRI) OR IXKN(IRI,IRE)),
   + SUM((IRE,IRI)$IXK_HASORPOT(IY411,IRE,IRI),
       SUM((IS3,T), IHOURSINST(IS3,T) * (VX_T.L(IY411,IRE,IRI,IS3,T) * XCOST(IRE,IRI))))


$ontext
    + IOF1000000*(SUM((IA,G)$IAGKNY(IY411,IA,G), VGKN.L(IY411,IA,G)*GINVCOST(IA,G)*(SUM(C$ICA(C,IA),ANNUITYC(C))))

    + SUM((IRE,IRI)$IXKN(IRI,IRE), VXKN.L(IY411,IRE,IRI)*XINVCOST(IRE,IRI)*
      (IOF05* (SUM(C$CCCRRR(C,IRE),ANNUITYC(C))+SUM(C$CCCRRR(C,IRI),ANNUITYC(C)))))
$offtext


*Weiming(add acumulative investment)
* Investment costs, new generation and storage capacity:
* Investment costs, new transmission capacity
* (the average of the annuities for the two countries in question is used for international transmission):

    + IOF1000000*(SUM((IA,G)$IAGKNY(IY411,IA,G), VGKNACCUMNET.L(IY411,IA,G)*GINVCOST(IA,G)*(SUM(C$ICA(C,IA),ANNUITYCG(C,G)))*IY4GINVCOSTWEIGHT(IY411,G)))

    + SUM((IRE,IRI)$IXKN(IRI,IRE), VXKNACCUMNET.L(IY411,IRE,IRI)*XINVCOST(IRE,IRI)*
      (IOF05* (SUM(C$CCCRRR(C,IRE),ANNUITYCX(C))+SUM(C$CCCRRR(C,IRI),ANNUITYCX(C)))))

* Emission taxes

    + SUM(C, SUM((IA,IGE)$(ICA(C,IA) AND IAGK_HASORPOT(IY411,IA,IGE)), SUM((IS3,T), IHOURSINST(IS3,T) * (IM_CO2(IGE)*IOF0001) *
      IOF3P6 *VGE_T.L(IY411,IA,IGE,IS3,T) /(GDATA(IGE,"GDFE") * GEFFRATE(IA,IGE))) * M_POL(IY411,"TAX_CO2",C)))

    + SUM(C, SUM((IA,IGE)$(ICA(C,IA) AND IAGK_HASORPOT(IY411,IA,IGE)), SUM((IS3,T), IHOURSINST(IS3,T) * (IM_SO2(IGE)*IOF0001) *
      IOF3P6 *VGE_T.L(IY411,IA,IGE,IS3,T)/(GDATA(IGE,"GDFE") * GEFFRATE(IA,IGE)))* M_POL(IY411,"TAX_SO2",C)))

    + SUM(C, SUM((IA,IGE)$(ICA(C,IA) AND IAGK_HASORPOT(IY411,IA,IGE)), SUM((IS3,T), IHOURSINST(IS3,T)*(GDATA(IGE,"GDNOX")*IOF0000001)*
      IOF3P6 * VGE_T.L(IY411,IA,IGE,IS3,T)/(GDATA(IGE,"GDFE")*GEFFRATE(IA,IGE)))* M_POL(IY411,"TAX_NOX",C)))

* Fuel taxes

    + SUM((C,FFF,IS3,T), SUM((IA,IGE)$(IGF(IGE,FFF) AND ICA(C,IA) AND IAGK_HASORPOT(IY411,IA,IGE)),
      IHOURSINST(IS3,T) * TAX_F(FFF,C) * IOF3P6 *
      (VGE_T.L(IY411,IA,IGE,IS3,T) / (GDATA(IGE,"GDFE") * GEFFRATE(IA,IGE)))))

* More fuel taxes on technology types.   TODO
/*  Not completely implemented yet - kept as appetizer.
   + SUM((Y,IA,IGH,IS3,T)$(IAGK(Y,IA,IGH) and (IGHOB(IGH) or IGETOH(IGH))),  IAGK -> IAGKFX
      TAX_FHO(Y,IA,IGH)*IHOURSINST(IS3,T)  * IOF3P6 * GDATA(IGH,"GDCV")* VGH_T(Y,IA,IGH,IS3,T)/(GDATA(IGH,"GDFE") * -GEFFRATE(IA,IGH)))
*   + SUM((Y,IA,IGH,IS3,T)$(IAGKNY(Y,IA,IGH) and (IGHOB(IGH) or IGETOH(IGH))),    TAX_FHO(Y,IA,IGH)*IHOURSINST(IS3,T)  * IOF3P6 *  VGHN_T(Y,IA,IGH,IS3,T)/(GDATA(IGH,"GDFE") * GEFFRATE(IA,IGH)))
*/

* Changes in consumers" utility relative to electricity consumption:

   + SUM(IR,
     SUM((IS3,T), IHOURSINST(IS3,T)
     * (SUM(DEF_D1, VDEF_T.L(IY411,IR,IS3,T,DEF_D1)* IDEFP_T(IR,IS3,T,DEF_D1)  )
     +  SUM(DEF_D2, VDEF_T.L(IY411,IR,IS3,T,DEF_D2)* IDEFP_T(IR,IS3,T,DEF_D2)  )
     +  SUM(DEF_D3, VDEF_T.L(IY411,IR,IS3,T,DEF_D3)* IDEFP_T(IR,IS3,T,DEF_D3)  )
     )))

   - SUM(IR,
     SUM((IS3,T), IHOURSINST(IS3,T)
     * (SUM(DEF_U1, VDEF_T.L(IY411,IR,IS3,T,DEF_U1)* IDEFP_T(IR,IS3,T,DEF_U1)  )
     +  SUM(DEF_U2, VDEF_T.L(IY411,IR,IS3,T,DEF_U2)* IDEFP_T(IR,IS3,T,DEF_U2)  )
     +  SUM(DEF_U3, VDEF_T.L(IY411,IR,IS3,T,DEF_U3)* IDEFP_T(IR,IS3,T,DEF_U3)  )
     )))


;



OSCALAR2=  SUM((IS3,T,IR),     IHOURSINST(IS3,T)*(IDE_T(IY411,IR,IS3,T)
                                         + SUM(DEF_U1,VDEF_T.L(IY411,IR,IS3,T,DEF_U1))
                                         - SUM(DEF_D1,VDEF_T.L(IY411,IR,IS3,T,DEF_D1))
                                         + SUM(DEF_U2,VDEF_T.L(IY411,IR,IS3,T,DEF_U2))
                                         - SUM(DEF_D2,VDEF_T.L(IY411,IR,IS3,T,DEF_D2))
                                         + SUM(DEF_U3,VDEF_T.L(IY411,IR,IS3,T,DEF_U3))
                                         - SUM(DEF_D3,VDEF_T.L(IY411,IR,IS3,T,DEF_D3))
                                         ))
;

OAEP_YNA(IY411FIRST,IY411)=(OSCALAR1/OSCALAR2)$(OSCALAR2 > 0);
*OAEP_YNA(IY411FIRST,IY411)=OSCALAR1;
 PUT OAEP_YNA(IY411FIRST,IY411):OTLWCRA:2;
 PUT /;


  );PUT /;
);PUT /;



$ontext


$ifi %BB4%==yes  SUM(Y$IY411(Y),
* Objective equation with time discounting of years and with weighting of years that are in Y but not in YYY
IOF1_ * IDISCOUNTFACTOR(Y) * IWEIGHTY(Y) * (

* Cost of fuel consumption during the year:

     SUM((IAGK_HASORPOT(Y,IA,IGE),FFF)$IGF(IGE,FFF),
                 FUELPRICE(Y,IA,FFF) * IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) *
                 VGE_T(Y,IA,IGE,IS3,T)/(GDATA(IGE,"GDFE")*GEFFRATE(IA,IGE))))

    +SUM((IAGK_HASORPOT(Y,IA,IGH),FFF)$IGF(IGH,FFF),
                 FUELPRICE(Y,IA,FFF) * IOF3P6 * SUM((IS3,T), IHOURSINST(IS3,T) *
                 GDATA(IGH,"GDCV")*VGH_T(Y,IA,IGH,IS3,T)/(GDATA(IGH,"GDFE")*GEFFRATE(IA,IGH))))

* Operation and maintainance cost:

   + SUM(IAGK_HASORPOT(Y,IA,IGE), GOMVCOST(IA,IGE) * SUM((IS3,T), IHOURSINST(IS3,T)*
     VGE_T(Y,IA,IGE,IS3,T)))

   + SUM(IAGK_HASORPOT(Y,IA,IGNOTETOH(IGH)), GOMVCOST(IA,IGNOTETOH) * SUM((IS3,T), IHOURSINST(IS3,T)*
     GDATA(IGNOTETOH,"GDCV")*(VGH_T(Y,IA,IGNOTETOH,IS3,T))))

    + IOF1000*(SUM((IA,G)$IAGK_HASORPOT(Y,IA,G),(VGKNACCUMNET(Y,IA,G) + GKFX(Y,IA,G))*GOMFCOST(IA,G)))


*  Hydro with storage seasonal price profile:

   + SUM((IA,IGHYRS)$IAGK_HASORPOT(Y,IA,IGHYRS), SUM((IS3,T), HYPPROFILS(IA,IS3)* IHOURSINST(IS3,T)
     * VGE_T(Y,IA,IGHYRS,IS3,T)))


* Transmission cost:

*   + SUM((IRE,IRI)$(XKINI(Y,IRE,IRI) OR IXKN(IRE,IRI) OR IXKN(IRI,IRE)),
   + SUM((IRE,IRI)$IXK_HASORPOT(Y,IRE,IRI),
       SUM((IS3,T), IHOURSINST(IS3,T) * (VX_T(Y,IRE,IRI,IS3,T) * XCOST(IRE,IRI))))

* Investment costs, new generation and storage capacity:

*   The ANNUITY of the investment cost relative to VGKN is to be taken every remaining year in the present BB4 model,
*   discounted back to the first year in the present BB4 model, this latter is represented by factor IY4GINVCOSTWEIGHT below.
*   Discounting further back from first year in the present BB4 model to the first year in Y is handled by the factor IDISCOUNTFACTOR(Y) above.
*   The relative weight of the years is represented by
    + IOF1000000*(SUM((IA,G)$IAGKNY(Y,IA,G), VGKN(Y,IA,G)*GINVCOST(IA,G)*(SUM(C$ICA(C,IA),ANNUITYC(C)))*IY4GINVCOSTWEIGHT(Y,G)))

$ifi %AGKNDISC%==yes  $include "../../base/addons/bb4/agkndisc/agkndiscaddqobj.inc";

* Investment costs, new transmission capacity
* (the average of the annuities for the two countries in question is used for international transmission):

    + SUM((IRE,IRI)$IXKN(IRI,IRE), VXKN(Y,IRE,IRI)*XINVCOST(IRE,IRI)*
      (IOF05* (SUM(C$CCCRRR(C,IRE),ANNUITYC(C))+SUM(C$CCCRRR(C,IRI),ANNUITYC(C)))))*IY4XINVCOSTWEIGHT(Y)

* Emission taxes

    + SUM(C, SUM((IA,IGE)$(ICA(C,IA) AND IAGK_HASORPOT(Y,IA,IGE)), SUM((IS3,T), IHOURSINST(IS3,T) * (IM_CO2(IGE)*IOF0001) *
      IOF3P6 *VGE_T(Y,IA,IGE,IS3,T) /(GDATA(IGE,"GDFE") * GEFFRATE(IA,IGE))) * M_POL(Y,"TAX_CO2",C)))

    + SUM(C, SUM((IA,IGH)$(ICA(C,IA) AND IAGK_HASORPOT(Y,IA,IGH)), SUM((IS3,T), IHOURSINST(IS3,T) * (IM_CO2(IGH)*IOF0001) *
      IOF3P6 *GDATA(IGH,"GDCV")* VGH_T(Y,IA,IGH,IS3,T)/(GDATA(IGH,"GDFE")*GEFFRATE(IA,IGH)))*M_POL(Y,"TAX_CO2",C)))

    + SUM(C, SUM((IA,IGE)$(ICA(C,IA) AND IAGK_HASORPOT(Y,IA,IGE)), SUM((IS3,T), IHOURSINST(IS3,T) * (IM_SO2(IGE)*IOF0001) *
      IOF3P6 *VGE_T(Y,IA,IGE,IS3,T)/(GDATA(IGE,"GDFE") * GEFFRATE(IA,IGE)))* M_POL(Y,"TAX_SO2",C)))

    + SUM(C, SUM((IA,IGH)$(ICA(C,IA) AND IAGK_HASORPOT(Y,IA,IGH)), SUM((IS3,T), IHOURSINST(IS3,T) * (IM_SO2(IGH)*IOF0001) *
      IOF3P6 *GDATA(IGH,"GDCV")* VGH_T(Y,IA,IGH,IS3,T)/(GDATA(IGH,"GDFE")*GEFFRATE(IA,IGH)))*M_POL(Y,"TAX_SO2",C)))

    + SUM(C, SUM((IA,IGE)$(ICA(C,IA) AND IAGK_HASORPOT(Y,IA,IGE)), SUM((IS3,T), IHOURSINST(IS3,T)*(GDATA(IGE,"GDNOX")*IOF0000001)*
      IOF3P6 * VGE_T(Y,IA,IGE,IS3,T)/(GDATA(IGE,"GDFE")*GEFFRATE(IA,IGE)))* M_POL(Y,"TAX_NOX",C)))

    + SUM(C, SUM((IA,IGH)$(ICA(C,IA) AND IAGK_HASORPOT(Y,IA,IGH)), SUM((IS3,T), IHOURSINST(IS3,T)*(GDATA(IGH,"GDNOX")*IOF0000001)*
      IOF3P6 *GDATA(IGH,"GDCV")* VGH_T(Y,IA,IGH,IS3,T)/(GDATA(IGH,"GDFE")*GEFFRATE(IA,IGH)) )* M_POL(Y,"TAX_NOX",C)))

* Fuel taxes

    + SUM((C,FFF,IS3,T), SUM((IA,IGE)$(IGF(IGE,FFF) AND ICA(C,IA) AND IAGK_HASORPOT(Y,IA,IGE)),
      IHOURSINST(IS3,T) * TAX_F(FFF,C) * IOF3P6 *
      (VGE_T(Y,IA,IGE,IS3,T) / (GDATA(IGE,"GDFE") * GEFFRATE(IA,IGE)))))

   + SUM((C,FFF,IS3,T), SUM((IA,IGH)$(IGF(IGH,FFF) AND ICA(C,IA) AND IAGK_HASORPOT(Y,IA,IGH)),
      IHOURSINST(IS3,T) * TAX_F(FFF,C) * IOF3P6 *
      GDATA(IGH,"GDCV")* VGH_T(Y,IA,IGH,IS3,T)/(GDATA(IGH,"GDFE") * GEFFRATE(IA,IGH))))

* More fuel taxes on technology types.   TODO
/*  Not completely implemented yet - kept as appetizer.
   + SUM((Y,IA,IGH,IS3,T)$(IAGK(Y,IA,IGH) and (IGHOB(IGH) or IGETOH(IGH))),  IAGK -> IAGKFX
      TAX_FHO(Y,IA,IGH)*IHOURSINST(IS3,T)  * IOF3P6 * GDATA(IGH,"GDCV")* VGH_T(Y,IA,IGH,IS3,T)/(GDATA(IGH,"GDFE") * -GEFFRATE(IA,IGH)))
*   + SUM((Y,IA,IGH,IS3,T)$(IAGKNY(Y,IA,IGH) and (IGHOB(IGH) or IGETOH(IGH))),    TAX_FHO(Y,IA,IGH)*IHOURSINST(IS3,T)  * IOF3P6 *  VGHN_T(Y,IA,IGH,IS3,T)/(GDATA(IGH,"GDFE") * GEFFRATE(IA,IGH)))
* Heat generation taxes.
   + SUM((Y,IA,IGH,IS3,T)$(IAGK(Y,IA,IGH) and TAX_GH(Y,IA,IGH)),                IAGK -> IAGKFX
      TAX_GH(Y,IA,IGH)*IOF3P6*VGH_T(Y,IA,IGH,IS3,T)*IHOURSINST(IS3,T))
*   + SUM((Y,IA,IGH,IS3,T)$(IAGKNY(Y,IA,IGH) and TAX_GH(Y,IA,IGH)), TAX_GH(Y,IA,IGH)*IOF3P6*VGHN_T(Y,IA,IGH,IS3,T)*IHOURSINST(IS3,T))
*/

* Changes in consumers" utility relative to electricity consumption:

   + SUM(IR,
     SUM((IS3,T), IHOURSINST(IS3,T)
     * (SUM(DEF_D1, VDEF_T(Y,IR,IS3,T,DEF_D1)* IDEFP_T(IR,IS3,T,DEF_D1)  )
     +  SUM(DEF_D2, VDEF_T(Y,IR,IS3,T,DEF_D2)* IDEFP_T(IR,IS3,T,DEF_D2)  )
     +  SUM(DEF_D3, VDEF_T(Y,IR,IS3,T,DEF_D3)* IDEFP_T(IR,IS3,T,DEF_D3)  )
     )))

   - SUM(IR,
     SUM((IS3,T), IHOURSINST(IS3,T)
     * (SUM(DEF_U1, VDEF_T(Y,IR,IS3,T,DEF_U1)* IDEFP_T(IR,IS3,T,DEF_U1)  )
     +  SUM(DEF_U2, VDEF_T(Y,IR,IS3,T,DEF_U2)* IDEFP_T(IR,IS3,T,DEF_U2)  )
     +  SUM(DEF_U3, VDEF_T(Y,IR,IS3,T,DEF_U3)* IDEFP_T(IR,IS3,T,DEF_U3)  )
     )))

* Changes in consumers" utility relative to heat consumption:
    + SUM((IS3,T), IHOURSINST(IS3,T) * SUM(IR,
        SUM(DEF_D1, VDEF_T(Y,IR,IS3,T,DEF_D1) * IDEFP_T(IR,IS3,T,DEF_D1) )
     +  SUM(DEF_D2, VDEF_T(Y,IR,IS3,T,DEF_D2) * IDEFP_T(IR,IS3,T,DEF_D2) )
     +  SUM(DEF_D3, VDEF_T(Y,IR,IS3,T,DEF_D3) * IDEFP_T(IR,IS3,T,DEF_D3) )
     -  SUM(DEF_U1, VDEF_T(Y,IR,IS3,T,DEF_U1) * IDEFP_T(IR,IS3,T,DEF_U1) )
     -  SUM(DEF_U2, VDEF_T(Y,IR,IS3,T,DEF_U2) * IDEFP_T(IR,IS3,T,DEF_U2) )
     -  SUM(DEF_U3, VDEF_T(Y,IR,IS3,T,DEF_U3) * IDEFP_T(IR,IS3,T,DEF_U3) )
     ))

* Changes in consumers" utility relative to heat consumption:
    + SUM((IS3,T), IHOURSINST(IS3,T) * SUM(IA,
        SUM(DHF_D1, VDHF_T(Y,IA,IS3,T,DHF_D1) * IDHFP_T(IA,IS3,T,DHF_D1) )
     +  SUM(DHF_D2, VDHF_T(Y,IA,IS3,T,DHF_D2) * IDHFP_T(IA,IS3,T,DHF_D2) )
     +  SUM(DHF_D3, VDHF_T(Y,IA,IS3,T,DHF_D3) * IDHFP_T(IA,IS3,T,DHF_D3) )
     -  SUM(DHF_U1, VDHF_T(Y,IA,IS3,T,DHF_U1) * IDHFP_T(IA,IS3,T,DHF_U1) )
     -  SUM(DHF_U2, VDHF_T(Y,IA,IS3,T,DHF_U2) * IDHFP_T(IA,IS3,T,DHF_U2) )
     -  SUM(DHF_U3, VDHF_T(Y,IA,IS3,T,DHF_U3) * IDHFP_T(IA,IS3,T,DHF_U3) )
     ))


* Infeasibility penalties:
   + PENALTYQ*(
$ifi %BB1%==yes    +SUM((IA,IS3)$SUM(IGHYRS,IAGKFX(IA,IGHYRS)),(VQHYRSSEQ(IA,IS3,"IMINUS")+VQHYRSSEQ(IA,IS3,"IPLUS")))

$ifi %BB2%==yes       +SUM((IA,IS3)$SUM(IGHYRS,IAGKFX(IA,IGHYRS)),(VQHYRSSEQ(IA,IS3,"IMINUS")+VQHYRSSEQ(IA,IS3,"IPLUS")))
* BB4:

     +SUM((IA,IS3,T)$(SUM(IGHSTO$IAGK_HASORPOT(Y,IA,IGHSTO),1)), (VQHSTOVOLT(Y,IA,IS3,T,"IMINUS")+VQHSTOVOLT(Y,IA,IS3,T,"IPLUS")))
     +SUM((IA,IS3,T)$(SUM(IGESTO$IAGK_HASORPOT(Y,IA,IGESTO),1)), (VQESTOVOLT(Y,IA,IS3,T,"IMINUS")+VQESTOVOLT(Y,IA,IS3,T,"IPLUS")))
     +SUM((IR,IS3,T), (VQEEQ(Y,IR,IS3,T,"IMINUS")+VQEEQ(Y,IR,IS3,T,"IPLUS")))
     +SUM((IA,IS3,T)$IDH_SUMST(IA), (VQHEQ(Y,IA,IS3,T,"IMINUS")+VQHEQ(Y,IA,IS3,T,"IPLUS")))

     +SUM((IA,IS3)$(SUM(IGHYRS,IAGK_HASORPOT(Y,IA,IGHYRS))),(VQHYRSSEQ(Y,IA,IS3,"IMINUS")+VQHYRSSEQ(Y,IA,IS3,"IPLUS")))
     +SUM((IA,IS3)$(HYRSDATA(IA,"HYRSMINVOL",IS3) AND SUM(IGHYRS$IAGK_HASORPOT(Y,IA,IGHYRS),1)),(VQHYRSMINVOL(Y,IA,IS3,"IPLUS")))
     +SUM((IA,IS3)$(HYRSDATA(IA,"HYRSMAXVOL",IS3) AND SUM(IGHYRS$IAGK_HASORPOT(Y,IA,IGHYRS),1)),(VQHYRSMAXVOL(Y,IA,IS3,"IMINUS")))
     +SUM((IA,IS3,T)$SUM(IGHYRS,IAGK_HASORPOT(Y,IA,IGHYRS)), VQHYMAXG(Y,IA,IS3,T,"IMINUS"))

     +SUM((IA,IGKFIND)$IAGKN(IA,IGKFIND), (VQGKNACCUMNET(Y,IA,IGKFIND,"IPLUS")+VQGKNACCUMNET(Y,IA,IGKFIND,"IMINUS")))
*    TODO   +SUM((IA,IGKFIND)$IAGKN(IA,IGKFIND), (VQGKNACCUMGROSS(Y,IA,IGKFIND,"IPLUS")+VQGKNACCUMGROSS(Y,IA,IGKFIND,"IMINUS"))) Presently out, because QGKNACCUMNET(unfinished) is identical to QGKNACCUMgross
     +SUM((IRE,IRI), VQXKNACCUMNET(Y,IRE,IRI,"IPLUS")+VQXKNACCUMNET(Y,IRE,IRI,"IMINUS"))

     +SUM((IA,IGDISPATCH(IGKENOSTO),IS3,T), (VQGKE_UP(Y,IA,IGKENOSTO,IS3,T,"IMINUS")+VQGKE_UP(Y,IA,IGKENOSTO,IS3,T,"IPLUS")))
     +SUM((IA,IGDISPATCH(IGKHNOSTO),IS3,T), (VQGKH_UP(Y,IA,IGKHNOSTO,IS3,T,"IMINUS")+VQGKH_UP(Y,IA,IGKHNOSTO,IS3,T,"IPLUS")))
     +SUM((IRE,IRI,IS3,T)$IXKN(IRE,IRI), (VQXK_UP(Y,IRE,IRI,IS3,T,"IMINUS")+VQXK_UP(Y,IRE,IRI,IS3,T,"IPLUS")))

     +SUM((C,FFF)$FKPOT(C,FFF),   VQKFUEL(Y,C,FFF))
     +SUM((IR,FFF)$FKPOT(IR,FFF), VQKFUEL(Y,IR,FFF))
     +SUM((IA,FFF)$FKPOT(IA,FFF), VQKFUEL(Y,IA,FFF))


           )

* Add-on objective function contributions
* This file containts the gas induced additions to the objective function.
$ifi %GAS%==yes $include "../../base/addons/gas/gascosts.inc"
* Electricity transmission with variable amounts
$ifi %X3V%==yes $include "../../base/addons/x3v/model/x3vobj.inc";
* This file contains hydrogen induced additions to the objective function.
$ifi %NAP%==yes $include "../../base/addons/NAP/NAPobj.inc";
* This file contains transport induced additions to the objective function (KHED)
$ifi %TSP%==yes $include "../../base/addons/Transport/TSPObj.inc"
* This file contains Heat transmission induced additions to the objective function.
$ifi %HEATTRANS%==yes $include "../../base/addons/heattrans/model/htcosts.inc";


)
$ifi %BB4%==yes )
;

$offtext

* -----------------------------------------------------------------------------
$LABEL ENDOFFILE

