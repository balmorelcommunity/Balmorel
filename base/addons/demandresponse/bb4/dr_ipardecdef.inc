* DR tech is SHED or SHIFT
DR_TECH_SHIFT(DR_TECH) = YES$(DR_DATA(DR_TECH,'DRTYPE') eq 2);
DR_TECH_SHED(DR_TECH) = YES$(DR_DATA(DR_TECH,'DRTYPE') eq 1);



* installed capacity of the load - the internal parameter includes also the adoption rate
PARAMETER IDR_FX(Y,AAA,DR_TECH);
IDR_FX(Y,IA,DR_TECH) = DR_FX(Y,IA,DR_TECH)  * DR_ADOPTIONRATE(DR_TECH,Y) ;


* how long it is possible to shift load to later point in time (DR_HHH1) or to an earlier point in time (DR_HHH2)
alias (T,T_alias);
set DR_HHH1(DR_TECH,T,T_alias)         'Shifting time matrix - whether a load can be shifted from H to HH';
set DR_HHH2(DR_TECH,T,T_alias)         'Shifting time matrix - whether a load can be shifted from H to HH';

DR_HHH1(DR_TECH_SHIFT,T,T_alias)  = YES$((ord(T_alias) le ord(T)+ DR_DATA(DR_TECH_SHIFT,'DRSHIFTNEXT')-1)   AND (ord(T_alias) ge ord(T)));
DR_HHH2(DR_TECH_SHIFT,T,T_alias)  = YES$((ord(T_alias) le ord(T))   AND (ord(T_alias) ge ord(T)- DR_DATA(DR_TECH_SHIFT,'DRSHIFTPREV')+1) );


* IDR_RATE - parameter for the usage profiles for demand response technologies
PARAMETER IDR_RATE(AAA,DR_TECH,S,T) 'Hourly rating/availability for downregulation of demand response technologies';

*Initializing all IDR_RATE alternatives
IDR_RATE(IA,DR_TECH,S,T)$SUM((Y),DR_FX(Y,IA,DR_TECH)) = DR_FLH(IA,DR_TECH) / 8760;
IDR_RATE(IA,DR_TECH,S,T)$(SUM((Y),DR_FX(Y,IA,DR_TECH)) AND DR_RATE_T(T,DR_TECH)) = DR_RATE_T(T,DR_TECH) * DR_FLH(IA,DR_TECH) / 8760;
IDR_RATE(IA,DR_TECH,S,T)$(SUM((Y),DR_FX(Y,IA,DR_TECH)) AND DR_RATE_S(IA,DR_TECH,S)) = DR_RATE_S(IA,DR_TECH,S) * DR_FLH(IA,DR_TECH) / 8760;
IDR_RATE(IA,DR_TECH,S,T)$(SUM((Y),DR_FX(Y,IA,DR_TECH)) AND DR_RATE_T(T,DR_TECH) AND DR_RATE_S(IA,DR_TECH,S)) = DR_RATE_S(IA,DR_TECH,S)*DR_RATE_T(T,DR_TECH) * DR_FLH(IA,DR_TECH) / 8760;


