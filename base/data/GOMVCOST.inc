* PARAMETER GOMVCOST(GGG,AAA) holds the variable operating and maintenance costs.
* Unit: EUR90/MWh.

TABLE GOMVCOST(AAA,GGG)  'Variable operating and maintenance costs (Money/MWh)'
             DK_E_Rural_WI
DK_E_Rural   0
;

* Default values given by GDATA(G,'GOPMVCOST0')
* are used unless non-zero values have been otherwise specified:

GOMVCOST(AAA,GGG)$(GOMVCOST(AAA,GGG) EQ 0)= GDATA(GGG,'GDOMVCOST0');

GOMVCOST('FI_R_Rural','HY-S01')=    GOMVCOST('FI_R_Rural','HY-S01')+    1.5     ;
GOMVCOST('FI_R_Rural','HY-S02')=    GOMVCOST('FI_R_Rural','HY-S02')+    1.5     ;
GOMVCOST('FI_R_Rural','HY-S03')=    GOMVCOST('FI_R_Rural','HY-S03')+    1.5     ;
GOMVCOST('FI_R_Rural','HY-S04')=    GOMVCOST('FI_R_Rural','HY-S04')+    1.5     ;
GOMVCOST('FI_R_Rural','HY-S05')=    GOMVCOST('FI_R_Rural','HY-S05')+    1.5     ;
GOMVCOST('FI_R_Rural','HY-S06')=    GOMVCOST('FI_R_Rural','HY-S06')+    1.5     ;
GOMVCOST('FI_R_Rural','HY-S07')=    GOMVCOST('FI_R_Rural','HY-S07')+    1.5     ;
GOMVCOST('FI_R_Rural','HY-S08')=    GOMVCOST('FI_R_Rural','HY-S08')+    1.5     ;
GOMVCOST('FI_R_Rural','HY-S09')=    GOMVCOST('FI_R_Rural','HY-S09')+    1.5     ;
GOMVCOST('FI_R_Rural','HY-S10')=    GOMVCOST('FI_R_Rural','HY-S10')+    1.5     ;

GOMVCOST('NO_N_Rural','HY-S01')=    GOMVCOST('NO_N_Rural','HY-S01')+    3.5     ;
GOMVCOST('NO_N_Rural','HY-S02')=    GOMVCOST('NO_N_Rural','HY-S02')+    3.5     ;
GOMVCOST('NO_N_Rural','HY-S03')=    GOMVCOST('NO_N_Rural','HY-S03')+    3.5     ;
GOMVCOST('NO_N_Rural','HY-S04')=    GOMVCOST('NO_N_Rural','HY-S04')+    3.5     ;
GOMVCOST('NO_N_Rural','HY-S05')=    GOMVCOST('NO_N_Rural','HY-S05')+    3.5     ;
GOMVCOST('NO_N_Rural','HY-S06')=    GOMVCOST('NO_N_Rural','HY-S06')+    3.5     ;
GOMVCOST('NO_N_Rural','HY-S07')=    GOMVCOST('NO_N_Rural','HY-S07')+    3.5     ;
GOMVCOST('NO_N_Rural','HY-S08')=    GOMVCOST('NO_N_Rural','HY-S08')+    3.5     ;
GOMVCOST('NO_N_Rural','HY-S09')=    GOMVCOST('NO_N_Rural','HY-S09')+    3.5     ;
GOMVCOST('NO_N_Rural','HY-S10')=    GOMVCOST('NO_N_Rural','HY-S10')+    3.5     ;

GOMVCOST('NO_M_Rural','HY-S01')=    GOMVCOST('NO_M_Rural','HY-S01')+    2.5     ;
GOMVCOST('NO_M_Rural','HY-S02')=    GOMVCOST('NO_M_Rural','HY-S02')+    2.5     ;
GOMVCOST('NO_M_Rural','HY-S03')=    GOMVCOST('NO_M_Rural','HY-S03')+    2.5     ;
GOMVCOST('NO_M_Rural','HY-S04')=    GOMVCOST('NO_M_Rural','HY-S04')+    2.5     ;
GOMVCOST('NO_M_Rural','HY-S05')=    GOMVCOST('NO_M_Rural','HY-S05')+    2.5     ;
GOMVCOST('NO_M_Rural','HY-S06')=    GOMVCOST('NO_M_Rural','HY-S06')+    2.5     ;
GOMVCOST('NO_M_Rural','HY-S07')=    GOMVCOST('NO_M_Rural','HY-S07')+    2.5     ;
GOMVCOST('NO_M_Rural','HY-S08')=    GOMVCOST('NO_M_Rural','HY-S08')+    2.5     ;
GOMVCOST('NO_M_Rural','HY-S09')=    GOMVCOST('NO_M_Rural','HY-S09')+    2.5     ;
GOMVCOST('NO_M_Rural','HY-S10')=    GOMVCOST('NO_M_Rural','HY-S10')+    2.5     ;

GOMVCOST('NO_S_Rural','HY-S01')=    GOMVCOST('NO_S_Rural','HY-S01')+    4.5     ;
GOMVCOST('NO_S_Rural','HY-S02')=    GOMVCOST('NO_S_Rural','HY-S02')+    4.5     ;
GOMVCOST('NO_S_Rural','HY-S03')=    GOMVCOST('NO_S_Rural','HY-S03')+    4.5     ;
GOMVCOST('NO_S_Rural','HY-S04')=    GOMVCOST('NO_S_Rural','HY-S04')+    4.5     ;
GOMVCOST('NO_S_Rural','HY-S05')=    GOMVCOST('NO_S_Rural','HY-S05')+    4.5     ;
GOMVCOST('NO_S_Rural','HY-S06')=    GOMVCOST('NO_S_Rural','HY-S06')+    4.5     ;
GOMVCOST('NO_S_Rural','HY-S07')=    GOMVCOST('NO_S_Rural','HY-S07')+    4.5     ;
GOMVCOST('NO_S_Rural','HY-S08')=    GOMVCOST('NO_S_Rural','HY-S08')+    4.5     ;
GOMVCOST('NO_S_Rural','HY-S09')=    GOMVCOST('NO_S_Rural','HY-S09')+    4.5     ;
GOMVCOST('NO_S_Rural','HY-S10')=    GOMVCOST('NO_S_Rural','HY-S10')+    4.5     ;

GOMVCOST('SE_N_Rural','HY-S01')=    GOMVCOST('SE_N_Rural','HY-S01')+    3.2     ;
GOMVCOST('SE_N_Rural','HY-S02')=    GOMVCOST('SE_N_Rural','HY-S02')+    3.2     ;
GOMVCOST('SE_N_Rural','HY-S03')=    GOMVCOST('SE_N_Rural','HY-S03')+    3.2     ;
GOMVCOST('SE_N_Rural','HY-S04')=    GOMVCOST('SE_N_Rural','HY-S04')+    3.2     ;
GOMVCOST('SE_N_Rural','HY-S05')=    GOMVCOST('SE_N_Rural','HY-S05')+    3.2     ;
GOMVCOST('SE_N_Rural','HY-S06')=    GOMVCOST('SE_N_Rural','HY-S06')+    3.2     ;
GOMVCOST('SE_N_Rural','HY-S07')=    GOMVCOST('SE_N_Rural','HY-S07')+    3.2     ;
GOMVCOST('SE_N_Rural','HY-S08')=    GOMVCOST('SE_N_Rural','HY-S08')+    3.2     ;
GOMVCOST('SE_N_Rural','HY-S09')=    GOMVCOST('SE_N_Rural','HY-S09')+    3.2     ;
GOMVCOST('SE_N_Rural','HY-S10')=    GOMVCOST('SE_N_Rural','HY-S10')+    3.2     ;
