POSITIVE VARIABLE         VEV_VSOC_BEV(Y,RRR,S,T)        'State of charge of the BEV vehicle fleet.'  ;
POSITIVE VARIABLE         VEV_VSOC_PHEV(Y,RRR,S,T)       'State of charge of the PHEV vehicle fleet.'  ;
POSITIVE VARIABLE         VEV_VG2V_BEV(Y,RRR,S,T)        'Grid to vehicle. Charging of BEVs.'          ;
POSITIVE VARIABLE         VEV_VV2G_BEV(Y,RRR,S,T)        'Vehicle to grid. Discharging of BEVs'       ;
POSITIVE VARIABLE         VEV_VG2V_PHEV(Y,RRR,S,T)       'Grid to vehicle. Charging of PHEVs.'        ;
POSITIVE VARIABLE         VEV_VV2G_PHEV(Y,RRR,S,T)       'Vehicle to grid. Discharging of PHEVs'      ;

$ifi %EV_infeas%==yes POSITIVE VARIABLE VQEV_BEV_SOCBALANCE(Y,RRR,S,T,IPLUSMINUS)  "Feasibility of QEV_BEV_SOCBALANCE";
$ifi %EV_infeas%==yes POSITIVE VARIABLE VQEV_PHEV_SOCBALANCE(Y,RRR,S,T,IPLUSMINUS)  "Feasibility of QEV_PHEV_SOCBALANCE";
