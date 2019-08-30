EQUATIONS
QEV_BEV_SOCBALANCE(Y,RRR,S,T)                               *'SOC balance of the BEV fleet all equeations excluded for <2019 since EV demand is already included in general EL demand'
QEV_BEV_CHARGEBALANCE(Y,RRR,S,T)                            *'G2V inflexible charging and V2G charging have to be smaller than maximum charger capacity for BEV'
QEV_PHEV_SOCBALANCE(Y,RRR,S,T)                              *'SOC balance of the PHEV fleet'
QEV_PHEV_CHARGEBALANCE(Y,RRR,S,T)                           *'G2V inflexible charging and V2G charging have to be smaller than maximum charger capacity for PHEV'
;



** BEV Battery balance
QEV_BEV_SOCBALANCE(IY411,IR,S,T)$(IY411.val>2019)..
                             VEV_VSOC_BEV(IY411,IR,S,T)
                             =E=
$ifi %STEPCHARGSCHEME%==yes  (
                             VEV_VSOC_BEV(IY411,IR,S,T--1) + EV_BEV_SOCFlex(IY411,S,T,IR) + VEV_VG2V_BEV(IY411,IR,S,T) * EV_PEFF(IY411) - EV_BEV_Flex(IY411,S,T,IR)
$ifi %V2G%==yes              - VEV_VV2G_BEV(IY411,IR,S,T) / EV_PEFF(IY411)
$ifi %STEPCHARGSCHEME%==yes  - (VEV_VV2G_BEV(IY411,IR,S,T) / EV_PEFF(IY411))$cs('v2g',IY411)   )$(not cs('dumb',IY411)) + 0
;




* total charging of BEV activity must be lower than ...
QEV_BEV_CHARGEBALANCE(IY411,IR,S,T)$((IY411.val>2019)
$ifi %STEPCHARGSCHEME%==yes AND cs('v2g',IY411)
)..
         EV_BEV_Avail(IY411,S,T,IR) * EV_BEV_CHARGERCAP(IY411) / EV_PEFF(IY411)
         =G=
         (VEV_VG2V_BEV(IY411,IR,S,T) + VEV_VV2G_BEV(IY411,IR,S,T))
;


** PHEV Battery balance
QEV_PHEV_SOCBALANCE(IY411,IR,S,T)$(IY411.val>2019)..
                             VEV_VSOC_PHEV(IY411,IR,S,T)
                             =E=
$ifi %STEPCHARGSCHEME%==yes  (
                             VEV_VSOC_PHEV(IY411,IR,S,T--1) + EV_PHEV_SOCFlex(IY411,S,T,IR) + VEV_VG2V_PHEV(IY411,IR,S,T) * EV_PEFF(IY411) - EV_PHEV_Flex(IY411,S,T,IR)
$ifi %V2G%==yes              - VEV_VV2G_PHEV(IY411,IR,S,T) / EV_PEFF(IY411)
$ifi %STEPCHARGSCHEME%==yes  - (VEV_VV2G_PHEV(IY411,IR,S,T) / EV_PEFF(IY411))$cs('v2g',IY411)   )$(not cs('dumb',IY411)) + 0
;



*Only V2G:
* total charging of BEV activity must be lower than ...
QEV_PHEV_CHARGEBALANCE(IY411,IR,S,T)$((IY411.val>2019)
$ifi %STEPCHARGSCHEME%==yes AND cs('v2g',IY411)
)..
         EV_PHEV_Avail(IY411,S,T,IR) * EV_PHEV_CHARGERCAP(IY411) / EV_PEFF(IY411) 
         =G=
* Total charging activity
         (VEV_VG2V_PHEV(IY411,IR,S,T) + VEV_VV2G_PHEV(IY411,IR,S,T))
;


