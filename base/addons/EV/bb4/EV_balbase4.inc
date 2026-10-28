* Adding SOC constraints for internal EV balancing
                                 QEV_BEV_BEBALANCE
                                 QEV_PHEV_BEBALANCE
                                 QEV_INFRA_V2G_PEAK
                                 QEV_INFRA_G2V_PEAK
$ifi     %TechInvest%==yes       QEV_INFRA_G2V_EXTRA
$ifi     %TechInvest%==yes       QEV_INFRA_G2V_EXTRA_BIS
$ifi     %TechInvest%==yes       QV2GINFRAACCUMNET
$ifi     %TechInvest%==yes       QG2VINFRAACCUMNET
* If V2G then add constraints to ensure G2V+V2G <= Cap
$ifi %V2G%==yes                  QEV_BEV_CHARGEBALANCE
$ifi %V2G%==yes                  QEV_PHEV_CHARGEBALANCE
*$ifi %V2G%==yes                  QEV_BEV_V2G_AVAILABLE
