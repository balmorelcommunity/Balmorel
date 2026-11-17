* File: eg_gfcy.inc
* This file is part of the Balmorel model, version 2.12 Alpha (July 2005)).

* Created 200812xx(hr)

* This file will print a table containing annnual net electricity generation
* from all technologies and fuels in each country.
* (Incl. the negative electricity generation for heat pumps)


* ------------------------------------------------------------------------------

PUT eg_gfcy;

* First print headings:

if ((eg_gfcy.pw LT 32000),
eg_gfcy.pw = 32000;
PUT "Version:              " "%PRINTSEPARATOR%" SYSTEM.TITLE /;
PUT "File name:            " "%PRINTSEPARATOR%" "eg_gfcy.out" /;
PUT "Time-stamp:           " "%PRINTSEPARATOR%" SYSTEM.DATE " " SYSTEM.TIME  /;
PUT "Case-identification:  " "%PRINTSEPARATOR%" OCASEID.TS   /;
$ifi %BB1%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE1"/;
$ifi %BB2%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE2"/;
$ifi %BB3%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE3"/;

PUT "Annual net electricity generation" /;
PUT "(Incl. negative electricity generation for heat pumps)" /;
PUT "Units: GWh" //;

);

* ------------------------------------------------------------------------------------


PUT / /  "By technology and fuel:"  //;



eg_gfcy.LJ = 2;
PUT Y.TL:6:0; PUT "";  PUT OTLW.TS;

eg_gfcy.LJ = 1;
LOOP(C, PUT C.TL:16) ;PUT /;

eg_gfcy.LJ = 2;

LOOP(G,

if(ignotetoh(g),
if( SUM(C,EGqCY(C,G)) NE 0,

  PUT G.TL:OTLW "    " ;
  LOOP(C, PUT (EGqCY(C,G)*IOF0001):16:0 ;) ;
  PUT "    Technology type:  " GDATA(G,'GDTYPE');
  LOOP(FFF$IGF(G,FFF), PUT "    Fuel:  " FFF.TL);
  PUT /;
   );

ELSE

if( SUM(C,EGqCY(C,G)) NE 0,

  PUT G.TL:OTLW "    " ;
  LOOP(C, PUT (-EGqCY(C,G) *IOF0001):16:0 ;) ;
  PUT /;
   );
);
);


PUT "TOTAL " OTLW.TS; LOOP(C, PUT ( sum(ignotetoh,EGqCY(C,ignotetoh)*IOF0001) + sum(igetoh,-EGqCY(C,igetoh)*IOF0001)):16:0 ; ); PUT //;          /*sarah*/


*-------------------------------------------------------------------------------
*-------------------------------------------------------------------------------
put / / "By fuel and technology: "/ /;

eg_gfcy.LJ = 2;
PUT Y.TL:6:0; PUT "";  PUT OTLW.TS;


eg_gfcy.LJ = 1;
LOOP(C, PUT C.TL:16) ;PUT /;

eg_gfcy.LJ = 2;

put / "WIND:"/;
LOOP(G$igwnd(G),
if(ignotetoh(g),
if( SUM(C,EGqCY(C,G)) NE 0,
  PUT G.TL:OTLW  "    " ;
  LOOP(C, PUT (EGqCY(C,G)*IOF0001):16:0 ;) ;
  PUT /;
   );
ELSE
if( SUM(C,EGqCY(C,G)) NE 0,
  PUT G.TL:OTLW  "    " ;
  LOOP(C, PUT (-EGqCY(C,G) *IOF0001):16:0 ;) ;
  PUT /;
   );
););
* fejl PUT "TOTAL       " ; LOOP(C, PUT ( sum(ignotetoh,EGqCY(C,ignotetoh)*IOF0001) + sum(igetoh,-EGqCY(C,igetoh)*IOF0001)):16:0 ; ); PUT //;          /*sarah*/




put / "Hydro:"/;
LOOP(G$(ighyrs(G) or ighyrr(g)),
if(ignotetoh(g),
if( SUM(C,EGqCY(C,G)) NE 0,
  PUT G.TL:OTLW  "    " ;
  LOOP(C, PUT (EGqCY(C,G)*IOF0001):16:0 ;) ;
  PUT /;
   );
ELSE
if( SUM(C,EGqCY(C,G)) NE 0,
  PUT G.TL:OTLW  "    " ;
  LOOP(C, PUT (-EGqCY(C,G) *IOF0001):16:0 ;) ;
  PUT /;
   );
));
* fejl PUT "TOTAL       " ; LOOP(C, PUT ( sum(ignotetoh,EGqCY(C,ignotetoh)*IOF0001) + sum(igetoh,-EGqCY(C,igetoh)*IOF0001)):16:0 ; ); PUT //;          /*sarah*/

put / "Bio-fired:  here preliminarily defined as MUNIWASTE, STRAW, WOOD and WOODWASTE"/;
LOOP(G$(IGF(G,'MUNIWASTE') OR IGF(G,'STRAW') OR IGF(G,'WOOD') OR IGF(G,'WOODWASTE')),
if(ignotetoh(g),
if( SUM(C,EGqCY(C,G)) NE 0,
  PUT G.TL:OTLW  "    " ;
  LOOP(C, PUT (EGqCY(C,G)*IOF0001):16:0 ;) ;
  PUT /;
   );
ELSE
if( SUM(C,EGqCY(C,G)) NE 0,
  PUT G.TL:OTLW  "    " ;
  LOOP(C, PUT (-EGqCY(C,G) *IOF0001):16:0 ;) ;
  PUT /;
   );
));




put / "GAS: "/;
LOOP(G$IGF(G,'NATGAS'),
if(ignotetoh(g),
if( SUM(C,EGqCY(C,G)) NE 0,
  PUT G.TL:OTLW  "    " ;
  LOOP(C, PUT (EGqCY(C,G)*IOF0001):16:0 ;) ;
  PUT /;
   );
ELSE
if( SUM(C,EGqCY(C,G)) NE 0,
  PUT G.TL:OTLW  "    " ;
  LOOP(C, PUT (-EGqCY(C,G) *IOF0001):16:0 ;) ;
  PUT /;
   );
));
