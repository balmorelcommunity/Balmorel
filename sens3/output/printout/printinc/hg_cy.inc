* File: hg_cy.inc

* Modified last time: 26-09-2002 by (rus), 16-02-2004 (ld), 20060328(hr), 20090121(hr), 20160407(hr)

* This file will print a table containing annnual heat generation at all
* technologies in each country and a table with use of heat storage.


* -----------------------------------------------------------------------------

PUT hg_cy;

* First print headings:

if ((hg_cy.pw LT 32000),
hg_cy.pw = 32000;
PUT "Version:              " "%PRINTSEPARATOR%" SYSTEM.TITLE /;
PUT "File name:            " "%PRINTSEPARATOR%" "hg_cy.out" /;
PUT "Time-stamp:           " "%PRINTSEPARATOR%" SYSTEM.DATE " " SYSTEM.TIME  /;
$ifi %BB1%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE1"/;
$ifi %BB2%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE2"/;
$ifi %BB3%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE3"/;
PUT "Case-identification:  " "%PRINTSEPARATOR%" OCASEID.TS   /;

PUT "Annual heat generation and heat taken from heat storage" //;

PUT "Units: GWh" //;

);

* End of file headings.
* ------------------------------------------------------------------------------------

* -----------------------------------------------------------------------------

hg_cy.LJ = 1;
PUT "Annual heat generation in " PUT Y.TL:4:0 ; PUT "     "; LOOP(C, PUT C.TL:12) ;PUT /;
hg_cy.LJ = 2;

LOOP(G,

if(not IGHSTOALL(G),




if( sum(C,HGqCY(C,G)) ne 0,

  PUT G.TL:35 ;
  LOOP(C, PUT (HGqCY(C,G) *IOF0001):12:0 ;) ;
  LOOP(FFF$IGF(G,FFF), PUT "        Fuel:  " FFF.TL);
  PUT /;
   );
)) ;

PUT "TOTAL                              " ; LOOP(C, PUT ( HZGqCY(C)*IOF0001):12:0 ; ); PUT //;

PUT "Annual heat taken from storage in " PUT Y.TL:4:0 ; PUT "  "; LOOP(C, PUT C.TL:12) ;PUT /;

LOOP(IGHSTOALL(G),

if( sum(C,HGqCY(C,G)) ne 0,

  PUT G.TL:35 ;
  LOOP(C, PUT (HGqCY(C,G) *IOF0001):12:0 ;) ;
  PUT /;
   );
) ;

PUT "TOTAL                              " ; LOOP(C, PUT sum(IGHSTOALL(G), HGqCY(C,G)*IOF0001):12:0 ; ); PUT //;

* PUT "Heat generation incl. heat storage " ; LOOP(C, PUT sum(G, HGqCY(C,G)*IOF0001):12:0 ; ); PUT //;







PUT / /  "Annual Heat production by Area and Technology ()"//;

*TODO!!!

$ontext
LOOP(C, LOOP(IA$ICA(C,IA),
 PUT  C.TL:12, IA.TL:35  , " Demand:" (IOF0001*DH(y,ia)):12:0 ,  "   Production:"  (IOF0001*SUM((IS3,T), IHOURSINST(IS3,T) *(SUM(IGH$IAGK_Y(IA,IGH), VGH_T.L(IA,IGH,IS3,T)) + SUM(IGH$IAGKN(IA,IGH),  VGHN_T.L(IA,IGH,IS3,T)) -VHSTOLOADT.l(IA,IS3,T) ))):12:0  ;
 put "   Old: "; loop(IGH$IAGK_Y(IA,IGH),  put" "  igh.tl:35  (IOF0001*SUM((IS3,T), IHOURSINST(IS3,T) *  VGH_T.L(IA,IGH,IS3,T))):12:0 ;  );
 put "   Hstoload:                       " (IOF0001*SUM((IS3,T), IHOURSINST(IS3,T) *VHSTOLOADT.l(IA,IS3,T))):12:0 ;
 put "   New:                            "; loop(IGH$IAGKN(IA,IGH),   put" "  igh.tl:35  (IOF0001*SUM((IS3,T), IHOURSINST(IS3,T) * VGHN_T.L(IA,IGH,IS3,T))):12:0 ;  );
* [Mangler New] put "   Hstoload: " (IOF0001*SUM((IS3,T), IHOURSINST(IS3,T) *VHSTOLOADT.l(IA,IS3,T)));
 put /;
));
$offtext  