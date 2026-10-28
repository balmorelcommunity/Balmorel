* Cyclic cost = Price for each time a battery is fully charged
* Price is based on battery pack in the EV and not the full EV.
* Calendar degredation is not included, since it would not change variable decisions. But needs to be accounted for if you want the exact cost of using the EVs.
* *1000 to convert from EUR/kWh to EUR/MWh in price
* Formulation is made fractional. G2V/Batsize * (batcost*batsize) * degcyc * 1000
* G2V is MW, so IHOURSINST turns it into MWh charged per year
+ (SUM((IR,IS3,T)$IHASBEV(IR),IHOURSINST(IS3,T)*VEV_G2V_BEV(Y,IR,IS3,T))) * EV_BEV_batcost(Y) * EV_BEV_degcyc(Y) * 1000
+ (SUM((IR,IS3,T)$IHASPHEV(IR),IHOURSINST(IS3,T)*VEV_G2V_PHEV(Y,IR,IS3,T))) * EV_PHEV_batcost(Y) * EV_PHEV_degcyc(Y) * 1000

* ----------------------------------------------------- *
* VQ

* Charging infrastructure, costs in 10'000 EUR/MW: fixed O&M on the capacity in place, and the annuity of every investment still in place
$ifi %TechInvest%==yes  + SUM((IR)$IHASBEV(IR),     VV2GINFRAACCUMNET(Y,IR)*10000*V2G_INFRA_COST_OPEX(Y) + V2G_INFRA_EXTRA(Y,IR) * 10000 * G2V_INFRA_COST_OPEX(Y)
$ifi %TechInvest%==yes      + 10000*IEV_INFRA_ANNUITY*SUM(IYALIAS2$IEV_INFRA_ALIVE(IYALIAS2,Y), V2G_INFRA_CAP(IYALIAS2,IR)*V2G_INFRA_INVCOST(IYALIAS2) + V2G_INFRA_EXTRA_BIS(IYALIAS2,IR)*G2V_INFRA_INVCOST(IYALIAS2)) )

$ifi %EV_infeas%==yes   +PENALTYQ*(SUM((IR,IS3,T),VQEV_PHEV_BEBALANCE(Y,IR,IS3,T,'IMINUS')$IHASPHEV(IR) +VQEV_PHEV_BEBALANCE(Y,IR,IS3,T,'IPLUS')$IHASPHEV(IR)  +VQEV_BEV_BEBALANCE(Y,IR,IS3,T,'IMINUS')$IHASBEV(IR) +VQEV_BEV_BEBALANCE(Y,IR,IS3,T,'IPLUS')$IHASBEV(IR)))
* Slack on the G2V infrastructure fixed from the investment run
$ifi not %TechInvest%==yes +PENALTYQ*SUM((IR,IS3,T), VG2VINFRASLACK(Y,IR,IS3,T))
