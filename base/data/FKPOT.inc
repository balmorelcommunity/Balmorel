* Fuel potentials specified at geographical level.
* The fuel potential is specified as an upper limit on the countries'installed
* generation capacity relative to the individual fuel type.

* Note: The value 0 or white space implies no restriction. The value 'eps' implies zero MW.

TABLE FKPOT(CCCRRRAAA,FFF)       'Fuel potential restriction by geography (MW)'
                 NUCLEAR  LIGNITE   ORIMULSION  SHALE  PEAT
DENMARK          eps      eps       1000        eps    eps
ESTONIA          eps                eps         6100   750
FINLAND          7500               eps         eps    3200
GERMANY          21000              eps         eps    eps
LATVIA           eps                eps         eps    370
LITHUANIA                           eps         eps
NORWAY           eps      eps       eps         eps    eps
POLAND           eps                eps         eps    eps
RUSSIA                              eps         600    4130
SWEDEN           10100    eps       eps         eps    400     /*hansnep: nuc se Oget med 600*/

+                WIND  WATER  SUN  STRAW  WOOD  WOODWASTE
denmark          8000
DK_E                   eps
DK_E_Urban       722
DK_E_Offshore    1360
DK_W             6000  eps
DK_W_Urban       2778
DK_W_Offshore    1610
FI_R             3000
DE_CS            20000
DE_NE            4500
DE_NW            30000
NO_N             3000
NO_M             3000
NO_S             1600
NO_O             eps   eps    eps  eps    eps   eps
SE_N             2000
SE_M             2000
SE_S             5000
EE_R             120   eps    eps  3440   3440  3440
LV_R             600   2500   eps  4820   4820  4820
LT_R             500   4000   eps  5040   5040  5040
PL_R             5000  1370   eps  29830  29830 29830
RU_W             1700  1600   eps  18590  18590 18590
RU_K             600   eps    eps  730    730   730
+                MUNIWASTE
DK_E_Urban       700
*DK_W_Urban       700
*EE_R_Urban       40
*FI_R_Urban       540
*DE_CS_A1         1000
*DE_NE_A1         1000
*DE_NW_A1         1000
*LV_R_Urban       70
*LT_R_Urban       100
*PL_R_Urban       2100
*RU_W_Urban       190
*RU_K_Urban       30
*SE_M_Urban       1000
*DK_E_Rural       500
*DK_W_Rural       1200
*EE_R_Rural
*FI_R_Rural
*LV_R_Rural
*LT_R_Rural
*NO_N_Rural       20
*NO_M_Rural       120
*NO_S_Rural       320
*NO_O_Rural       eps
*PL_R_Rural
*RU_W_Rural
*RU_K_Rural
*SE_N_Rural       500
*SE_M_Rural       2000
*SE_S_Rural       1400
;