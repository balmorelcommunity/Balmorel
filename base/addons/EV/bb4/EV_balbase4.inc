

$ifi %DUMB%==yes $goto DUMB_BB4_END
                                 QEV_BEV_SOCBALANCE
$ifi %V2G%==yes                  QEV_BEV_CHARGEBALANCE
$ifi %STEPCHARGSCHEME%==yes      QEV_BEV_CHARGEBALANCE
                                 QEV_PHEV_SOCBALANCE
$ifi %V2G%==yes                  QEV_PHEV_CHARGEBALANCE
$ifi %STEPCHARGSCHEME%==yes      QEV_PHEV_CHARGEBALANCE

$label  DUMB_BB4_END