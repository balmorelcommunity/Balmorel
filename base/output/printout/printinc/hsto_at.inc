* File: hsto_at.inc
* This file is part of the Balmorel model.


* Created 2001.03.20 (hrv), 16-02-2004 (ld)
* Modified last time: 2005.07.31 (hr), 20060328(hr), 20160407(hr)

* This file will print a table containing content of short term heat storages
* at the beginning of each time segment
* and the loading and unloading of the storage during each time segment.

PUT hsto_at;


* First print headings:
hsto_at.LJ = 1;
if ((hsto_at.pw LT 32000),
hsto_at.pw = 32000;
PUT "Version:              " "%PRINTSEPARATOR%" SYSTEM.TITLE /;
PUT "File name:            " "%PRINTSEPARATOR%" "hsto_at.out" /;
PUT "Time-stamp:           " "%PRINTSEPARATOR%" SYSTEM.DATE " " SYSTEM.TIME  /;
$ifi %BB1%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE1"/;
$ifi %BB2%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE2"/;
$ifi %BB3%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE3"/;
PUT "Case-identification:  " "%PRINTSEPARATOR%" OCASEID.TS   //;

PUT "Short term heat storage contents (MWh) at the beginning of each time segment "/;
PUT "and loading and unloading (MW and MWh) during each time segment."/
PUT "--------------------------------------------------------------------------------"/;
PUT "It may be usefull to recall the assumed lengths (hours) of the time segments "/;
PUT "which are used in relation to the representation of the daily cyclic storage movements:"/;
PUT "               ";
LOOP(T,
PUT  T.TL:8 ;)  PUT /;
LOOP(S,
PUT S.TL:15;
LOOP(T, PUT ( IHOURSINst(s,T)/(IOF365*WEIGHT_S(S)/IWEIGHSUMS)):8:2); PUT /;
);
PUT "Be aware that you use the intended modelling of the short term heat storage. "/;
PUT "If you have a gross time resolution within the season S you may intend to model "/;
PUT "the heat cycles within the season as represented by 1 typical day;" /
PUT "in this case you should in equation QHSTOVOLT have a division by CYCLESINS(S)."/;
PUT "If you have a fine time resolution within the season S (e.g., a season corresponds to a week)"/;
PUT "and intend to represent all daily cycles within S (e.g.,  each hour within the week "/;
PUT "is represented in T) then CYCLESINS(S) should be 1, otherwise larger."/;
PUT "--------------------------------------------------------------------------------"///;
);

* End of file headings.
* ------------------------------------------------------------------------------------


hsto_at.LJ = 2;
LOOP(C,
LOOP(IA$ICA(C,IA),
PUT IA.TL:18 " :   Storage capacity (MWh): "
   (SUM(IGHSTOALL$(IGKFX_Y(IA,IGHSTOALL) GT 0),IGKFX_Y(IA,IGHSTOALL))):10:1/;
PUT "Content at beginning of time segment (MWh)"  /;
PUT "            ";
hsto_at.LJ = 1;
LOOP(T, PUT T.TL:12 ); PUT /;


hsto_at.LJ = 2;
LOOP(S,
PUT S.TL:12;
LOOP(T, PUT VHSTOVOLT.L(IA,S,T):12:1); PUT /;
)PUT /;


LOOP((ISALIAS,ITALIAS)$((ORD(ISALIAS) EQ 1) AND (ORD(ITALIAS) EQ 1)),
PUT IA.TL:18 " :   Loading capacity (MW): "
    VHSTOLOADT.UP(IA,ISALIAS,ITALIAS):8:1 "   Unloading capcity (MW): "
    SUM(IGHSTOALL,VGH_T.UP(IA,IGHSTOALL,ISALIAS,ITALIAS)):8:1/;
);
PUT "Loading (+) and unloading (-) during time segment (MW):"  /;
PUT "            ";
hsto_at.LJ = 1;


LOOP(T, PUT T.TL:12 ); PUT /;
hsto_at.LJ = 2;


LOOP(S,
PUT S.TL:12  ;
LOOP(T,
 PUT (VHSTOLOADT.L(IA,S,T)-SUM(IGHSTOALL,VGH_T.L(IA,IGHSTOALL,S,T)*GDATA(IGHSTOALL,'GDFE'))):12:3;
) PUT /)
PUT /"Loading (+) and unloading (-) during time segment (MWh):"  /;
LOOP(S,
PUT S.TL:12  ;
LOOP(T,
PUT ((VHSTOLOADT.L(IA,S,T)-SUM(IGHSTOALL,VGH_T.L(IA,IGHSTOALL,S,T)*GDATA(IGHSTOALL,'GDFE')))*IHOURSINST(S,T) / (IOF365*WEIGHT_S(S)/IWEIGHSUMS) ):12:3;
)PUT /)


PUT //;

));
