** declaring internal sets

SET DR_TECH_SHIFT(DR_TECH)'Shifting demand response technology'
SET DR_TECH_SHED(DR_TECH) 'Shedding demand response technology'

SET DR_TECH_USER(DR_TECH,DEUSER)

ALIAS (T,T_alias);
SET DR_HHH1(DR_TECH,T,T_alias)         'Shifting time matrix - whether a load can be shifted from H to HH';
SET DR_HHH2(DR_TECH,T,T_alias)         'Shifting time matrix - whether a load can be shifted from H to HH';

SET IADR(Y,AAA,DR_TECH)  'Set of areas and demand side management technologies in the simulation';


** Defining internal sets

* DR tech is SHED or SHIFT
DR_TECH_SHIFT(DR_TECH) = YES$(DR_DATA(DR_TECH,'DRTYPE') eq 2);
DR_TECH_SHED(DR_TECH) = YES$(DR_DATA(DR_TECH,'DRTYPE') eq 1);

* Relationship between DR_TECH and Balmorel user group
DR_TECH_USER(DR_TECH,'RESE') = YES$(DR_DATA(DR_TECH,'DRUSER') eq 1);
DR_TECH_USER(DR_TECH,'OTHER') = YES$(DR_DATA(DR_TECH,'DRUSER') eq 3);
DR_TECH_USER(DR_TECH,'PII') = YES$(DR_DATA(DR_TECH,'DRUSER') eq 2);

* how long it is possible to shift load to later point in time (DR_HHH1) or to an earlier point in time (DR_HHH2)
DR_HHH1(DR_TECH_SHIFT,T,T_alias)  = YES$((ord(T_alias) le ord(T)+ DR_DATA(DR_TECH_SHIFT,'DRSHIFTNEXT')-1)   AND (ord(T_alias) ge ord(T)));
DR_HHH2(DR_TECH_SHIFT,T,T_alias)  = YES$((ord(T_alias) le ord(T))   AND (ord(T_alias) ge ord(T)- DR_DATA(DR_TECH_SHIFT,'DRSHIFTPREV')+1) );


