* File: eg_ya.inc
* This file is part of the Balmorel model.

* Modified last time: 01-02-2002 by (rus), 16-02-2004 (sns,ld), 20060328(hr), 200804xx(hr), 20110508(hr),20150312(Weiming)

* This file will print a table containing annnual electricity generation
* from all technologies in each country.
* (Incl. the negative electricity generation for heat pumps)


* ------------------------------------------------------------------------------

PUT eg_yr;

* First print headings:

if ((eg_yr.pw LT 32000),
eg_yr.pw = 32000;

PUT "Version:              " "%PRINTSEPARATOR%" SYSTEM.TITLE /;
PUT "File name:            " "%PRINTSEPARATOR%" "eg_yr.out" /;
PUT "Time-stamp:           " "%PRINTSEPARATOR%" SYSTEM.DATE " " SYSTEM.TIME  /;
$ifi %BB1%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE1"/;
$ifi %BB2%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE2"/;
$ifi %BB3%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE3"/;
$ifi %BB4%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE4"/;

PUT "Case-identification:  " "%PRINTSEPARATOR%" OCASEID.TS   //;

$ifi %BB1%==yes PUT / "Annual net electricity generation, old and new technologies, (incl. negative electricity generation for heat pumps)." //;
$ifi %BB2%==yes PUT / "Annual net electricity generation, old and new technologies, (incl. negative electricity generation for heat pumps)." //;
$ifi %BB3%==yes PUT / "Annual net electricity generation, old and new technologies, (incl. negative electricity generation for heat pumps)." //;
$ifi %BB4%==yes PUT / "Annual net electricity generation for regions(incl. negative electricity generation for heat pumps)." //;
PUT "Units: GWh" //;

);

* End of file headings.

* -----------------------------------------------------------------------------

*OEG_YR(IY411FIRST,IY411,IR,G)=SUM(IA$RRRAAA(IR,IA),SUM((S,T),IHOURSINST(S,T)*VGE_T(IY411,IA,G,S,T)));

LOOP(IY411FIRST,
EG_YR.LJ=1;
PUT "BB4 model starting year "  IY411FIRST.TL:4  " ....................................................................:" /;PUT /;
EG_YR.LJ=2;
  LOOP(IY411,PUT IY411.TL ; PUT /;
    LOOP(IR, PUT IR.TL:OTLWCRA ; PUT /;
    PUT /;
      LOOP(G,
      PUT G.TL:OTLWG;PUT "    ";
      OEG_YR(IY411FIRST,IY411,IR,G)=IOF0001*SUM(IA$RRRAAA(IR,IA),SUM((S,T),IHOURSINST(S,T)*VGE_T.L(IY411,IA,G,S,T)));
      PUT OEG_YR(IY411FIRST,IY411,IR,G):40:2 /;
      )
    PUT /;
    );
  PUT /;
  );


);


$ontext
LOOP(IY411FIRST,
EG_YR.LJ=1;
PUT "BB4 model starting year "  IY411FIRST.TL:4  " ....................................................................:" /;PUT /;
EG_YR.LJ=2;
  LOOP(IY411,PUT IY411.TL ; PUT /;
    LOOP(C,PUT C.TL:OTLWCRA ; PUT /; PUT /;
      LOOP(G,
      PUT G.TL:OTLWG;PUT "    ";
      OSCALAR1=0;
      OSCALAR1=IOF0001*SUM(IA$ICA(C,IA),SUM((S,T),IHOURSINST(S,T)*VGE_T.L(IY411,IA,G,S,T)));
      PUT OSCALAR1:40:2 /;
      );
    );
  PUT /;
  );

);

$offtext


$ontext

=IOF0001*SUM(IA$RRRAAA(IR,IA),SUM((S,T),IHOURSINST(S,T)*VGE_T(IY411,IA,G,S,T)))
eg_cy.LJ = 1;
*                         |<------ OTLW characters ----->|
PUT Y.TL:OTLW1:0;    PUT "                                " ; LOOP(C, PUT   "%PRINTSEPARATOR%"  C.TL:OTLW) ;
*                         |<------ OTLW characters ----->|                        |<------ OTLW characters ----->|
PUT  "%PRINTSEPARATOR%"  "                 Technology type"  "%PRINTSEPARATOR%"  "                            Fuel" /;
eg_cy.LJ = 2;

LOOP(G,

if(ignotetoh(g),
if( SUM(C,EGqCY(C,G)) NE 0,

  PUT OTLW1.ts  G.TL:OTLW ;
  LOOP(C, PUT   "%PRINTSEPARATOR%" (EGqCY(C,G)*IOF0001):OTLW:0 ;) ;  PUT     "%PRINTSEPARATOR%"  GDATA(G,'GDTYPE'):OTLW:0  "%PRINTSEPARATOR%"  GDATA(G,'GDFUEL'):OTLW:0 /;
*  PUT "    Technology type:  " GDATA(G,'GDTYPE');
*  LOOP(FFF$IGF(G,FFF), PUT "    Fuel:  " FFF.TL);
);

ELSE

if( SUM(C,EGqCY(C,G)) NE 0,

  PUT OTLW1.ts  G.TL:OTLW ;
  LOOP(C, PUT  "%PRINTSEPARATOR%" (-EGqCY(C,G) *IOF0001):OTLW:0 ;) ;  PUT     "%PRINTSEPARATOR%"  GDATA(G,'GDTYPE'):OTLW:0  "%PRINTSEPARATOR%"  GDATA(G,'GDFUEL'):OTLW:0 /;
);
);
);


*PUT  OTLW1.ts "TOTAL "; LOOP(C, PUT  "%PRINTSEPARATOR%" ( sum(ignotetoh,EGqCY(C,ignotetoh)*IOF0001) + sum(igetoh,-EGqCY(C,igetoh)*IOF0001)):OTLW:0 ; ); PUT //;
*              |<------ OTLW characters ----->|
PUT OTLW1.ts  "TOTAL (note any minus sign)     " ; LOOP(C, PUT  "%PRINTSEPARATOR%"  ( sum(ignotetoh,EGqCY(C,ignotetoh)*IOF0001) + sum(igetoh,-EGqCY(C,igetoh)*IOF0001)):OTLW:0 ; ); PUT //;

$offtext
