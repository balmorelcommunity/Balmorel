* File: esto2_at.inc
* This file is part of the Balmorel model, version 2.12 Alpha (July 2005)).

* Created 2005.07.31 (hr), 2005.10.29 (hr), 20060328(HR)


* This file will print a table containing content of short term electricity storages
* at the beginning of each time segment
* One row contains one year - usefull for graphing e.g. in Excel.



PUT esto2_at;

* First print headings:

if ((esto2_at.pw LT 32000),
esto2_at.pw = 32000;
PUT "Version:              " "%PRINTSEPARATOR%" SYSTEM.TITLE /;
PUT "File name:            " "%PRINTSEPARATOR%" "esto2_at.out" /;
PUT "Time-stamp:           " "%PRINTSEPARATOR%" SYSTEM.DATE " " SYSTEM.TIME  /;
$ifi %BB1%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE1"/;
$ifi %BB2%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE2"/;
$ifi %BB3%==yes PUT "Solved:               " "%PRINTSEPARATOR%" "BALBASE3"/;
PUT "Case-identification:  " "%PRINTSEPARATOR%" OCASEID.TS   //;

PUT '"Short term electricity storage contents (MWh) at the beginning of each time segment"'////;
);

* End of file headings.
* ------------------------------------------------------------------------------------

esto2_at.LJ = 1;
PUT Y.TL:4 "        ";     LOOP(S,  LOOP(T, PUT T.TL:12 ) PUT ""); PUT /;
esto2_at.LJ = 2;

LOOP(C,
LOOP(IA$(ICA(C,IA) AND (SUM(IGESTO,IGKFX_Y(IA,IGESTO)) GT 0)   ),
PUT IA.TL:12 ;
LOOP(S,
 LOOP(T,
        PUT VESTOVOLT.L(IA,S,T):12:1
);
)PUT /;
))
PUT/;
