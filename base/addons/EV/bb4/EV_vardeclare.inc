POSITIVE VARIABLE         VEV_BE_BEV(Y,RRR,S,T)         'Battery Energy of the BEV vehicle fleet.'  ;
POSITIVE VARIABLE         VEV_BE_PHEV(Y,RRR,S,T)        'Battery Energy of the PHEV vehicle fleet.'  ;
POSITIVE VARIABLE         VEV_G2V_BEV(Y,RRR,S,T)        'Grid to vehicle. Charging of BEVs.'          ;
POSITIVE VARIABLE         VEV_G2V_PHEV(Y,RRR,S,T)       'Grid to vehicle. Charging of PHEVs.'        ;
POSITIVE VARIABLE         VEV_V2G_BEV(Y,RRR,S,T)        'Vehicle to grid. Discharging of BEVs'       ;
POSITIVE VARIABLE         VEV_V2G_PHEV(Y,RRR,S,T)       'Vehicle to grid. Discharging of PHEVs'      ;

$ifi %EV_infeas%==yes POSITIVE VARIABLE VQEV_BEV_BEBALANCE(Y,RRR,S,T,IPLUSMINUS)  "Feasibility of QEV_BEV_BEBALANCE";
$ifi %EV_infeas%==yes POSITIVE VARIABLE VQEV_PHEV_BEBALANCE(Y,RRR,S,T,IPLUSMINUS)  "Feasibility of QEV_PHEV_BEBALANCE";


POSITIVE VARIABLE         V2G_INFRA_CAP(Y,RRR)         'V2G infrastructure peak capacity [MW]'  ;
POSITIVE VARIABLE         G2V_INFRA_CAP(Y,RRR)         'G2V infrastructure peak capacity [MW]'  ;
POSITIVE VARIABLE         V2G_INFRA_EXTRA(Y,RRR)    "Additional unidirectional-only infra capacity needed beyond bidirectional V2G capacity, MW";
POSITIVE VARIABLE         VV2GINFRAACCUMNET(Y,RRR)   "Accumulated V2G infrastructure capacity [MW]";
POSITIVE VARIABLE         VG2VINFRAACCUMNET(Y,RRR)   "Accumulated G2V infrastructure capacity [MW]";
*POSITIVE VARIABLE         V2G_INFRA_EXTRA_BIS(Y,RRR) "Additional unidirectional-only infra capacity needed beyond bidirectional V2G capacity, MW";