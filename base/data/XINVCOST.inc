* PARAMETER XINVCOST contains information about the investment cost
* in new electrical transmission capacity between pairs of regions.
* Units: EUR90/MW.

* Observe: if INF is entered in the table, this means that no tranmission
* capacity can be established between the two associated regions.
* The matrix should only have values in the lower half, as only those
* values are used in the model.

* Data source:

TABLE XINVCOST(IRRRE,IRRRI)  'Investment cost in new transmission capacity (Money/MW)'

          DK_E    DK_W    EE_R    FI_R    DE_CS   DE_NE   DE_NW   LV_R    LT_R    NO_N     NO_M
DK_E
DK_W     300000
EE_R       INF     INF
FI_R       INF     INF  300000
DE_CS    300000  300000    INF     INF
DE_NE      INF     INF     INF     INF     INF
DE_NW      INF     INF     INF     INF     INF    INF
LV_R       INF     INF  300000     INF     INF    INF     INF
LT_R       INF     INF     INF     INF     INF    INF     INF     INF
NO_N       INF     INF  300000  300000     INF    INF     INF     INF      INF
NO_M       INF     INF     INF  300000     INF    INF     INF     INF      INF   300000
NO_S    300000  300000     INF     INF     INF    INF     INF     INF      INF    INF     300000
NO_O    300000  300000     INF     INF     INF    INF     INF     INF      INF    INF     300000
PL_R    300000     INF     INF     INF  300000    INF     INF     INF    300000   INF      INF
RU_W       INF     INF  300000  300000     INF    INF     INF    300000  300000   INF      INF
RU_K       INF  300000     INF     INF     INF    INF     INF     INF    300000   INF      INF
SE_N       INF     INF     INF  300000     INF    INF     INF    300000  300000  300000   300000
SE_M       INF  300000  300000  300000     INF    INF     INF    300000  300000  300000   300000
SE_S    300000     INF    INF      INF  300000    INF     INF     INF    300000   INF      INF

+         NO_S    NO_O    PL_R    RU_W    RU_K    SE_N    SE_M    SE_S
DK_E
DK_W
EE_R
FI_R
DE_CS
DE_NE
DE_NW
LV_R
LT_R
NO_N
NO_M
NO_S
NO_O    300000
PL_R      INF      INF
RU_W       INF     INF     INF
RU_K       INF     INF  300000     INF
SE_N       INF     INF     INF  300000     INF
SE_M    300000  300000  300000     INF  300000  300000
SE_S    300000     INF  300000     INF  300000     INF  300000
;
XINVCOST(IRRRE,IRRRI)$(ORD(IRRRE) LT ORD(IRRRI))=XINVCOST(IRRRI,IRRRE);

