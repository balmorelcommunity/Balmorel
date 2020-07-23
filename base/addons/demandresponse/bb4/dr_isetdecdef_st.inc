** declaring internal sets

ALIAS (T,T_alias);
SET DR_HHH1(DR_TECH,T,T_alias)         'Shifting time matrix - whether a load can be shifted from H to HH';
SET DR_HHH2(DR_TECH,T,T_alias)         'Shifting time matrix - whether a load can be shifted from H to HH';


** Defining internal sets

* how long it is possible to shift load to later point in time (DR_HHH1) or to an earlier point in time (DR_HHH2)
$ifi NOT %timeaggr%==yes DR_HHH1(DR_TECH_SHIFT,T,T_alias)  = YES$((ord(T_alias) le ord(T)+ DR_DATA(DR_TECH_SHIFT,'DRSHIFTNEXT')-1)   AND (ord(T_alias) ge ord(T)));
$ifi NOT %timeaggr%==yes DR_HHH2(DR_TECH_SHIFT,T,T_alias)  = YES$((ord(T_alias) le ord(T))   AND (ord(T_alias) ge ord(T)- DR_DATA(DR_TECH_SHIFT,'DRSHIFTPREV')+1) );

$ifi %timeaggr%==yes DR_HHH1(DR_TECH_SHIFT,T,T_alias)  = YES$((ord(T_alias) le ord(T)+ DR_DATA(DR_TECH_SHIFT,'DRSHIFTNEXT')/SUM(HOURS24,T2HOURS24(T,HOURS24))-1)   AND (ord(T_alias) ge ord(T)));
$ifi %timeaggr%==yes DR_HHH2(DR_TECH_SHIFT,T,T_alias)  = YES$((ord(T_alias) le ord(T))   AND (ord(T_alias) ge ord(T)- DR_DATA(DR_TECH_SHIFT,'DRSHIFTPREV')/SUM(HOURS24,T2HOURS24(T,HOURS24))+1) );
