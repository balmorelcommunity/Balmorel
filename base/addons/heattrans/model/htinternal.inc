SET IXHKN(IAAAE,IAAAI) 'Pair of areas that may get new heat transmission capacity';

* Transmission capacity (MW) between areas IAE (exporting) and  IAI (importing)
* at the beginning of current simulation year:
PARAMETER IXHKINI_Y(IAAAE,IAAAI) 'Heat transmission capacity between regions at beginning of year (MW)'; 

IXHKN(IAE,IAI) = NO;