$ifi not %STEPCHARGSCHEME%==yes $goto STEPCHARGSCHEME_SET_END
set CHARGINGSTRAGEGY /dumb, smart, v2g/;
set cs(CHARGINGSTRAGEGY,Y);
cs('dumb',Y)$(Y.val =2020) = yes;
cs('dumb',Y)$(Y.val =2030) = yes;
cs('smart',Y)$(Y.val =2040) = yes;
cs('v2g',Y)$(Y.val =2050) = yes;

$label  STEPCHARGSCHEME_SET_END


$ifi not %DUMB%==yes $goto DUMB_END
Equations
QEV_BEV_NETCHARGETAX(Y,RRR,S,T)                             *'Netcharging of BEV for tax and tariff calculation all equeations excluded for <2019 since EV demand is already included in general EL demand'
QEV_PHEV_NETCHARGETAX(Y,RRR,S,T)                            *'Netcharging of PHEV for tax and tariff calculation'
QEV_BEV_NETDISCHARGETAX(Y,RRR,S,T)                          *'Netdischarging of BEV for tax and tariff calculation'
QEV_PHEV_NETDISCHARGETAX(Y,RRR,S,T)                         *'Netdischarging of PHEV for tax and tariff calculation'

;

QEV_BEV_NETCHARGETAX(IY411,IR,S,T)..
VEV_VNETCHARGE_BEV(IY411,IR,S,T)
=E=
+(EV_BEV_Dumb(IY411,S,T,IR)*(1/EV_PEFF(IY411)))$(IY411.val>2019)+0

;

QEV_PHEV_NETCHARGETAX(IY411,IR,S,T)..

VEV_VNETCHARGE_PHEV(IY411,IR,S,T)
=E=
+(EV_PHEV_Dumb(IY411,S,T,IR)*(1/EV_PEFF(IY411)))$(IY411.val>2019)+0

;

QEV_BEV_NETDISCHARGETAX(IY411,IR,S,T)..

VEV_VNETDISCHARGE_BEV(IY411,IR,S,T)
=E=
0

;

QEV_PHEV_NETDISCHARGETAX(IY411,IR,S,T)..

VEV_VNETDISCHARGE_PHEV(IY411,IR,S,T)
=E=
0

;


$label  DUMB_END









$ifi not %SMART%==yes $goto SMART_END
EQUATIONS
QEV_BEV_SOCBALANCE(Y,RRR,S,T)                               'SOC balance of the BEV fleet all equeations excluded for <2019 since EV demand is already included in general EL demand'
QEV_BEV_CHARGEBALANCE(Y,RRR,S,T)                            'G2V inflexible charging and V2G charging have to be smaller than maximum charger capacity for BEV'
QEV_PHEV_SOCBALANCE(Y,RRR,S,T)                              'SOC balance of the PHEV fleet'
QEV_PHEV_CHARGEBALANCE(Y,RRR,S,T)                           'G2V inflexible charging and V2G charging have to be smaller than maximum charger capacity for PHEV'
QEV_BEV_NETCHARGETAX(Y,RRR,S,T)                             'Netcharging of BEV for tax and tariff calculation'
QEV_PHEV_NETCHARGETAX(Y,RRR,S,T)                            'Netcharging of PHEV for tax and tariff calculation'
QEV_BEV_NETDISCHARGETAX(Y,RRR,S,T)                          'Netcharging of BEV for tax and tariff calculation'
QEV_PHEV_NETDISCHARGETAX(Y,RRR,S,T)                         'Netdischarging of PHEV for tax and tariff calculation'


;

QEV_BEV_SOCBALANCE(IY411,IR,S,T)..

VEV_VSOC_BEV(IY411,IR,S,T)
=E=
* Total charging demand within each interval BEV
(VEV_VSOC_BEV(IY411,IR,S,T--1) + EV_BEV_SOCFlex(IY411,S,T,IR) + EV_BEV_Inflex(IY411,S,T,IR) + VEV_VG2V_BEV(IY411,IR,S,T) * EV_PEFF(IY411) - EV_BEV_Flex(IY411,S,T,IR))$(IY411.val>2019)+0
;


QEV_BEV_CHARGEBALANCE(IY411,IR,S,T)..



EV_BEV_Avail(IY411,S,T,IR) * EV_BEV_CHARGERCAP(IY411)
=G=
* Total charging activity
(EV_BEV_Inflex(IY411,S,T,IR) + VEV_VG2V_BEV(IY411,IR,S,T))$(IY411.val>2019)+0
;



QEV_PHEV_SOCBALANCE(IY411,IR,S,T)..


VEV_VSOC_PHEV(IY411,IR,S,T)
=E=
* Total charging demand within each interval PHEV
(VEV_VSOC_PHEV(IY411,IR,S,T--1) + EV_PHEV_SOCFlex(IY411,S,T,IR) + EV_PHEV_Inflex(IY411,S,T,IR) + VEV_VG2V_PHEV(IY411,IR,S,T) * EV_PEFF(IY411)  - EV_PHEV_Flex(IY411,S,T,IR))$(IY411.val>2019)+0
;


QEV_PHEV_CHARGEBALANCE(IY411,IR,S,T)..


EV_PHEV_Avail(IY411,S,T,IR) * EV_PHEV_CHARGERCAP(IY411)
=G=
* Total charging activity
(EV_PHEV_Inflex(IY411,S,T,IR) + VEV_VG2V_PHEV(IY411,IR,S,T))$(IY411.val>2019)+0
;




QEV_BEV_NETCHARGETAX(IY411,IR,S,T)..
VEV_VNETCHARGE_BEV(IY411,IR,S,T)
=E=
(+ EV_BEV_Inflex(IY411,S,T,IR)* 1/EV_PEFF(IY411)  + VEV_VG2V_BEV(IY411,IR,S,T))$(IY411.val>2019)+0

;

QEV_PHEV_NETCHARGETAX(IY411,IR,S,T)..

VEV_VNETCHARGE_PHEV(IY411,IR,S,T)
=E=
(+ EV_PHEV_Inflex(IY411,S,T,IR)* 1/EV_PEFF(IY411) + VEV_VG2V_PHEV(IY411,IR,S,T))$(IY411.val>2019)+0

;

QEV_BEV_NETDISCHARGETAX(IY411,IR,S,T)..

VEV_VNETDISCHARGE_BEV(IY411,IR,S,T)
=E=
0

;

QEV_PHEV_NETDISCHARGETAX(IY411,IR,S,T)..

VEV_VNETDISCHARGE_PHEV(IY411,IR,S,T)
=E=
0

;

$label  SMART_END




$ifi not %V2G%==yes $goto V2G_END
EQUATIONS
QEV_BEV_SOCBALANCE(Y,RRR,S,T)                               *'SOC balance of the BEV fleet'
QEV_BEV_CHARGEBALANCE(Y,RRR,S,T)                            *'G2V inflexible charging and V2G charging have to be smaller than maximum charger capacity for BEV'
QEV_PHEV_SOCBALANCE(Y,RRR,S,T)                              *'SOC balance of the PHEV fleet'
QEV_PHEV_CHARGEBALANCE(Y,RRR,S,T)                           *'G2V inflexible charging and V2G charging have to be smaller than maximum charger capacity for PHEV'
QEV_BEV_NETCHARGETAX(Y,RRR,S,T)                             *'Netcharging of BEV for tax and tariff calculation'
QEV_PHEV_NETCHARGETAX(Y,RRR,S,T)                            *'Netcharging of PHEV for tax and tariff calculation'
QEV_BEV_NETDISCHARGETAX(Y,RRR,S,T)                          *'Netcharging of BEV for tax and tariff calculation'
QEV_PHEV_NETDISCHARGETAX(Y,RRR,S,T)                         *'Netdischarging of PHEV for tax and tariff calculation'

;

QEV_BEV_SOCBALANCE(IY411,IR,S,T)..

VEV_VSOC_BEV(IY411,IR,S,T)
=E=
* Total charging demand within each interval BEV
(VEV_VSOC_BEV(IY411,IR,S,T--1) + EV_BEV_SOCFlex(IY411,S,T,IR) + EV_BEV_Inflex(IY411,S,T,IR) + VEV_VG2V_BEV(IY411,IR,S,T) * EV_PEFF(IY411) - VEV_VV2G_BEV(IY411,IR,S,T) * 1/EV_PEFF(IY411) - EV_BEV_Flex(IY411,S,T,IR))$(IY411.val>2019)+0
;


QEV_BEV_CHARGEBALANCE(IY411,IR,S,T)..



EV_BEV_Avail(IY411,S,T,IR) * EV_BEV_CHARGERCAP(IY411)
=G=
* Total charging activity
(EV_BEV_Inflex(IY411,S,T,IR) + VEV_VG2V_BEV(IY411,IR,S,T) + VEV_VV2G_BEV(IY411,IR,S,T))$(IY411.val>2019)+0
;



QEV_PHEV_SOCBALANCE(IY411,IR,S,T)..


VEV_VSOC_PHEV(IY411,IR,S,T)
=E=
* Total charging demand within each interval PHEV
(VEV_VSOC_PHEV(IY411,IR,S,T--1) + EV_PHEV_SOCFlex(IY411,S,T,IR) + EV_PHEV_Inflex(IY411,S,T,IR) + VEV_VG2V_PHEV(IY411,IR,S,T) * EV_PEFF(IY411)  - EV_PHEV_Flex(IY411,S,T,IR))$(IY411.val>2019)+0
;


QEV_PHEV_CHARGEBALANCE(IY411,IR,S,T)..


EV_PHEV_Avail(IY411,S,T,IR) * EV_PHEV_CHARGERCAP(IY411)
=G=
* Total charging activity
(EV_PHEV_Inflex(IY411,S,T,IR) + VEV_VG2V_PHEV(IY411,IR,S,T))$(IY411.val>2019)+0
;





QEV_BEV_NETCHARGETAX(IY411,IR,S,T)..
VEV_VNETCHARGE_BEV(IY411,IR,S,T)
=E=
(+ EV_BEV_Inflex(IY411,S,T,IR)* 1/EV_PEFF(IY411)  + VEV_VG2V_BEV(IY411,IR,S,T))$(IY411.val>2019)+0

;

QEV_PHEV_NETCHARGETAX(IY411,IR,S,T)..

VEV_VNETCHARGE_PHEV(IY411,IR,S,T)
=E=
(+ EV_PHEV_Inflex(IY411,S,T,IR)* 1/EV_PEFF(IY411) + VEV_VG2V_PHEV(IY411,IR,S,T))$(IY411.val>2019)+0

;

QEV_BEV_NETDISCHARGETAX(IY411,IR,S,T)..

VEV_VNETDISCHARGE_BEV(IY411,IR,S,T)
=E=
(VEV_VV2G_BEV(IY411,IR,S,T))$(IY411.val>2019)+0

;

QEV_PHEV_NETDISCHARGETAX(IY411,IR,S,T)..

VEV_VNETDISCHARGE_PHEV(IY411,IR,S,T)
=E=
* Has been excluded from the start because V2G with small plugin hybrid batteries does not make sense - will never be feasible with additional charger cost
0
;

$label  V2G_END










$ifi not %STEPCHARGSCHEME%==yes $goto STEPCHARGSCHEME_END




EQUATIONS
QEV_BEV_SOCBALANCE(Y,RRR,S,T)                               *'SOC balance of the BEV fleet all equeations excluded for <2019 since EV demand is already included in general EL demand'
QEV_BEV_CHARGEBALANCE(Y,RRR,S,T)                            *'G2V inflexible charging and V2G charging have to be smaller than maximum charger capacity for BEV'
QEV_PHEV_SOCBALANCE(Y,RRR,S,T)                              *'SOC balance of the PHEV fleet'
QEV_PHEV_CHARGEBALANCE(Y,RRR,S,T)                           *'G2V inflexible charging and V2G charging have to be smaller than maximum charger capacity for PHEV'
;
QEV_BEV_SOCBALANCE(IY411,IR,S,T)..
(EV_BEV_SOCDumb(IY411,S,T,IR))$cs('dumb',IY411)+
(VEV_VSOC_BEV(IY411,IR,S,T))$cs('smart',IY411)+
(VEV_VSOC_BEV(IY411,IR,S,T))$cs('V2G',IY411)
=E=
(EV_BEV_SOCDumb(IY411,S,T,IR))$cs('dumb',IY411)+
(VEV_VSOC_BEV(IY411,IR,S,T--1) + EV_BEV_SOCFlex(IY411,S,T,IR) + EV_BEV_Inflex(IY411,S,T,IR) + VEV_VG2V_BEV(IY411,IR,S,T) * EV_PEFF(IY411) - EV_BEV_Flex(IY411,S,T,IR))$cs('smart',IY411)+
(VEV_VSOC_BEV(IY411,IR,S,T--1) + EV_BEV_SOCFlex(IY411,S,T,IR) + EV_BEV_Inflex(IY411,S,T,IR) + VEV_VG2V_BEV(IY411,IR,S,T) * EV_PEFF(IY411) - VEV_VV2G_BEV(IY411,IR,S,T) * 1/EV_PEFF(IY411) - EV_BEV_Flex(IY411,S,T,IR))$cs('V2G',IY411)
;
QEV_BEV_CHARGEBALANCE(IY411,IR,S,T)..
(EV_BEV_Dumb(IY411,S,T,IR))$cs('dumb',IY411)+
(EV_BEV_Avail(IY411,S,T,IR) * EV_BEV_CHARGERCAP(IY411))$cs('smart',IY411)+
(EV_BEV_Avail(IY411,S,T,IR) * EV_BEV_CHARGERCAP(IY411))$cs('V2G',IY411)
=E=
(EV_BEV_Dumb(IY411,S,T,IR))$cs('dumb',IY411)+
(EV_BEV_Inflex(IY411,S,T,IR) + VEV_VG2V_BEV(IY411,IR,S,T))$cs('smart',IY411)+
(EV_BEV_Inflex(IY411,S,T,IR) + VEV_VG2V_BEV(IY411,IR,S,T) + VEV_VV2G_BEV(IY411,IR,S,T))$cs('V2G',IY411)
;
QEV_PHEV_SOCBALANCE(IY411,IR,S,T)..
(EV_PHEV_SOCDumb(IY411,S,T,IR))$cs('dumb',IY411)+
(VEV_VSOC_PHEV(IY411,IR,S,T))$cs('smart',IY411)+
(VEV_VSOC_PHEV(IY411,IR,S,T))$cs('V2G',IY411)
=E=
(EV_PHEV_SOCDumb(IY411,S,T,IR))$cs('dumb',IY411)+
(VEV_VSOC_PHEV(IY411,IR,S,T--1) + EV_PHEV_SOCFlex(IY411,S,T,IR) + EV_PHEV_Inflex(IY411,S,T,IR) + VEV_VG2V_PHEV(IY411,IR,S,T) * EV_PEFF(IY411)  - EV_PHEV_Flex(IY411,S,T,IR))$cs('smart',IY411)+
(VEV_VSOC_PHEV(IY411,IR,S,T--1) + EV_PHEV_SOCFlex(IY411,S,T,IR) + EV_PHEV_Inflex(IY411,S,T,IR) + VEV_VG2V_PHEV(IY411,IR,S,T) * EV_PEFF(IY411) - VEV_VV2G_PHEV(IY411,IR,S,T) * 1/EV_PEFF(IY411) - EV_PHEV_Flex(IY411,S,T,IR))$cs('V2G',IY411)
;
QEV_PHEV_CHARGEBALANCE(IY411,IR,S,T)..
(EV_PHEV_Dumb(IY411,S,T,IR))$cs('dumb',IY411)+
(EV_PHEV_Avail(IY411,S,T,IR) * EV_PHEV_CHARGERCAP(IY411))$cs('smart',IY411)+
(EV_PHEV_Avail(IY411,S,T,IR) * EV_PHEV_CHARGERCAP(IY411))$cs('V2G',IY411)
=E=
(EV_PHEV_Dumb(IY411,S,T,IR))$cs('dumb',IY411)+
(EV_PHEV_Inflex(IY411,S,T,IR) + VEV_VG2V_PHEV(IY411,IR,S,T))$cs('smart',IY411)+
(EV_PHEV_Inflex(IY411,S,T,IR) + VEV_VG2V_PHEV(IY411,IR,S,T) + VEV_VV2G_PHEV(IY411,IR,S,T))$cs('V2G',IY411)
;




$label STEPCHARGSCHEME_END
