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

*Weiming:annually averaged, To be implenmented


PUT "Annual average electricity price, weighted by consumption quantity:" /;

*OEP_YR(IY411FIRST,IY411,IR) = SUM((S,T),OEP_YRT(IY411FIRST,IY411,IR,S,T));

LOOP(IY411FIRST,
PUT "BB4 model starting year "  IY411FIRST.TL:4 "..............................:" //;
ep_yr.LJ = 1;
PUT "YEAR        " ; LOOP(IR, PUT IR.TL:OTLWCRA); PUT /;
ep_yr.LJ = 2;
LOOP(IY411,
  PUT IY411.TL ;
    LOOP(IR,

         OSCALAR1=0;  /* To become counter of demand */
         OSCALAR3=0;  /* To become total cost        */
         OSCALAR2=0;  /* To become total consumption */
                 LOOP(S,  LOOP(T,
                 OSCALAR1 =(IDE_T(IY411,IR,S,T)
                  + SUM(DEF_U1,VDEF_T.L(IY411,IR,S,T,DEF_U1))
                  - SUM(DEF_D1,VDEF_T.L(IY411,IR,S,T,DEF_D1) )
                  + SUM(DEF_U2,VDEF_T.L(IY411,IR,S,T,DEF_U2) )
                  - SUM(DEF_D2,VDEF_T.L(IY411,IR,S,T,DEF_D2) )
                  + SUM(DEF_U3,VDEF_T.L(IY411,IR,S,T,DEF_U3) )
                  - SUM(DEF_D3,VDEF_T.L(IY411,IR,S,T,DEF_D3) )
                   );
                 OSCALAR2 = OSCALAR2 + OSCALAR1 * IHOURSINST(S,T);
                 OSCALAR3 = OSCALAR3 + OSCALAR1 * OEP_YRT(IY411FIRST,IY411,IR,S,T)* IHOURSINST(S,T);
                         ));

         OEP_YR(IY411FIRST,IY411,IR)=(OSCALAR3 / OSCALAR2)$(OSCALAR2 NE 0)  + NA$(OSCALAR2 EQ 0);

PUT OEP_YR(IY411FIRST,IY411,IR):OTLWCRA:2;

    );PUT /;
  );PUT /;
);PUT /;

* -----------------------------------------------------------------------------

