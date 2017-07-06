* PARAMETER XKINI contains the intital electrical transmission capacities
* between pairs of regions.
* Units: MW.

* The electrical transmission capacity is the capacity
* disregarding an eventual loss (see the table XLOSS).
* Thus, if there is a loss, a maximum of XCAPINIT MW may be sent into
* the transmisison line, but at most (XCAPINIT*XLOSS) MW may be extracted.


* Data source:
* The data is from "Nordel Aarsberetning 1995" (in Danish) supplemented ad hoc
* for countries not covered in this. Some capacities adjusted according to observed
* patterns in transmission


* ELKRAFT data taken from trans_jwe.inc sent from Elkraft
$ontext
TABLE XKINI(YYY,IRRRE,IRRRI)  'Initial transmission capacity between regions (MW)'

               DK_E    DK_W    FI_R  DE_CS  DE_NE  DE_NW     NO_N    NO_M  NO_S    NO_O     SE_N    SE_M    SE_S
DK_E           0       600     0     0      550    0         0       0     0       0        0       0       1700
DK_W           600     0       0     0      0      1400      0       0     1600    0        0       730     0
FI_R           0       0       0     0      0      0         100     0     0       0        1100    1150    0
DE_CS          0       0       0     0      3060   7330      0       0     700     0        0       0       0
DE_NE          550     0       0     3060   0      1200      0       0     0       0        0       0       0
DE_NW          0       1400    0     7330   1200   0         0       0     0       0        0       0       400
NO_N           0       0       120   0      0      0         0       1500  0       0        700     0       0
NO_M           0       0       0     0      0      0         1500    0     1200    0        1350    0       0
NO_S           0       1600    0     700    0      0         0       1200  0       5200     0       0       0
NO_O           0       0       0     0      0      0         0       0     2500    0        0       2300    0
SE_N           0       0       1600  0      0      0         700     1350  0       0        0       7000    0
SE_M           0       730     1150  0      0      0         0       0     0       2150     7000    0       4300
SE_S           1300    0       0     0      0      400       0       0     0       0        0       4300    0
;
$offtext

TABLE XKINI(YYY,IRRRE,IRRRI)  'Initial transmission capacity between regions'

             DK_E    DK_W    EE_R    FI_R    DE_NE  DE_NW  DE_CS   LV_R    LT_R    NO_N    NO_M   NO_S    NO_O    PL_R    RU_W    RU_K    SE_N    SE_M    SE_S
2000.DK_E    0       0       0       0       600    0      0       0       0       0       0      0       0       0       0       0       0       0       1700
2000.DK_W    0       0       0       0       0      1500   0       0       0       0       0      1000    0       0       0       0       0       740     0
2000.EE_R    0       0       0       0       0      0      0       1300    0       0       0      0       0       0       0       1400    0       0       0
2000.FI_R    0       0       0       0       0      0      0       0       0       100     0      0       0       0       0       60      1200    550     0
2000.DE_NE   600     0       0       0       0      1200   3060    0       0       0       0      0       0       0       0       0       0       0       0
2000.DE_NW   0       950     0       0       1200   0      3330    0       0       0       0      0       0       0       0       0       0       0       390
2000.DE_CS   0       0       0       0       3060   3330   0       0       0       0       0      0       0       1000    0       0       0       0       0
2000.LV_R    0       0       1300    0       0      0      0       0       2000    0       0      0       0       0       0       700     0       0       0
2000.LT_R    0       0       0       0       0      0      0       2000    0       0       0      0       0       0       1000    0       0       0       0
2000.NO_N    0       0       0       100     0      0      0       0       0       0       900    0       0       0       0       50      700     0       0
2000.NO_M    0       0       0       0       0      0      0       0       0       900     0      600     0       0       0       0       450     0       0
2000.NO_S    0       1000    0       0       0      0      0       0       0       0       600    0       5200    0       0       0       0       0       0
2000.NO_O    0       0       0       0       0      0      0       0       0       0       0      2500    0       0       0       0       0       2300    0
2000.PL_R    0       0       0       0       0      0      1000    0       0       0       0      0       0       0       0       0       0       0       400
2000.RU_W    0       0       0       0       0      0      0       0       1000    0       0      0       0       0       0       0       0       0       0
2000.RU_K    0       0       1400    1160    0      0      0       700     0       50      0      0       0       0       0       0       0       0       0
2000.SE_N    0       0       0       1600    0      0      0       0       0       700     450    0       0       0       0       0       0       7000    0
2000.SE_M    0       740     0       550     0      0      0       0       0       0       0      0       2150    0       0       0       7000    0       4000
2000.SE_S    1300    0       0       0       0      460    0       0       0       0       0      0       0       600     0       0       0       4000    0
;

XKINI(YYY,'NO_N','NO_M') = XKINI(YYY,'NO_N','NO_M')+300; /*HaNS nep: added*/
XKINI(YYY,'NO_M','NO_N') = XKINI(YYY,'NO_M','NO_N')+300;  /*HaNS nep: added*/


XKINI(YYY,IRRRE,IRRRI)$(YVALUE(YYY)>2000)  = XKINI('2000',IRRRE,IRRRI);

* NordNed cable completed in 2008
XKINI(YYY,'NO_S','DE_CS')$(YVALUE(YYY) ge 2008) = XKINI(YYY,'NO_S','DE_CS')+700;
XKINI(YYY,'DE_CS','NO_S')$(YVALUE(YYY) ge 2008) = XKINI(YYY,'DE_CS','NO_S')+700;

* Great Belt cable completed in 2010
XKINI(YYY,'DK_W','DK_E')$(YVALUE(YYY) ge 2011) = XKINI(YYY,'DK_W','DK_E')+600;
XKINI(YYY,'DK_E','DK_W')$(YVALUE(YYY) ge 2011) = XKINI(YYY,'DK_E','DK_W')+600;

* Nea-Jarpstrommen in 2010
XKINI(YYY,'NO_M','SE_N')$(YVALUE(YYY) ge 2010) = XKINI(YYY,'NO_M','SE_N')+1350; /*hans  oprindeligt 750*/
XKINI(YYY,'SE_N','NO_M')$(YVALUE(YYY) ge 2010) = XKINI(YYY,'SE_N','NO_M')+1350; /*hans  oprindeligt 750*/

* Fenno-Skan 2 cable completed in 2011
XKINI(YYY,'SE_M','FI_R')$(YVALUE(YYY) ge 2011) = XKINI(YYY,'SE_M','FI_R')+1300;   /*hans  oprindeligt 800*/
XKINI(YYY,'FI_R','SE_M')$(YVALUE(YYY) ge 2011) = XKINI(YYY,'FI_R','SE_M')+1300;    /*hans  oprindeligt 800*/

* South Link in 2013
XKINI(YYY,'SE_M','SE_S')$(YVALUE(YYY) ge 2013) = XKINI(YYY,'SE_M','SE_S')+600;
XKINI(YYY,'SE_S','SE_M')$(YVALUE(YYY) ge 2013) = XKINI(YYY,'SE_S','SE_M')+600;

* Skagerrak IV in 2013
XKINI(YYY,'DK_W','NO_S')$(YVALUE(YYY) ge 2013) = XKINI(YYY,'DK_W','NO_S')+600;
XKINI(YYY,'NO_S','DK_W')$(YVALUE(YYY) ge 2013) = XKINI(YYY,'NO_S','DK_W')+600;

* Vestdanmark tyskland IV in 2015
* XKINI(YYY,'DK_W','DE_NW')$(YVALUE(YYY) ge 2015) = XKINI(YYY,'DK_W','DE_NW')+500;
* XKINI(YYY,'DE_NW','DK_W')$(YVALUE(YYY) ge 2015) = XKINI(YYY,'DE_NW','DK_W')+1050;
* Vestdanmark tyskland IV in 2025
* XKINI(YYY,'DK_W','DE_NW')$(YVALUE(YYY) ge 2025) = XKINI(YYY,'DK_W','DE_NW')+500;
* XKINI(YYY,'DE_NW','DK_W')$(YVALUE(YYY) ge 2025) = XKINI(YYY,'DE_NW','DK_W')+500;

* Elbensnit in 2015
* XKINI(YYY,'DE_CS','DE_NW')$(YVALUE(YYY) ge 2015) = XKINI(YYY,'DE_CS','DE_NW')+2000;
* XKINI(YYY,'DE_NW','DE_CS')$(YVALUE(YYY) ge 2015) = XKINI(YYY,'DE_NW','DE_CS')+2000;
* Elbensnit in 2020
* XKINI(YYY,'DE_CS','DE_NW')$(YVALUE(YYY) ge 2020) = XKINI(YYY,'DE_CS','DE_NW')+2000;
* XKINI(YYY,'DE_NW','DE_CS')$(YVALUE(YYY) ge 2020) = XKINI(YYY,'DE_NW','DE_CS')+2000;

