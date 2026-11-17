* File ep_yc.inc.

* Modified 20150422(Weiming). 20161024 (hr): Guading against division-by-zero (search NA). Todo: detect the source for division-by-0, at do something about that. 20171213(hr) update for BB4

* This file will print a table containing
* the annual weighted average marginal electricity price by C.
* Consumption weighting used.



* -----------------------------------------------------------------------------

PUT ep_yc;

* First print headings:

if ((ep_yc.pw LT 32000),
ep_yc.pw = 32000;
PUT "Version:              " "%PRINTSEPARATOR%" SYSTEM.TITLE /;
PUT "Printed from file:    " "%PRINTSEPARATOR%" "ep_yc.inc" /;
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

*Weiming:annually averaged, To be implenmented


PUT "Annual average electricity price, weighted by consumption quantity:" /;


LOOP(IY411FIRST,
PUT "BB4 model starting year "  IY411FIRST.TL:4 "..............................:" //;
ep_yc.LJ = 1;
PUT "YEAR        " ; LOOP(C, PUT C.TL:OTLWCRA); PUT /;
ep_yc.LJ = 2;
LOOP(IY411,
  PUT IY411.TL ;
    LOOP(C,
         OSCALAR1=0;  /* To become counter of demand */
         OSCALAR3=0;  /* To become total cost        */
         OSCALAR2=0;  /* To become total consumption */
         LOOP(IR$CCCRRR(C,IR),
          LOOP(DEUSER,
           LOOP(IS3,  LOOP(T,
                 OSCALAR1 = (((DE(IY411,IR,DEUSER) * DE_VAR_T(IR,DEUSER,IS3,T)) / IDE_SUMST(IR,DEUSER))$(IDE_SUMST(IR,DEUSER) GT 0)   !! MAYBE USE IDE_T

$ifi %dflexquant%==yes   + SUM(DEF_U1,VDEF_T.L(IY411,IR,DEUSER,IS3,T,DEF_U1) )
$ifi %dflexquant%==yes   - SUM(DEF_D1,VDEF_T.L(IY411,IR,DEUSER,IS3,T,DEF_D1) )
$ifi %dflexquant%==yes   + SUM(DEF_U2,VDEF_T.L(IY411,IR,DEUSER,IS3,T,DEF_U2) )
$ifi %dflexquant%==yes   - SUM(DEF_D2,VDEF_T.L(IY411,IR,DEUSER,IS3,T,DEF_D2) )
$ifi %dflexquant%==yes   + SUM(DEF_U3,VDEF_T.L(IY411,IR,DEUSER,IS3,T,DEF_U3) )
$ifi %dflexquant%==yes   - SUM(DEF_D3,VDEF_T.L(IY411,IR,DEUSER,IS3,T,DEF_D3) )
                            );                                                  !! TODO:  Correct not to divide by  (1-DISLOSS_E(IR))?    Cf ep_yr.inc
                 OSCALAR2 = OSCALAR2 + OSCALAR1 * IHOURSINST(IS3,T);
                 OSCALAR3 = OSCALAR3 + OSCALAR1 * OEP_YRT(IY411FIRST,IY411,IR,IS3,T)* IHOURSINST(IS3,T);
                 ));

         );
     OEP_YC(IY411FIRST,IY411,C)=OSCALAR3 / (OSCALAR2$(OSCALAR2 NE 0) + NA$(OSCALAR2 EQ 0));
     PUT OEP_YC(IY411FIRST,IY411,C):OTLWCRA:2;
    );PUT /;
    );PUT /;
  );PUT /;
);PUT /;

* -----------------------------------------------------------------------------

