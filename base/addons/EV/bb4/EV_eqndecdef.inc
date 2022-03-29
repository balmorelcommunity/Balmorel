EQUATIONS
QEV_BEV_SOCBALANCE(Y,RRR,S,T)                               *'SOC balance of the BEV fleet all equeations excluded for <2019 since EV demand is already included in general EL demand'
QEV_BEV_CHARGEBALANCE(Y,RRR,S,T)                            *'G2V inflexible charging and V2G charging have to be smaller than maximum charger capacity for BEV'
QEV_PHEV_SOCBALANCE(Y,RRR,S,T)                              *'SOC balance of the PHEV fleet'
QEV_PHEV_CHARGEBALANCE(Y,RRR,S,T)                           *'G2V inflexible charging and V2G charging have to be smaller than maximum charger capacity for PHEV'
;

** BEV Battery balance
QEV_BEV_SOCBALANCE(IY411,IR,S,T)$(IHASBEV(IR) AND IY411.val>2019 AND IS3(S))..
                             VEV_VSOC_BEV(IY411,IR,S,T)
                             =E=
$ifi %STEPCHARGSCHEME%==yes  (

$ifi not %EV_INTERSEASONAL%==yes   VEV_VSOC_BEV(IY411,IR,S,T--1)
$ifi not %EV_INTERSEASONAL%==yes  $ifi %RollingSeasons%==yes $ifi %import_results%==yes $ifi %ADDEVSTOS%==netcharging + VEV_VSOC_BEV(IY411,IR,S,T)-VEV_VSOC_BEV(IY411,IR,S,T--1) -EV_BEV_NETCHARGING(IY411,IR,S,T)
$ifi %EV_INTERSEASONAL%==yes   VEV_VSOC_BEV(IY411,IR,S,T-1)  +SUM(ITALIAS$(ORD(ITALIAS) EQ CARD(ITALIAS)),VEV_VSOC_BEV(IY411,IR,S--1,ITALIAS))$(1 EQ ORD(T))
$ifi %EV_INTERSEASONAL%==yes $ifi %RollingSeasons%==yes $ifi %import_results%==yes $ifi  %ADDEVSTOS%==cont   -SUM(ITALIAS$(ORD(ITALIAS) EQ CARD(ITALIAS)),VEV_VSOC_BEV(IY411,IR,S--1,ITALIAS))$(1 EQ ORD(T) AND ORD(S) EQ 1) +SUM(SSS$(ICOUNTSSSTTT(S,T) EQ ICOUNTSSSTTT(SSS,T)),SUM(ITALIAS$(ORD(ITALIAS) EQ CARD(ITALIAS)),EV_VSOC_BEV(IY411,IR,SSS--1,ITALIAS)))$(1 EQ ORD(T) AND (1 EQ ORD(S)))

                             + (EV_BEV_SOCFlex(IY411,S,T,IR) + VEV_VG2V_BEV(IY411,IR,S,T) * EV_PEFF(IY411) - EV_BEV_Flex(IY411,S,T,IR))*CHRONOHOUR(S,T)
$ifi %V2G%==yes              - VEV_VV2G_BEV(IY411,IR,S,T) / EV_PEFF(IY411)*CHRONOHOUR(S,T)
$ifi %STEPCHARGSCHEME%==yes  - (VEV_VV2G_BEV(IY411,IR,S,T) / EV_PEFF(IY411)*CHRONOHOUR(S,T))$cs('v2g',IY411)   )$(not cs('dumb',IY411)) + 0

$ifi %EV_infeas%==yes     +VQEV_BEV_SOCBALANCE(IY411,IR,S,T,'IMINUS') -VQEV_BEV_SOCBALANCE(IY411,IR,S,T,'IPLUS')
;


* total charging of BEV activity must be lower than ...
QEV_BEV_CHARGEBALANCE(IY411,IR,S,T)$(IHASBEV(IR) AND IY411.val>2019 AND IS3(S)
$ifi %STEPCHARGSCHEME%==yes AND cs('v2g',IY411)
)..
         EV_BEV_Avail(IY411,S,T,IR) * EV_BEV_CHARGERCAP(IY411) / EV_PEFF(IY411)
         =G=
         (VEV_VG2V_BEV(IY411,IR,S,T) + VEV_VV2G_BEV(IY411,IR,S,T))
;


** PHEV Battery balance
QEV_PHEV_SOCBALANCE(IY411,IR,S,T)$(IHASPHEV(IR) AND IY411.val>2019 AND IS3(S))..
                             VEV_VSOC_PHEV(IY411,IR,S,T)
                             =E=
$ifi %STEPCHARGSCHEME%==yes  (

$ifi not %EV_INTERSEASONAL%==yes   VEV_VSOC_PHEV(IY411,IR,S,T--1)
$ifi not %EV_INTERSEASONAL%==yes  $ifi %RollingSeasons%==yes $ifi %import_results%==yes $ifi %ADDEVSTOS%==netcharging + VEV_VSOC_PHEV(IY411,IR,S,T)-VEV_VSOC_PHEV(IY411,IR,S,T--1) -EV_PHEV_NETCHARGING(IY411,IR,S,T)
$ifi %EV_INTERSEASONAL%==yes $ifi %RollingSeasons%==yes $ifi %import_results%==yes $ifi  %ADDEVSTOS%==cont   -SUM(ITALIAS$(ORD(ITALIAS) EQ CARD(ITALIAS)),VEV_VSOC_PHEV(IY411,IR,S--1,ITALIAS))$(1 EQ ORD(T) AND ORD(S) EQ 1) +SUM(SSS$(ICOUNTSSSTTT(S,T) EQ ICOUNTSSSTTT(SSS,T)),SUM(ITALIAS$(ORD(ITALIAS) EQ CARD(ITALIAS)),EV_VSOC_PHEV(IY411,IR,SSS--1,ITALIAS)))$(1 EQ ORD(T) AND (1 EQ ORD(S)))

                             + (EV_PHEV_SOCFlex(IY411,S,T,IR) + VEV_VG2V_PHEV(IY411,IR,S,T) * EV_PEFF(IY411) - EV_PHEV_Flex(IY411,S,T,IR))*CHRONOHOUR(S,T)
$ifi %V2G%==yes              - VEV_VV2G_PHEV(IY411,IR,S,T) / EV_PEFF(IY411)*CHRONOHOUR(S,T)
$ifi %STEPCHARGSCHEME%==yes  - (VEV_VV2G_PHEV(IY411,IR,S,T) / EV_PEFF(IY411)*CHRONOHOUR(S,T))$cs('v2g',IY411)   )$(not cs('dumb',IY411)) + 0

$ifi %EV_infeas%==yes     +VQEV_PHEV_SOCBALANCE(IY411,IR,S,T,'IMINUS') -VQEV_PHEV_SOCBALANCE(IY411,IR,S,T,'IPLUS')
;



*Only V2G:
* total charging of BEV activity must be lower than ...
QEV_PHEV_CHARGEBALANCE(IY411,IR,S,T)$(IHASPHEV(IR) AND IY411.val>2019 AND IS3(S)
$ifi %STEPCHARGSCHEME%==yes AND cs('v2g',IY411)
)..
         EV_PHEV_Avail(IY411,S,T,IR) * EV_PHEV_CHARGERCAP(IY411) / EV_PEFF(IY411)
         =G=
* Total charging activity
         (VEV_VG2V_PHEV(IY411,IR,S,T) + VEV_VV2G_PHEV(IY411,IR,S,T))
;



