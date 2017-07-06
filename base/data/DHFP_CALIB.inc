* PARAMETER DHFP_CALIB is used to calibrate the price side of the demand
* function in order to get demand consistent for a base year.
* Unit: EUR90/MWh.

TABLE DHFP_CALIB(AAA,SSS,TTT)   'Calibrate the price side of heat demand'
                       T001        T002
DK_E_Urban.S01           0         0
;
* Default data: all identical
DHFP_CALIB(AAA,S,T)
=DHFP_CALIB('DK_E_Urban','S01','T001')  ;