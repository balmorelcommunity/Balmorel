* File: esto_at.inc
* This file is part of the Balmorel model, version 2.12 Alpha (July 2005).

* Created 2005.07.31 (hr)
* Modified last time:  2005.10.29 (hr), 20060328(HR)

* This file will print a table containing content of short term electricity storages
* at the beginning of each time segment
* and the loading and unloading of the storage during each time segment.

PUT esto_at;


* First print headings:
esto_at.LJ = 1;
if ((esto_at.pw LT 32000),
esto_at.pw = 32000;
PUT "Version:              " SYSTEM.TITLE /;
PUT "File name:            esto_at.out" /;
PUT "File created:         " SYSTEM.DATE " " SYSTEM.TIME /;
PUT "Case-identification:  " OCASEID.TS //;
PUT "Short term electricity storage contents (MWh) at the beginning of each time segment "/;
PUT "and loading and unloading (MW and MWh) during each time segment."///

PUT "--------------------------------------------------------------------------------"/;
PUT "It may be usefull to recall the assumed lengths (hours) of the time segments "/;
PUT "which are used in relation to the representation of the daily cyclic storage movements:"/;
PUT "               ";
LOOP(T,
PUT  T.TL:8 ;)  PUT /;
LOOP(S,
PUT S.TL:15;
LOOP(T, PUT ( IHOURSINst(S,T)/idaysin_s(S)):8:2); PUT /;
);
PUT "--------------------------------------------------------------------------------"///;

* End of headings.
);
* ------------------------------------------------------------------------------------
* If scenarios (i.e., more than base case) print scenario heading:
IF((CARD(SCENARIO) GT 1),
PUT /"*==============================================================================="/;
PUT "*       "   SCENARIO.TL "      " SCENARIO.TE(SCENARIO) /;
PUT "*==============================================================================="//;
);
* End of scenario heading
* ------------------------------------------------------------------------------------

esto_at.LJ = 2;
LOOP(C,
LOOP(IA$ICA(C,IA),
PUT IA.TL:18 " :   Storage capacity (MWh): "
   (SUM(IGESTO$(IGKFX_Y(IA,IGESTO) GT 0),IGKFX_Y(IA,IGESTO))):10:1/;
PUT "Content at beginning of time segment (MWh)"  /;
PUT "            ";
esto_at.LJ = 1;
LOOP(T, PUT T.TL:12 ); PUT /;


esto_at.LJ = 2;
LOOP(S,
PUT S.TL:12;
LOOP(T, PUT VESTOVOLT.L(IA,S,T):12:1); PUT /;
)PUT /;


LOOP((ISALIAS,ITALIAS)$((ORD(ISALIAS) EQ 1) AND (ORD(ITALIAS) EQ 1)),
PUT IA.TL:18 " :   Loading capacity (MW): "
    VESTOLOADT.UP(IA,ISALIAS,ITALIAS):8:1 "   Unloading capcity (MW): "
    SUM(IGESTO,VGE_T.UP(IA,IGESTO,ISALIAS,ITALIAS)):8:1/;
);
PUT "Loading (+) and unloading (-) during time segment (MW and MWh)"  /;
PUT "            ";
esto_at.LJ = 1;


LOOP(T, PUT T.TL:12 ); PUT /;
esto_at.LJ = 2;


LOOP(S,
PUT S.TL:12  ;
LOOP(T,
 PUT (VESTOLOADT.L(IA,S,T)-SUM(IGESTO,VGE_T.L(IA,IGESTO,S,T)*GDATA(IGESTO,'GDFE'))):12:3;
) PUT /)


LOOP(S,
PUT S.TL:12  ;
LOOP(T,
PUT ((VESTOLOADT.L(IA,S,T)-SUM(IGESTO,VGE_T.L(IA,IGESTO,S,T)*GDATA(IGESTO,'GDFE')))*IHOURSINST(S,T)/idaysin_s(S)):12:3;
)PUT /)





PUT /;

));