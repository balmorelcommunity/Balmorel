EQUATIONS
QEV_BEV_SOCBALANCE(Y,RRR,S,T)                               *'SOC balance of the BEV fleet all equeations excluded for <2019 since EV demand is already included in general EL demand'
QEV_BEV_CHARGEBALANCE(Y,RRR,S,T)                            *'G2V inflexible charging and V2G charging have to be smaller than maximum charger capacity for BEV'
QEV_PHEV_SOCBALANCE(Y,RRR,S,T)                              *'SOC balance of the PHEV fleet'
QEV_PHEV_CHARGEBALANCE(Y,RRR,S,T)                           *'G2V inflexible charging and V2G charging have to be smaller than maximum charger capacity for PHEV'
;

** BEV Battery balance
QEV_BEV_SOCBALANCE(IY411,IR,IS3,T)$(IHASBEV(IR) AND IY411.val>2019)..
                             VEV_VSOC_BEV(IY411,IR,IS3,T)
                             =E=
$ifi %STEPCHARGSCHEME%==yes  (
                             VEV_VSOC_BEV(IY411,IR,IS3,T--1) + (EV_BEV_SOCFlex(IY411,IS3,T,IR) + VEV_VG2V_BEV(IY411,IR,IS3,T) * EV_PEFF(IY411) - EV_BEV_Flex(IY411,IS3,T,IR))*CHRONOHOUR(IS3,T)
$ifi %V2G%==yes              - VEV_VV2G_BEV(IY411,IR,IS3,T) / EV_PEFF(IY411)*CHRONOHOUR(IS3,T)
$ifi %STEPCHARGSCHEME%==yes  - (VEV_VV2G_BEV(IY411,IR,IS3,T) / EV_PEFF(IY411)*CHRONOHOUR(IS3,T))$cs('v2g',IY411)   )$(not cs('dumb',IY411)) + 0

$ifi %EV_infeas%==yes     +VQEV_BEV_SOCBALANCE(IY411,IR,IS3,T,'IMINUS') -VQEV_BEV_SOCBALANCE(IY411,IR,IS3,T,'IPLUS')
;


* total charging of BEV activity must be lower than ...
QEV_BEV_CHARGEBALANCE(IY411,IR,IS3,T)$(IHASBEV(IR) AND IY411.val>2019
$ifi %STEPCHARGSCHEME%==yes AND cs('v2g',IY411)
)..
         EV_BEV_Avail(IY411,IS3,T,IR) * EV_BEV_CHARGERCAP(IY411) / EV_PEFF(IY411)
         =G=
         (VEV_VG2V_BEV(IY411,IR,IS3,T) + VEV_VV2G_BEV(IY411,IR,IS3,T))
;


** PHEV Battery balance
QEV_PHEV_SOCBALANCE(IY411,IR,IS3,T)$(IHASPHEV(IR) AND IY411.val>2019)..
                             VEV_VSOC_PHEV(IY411,IR,IS3,T)
                             =E=
$ifi %STEPCHARGSCHEME%==yes  (
                             VEV_VSOC_PHEV(IY411,IR,IS3,T--1) + (EV_PHEV_SOCFlex(IY411,IS3,T,IR) + VEV_VG2V_PHEV(IY411,IR,IS3,T) * EV_PEFF(IY411) - EV_PHEV_Flex(IY411,IS3,T,IR))*CHRONOHOUR(IS3,T)
$ifi %V2G%==yes              - VEV_VV2G_PHEV(IY411,IR,IS3,T) / EV_PEFF(IY411)*CHRONOHOUR(IS3,T)
$ifi %STEPCHARGSCHEME%==yes  - (VEV_VV2G_PHEV(IY411,IR,IS3,T) / EV_PEFF(IY411)*CHRONOHOUR(IS3,T))$cs('v2g',IY411)   )$(not cs('dumb',IY411)) + 0

$ifi %EV_infeas%==yes     +VQEV_PHEV_SOCBALANCE(IY411,IR,IS3,T,'IMINUS') -VQEV_PHEV_SOCBALANCE(IY411,IR,IS3,T,'IPLUS')
;



*Only V2G:
* total charging of BEV activity must be lower than ...
QEV_PHEV_CHARGEBALANCE(IY411,IR,IS3,T)$(IHASPHEV(IR) AND IY411.val>2019
$ifi %STEPCHARGSCHEME%==yes AND cs('v2g',IY411)
)..
         EV_PHEV_Avail(IY411,IS3,T,IR) * EV_PHEV_CHARGERCAP(IY411) / EV_PEFF(IY411)
         =G=
* Total charging activity
         (VEV_VG2V_PHEV(IY411,IR,IS3,T) + VEV_VV2G_PHEV(IY411,IR,IS3,T))
;

