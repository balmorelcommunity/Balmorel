* PARAMETER XCOST contains information about the electrical transmission
* cost between pairs of regions.
* Units: EUR90/MW.
* The input data are checked for reasonable values. See the file CHECK0.INC.

* The electrical transmission cost is applied to the electricity
* entering the transmission line.

* Observe: Unreasonable results may be found if there are neither
* cost nor loss associated with electrical transmission.
* Therefore for all (non-diagonal) entries there should be a positive number
* in either TABLE XCOST or in TABLE XLOSS.

* 0.32 EUR90/MWh approx 3 NOK/KWh
* 0.75 EUR90/MWh approx 7 NOK/KWh
* 2.00 EUR90/MWh approx 18.75 NOK/KWh

* Data source:

TABLE XCOST(IRRRE,IRRRI)  'Transmission cost between countries'

        DK_E     DK_W      FI_R    DE_CS   DE_NE   DE_NW   NO_N         NO_M        NO_S      NO_O      SE_N      SE_M      SE_S
DK_E    0        0.0001    0.0001  0.0001  0.0001  0.0001  0.0001       0.0001      0.0001    0.0001    0.0001    0.0001    0.0001
DK_W    0.0001   0         0.0001  0.0001  0.0001  0.0001  0.0001       0.0001      0.0001    0.0001    0.0001    0.0001    0.0001
FI_R    0.0001   0.0001    0       0.0001  0.0001  0.0001  0.0001       0.0001      0.0001    0.0001    0.0001    0.0001    0.0001
DE_CS   0.0001   0.0001    0.0001  0       0.0001  0.0001  0.0001       0.0001      0.0001    0.0001    0.0001    0.0001    0.0001
DE_NE   0.0001   0.0001    0.0001  0.0001  0       0.0001  0.0001       0.0001      0.0001    0.0001    0.0001    0.0001    0.0001
DE_NW   0.0001   0.0001    0.0001  0.0001  0.0001  0       0.0001       0.0001      0.0001    0.0001    0.0001    0.0001    0.0001
NO_N    0.0001   0.0001    0.0001  0.0001  0.0001  0.0001  0            0.0001      0.0001    0.0001    0.0001    0.0001    0.0001
NO_M    0.0001   0.0001    0.0001  0.0001  0.0001  0.0001  0.0001       0           0.0001    0.0001    0.0001    0.0001    0.0001
NO_S    0.0001   0.0001    0.0001  0.0001  0.0001  0.0001  0.0001       0.0001      0         0.0001    0.0001    0.0001    0.0001
NO_O    0.0001   0.0001    0.0001  0.0001  0.0001  0.0001  0.0001       0.0001      0.0001    0         0.0001    0.0001    0.0001
SE_N    0.0001   0.0001    0.0001  0.0001  0.0001  0.0001  0.0001       0.0001      0.0001    0.0001    0         0.0001    0.0001
SE_M    0.0001   0.0001    0.0001  0.0001  0.0001  0.0001  0.0001       0.0001      0.0001    0.0001    0.0001    0         0.0001
SE_S    0.0001   0.0001    0.0001  0.0001  0.0001  0.0001  0.0001       0.0001      0.0001    0.0001    0.0001    0.0001    0
;


$ontext
TABLE XCOST(IRRRE,IRRRI)  'Transmission cost between regions (Money/MWh)'

        DK_E    DK_W    EE_R    FI_R    DE_R    LV_R    LT_R    NO_N    NO_M
DK_E    0       0.32    2       2       0.75    2       2       2       2
DK_W    0.32    0       2       2       0.32    2       2       2       2
EE_R    2       2       0       0.32    2       0.32    0.32    2       2
FI_R    2       2       0.32    0       2       0.32    0.32    0.32    2
DE_R    0.75    0.32    2       2       0       2       2       2       2
LV_R    2       2       0.32    0.32    2       0       0.32    2       2
LT_R    2       2       0.32    0.32    2       0.32    0       2       2
NO_N    2       2       2       0.32    2       2       2       0       0.32
NO_M    2       2       2       2       2       2       2       0.32    0
NO_S    0.32    0.32    2       2       0.75    2       2       0.32    0.32
NO_O    0.32    0.32    2       2       0.75    2       2       0.32    0.32
PL_R    0.32    2       2       2       0.32    0.75    0.32    2       2
RU_W    2       2       0.32    0.75    2       0.32    0.32    0.75    2
RU_K    2       2       2       2       2       0.32    0.32    2       2
SE_N    2       2       2       0.32    2       0.75    2       0.32    0.32
SE_M    0.75    0.32    2       0.32    2       0.75    2       0.75    0.32
SE_S    0.75    0.32    2       0.32    0.75    0.75    2       2       0.75

+       NO_S    NO_O    PL_R    RU_W    RU_K    SE_N    SE_M    SE_S
DK_E    0.32    0.32    0.75    2       2       2       0.32    0.32
DK_W    0.32    0.32    2       2       2       2       0.32    0.32
EE_R    2       2       2       0.32    2       2       2       2
FI_R    2       2       2       0.75    2       0.32    2       2
DE_R    0.75    0.75    0.32    2       2       2       2       0.75
LV_R    2       2       2       0.32    0.32    2       2       2
LT_R    2       2       0.32    0.32    0.32    2       2       2
NO_N    0.32    0.32    2       0.75    2       0.32    0.32    2
NO_M    0.32    0.32    2       2       2       0.32    0.32    2
NO_S    0       0.32    2       2       2       2       0.32    2
NO_O    0.32    0       2       2       2       2       0.32    2
PL_R    2       2       0       0.75    0.32    2       2       0.75
RU_W    2       2       0.75    0       0.32    2       2       2
RU_K    2       2       0.32    0.32    0       2       2       2
SE_N    2       0.75    2       2       2       0       0.32    0.32
SE_M    0.75    0.32    132     2       2       0.32    0       0.32
SE_S    2       0.75    0.75    2       2       0.32    0.32    0
;
$offtext

