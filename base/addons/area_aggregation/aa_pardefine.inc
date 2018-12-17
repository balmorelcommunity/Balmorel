**** AREA Aggregation

ALIAS(AAA,A_ALIAS);
ALIAS(AAA,IA_ALIAS);



SET AREA_AGGREGATION(AAA,A_ALIAS) 'Areas to aggregate'     %semislash%
$if     EXIST '../data/AREA_AGGREGATION.inc' $INCLUDE         '../data/AREA_AGGREGATION.inc';
$if not EXIST '../data/AREA_AGGREGATION.inc' $INCLUDE '../../base/data/AREA_AGGREGATION.inc';
%semislash%;




*** All parameters over the AAA set with changes:


*** AGKN

AGKN(IA,G)$(SUM(A_ALIAS, AREA_AGGREGATION(IA,A_ALIAS))) = AGKN(IA,G) + SUM(IA_ALIAS$AREA_AGGREGATION(IA,IA_ALIAS), AGKN(IA_ALIAS,G));
AGKN(IA_ALIAS,G)$(SUM(IA, AREA_AGGREGATION(IA,IA_ALIAS))) = NO;

*** GKFX

GKFX(Y,IA,G)$(SUM(A_ALIAS, AREA_AGGREGATION(IA,A_ALIAS))) = GKFX(Y,IA,G) + SUM(IA_ALIAS$AREA_AGGREGATION(IA,IA_ALIAS), GKFX(Y,IA_ALIAS,G));
GKFX(Y,IA_ALIAS,G)$SUM(IA, AREA_AGGREGATION(IA,IA_ALIAS) ) = 0;

*** AGKNDISC  (not currently in use)

*** DHFP_CALIB  (not currently in use)

*** GKNMAX (not currently in use for relevant areas)

*** DISCOST_H, DISLOSS_H, DISLOSS1H (not currently relevant)

*** FKPOT, TECHGROUPKPOT (not currently relevant)

*** FGEMIN, FGEMAX (not currently relevant)

*** GMINF, GMAXF, GEQF (not currently relevant)

*** FKMIN, FKMAX, FKEQ, FKMINA, FKMAXNA, FKEQNA, FMAXINVESTNA  (not currently relevant)

*** WTRRSFLH  (not currently relevant)

*** WTRRRFLH (avoided)

*** WNDFLH  (not currently relevant)

*** SOLEFLH  (not currently relevant)

*** SOLHFLH
*Orignial values of SOLHFLH is saved for later use in SOLH_VAR_T calculation
PARAMETER VT_SOLHFLH(AAA); VT_SOLHFLH(IA)$(SUM(IA_ALIAS,AREA_AGGREGATION(IA,IA_ALIAS)) OR SUM(IA_ALIAS,AREA_AGGREGATION(IA_ALIAS,IA)))  = SOLHFLH(IA);

** METHOD: ARITHMETIC MEAN
SOLHFLH(IA)$(SUM(A_ALIAS, AREA_AGGREGATION(IA,A_ALIAS))) =
                 (SOLHFLH(IA) + SUM(IA_ALIAS$AREA_AGGREGATION(IA,IA_ALIAS),   SOLHFLH(IA_ALIAS))) / (SUM(IA_ALIAS$(AREA_AGGREGATION(IA,IA_ALIAS) AND (SOLHFLH(IA_ALIAS) >0)), 1)+1$(SOLHFLH(IA) >0));
SOLHFLH(IA_ALIAS)$SUM(IA, AREA_AGGREGATION(IA,IA_ALIAS) ) = 0;

*** WAVEFLH  (not currently relevant)

*** HYRSMAXVOL_G, HYRSDATA (not currently relevant)

*** GINVCOST  (Through changes in AGKN this parameter updates accordingly)

*** GOMVCOST  (Through changes in AGKN this parameter updates accordingly)

*** GOMFCOST  (Through changes in AGKN this parameter updates accordingly)

*** DECOM_G   (Through changes in AGKN this parameter updates accordingly)

*** GEFFDERATE  (currently not relevant)

*** GKRATE  (currently not relevant)
** METHOD: ARITHMETIC MEAN
GKRATE(IA,G,S)$(SUM(IA_ALIAS$AREA_AGGREGATION(IA,IA_ALIAS), GKRATE(IA_ALIAS,G,S) )>0)  =
         (GKRATE(IA,G,S)$(SUM(A_ALIAS, AREA_AGGREGATION(IA,A_ALIAS)))+  SUM(IA_ALIAS$AREA_AGGREGATION(IA,IA_ALIAS) , GKRATE(IA_ALIAS,G,S)  )  )
                 /      (SUM(IA_ALIAS$(AREA_AGGREGATION(IA,IA_ALIAS) AND (GKRATE(IA_ALIAS,G,S) >0)), 1)+1$(GKRATE(IA,G,S) >0));    !!
GKRATE(IA_ALIAS,G,S)$(SUM(IA, AREA_AGGREGATION(IA,IA_ALIAS) ))  = 0;

*** CHPPROFILES (not currently relevant)

*** DHFP_BASE (data exist, but same for all relevant areas)

*** DH
*Orignial values of DH is saved for later use in DH_VAR_T calculation
PARAMETER VT_DHSUM(AAA,DHUSER);  VT_DHSUM(IA,DHUSER)$(SUM(IA_ALIAS,AREA_AGGREGATION(IA,IA_ALIAS)) OR SUM(IA_ALIAS,AREA_AGGREGATION(IA_ALIAS,IA)))  =    SUM(Y, DH(Y,IA,DHUSER))/CARD(Y);

DH(Y,IA,DHUSER)$(SUM(IA_ALIAS, AREA_AGGREGATION(IA,IA_ALIAS))) = DH(Y,IA,DHUSER) + SUM(IA_ALIAS$AREA_AGGREGATION(IA,IA_ALIAS), DH(Y,IA_ALIAS,DHUSER));
DH(Y,IA_ALIAS,DHUSER)$SUM(IA, AREA_AGGREGATION(IA,IA_ALIAS) ) = 0;


*** FUELPRICE (currently on region level)

*** WTRRSVAR_S (not currently relevant)

*** WTRRRVAR_S  (not currently relevant)

*** SOLH_VAR_T
PARAMETER VT_SOLHVARTSUM(AAA);
VT_SOLHVARTSUM(IA)$(SUM(IA_ALIAS,AREA_AGGREGATION(IA,IA_ALIAS)) OR SUM(IA_ALIAS,AREA_AGGREGATION(IA_ALIAS,IA)))    = SUM((S,T), SOLH_VAR_T(IA,S,T));

SOLH_VAR_T(IA,S,T)$(SUM(A_ALIAS, AREA_AGGREGATION(IA,A_ALIAS))) =
                ( SOLH_VAR_T(IA,S,T)*VT_SOLHFLH(IA)/VT_SOLHVARTSUM(IA))$VT_SOLHVARTSUM(IA)
         + SUM(IA_ALIAS$AREA_AGGREGATION(IA,IA_ALIAS),   (SOLH_VAR_T(IA_ALIAS,S,T)*VT_SOLHFLH(IA_ALIAS)/VT_SOLHVARTSUM(IA_ALIAS))$VT_SOLHVARTSUM(IA_ALIAS));

SOLH_VAR_T(IA_ALIAS,S,T)$SUM(IA, AREA_AGGREGATION(IA,IA_ALIAS) ) = 0;

*** SOLE_VAR_T  (not currently relevant)

*** WND_VAR_T  (not currently relevant)

*** WAVE_VAR_T  (not currently relevant)

*** HYPPROFILS (not currently relevant)

*** DHF_STEPS (not currently relevant)

*** DH_VAR_T
*** METHOD: Mean weighted to average DH consumption in the years in Y

PARAMETER VT_DHVARTSUM(AAA,DHUSER);
VT_DHVARTSUM(IA,DHUSER)$(SUM(IA_ALIAS,AREA_AGGREGATION(IA,IA_ALIAS)) OR SUM(IA_ALIAS,AREA_AGGREGATION(IA_ALIAS,IA)))    = SUM((S,T), DH_VAR_T(IA,DHUSER,S,T));

DH_VAR_T(IA,DHUSER,S,T)$(SUM(A_ALIAS, AREA_AGGREGATION(IA,A_ALIAS))) =
                 (DH_VAR_T(IA,DHUSER,S,T)*VT_DHSUM(IA,DHUSER)/VT_DHVARTSUM(IA,DHUSER))$VT_DHVARTSUM(IA,DHUSER)
         + SUM(IA_ALIAS$AREA_AGGREGATION(IA,IA_ALIAS),   (DH_VAR_T(IA_ALIAS,DHUSER,S,T)*VT_DHSUM(IA_ALIAS,DHUSER)/VT_DHVARTSUM(IA_ALIAS,DHUSER))$VT_DHVARTSUM(IA_ALIAS,DHUSER));

DH_VAR_T(IA_ALIAS,DHUSER,S,T)$SUM(IA, AREA_AGGREGATION(IA,IA_ALIAS) ) = 0;














