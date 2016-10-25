* File: eg_yc.inc
* This file is part of the Balmorel model.

* Modified last time: 20150423(Weiming)

* This file will print a table containing annnual electricity generation
* from all technologies in each country.
* (Incl. the negative electricity generation for heat pumps)


* ------------------------------------------------------------------------------

PUT eg_yc;

* First print headings:

if ((eg_yc.pw LT 32000),
eg_yc.pw = 32000;

PUT "Version:              " "%PRINTSEPARATOR%" SYSTEM.TITLE /;
PUT "File name:            " "%PRINTSEPARATOR%" "eg_yc.out" /;
PUT "Time-stamp:           " "%PRINTSEPARATOR%" SYSTEM.DATE " " SYSTEM.TIME  /;
$ifi %BB1%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE1"/;
$ifi %BB2%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE2"/;
$ifi %BB3%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE3"/;
$ifi %BB4%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE4"/;

PUT "Case-identification:  " "%PRINTSEPARATOR%" OCASEID.TS   //;

$ifi %BB1%==yes PUT / "Annual net electricity generation, old and new technologies, (incl. negative electricity generation for heat pumps)." //;
$ifi %BB2%==yes PUT / "Annual net electricity generation, old and new technologies, (incl. negative electricity generation for heat pumps)." //;
$ifi %BB3%==yes PUT / "Annual net electricity generation, old and new technologies, (incl. negative electricity generation for heat pumps)." //;
$ifi %BB4%==yes PUT / "Annual net electricity generation for countries(incl. negative electricity generation for heat pumps)." //;
PUT "Units: GWh" //;

);

* End of file headings.

* -----------------------------------------------------------------------------

*OEG_YC(IY411FIRST,IY411,C,G)=SUM(IA$ICA(C,IA),SUM((S,T),IHOURSINST(S,T)*VGE_T(IY411,IA,G,S,T)));

LOOP(IY411FIRST,
EG_YC.LJ=1;
PUT "BB4 model starting year "  IY411FIRST.TL:4  " ....................................................................:" /;PUT /;
EG_YC.LJ=2;
  LOOP(IY411,PUT IY411.TL ; PUT /;
    LOOP(C,PUT C.TL:OTLWCRA ; PUT /; PUT /; 
      LOOP(G,
      PUT G.TL:OTLWG;PUT "    ";
      OSCALAR1=0;
      OSCALAR1=IOF0001*SUM(IA$ICA(C,IA),SUM((S,T),IHOURSINST(S,T)*VGE_T.L(IY411,IA,G,S,T)));
      PUT OSCALAR1:40:2 /;
      );PUT /;
    );
  PUT /;
  );

);


