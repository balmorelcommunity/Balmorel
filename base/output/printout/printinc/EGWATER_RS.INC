* File: EGWATER_RS.INC

* Modified last time:

* This file will print a table containing electricity generation from all
* technologies in each time period in each season in each region.
* (Incl. the negative electricity generation for heat pumps)


* -----------------------------------------------------------------------------

PUT EGWATER_RS;

if ((EGWATER_RS.PW LT 32000),
EGWATER_RS.PW = 32000;
PUT "*Version:              " SYSTEM.TITLE /;
PUT "*File name:            EGWATER_RS.OUT" /;
PUT "*File created:         " SYSTEM.DATE " " SYSTEM.TIME /;
PUT "*Case-identification:  " OCASEID.TS //;
PUT '*"Maximum Waterproduction (MWh) during each week"'//;
PUT "TABLE HYFXRW(SSS,RRR) 'Weekly hydro production in the Nordic hydro countries (MWh)'" //;

PUT "* Note that if there are less than 52 seasons, the results are not correct (the sum will indicate approximately the annual value); there are " (card(S)):2:0 " seasons."//;
);

* End of headings.

* -----------------------------------------------------------------------------

EGWATER_RS.LJ = 2;
PUT "                " ; LOOP(IR, PUT IR.TL:14) ; PUT /;
EGWATER_RS.LJ = 2;

LOOP(S,
EGWATER_RS.TJ = 2;
PUT S.TL:12
  LOOP(IR,
    PUT SUM(ighyrs, EGqRS(IR,ighyrs,S)):8:0 ;
PUT "      "; );  PUT /;
)

PUT //;