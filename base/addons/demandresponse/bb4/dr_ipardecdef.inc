* installed capacity of the load - the internal parameter includes also the adoption rate
PARAMETER IDR_FX(Y,AAA,DR_TECH);
IDR_FX(Y,IA,DR_TECH) = DR_FX(Y,IA,DR_TECH)  * DR_ADOPTIONRATE(DR_TECH,Y) ;

PARAMETER ANNUITYDR(DR_TECH) 'Annuity factor for investments in DR technologies';
* Standard annuity factor r/(1-(1+r)^-n); the numerator was a hard-coded 0.06
ANNUITYDR(DR_TECH)$DR_DATA(DR_TECH,'DRINVCOST') = DR_DATA(DR_TECH,'DRINTERESTRATE')/(1-(1+DR_DATA(DR_TECH,'DRINTERESTRATE'))**(-DR_DATA(DR_TECH,'DRLIFETIME')));



* IDR_RATE - parameter for the usage profiles for demand response technologies
PARAMETER IDR_RATE(AAA,DR_TECH,S,T) 'Hourly rating/availability for downregulation of demand response technologies';

*Initializing all IDR_RATE alternatives
IDR_RATE(IA,DR_TECH,S,T)$SUM((Y),DR_FX(Y,IA,DR_TECH)) = DR_FLH(IA,DR_TECH) / 8760;
IDR_RATE(IA,DR_TECH,S,T)$(SUM((Y),DR_FX(Y,IA,DR_TECH)) AND DR_RATE_T(T,DR_TECH)) = DR_RATE_T(T,DR_TECH) * DR_FLH(IA,DR_TECH) / 8760;
IDR_RATE(IA,DR_TECH,S,T)$(SUM((Y),DR_FX(Y,IA,DR_TECH)) AND DR_RATE_S(IA,DR_TECH,S)) = DR_RATE_S(IA,DR_TECH,S) * DR_FLH(IA,DR_TECH) / 8760;
IDR_RATE(IA,DR_TECH,S,T)$(SUM((Y),DR_FX(Y,IA,DR_TECH)) AND DR_RATE_T(T,DR_TECH) AND DR_RATE_S(IA,DR_TECH,S)) = DR_RATE_S(IA,DR_TECH,S)*DR_RATE_T(T,DR_TECH) * DR_FLH(IA,DR_TECH) / 8760;
IDR_RATE(IA,DR_TECH,S,T)$(IDR_RATE(IA,DR_TECH,S,T) > 1) = 1;

* How long load can be shifted, in hours. IDR_HHH1/IDR_HHH2(DR_TECH,S,T,T_alias) are the hours of
* time step T_alias inside the shifting window of time step T, built from cumulative hours (CHRONOHOUR), so DRSHIFTNEXT
* and DRSHIFTPREV mean the same number of hours in every run type:
* IDR_HHH1: the DRSHIFTNEXT hours up to the end of T (load shifted to a later point in time)
* IDR_HHH2: the DRSHIFTPREV hours from the start of T (load shifted to an earlier point in time)
* With hourly time steps they equal the former step-count windows.
PARAMETER IDR_ENDHOUR(S,T)              'Hours from the start of the season to the end of time step T (h)';
PARAMETER IDR_HHH1(DR_TECH,S,T,T_alias) 'Hours of T_alias inside the shift-later window ending with T (h)';
PARAMETER IDR_HHH2(DR_TECH,S,T,T_alias) 'Hours of T_alias inside the shift-earlier window starting with T (h)';
IDR_ENDHOUR(S,T) = SUM(T_alias$(ORD(T_alias) LE ORD(T)), CHRONOHOUR(S,T_alias));
IDR_HHH1(DR_TECH_SHIFT,S,T,T_alias)$(ORD(T_alias) LE ORD(T)
    AND IDR_ENDHOUR(S,T_alias) GT IDR_ENDHOUR(S,T) - DR_DATA(DR_TECH_SHIFT,'DRSHIFTNEXT'))
    = IDR_ENDHOUR(S,T_alias) - MAX(IDR_ENDHOUR(S,T_alias) - CHRONOHOUR(S,T_alias), IDR_ENDHOUR(S,T) - DR_DATA(DR_TECH_SHIFT,'DRSHIFTNEXT'));
IDR_HHH2(DR_TECH_SHIFT,S,T,T_alias)$(ORD(T_alias) GE ORD(T)
    AND IDR_ENDHOUR(S,T_alias) - CHRONOHOUR(S,T_alias) LT IDR_ENDHOUR(S,T) - CHRONOHOUR(S,T) + DR_DATA(DR_TECH_SHIFT,'DRSHIFTPREV'))
    = MIN(IDR_ENDHOUR(S,T_alias), IDR_ENDHOUR(S,T) - CHRONOHOUR(S,T) + DR_DATA(DR_TECH_SHIFT,'DRSHIFTPREV')) - (IDR_ENDHOUR(S,T_alias) - CHRONOHOUR(S,T_alias));

