* File: esto_at.inc
* This file is part of the Balmorel model.

* Created 2005.07.31 (hr)
* Modified last time:  2005.10.29 (hr), 20060328(HR), 20160407(hr)

* This file will print a table containing content of short term electricity storages
* at the beginning of each time segment
* and the loading and unloading of the storage during each time segment.

PUT esto_at;


* First print headings:
esto_at.LJ = 1;
if ((esto_at.pw LT 32000),
esto_at.pw = 32000;
PUT "Version:              " "%PRINTSEPARATOR%" SYSTEM.TITLE /;
PUT "File name:            " "%PRINTSEPARATOR%" "esto_at.out" /;
PUT "Time-stamp:           " "%PRINTSEPARATOR%" SYSTEM.DATE " " SYSTEM.TIME  /;
$ifi %BB1%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE1"/;
$ifi %BB2%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE2"/;
$ifi %BB3%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE3"/;
PUT "Case-identification:  " "%PRINTSEPARATOR%" OCASEID.TS   //;

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
LOOP(T, PUT ( IHOURSINst(S,T)/(IOF365*WEIGHT_S(S)/IWEIGHSUMS)):8:2); PUT /;
);
PUT "--------------------------------------------------------------------------------"///;

* End of headings.
);
* ------------------------------------------------------------------------------------

esto_at.LJ = 2;
LOOP(C,
LOOP(IA$ICA(C,IA),
PUT IA.TL:18 " :   Storage capacity (MWh): "
   (SUM(IGESTOALL$(IGKFX_Y(IA,IGESTOALL) GT 0),IGKFX_Y(IA,IGESTOALL))):10:1/;
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
    SUM(IGESTOALL,VGE_T.UP(IA,IGESTOALL,ISALIAS,ITALIAS)):8:1/;
);
PUT "Loading (+) and unloading (-) during time segment (MW and MWh)"  /;
PUT "            ";
esto_at.LJ = 1;


LOOP(T, PUT T.TL:12 ); PUT /;
esto_at.LJ = 2;


LOOP(S,
PUT S.TL:12  ;
LOOP(T,
 PUT (VESTOLOADT.L(IA,S,T)-SUM(IGESTOALL,VGE_T.L(IA,IGESTOALL,S,T)*GDATA(IGESTOALL,'GDFE'))):12:3;
) PUT /)


LOOP(S,
PUT S.TL:12  ;
LOOP(T,
PUT ((VESTOLOADT.L(IA,S,T)-SUM(IGESTOALL,VGE_T.L(IA,IGESTOALL,S,T)*GDATA(IGESTOALL,'GDFE')))*IHOURSINST(S,T)/(IOF365*WEIGHT_S(S)/IWEIGHSUMS)):12:3;
)PUT /)





PUT /;

));
