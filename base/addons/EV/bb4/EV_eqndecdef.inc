EQUATIONS
QEV_BEV_BEBALANCE(Y,RRR,S,T)                               *'Batter Energy balance of the BEV fleet all equations excluded for <2019 since EV demand is already included in general EL demand'
QEV_BEV_CHARGEBALANCE(Y,RRR,S,T)                            *'G2V inflexible charging and V2G charging have to be smaller than maximum charger capacity for BEV'
QEV_PHEV_BEBALANCE(Y,RRR,S,T)                              *'Battery Energy balance of the PHEV fleet'
QEV_PHEV_CHARGEBALANCE(Y,RRR,S,T)                           *'G2V inflexible charging and V2G charging have to be smaller than maximum charger capacity for PHEV'
;



** BEV Battery SOC balance
QEV_BEV_BEBALANCE(IY411,IR,S,T)$(IHASBEV(IR) AND IS3(S) AND IY411.val>2019)..
                                    VEV_BE_BEV(IY411,IR,S,T)
                                    =E=
* If intraseasonal take T--1 to get last time step in current season, when T=1.
$ifi not %EV_INTERSEASONAL%==yes    VEV_BE_BEV(IY411,IR,S,T--1)
* If intraseasonal and rolling seasons, use netcharging. Copied from old EV Addon, variable names adapted.
$ifi not %EV_INTERSEASONAL%==yes  $ifi %RollingSeasons%==yes $ifi %import_results%==yes $ifi %ADDEVSTOS%==netcharging + VEV_BE_BEV(IY411,IR,S,T) - VEV_BE_BEV(IY411,IR,S,T--1) - EV_BEV_NETCHARGING(IY411,IR,S,T)
* If interseasonal, get last time step in last season, when T=1. SUM() to get the right T index, only summing 1 value.
$ifi %EV_INTERSEASONAL%==yes        VEV_BE_BEV(IY411,IR,S,T-1) + SUM(ITALIAS$(ORD(ITALIAS) EQ CARD(ITALIAS)), VEV_BE_BEV(IY411,IR,S--1,ITALIAS))$(1 EQ ORD(T))
* If interseasonal and rolling seasons, use previous run storage. Copied from old EV Addon, variable names adapted.
*$ifi %EV_INTERSEASONAL%==yes $ifi %RollingSeasons%==yes $ifi %import_results%==yes $ifi  %ADDEVSTOS%==cont   -SUM(ITALIAS$(ORD(ITALIAS) EQ CARD(ITALIAS)), VEV_BE_BEV(IY411,IR,S--1,ITALIAS))$(1 EQ ORD(T) AND ORD(S) EQ 1) + SUM(SSS$(ICOUNTSSSTTT(S,T) EQ ICOUNTSSSTTT(SSS,T)), SUM(ITALIAS$(ORD(ITALIAS) EQ CARD(ITALIAS)), EV_BE_BEV(IY411,IR,SSS--1,ITALIAS)))$(1 EQ ORD(T) AND (1 EQ ORD(S)))

  
* The load (EVs returning with SOC, EVs leaving with SOC and variable charging and passive discharging) multiplied with CHRONOHOUR if not all T is chosen for scaling.
$ifi not %EV_allreturn%==yes        + (IEV_BEV_return(IY411,S,T,IR)*EV_BEV_return_energy(IY411) + VEV_G2V_BEV(IY411,IR,S,T)*EV_BEV_G2V_EFF(IY411) + IEV_BEV_leave(IY411,S,T,IR)*EV_BEV_leave_energy(IY411)) * CHRONOHOUR(S,T)
$ifi %EV_allreturn%==yes            + (IEV_BEV_return(IY411,S,T,IR)*(EV_BEV_batsize(IY411)-EV_BEV_return_energy(T,IR)) + VEV_G2V_BEV(IY411,IR,S,T)*EV_BEV_G2V_EFF(IY411) + IEV_BEV_leave(IY411,S,T,IR)*EV_BEV_leave_energy(IY411)) * CHRONOHOUR(S,T)


* V2G multiplied with CHRONOHOUR if not all T is chosen for scaling
$ifi %V2G%==yes                     - (VEV_V2G_BEV(IY411,IR,S,T)/EV_BEV_V2G_EFF(IY411))*CHRONOHOUR(S,T)
* Slack variables to avoid infeasibility
$ifi %EV_infeas%==yes               + VQEV_BEV_BEBALANCE(IY411,IR,S,T,'IMINUS') - VQEV_BEV_BEBALANCE(IY411,IR,S,T,'IPLUS')
;

** BEV total chargercap for G2V+V2G
QEV_BEV_CHARGEBALANCE(IY411,IR,S,T)$(IHASBEV(IR) AND IS3(S) AND IY411.val>2019)..
                                    IEV_BEV_available(IY411,S,T,IR) * EV_BEV_dumb(IY411,IR) * EV_BEV_dumb_energy(IY411) + (IEV_BEV_available(IY411,S,T,IR) - IEV_BEV_available(IY411,S,T,IR) * EV_BEV_dumb(IY411,IR)) * EV_BEV_chargercap(IY411)
                                    =G=
                                    VEV_G2V_BEV(IY411,IR,S,T) + VEV_V2G_BEV(IY411,IR,S,T)
;

*-------------------------------------------------*

** PHEV Battery SOC balance
QEV_PHEV_BEBALANCE(IY411,IR,S,T)$(IHASPHEV(IR) AND IS3(S) AND IY411.val>2019)..
                                    IEV_PHEV_available(IY411,S,T,IR) * EV_PHEV_dumb(IY411,IR) * EV_PHEV_dumb_energy(IY411) + (IEV_PHEV_available(IY411,S,T,IR) - IEV_PHEV_available(IY411,S,T,IR) * EV_PHEV_dumb(IY411,IR)) * EV_PHEV_chargercap(IY411)
                                    =E=
* If intraseasonal take T--1 to get last time step in current season, when T=1.
$ifi not %EV_INTERSEASONAL%==yes    VEV_BE_PHEV(IY411,IR,S,T--1)
* If intraseasonal and rolling seasons, use netcharging. Copied from old EV Addon, variable names adapted.
$ifi not %EV_INTERSEASONAL%==yes  $ifi %RollingSeasons%==yes $ifi %import_results%==yes $ifi %ADDEVSTOS%==netcharging + VEV_BE_PHEV(IY411,IR,S,T) - VEV_BE_PHEV(IY411,IR,S,T--1) - EV_PHEV_NETCHARGING(IY411,IR,S,T)
* If interseasonal, get last time step in last season, when T=1. SUM() to get the right T index, only summing 1 value.
$ifi %EV_INTERSEASONAL%==yes        VEV_BE_PHEV(IY411,IR,S,T-1) + SUM(ITALIAS$(ORD(ITALIAS) EQ CARD(ITALIAS)), VEV_BE_PHEV(IY411,IR,S--1,ITALIAS))$(ORD(T) EQ 1)
* If interseasonal and rolling seasons, use previous run storage. Copied from old EV Addon, variable names adapted.
$ifi %EV_INTERSEASONAL%==yes $ifi %RollingSeasons%==yes $ifi %import_results%==yes $ifi  %ADDEVSTOS%==cont   -SUM(ITALIAS$(ORD(ITALIAS) EQ CARD(ITALIAS)), VEV_BE_PHEV(IY411,IR,S--1,ITALIAS))$(1 EQ ORD(T) AND ORD(S) EQ 1) + SUM(SSS$(ICOUNTSSSTTT(S,T) EQ ICOUNTSSSTTT(SSS,T)), SUM(ITALIAS$(ORD(ITALIAS) EQ CARD(ITALIAS)), EV_BE_PHEV(IY411,IR,SSS--1,ITALIAS)))$(1 EQ ORD(T) AND (1 EQ ORD(S)))
* The load (EVs returning with SOC, EVs leaving with SOC and variable charging) multiplied with CHRONOHOUR if not all T is chosen for scaling.
                                    + (IEV_PHEV_return(IY411,S,T,IR)*EV_PHEV_return_energy(IY411) + VEV_G2V_PHEV(IY411,IR,S,T)*EV_PHEV_G2V_EFF(IY411) + IEV_PHEV_leave(IY411,S,T,IR)*EV_PHEV_leave_energy(IY411)) * CHRONOHOUR(S,T)
* V2G multiplied with CHRONOHOUR if not all T is chosen for scaling
$ifi %V2G%==yes                     - (VEV_V2G_PHEV(IY411,IR,S,T)/EV_PHEV_V2G_EFF(IY411))*CHRONOHOUR(S,T)
* Slack variables to avoid infeasibility
$ifi %EV_infeas%==yes              + VQEV_PHEV_BEBALANCE(IY411,IR,S,T,'IMINUS') - VQEV_PHEV_BEBALANCE(IY411,IR,S,T,'IPLUS')
;


** PHEV total chargercap for G2V+V2G
QEV_PHEV_CHARGEBALANCE(IY411,IR,S,T)$(IHASPHEV(IR) AND IS3(S) AND IY411.val>2019)..
                                    IEV_PHEV_available(IY411,S,T,IR) * EV_PHEV_chargercap(IY411)
                                    =G=
                                    VEV_G2V_PHEV(IY411,IR,S,T) + VEV_V2G_PHEV(IY411,IR,S,T)
;
