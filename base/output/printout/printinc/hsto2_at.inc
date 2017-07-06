* File: hsto2_at.inc

* Created 2001.03.20 (hrv), 16-02-2004 (ld)
* Modified last time:  2005.07.31 (hr), 2005.10.29 (hr), 20060238(hr)

* This file will print a table containing content of short term heat storages
* at the beginning of each time segment
* One row contains one year - usefull for graphing e.g. in Excel.


PUT hsto2_at;

* First print headings:

if ((hsto2_at.pw LT 32000),
hsto2_at.pw = 32000;
PUT "Version:              " SYSTEM.TITLE /;
PUT "File name:            hsto2_at.GRF" /;
PUT "File created:         " SYSTEM.DATE " " SYSTEM.TIME /;
PUT "Case-identification:  " OCASEID.TS //;
PUT '"Short term heat storage contents (MWh) at the beginning of each time segment"'////;
);

* End of file headings.
* ------------------------------------------------------------------------------------
* If scenarios (i.e., more than base case) print scenario heading:
IF((CARD(SCENARIO) GT 1),
PUT /"*==============================================================================="/;
PUT "*       "   SCENARIO.TL "      " SCENARIO.TE(SCENARIO) /;
PUT "*==============================================================================="//;
);
* End of scenario heading
* ------------------------------------------------------------------------------------

hsto2_at.LJ = 1;
PUT Y.TL:4 "        ";     LOOP(S,  LOOP(T, PUT T.TL:12 ) PUT ""); PUT /;
hsto2_at.LJ = 2;

LOOP(C,
LOOP(IA$(ICA(C,IA) AND (SUM(IGHSTO,IGKFX_Y(IA,IGHSTO)) GT 0)   ),
PUT IA.TL:12 ;
LOOP(S,
 LOOP(T,
        PUT VHSTOVOLT.L(IA,S,T):12:1
);
)PUT /;
))
PUT/;