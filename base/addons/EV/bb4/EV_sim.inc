** Upper and lower limits to charging of electrical vehicles
* Dumb charging: levels are fixed
$ifi %DUMB%==yes    VEV_VG2V_BEV.FX(IY411,IR,S,T)$IHASBEV(IR) = (EV_BEV_Dumb(IY411,S,T,IR) / EV_PEFF(IY411))$(IY411.val>2019) +0   ;
$ifi %DUMB%==yes    VEV_VG2V_PHEV.FX(IY411,IR,S,T)$IHASPHEV(IR) = (EV_PHEV_Dumb(IY411,S,T,IR) / EV_PEFF(IY411))$(IY411.val>2019) +0  ;

*That's it for dumb charging
$ifi %DUMB%==yes  $goto limits_dumb_end


*Smart and V2G charging:
* Upper limit is the charging capacity divided by charging efficiency
VEV_VG2V_BEV.UP(IY411,IR,S,T)$IHASBEV(IR) =  (EV_BEV_Avail(IY411,S,T,IR) * EV_BEV_CHARGERCAP(IY411) / EV_PEFF(IY411))$(IY411.val>2019) + 0 ;    !!
VEV_VG2V_PHEV.UP(IY411,IR,S,T)$IHASPHEV(IR) = (EV_PHEV_Avail(IY411,S,T,IR) * EV_PHEV_CHARGERCAP(IY411)/ EV_PEFF(IY411))$(IY411.val>2019) + 0 ; !!

* Lower limit is the inflexible charging
VEV_VG2V_BEV.LO(IY411,IR,S,T)$IHASBEV(IR) =  (EV_BEV_Inflex(IY411,S,T,IR) / EV_PEFF(IY411))$(IY411.val>2019) + 0 ;
VEV_VG2V_PHEV.LO(IY411,IR,S,T)$IHASPHEV(IR) = (EV_PHEV_Inflex(IY411,S,T,IR) / EV_PEFF(IY411))$(IY411.val>2019) + 0 ;

* V2G discharge capacities:
$ifi not %V2G%==yes VEV_VV2G_BEV.FX(IY411,IR,S,T)$IHASBEV(IR)  = 0;
$ifi not %V2G%==yes VEV_VV2G_PHEV.FX(IY411,IR,S,T)$IHASPHEV(IR) = 0;
$ifi %V2G%==yes     VEV_VV2G_BEV.UP(IY411,IR,S,T)$IHASBEV(IR) = (EV_BEV_Avail(IY411,S,T,IR) * EV_BEV_CHARGERCAP(IY411))$(IY411.val>2019) + 0 ;       !! Should it be PHEV charger cap?? or was that a bug?
$ifi %V2G%==yes     VEV_VV2G_PHEV.UP(IY411,IR,S,T)$IHASPHEV(IR) = (EV_PHEV_Avail(IY411,S,T,IR) * EV_PHEV_CHARGERCAP(IY411))$(IY411.val>2019) + 0 ;

* Step charging settings:
$ifi %STEPCHARGSCHEME%==yes  VEV_VG2V_BEV.FX(IY411,IR,S,T)$IHASBEV(IR) = (EV_BEV_Dumb(IY411,S,T,IR) / EV_PEFF(IY411))$((IY411.val>2019) AND cs('dumb',IY411))+0  ;
$ifi %STEPCHARGSCHEME%==yes  VEV_VG2V_PHEV.FX(IY411,IR,S,T)$IHASPHEV(IR) = (EV_PHEV_Dumb(IY411,S,T,IR) / EV_PEFF(IY411))$((IY411.val>2019) AND cs('dumb',IY411))+0 ;
$ifi %STEPCHARGSCHEME%==yes  VEV_VV2G_BEV.UP(IY411,IR,S,T)$IHASBEV(IR) = (EV_BEV_Avail(IY411,S,T,IR) * EV_BEV_CHARGERCAP(IY411))$((IY411.val>2019) AND cs('v2g',IY411))  + 0 ;
$ifi %STEPCHARGSCHEME%==yes  VEV_VV2G_PHEV.UP(IY411,IR,S,T)$IHASPHEV(IR) = (EV_PHEV_Avail(IY411,S,T,IR) * EV_PHEV_CHARGERCAP(IY411))$((IY411.val>2019) AND cs('v2g',IY411)) + 0  ;


** Upper and lower limits to storage in electrical vehicles
VEV_VSOC_BEV.UP(IY411,IR,S,T)$IHASBEV(IR) = EV_BEV_Max(IY411,S,T,IR);
VEV_VSOC_PHEV.UP(IY411,IR,S,T)$IHASPHEV(IR) = EV_PHEV_Max(IY411,S,T,IR);
VEV_VSOC_BEV.LO(IY411,IR,S,T)$IHASBEV(IR) = EV_BEV_Min(IY411,S,T,IR);
VEV_VSOC_PHEV.LO(IY411,IR,S,T)$IHASPHEV(IR) = EV_PHEV_Min(IY411,S,T,IR);

$ifi %STEPCHARGSCHEME%==yes  VEV_VSOC_BEV.UP(IY411,IR,S,T)$(cs('dumb',IY411) AND IHASBEV(IR)) = 0  ;
$ifi %STEPCHARGSCHEME%==yes  VEV_VSOC_PHEV.UP(IY411,IR,S,T)$(cs('dumb',IY411) AND IHASPHEV(IR))  = 0 ;

*Restricting V2G from PHEV
$ifi %V2G%==yes $ifi %NO_PHEV_V2G%==yes  VEV_VV2G_PHEV.FX(IY411,IR,S,T)$IHASPHEV(IR)=0;




*Fixing storage level for EV from previous runs:
$ifi %import_results%==yes $ifi %EV%==yes $ifi %ADDEVSTOS%==cont  VEV_VSOC_BEV.FX(IY411,IR,S,T)$(ORD(T) EQ CARD(T))=EV_VSOC_BEV(IY411,IR,S,T);
$ifi %import_results%==yes $ifi %EV%==yes $ifi %ADDEVSTOS%==cont  VEV_VSOC_PHEV.FX(IY411,IR,S,T)$(ORD(T) EQ CARD(T))=EV_VSOC_PHEV(IY411,IR,S,T);
$ifi %import_results%==yes $ifi %EV%==yes $ifi %ADDEVSTOS%==netcharging  VEV_VSOC_BEV.FX(IY411,IR,S,T)$(ORD(T) EQ CARD(T))=EV_VSOC_BEV(IY411,IR,S,T);
$ifi %import_results%==yes $ifi %EV%==yes $ifi %ADDEVSTOS%==netcharging  VEV_VSOC_PHEV.FX(IY411,IR,S,T)$(ORD(T) EQ CARD(T))=EV_VSOC_PHEV(IY411,IR,S,T);


$label limits_dumb_end

