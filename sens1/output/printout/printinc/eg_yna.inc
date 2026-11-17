* File: eg_yna.inc
* This file is part of the Balmorel model.

* Modified last time: 20150421(Weiming)

* This file will print a table containing annnual electricity generation
* from all technologies of aggerated countries.
* (Incl. the negative electricity generation for heat pumps)


* ------------------------------------------------------------------------------

PUT eg_yna;

* First print headings:

if ((eg_yna.pw LT 32000),
eg_yna.pw = 32000;

PUT "Version:              " "%PRINTSEPARATOR%" SYSTEM.TITLE /;
PUT "File name:            " "%PRINTSEPARATOR%" "eg_yna.out" /;
PUT "Time-stamp:           " "%PRINTSEPARATOR%" SYSTEM.DATE " " SYSTEM.TIME  /;
$ifi %BB1%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE1"/;
$ifi %BB2%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE2"/;
$ifi %BB3%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE3"/;
$ifi %BB4%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE4"/;

PUT "Case-identification:  " "%PRINTSEPARATOR%" OCASEID.TS   //;


$ifi %BB4%==yes PUT / "Annual net electricity generation for all the simulated countries(incl. negative electricity generation for heat pumps)." //;
PUT "Units: GWh" //;

);

* End of file headings.

* -----------------------------------------------------------------------------

*OEG_YNA(IY411FIRST,IY411,G)=SUM(C,SUM(IA$ICA(C,IA),SUM((S,T),IHOURSINST(S,T)*VGE_T(IY411,IA,G,S,T))));

LOOP(IY411FIRST,
EG_YNA.LJ=1;
PUT "BB4 model starting year "  IY411FIRST.TL:4  " ....................................................................:" /;PUT /;
EG_YNA.LJ=2;
  LOOP(IY411,PUT IY411.TL ; PUT /;
    OSCALAR1=0;
    LOOP(G,
    PUT G.TL:OTLWG;PUT "    ";
    OSCALAR1=IOF0001*SUM(C,SUM(IA$ICA(C,IA),SUM((S,T),IHOURSINST(S,T)*VGE_T.L(IY411,IA,G,S,T))));
    PUT OSCALAR1:40:2 /;
    );
  PUT /; 
  );

);


