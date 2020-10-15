
** Upper and lower limits to charging of electrical vehicles
* Dumb charging: levels are fixed
$ifi %DUMB%==yes    VEV_VG2V_BEV.FX(IY411,IR,S,T) = (EV_BEV_Dumb(IY411,S,T,IR) / EV_PEFF(IY411))$(IY411.val>2019) +0   ;
$ifi %DUMB%==yes    VEV_VG2V_PHEV.FX(IY411,IR,S,T) = (EV_PHEV_Dumb(IY411,S,T,IR) / EV_PEFF(IY411))$(IY411.val>2019) +0  ;

* if not V2G, this variable is set to zero
VEV_VV2G_BEV.UP(IY411,IR,S,T)  = 0;
VEV_VV2G_PHEV.UP(IY411,IR,S,T) = 0;

*That's it for dumb charging
$ifi %DUMB%==yes  $goto limits_dumb_end


*Smart and V2G charging:
* Upper limit is the charging capacity divided by charging efficiency
VEV_VG2V_BEV.UP(IY411,IR,S,T) =  (EV_BEV_Avail(IY411,S,T,IR) * EV_BEV_CHARGERCAP(IY411) / EV_PEFF(IY411) )$(IY411.val>2019) + 0 ;    !!
VEV_VG2V_PHEV.UP(IY411,IR,S,T) = (EV_PHEV_Avail(IY411,S,T,IR) * EV_PHEV_CHARGERCAP(IY411)/ EV_PEFF(IY411)  )$(IY411.val>2019) + 0 ; !!

* Lower limit is the inflexible charging
VEV_VG2V_BEV.LO(IY411,IR,S,T) =  (EV_BEV_Inflex(IY411,S,T,IR) / EV_PEFF(IY411))$(IY411.val>2019) + 0 ;
VEV_VG2V_PHEV.LO(IY411,IR,S,T) = (EV_PHEV_Inflex(IY411,S,T,IR) / EV_PEFF(IY411))$(IY411.val>2019) + 0 ;

* V2G discharge capacities:
$ifi %V2G%==yes     VEV_VV2G_BEV.UP(IY411,IR,S,T) = (EV_BEV_Avail(IY411,S,T,IR) * EV_BEV_CHARGERCAP(IY411))$(IY411.val>2019) + 0 ;       !! Should it be PHEV charger cap?? or was that a bug?
$ifi %V2G%==yes     VEV_VV2G_PHEV.UP(IY411,IR,S,T) = (EV_PHEV_Avail(IY411,S,T,IR) * EV_PHEV_CHARGERCAP(IY411))$(IY411.val>2019) + 0 ;

* Step charging settings:
$ifi %STEPCHARGSCHEME%==yes  VEV_VG2V_BEV.FX(IY411,IR,S,T) = (EV_BEV_Dumb(IY411,S,T,IR) / EV_PEFF(IY411))$((IY411.val>2019) AND cs('dumb',IY411))+0  ;
$ifi %STEPCHARGSCHEME%==yes  VEV_VG2V_PHEV.FX(IY411,IR,S,T) = (EV_PHEV_Dumb(IY411,S,T,IR) / EV_PEFF(IY411))$((IY411.val>2019) AND cs('dumb',IY411))+0 ;
$ifi %STEPCHARGSCHEME%==yes  VEV_VV2G_BEV.UP(IY411,IR,S,T) = (EV_BEV_Avail(IY411,S,T,IR) * EV_BEV_CHARGERCAP(IY411))$((IY411.val>2019) AND cs('v2g',IY411))  + 0 ;
$ifi %STEPCHARGSCHEME%==yes  VEV_VV2G_PHEV.UP(IY411,IR,S,T) = (EV_PHEV_Avail(IY411,S,T,IR) * EV_PHEV_CHARGERCAP(IY411))$((IY411.val>2019) AND cs('v2g',IY411)) + 0  ;


** Upper and lower limits to storage in electrical vehicles
VEV_VSOC_BEV.UP(IY411,IR,S,T) = EV_BEV_Max(IY411,S,T,IR)+0.1;
VEV_VSOC_PHEV.UP(IY411,IR,S,T) = EV_PHEV_Max(IY411,S,T,IR)+0.1;
VEV_VSOC_BEV.LO(IY411,IR,S,T) = EV_BEV_Min(IY411,S,T,IR);
VEV_VSOC_PHEV.LO(IY411,IR,S,T) = EV_PHEV_Min(IY411,S,T,IR);

$ifi %STEPCHARGSCHEME%==yes  VEV_VSOC_BEV.UP(IY411,IR,S,T)$cs('dumb',IY411) = 0  ;
$ifi %STEPCHARGSCHEME%==yes  VEV_VSOC_PHEV.UP(IY411,IR,S,T)$cs('dumb',IY411)  = 0 ;


$LABEL limits_dumb_end


