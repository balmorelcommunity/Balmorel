* SOC Limits
VEV_BE_BEV.UP(IY411,IR,S,T)$(IHASBEV(IR) AND IY411.val>2019) = IEV_BEV_available(IY411,S,T,IR) * EV_BEV_batsize(IY411);
VEV_BE_BEV.LO(IY411,IR,S,T)$(IHASBEV(IR) AND IY411.val>2019) = IEV_BEV_available(IY411,S,T,IR) * EV_BEV_emergency(IY411);

VEV_BE_PHEV.UP(IY411,IR,S,T)$(IHASPHEV(IR) AND IY411.val>2019) = IEV_PHEV_available(IY411,S,T,IR) * EV_PHEV_batsize(IY411);
VEV_BE_PHEV.LO(IY411,IR,S,T)$(IHASPHEV(IR) AND IY411.val>2019) = IEV_PHEV_available(IY411,S,T,IR) * EV_PHEV_emergency(IY411);

* G2V Limits
* TODO: Make a dynamic lower bound, so it will never be larger than the difference between current SOC and upper bound for SOC. Cases where this happend: Unrealistic large dumb charging, bad profiles where noone leaves.
* Upper bound is the lower bound + EVs not dumb charging (= Dumb_charging + Smart_charging), where the ones Smart_charging is the variable.
* TODO: Upper bound = Avail*CCAP - Change before turning in
VEV_G2V_BEV.LO(IY411,IR,S,T)$(IHASBEV(IR) AND IY411.val>2019) = IEV_BEV_available(IY411,S,T,IR) * EV_BEV_dumb(IY411,IR) * EV_BEV_dumb_energy(IY411);
VEV_G2V_BEV.UP(IY411,IR,S,T)$(IHASBEV(IR) AND IY411.val>2019) = VEV_G2V_BEV.LO(IY411,IR,S,T) + (IEV_BEV_available(IY411,S,T,IR) - IEV_BEV_available(IY411,S,T,IR) * EV_BEV_dumb(IY411,IR)) * EV_BEV_chargercap(IY411);  

VEV_G2V_PHEV.LO(IY411,IR,S,T)$(IHASPHEV(IR) AND IY411.val>2019) = IEV_PHEV_available(IY411,S,T,IR) * EV_PHEV_dumb(IY411,IR) * EV_PHEV_dumb_energy(IY411);
VEV_G2V_PHEV.UP(IY411,IR,S,T)$(IHASPHEV(IR) AND IY411.val>2019) = VEV_G2V_PHEV.LO(IY411,IR,S,T) + (IEV_PHEV_available(IY411,S,T,IR) - IEV_PHEV_available(IY411,S,T,IR) * EV_PHEV_dumb(IY411,IR)) * EV_PHEV_chargercap(IY411);  


* V2G Limits. Minus amount of DUMB charging, due to these is not capable of V2G

$ifi %V2G%==yes VEV_V2G_BEV.UP(IY411,IR,S,T)$(IHASBEV(IR) AND IY411.val > 2019) = min((IEV_BEV_available(IY411,S,T,IR) - IEV_BEV_available(IY411,S,T,IR)*EV_BEV_dumb(IY411,IR)) * EV_BEV_chargercap(IY411),IEV_BEV_available(IY411,S,T,IR) * Share_EV_V2G(IY411) * EV_BEV_chargercap(IY411));

*$ifi %V2G%==yes VEV_V2G_BEV.UP(IY411,IR,S,T)$(IHASBEV(IR) AND IY411.val>2019) = (IEV_BEV_available(IY411,S,T,IR) - IEV_BEV_available(IY411,S,T,IR)*EV_BEV_dumb(IY411,IR)) * EV_BEV_chargercap(IY411);

*$ifi %V2G%==yes VEV_V2G_BEV.UP(IY411,IR,S,T)$(IHASBEV(IR) AND IY411.val>2019) = IEV_BEV_available(IY411,S,T,IR) * Share_EV_V2G(IY411) * EV_BEV_chargercap(IY411);

$ifi %V2G%==yes VEV_V2G_PHEV.UP(IY411,IR,S,T)$(IHASPHEV(IR) AND IY411.val>2019) = (IEV_BEV_available(IY411,S,T,IR) - IEV_PHEV_available(IY411,S,T,IR)*EV_PHEV_dumb(IY411,IR)) * EV_PHEV_chargercap(IY411);

$ifi not %V2G%==yes VEV_V2G_BEV.FX(IY411,IR,S,T)$(IHASBEV(IR) AND IY411.val>2019) = 0;
$ifi not %V2G%==yes VEV_V2G_PHEV.FX(IY411,IR,S,T)$(IHASBEV(IR) AND IY411.val>2019) = 0;


*Fixing storage level for EV from previous runs. Copied from old EV Addon, variable names adapted.
*$ifi %import_results%==yes $ifi %EV%==yes $ifi %ADDEVSTOS%==cont  VEV_BE_BEV.FX(IY411,IR,S,T)$(ORD(T) EQ CARD(T))=EV_BE_BEV(IY411,IR,S,T);
*$ifi %import_results%==yes $ifi %EV%==yes $ifi %ADDEVSTOS%==cont  VEV_BE_PHEV.FX(IY411,IR,S,T)$(ORD(T) EQ CARD(T))=EV_BE_PHEV(IY411,IR,S,T);
*$ifi %import_results%==yes $ifi %EV%==yes $ifi %ADDEVSTOS%==netcharging  VEV_BE_BEV.FX(IY411,IR,S,T)$(ORD(T) EQ CARD(T))=EV_BE_BEV(IY411,IR,S,T);
*$ifi %import_results%==yes $ifi %EV%==yes $ifi %ADDEVSTOS%==netcharging  VEV_BE_PHEV.FX(IY411,IR,S,T)$(ORD(T) EQ CARD(T))=EV_BE_PHEV(IY411,IR,S,T);