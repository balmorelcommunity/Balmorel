* PARAMETER DHFP_BASE gives the annual average consumer price
* of heat(including taxes) in the base year.
* Unit: EUR90/MWh.

* It is used as nominal value for calculations in relation to elastic demands.

* Data source:

PARAMETER DHFP_BASE(AAA)  'Nominal annual average consumer heat price (Money/MWh)'
/
DK_E_Urban                    12.43
DK_W_Urban                    12.43
EE_R_Urban                    6.5
*FI_R_Urban                    8.67
DE_CS_A1                      13.43
DE_NE_A1                      13.43
DE_NW_A1                      13.43
LV_R_Urban                    6.55
LT_R_Urban                    7.29
PL_R_Urban                    6.38
RU_W_Urban                    6.1
RU_K_Urban                    6.1
SE_M_Urban                    5.82
DK_E_Rural                    13.43
DK_W_Rural                    13.43
EE_R_Rural                    7.5
FI_R_Rural                    9.67
LV_R_Rural                    7.55
LT_R_Rural                    8.29
NO_N_Rural                    8.82
NO_M_Rural                    8.82
NO_S_Rural                    8.82
NO_O_Rural                    8.82
PL_R_Rural                    6.38
RU_W_Rural                    7.1
RU_K_Rural                    7.1
SE_N_Rural                    6.82
SE_M_Rural                    6.82
SE_S_Rural                    6.82
/;

DHFP_BASE(AAA)$(DHFP_BASE(AAA) EQ 0)= DHFP_BASE('DK_E_Urban');