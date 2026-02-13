* Cyclic cost = Price for each time a battery is fully charged
* Price is based on battery pack in the EV and not the full EV.
* Calendar degredation is not included, since it would not change variable decisions. But needs to be accounted for if you want the exact cost of using the EVs.
* *1000 to convert from EUR/kWh to EUR/MWh in price
* Formulation is made fractional. G2V/Batsize * (batcost*batsize) * degcyc * 1000
+ (SUM((IR,IS3,T)$IHASBEV(IR),VEV_G2V_BEV(Y,IR,IS3,T))) * EV_BEV_batcost(Y) * EV_BEV_degcyc(Y) * 1000
+ (SUM((IR,IS3,T)$IHASPHEV(IR),VEV_G2V_PHEV(Y,IR,IS3,T))) * EV_PHEV_batcost(Y) * EV_PHEV_degcyc(Y) * 1000

* ----------------------------------------------------- *
* VQ


$ifi %EV_infeas%==yes   +PENALTYQ*(SUM((IR,IS3,T),VQEV_PHEV_BEBALANCE(Y,IR,IS3,T,'IMINUS')$IHASPHEV(IR) +VQEV_PHEV_BEBALANCE(Y,IR,IS3,T,'IPLUS')$IHASPHEV(IR)  +VQEV_BEV_BEBALANCE(Y,IR,IS3,T,'IMINUS')$IHASBEV(IR) +VQEV_BEV_BEBALANCE(Y,IR,IS3,T,'IPLUS')$IHASBEV(IR)))
