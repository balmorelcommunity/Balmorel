* PARAMETER DEFP_CALIB is used to calibrate the price side of the electricity demand
* function in order to get demand consistent for a base year.
* Unit: EUR90/MWh.


* hans__ : kopi var3low,inc
TABLE DEFP_CALIB(RRR,SSS,TTT)  'Calibrate the price side of electricity demand'
                          S01.T001 S01.T002 S02.T001   S02.T002
DK_E                      0         0         0         0
DK_W                      0         0         0         0
EE_R                      0         0         0         0
FI_R                      0         0         0         0
DE_CS                     0         0         0         0
DE_NE                     0         0         0         0
DE_NW                     0         0         0         0
LV_R                      0         0         0         0
LT_R                      0         0         0         0
NO_N                      0         0         0         0
NO_M                      0         0         0         0
NO_S                      0         0         0         0
NO_O                      0         0         0         0
PL_R                      0         0         0         0
RU_W                      0         0         0         0
RU_K                      0         0         0         0
SE_N                      0         0         0         0
SE_M                      0         0         0         0
SE_S                      0         0         0         0
;
