* File ep_yr.inc.

* Modified last time: 01-02-2002 (rus), ... ,  20150130(hr),20150312(Weiming)

* This file will print a table containing
* the annual weighted average marginal electricity price by IR.
* Different weighting used.



* -----------------------------------------------------------------------------

PUT ep_yr;

* First print headings:

if ((ep_yr.pw LT 32000),
ep_yr.pw = 32000;
PUT "Version:              " "%PRINTSEPARATOR%" SYSTEM.TITLE /;
PUT "Printed from file:    " "%PRINTSEPARATOR%" "ep_yr.inc" /;
PUT "Time-stamp:           " "%PRINTSEPARATOR%" SYSTEM.DATE " " SYSTEM.TIME  /;
$ifi %BB1%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE1"/;
$ifi %BB2%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE2"/;
$ifi %BB3%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE3"/;
$ifi %BB4%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE4"/;
PUT "Case-identification:  " "%PRINTSEPARATOR%" OCASEID.TS   //;

PUT "Annual electricity price, several versions, all years in each BB4 model." /;
PUT "Currency: " OMONEY.TS "  with exchange rate to input currency: "  OMONEY:7:3  " ("OMONEY.TS"/"OIMONEY.TS").";
PUT "   (The output currency and its relation to input currency is specified in input data file OMONEY.inc. The input currency is specified in file print1.inc.)" /;
PUT "Units: "; PUT OMONEY.ts "/MWh" //;
$ifi %BB4%==yes PUT "Electricity prices are in undiscounted values." //;

PUT "Annual average electricity price, weighted by production quantity: NOT IMPLEMENTED YET"/;
PUT "Annual average electricity price, weighted by consumption quantity"//;

);

* End of file headings.
* -----------------------------------------------------------------------------

*Weiming: annually averaged, To be implemented


PUT "Annual average electricity price, weighted by consumption quantity:" /;

*OEP_YR(IY411FIRST,IY411,IR) = SUM((S,T),OEP_YRT(IY411FIRST,IY411,IR,S,T));

LOOP(IY411FIRST,                                                                !! TODO: why only one year?
PUT "BB4 model starting year "  IY411FIRST.TL:4 "..............................:" //;
ep_yr.LJ = 1;
PUT "YEAR        " ; LOOP(IR, PUT IR.TL:OTLWCRA); PUT /;
ep_yr.LJ = 2;
LOOP(IY411,
  PUT IY411.TL ;
    LOOP(IR,
    LOOP(DEUSER,
         OSCALAR1=0;  /* To become counter of demand */
         OSCALAR3=0;  /* To become total cost        */
         OSCALAR2=0;  /* To become total consumption */
      LOOP(IS3,  LOOP(T,

         OSCALAR1 =    (((DE(IY411,IR,DEUSER) * DE_VAR_T(IR,DEUSER,IS3,T)) / IDE_SUMST(IR,DEUSER))$(IDE_SUMST(IR,DEUSER) GT 0)
$ifi %dflexquant%==yes   + SUM(DEF_U1,VDEF_T.L(IY411,IR,DEUSER,IS3,T,DEF_U1) )
$ifi %dflexquant%==yes   - SUM(DEF_D1,VDEF_T.L(IY411,IR,DEUSER,IS3,T,DEF_D1) )
$ifi %dflexquant%==yes   + SUM(DEF_U2,VDEF_T.L(IY411,IR,DEUSER,IS3,T,DEF_U2) )
$ifi %dflexquant%==yes   - SUM(DEF_D2,VDEF_T.L(IY411,IR,DEUSER,IS3,T,DEF_D2) )
$ifi %dflexquant%==yes   + SUM(DEF_U3,VDEF_T.L(IY411,IR,DEUSER,IS3,T,DEF_U3) )
$ifi %dflexquant%==yes   - SUM(DEF_D3,VDEF_T.L(IY411,IR,DEUSER,IS3,T,DEF_D3) )
          )/(1-DISLOSS_E(IR));                                                  !! TODO:  Correct to divide by  (1-DISLOSS_E(IR))?    Cf ep_yc.inc
           OSCALAR2 = OSCALAR2 + OSCALAR1 * IHOURSINST(IS3,T);
           OSCALAR3 = OSCALAR3 + OSCALAR1 * OEP_YRT(IY411FIRST,IY411,IR,IS3,T)* IHOURSINST(IS3,T);
           ));

         OEP_YR(IY411FIRST,IY411,IR)=(OSCALAR3 / OSCALAR2)$(OSCALAR2 NE 0)  + NA$(OSCALAR2 EQ 0);
         PUT OEP_YR(IY411FIRST,IY411,IR):OTLWCRA:2;

    );PUT /;
  );PUT /;
);PUT /;
);PUT /;

* -----------------------------------------------------------------------------
