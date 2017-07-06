* PARAMETER XLOSS1 contains the loss in transmission is expressed as a fraction
* of the power entering the transmission line.
* Units: (none)
* The input data are checked for reasonable values. See the file CHECK0.INC.


* Observe: Unreasonable results may be found if there are neither
* cost nor loss associated with electrical transmission.
* Therefore for all (non-diagonal) entries there should be a positive number
* in either TABLE XCOST or in TABLE XLOSS.

* Data source:

* The data entered assumes for simplicity that all transmission losses
* between regions RE and RI are the same in both directions.
* Therefore the loss data is given only once.
* It is therefore by convention assumed that loss data between regions RE and RI
* is given only for ORD(RE) LT ORD(RI), i.e. data is entered
* only in the upper right half of the table; the remaining data
* is filled in by the LOOP statement immediately after the table.

* (If this assumption is not found reasonable upon revision of the data,
* then fill in the whole table,
* and delete the fill-in LOOP statement immediately after the table.)


TABLE XLOSS1(IRRRE,IRRRI)  'Transmission loss between regions (fraction)'

        DK_E    DK_W    EE_R    FI_R    DE_CS   DE_NE   DE_NW   LV_R    LT_R    NO_N    NO_M
DK_E    0       0.001   0.001   0.001   0.001   0.001   0.001   0.001   0.001   0.001   0.001
DK_W    0.001   0       0.001   0.001   0.001   0.001   0.001   0.001   0.001   0.001   0.001
EE_R    0.001   0.001   0       0.001   0.001   0.001   0.001   0.001   0.001   0.001   0.001
FI_R    0.001   0.001   0.001   0       0.001   0.001   0.001   0.001   0.001   0.001   0.001
DE_CS   0.001   0.001   0.001   0.001   0       0.001   0.001   0.001   0.001   0.001   0.001
DE_NE   0.001   0.001   0.001   0.001   0.001   0       0.001   0.001   0.001   0.001   0.001
DE_NW   0.001   0.001   0.001   0.001   0.001   0.001   0       0.001   0.001   0.001   0.001
LV_R    0.001   0.001   0.001   0.001   0.001   0.001   0.001   0       0.001   0.001   0.001
LT_R    0.001   0.001   0.001   0.001   0.001   0.001   0.001   0.001   0       0.001   0.001
NO_N    0.001   0.001   0.001   0.001   0.001   0.001   0.001   0.001   0.001   0       0.001
NO_M    0.001   0.001   0.001   0.001   0.001   0.001   0.001   0.001   0.001   0.001   0
NO_S    0.001   0.001   0.001   0.001   0.001   0.001   0.001   0.001   0.001   0.001   0.001
NO_O    0.001   0.001   0.001   0.001   0.001   0.001   0.001   0.001   0.001   0.001   0.001
PL_R    0.001   0.001   0.001   0.001   0.001   0.001   0.001   0.001   0.001   0.001   0.001
RU_W    0.001   0.001   0.001   0.001   0.001   0.001   0.001   0.001   0.001   0.001   0.001
RU_K    0.001   0.001   0.001   0.001   0.001   0.001   0.001   0.001   0.001   0.001   0.001
SE_N    0.001   0.001   0.001   0.001   0.001   0.001   0.001   0.001   0.001   0.001   0.001
SE_M    0.001   0.001   0.001   0.001   0.001   0.001   0.001   0.001   0.001   0.001   0.001
SE_S    0.001   0.001   0.001   0.001   0.001   0.001   0.001   0.001   0.001   0.001   0.001

+       NO_S    NO_O    PL_R    RU_W    RU_K    SE_N    SE_M    SE_S
DK_E    0.001   0.001   0.001   0.001   0.001   0.001   0.001   0.001
DK_W    0.001   0.001   0.001   0.001   0.001   0.001   0.001   0.001
EE_R    0.001   0.001   0.001   0.001   0.001   0.001   0.001   0.001
FI_R    0.001   0.001   0.001   0.001   0.001   0.001   0.001   0.001
DE_CS   0.001   0.001   0.001   0.001   0.001   0.001   0.001   0.001
DE_NE   0.001   0.001   0.001   0.001   0.001   0.001   0.001   0.001
DE_NW   0.001   0.001   0.001   0.001   0.001   0.001   0.001   0.001
LV_R    0.001   0.001   0.001   0.001   0.001   0.001   0.001   0.001
LT_R    0.001   0.001   0.001   0.001   0.001   0.001   0.001   0.001
NO_N    0.001   0.001   0.001   0.001   0.001   0.001   0.001   0.001
NO_M    0.001   0.001   0.001   0.001   0.001   0.001   0.001   0.001
NO_S    0       0.001   0.001   0.001   0.001   0.001   0.001   0.001
NO_O    0.001   0       0.001   0.001   0.001   0.001   0.001   0.001
PL_R    0.001   0.001   0       0.001   0.001   0.001   0.001   0.001
RU_W    0.001   0.001   0.001   0       0.001   0.001   0.001   0.001
RU_K    0.001   0.001   0.001   0.001   0       0.001   0.001   0.001
SE_N    0.001   0.001   0.001   0.001   0.001   0       0.001   0.001
SE_M    0.001   0.001   0.001   0.001   0.001   0.001   0       0.001
SE_S    0.001   0.001   0.001   0.001   0.001   0.001   0.001   0
;

* Then fill in the values not entered in the table assuming symmetry:
LOOP( (IRRRE,IRRRI)$(ORD(IRRRE) GT ORD(IRRRI)),  XLOSS(IRRRE,IRRRI)=XLOSS(IRRRI,IRRRE););
