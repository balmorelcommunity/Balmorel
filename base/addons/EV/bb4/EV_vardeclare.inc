POSITIVE VARIABLE         VEV_BE_BEV(Y,RRR,S,T)         'Battery Energy of the BEV vehicle fleet.'  ;
POSITIVE VARIABLE         VEV_BE_PHEV(Y,RRR,S,T)        'Battery Energy of the PHEV vehicle fleet.'  ;
POSITIVE VARIABLE         VEV_G2V_BEV(Y,RRR,S,T)        'Grid to vehicle. Charging of BEVs.'          ;
POSITIVE VARIABLE         VEV_G2V_PHEV(Y,RRR,S,T)       'Grid to vehicle. Charging of PHEVs.'        ;
POSITIVE VARIABLE         VEV_V2G_BEV(Y,RRR,S,T)        'Vehicle to grid. Discharging of BEVs'       ;
POSITIVE VARIABLE         VEV_V2G_PHEV(Y,RRR,S,T)       'Vehicle to grid. Discharging of PHEVs'      ;

$ifi %EV_infeas%==yes POSITIVE VARIABLE VQEV_BEV_BEBALANCE(Y,RRR,S,T,IPLUSMINUS)  "Feasibility of QEV_BEV_BEBALANCE";
$ifi %EV_infeas%==yes POSITIVE VARIABLE VQEV_PHEV_BEBALANCE(Y,RRR,S,T,IPLUSMINUS)  "Feasibility of QEV_PHEV_BEBALANCE";
