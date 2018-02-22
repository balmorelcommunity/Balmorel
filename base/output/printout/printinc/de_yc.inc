* File: de_yc.inc
* This file is part of the Balmorel model.

* Modified last time: 20150422(Weiming)  20171213(hr) update for BB4

* This file will print a table containing annnual electricity demand
* (Excl. the electricity consumption for heat pumps)


* ------------------------------------------------------------------------------

PUT de_yc;

* First print headings:

if ((de_yc.pw LT 32000),
de_yc.pw = 32000;

PUT "Version:              " "%PRINTSEPARATOR%" SYSTEM.TITLE /;
PUT "File name:            " "%PRINTSEPARATOR%" "de_yc.out" /;
PUT "Time-stamp:           " "%PRINTSEPARATOR%" SYSTEM.DATE " " SYSTEM.TIME  /;
$ifi %BB1%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE1"/;
$ifi %BB2%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE2"/;
$ifi %BB3%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE3"/;
$ifi %BB4%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE4"/;

PUT "Case-identification:  " "%PRINTSEPARATOR%" OCASEID.TS   //;

PUT / "Annual net power demand(incl. negative electricity generation for heat pumps)." //;
PUT "Units: TWh" //;

);

* End of file headings.

* -----------------------------------------------------------------------------





LOOP(IY411FIRST,
DE_YC.LJ=1;
PUT "BB4 model starting year "  IY411FIRST.TL:4  " ....................................................................:" /;PUT /;
DE_YC.LJ=2;

  LOOP(IY411,PUT IY411.TL ; PUT /;
    LOOP(C,PUT C.TL:OTLWCRA ;
    LOOP(DEUSER,
            OSCALAR1=0;
            OSCALAR1=IOF0000001*SUM((IR,IS3,T)$CCCRRR(C,IR),
            IHOURSINST(IS3,T)*(IDE_T(IY411,IR,DEUSER,IS3,T)
$ifi %dflexquant%==yes   + SUM(DEF_U1,VDEF_T.L(IY411,IR,DEUSER,IS3,T,DEF_U1) )
$ifi %dflexquant%==yes   - SUM(DEF_D1,VDEF_T.L(IY411,IR,DEUSER,IS3,T,DEF_D1) )
$ifi %dflexquant%==yes   + SUM(DEF_U2,VDEF_T.L(IY411,IR,DEUSER,IS3,T,DEF_U2) )
$ifi %dflexquant%==yes   - SUM(DEF_D2,VDEF_T.L(IY411,IR,DEUSER,IS3,T,DEF_D2) )
$ifi %dflexquant%==yes   + SUM(DEF_U3,VDEF_T.L(IY411,IR,DEUSER,IS3,T,DEF_U3) )
$ifi %dflexquant%==yes   - SUM(DEF_D3,VDEF_T.L(IY411,IR,DEUSER,IS3,T,DEF_D3) )

                              )
                     ));

             PUT OSCALAR1:40:2 /;
        );PUT /;
  );

);


