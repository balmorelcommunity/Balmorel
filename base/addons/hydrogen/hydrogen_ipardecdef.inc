PARAMETERS
   IDH2_SUMST(RRR)               'Variation profile of H2 demand per region'
   IDH2_REGION_T_Y(RRR,SSS,TTT)  'Variation of H2 demand in each region along the year'
   IDH2_AREA_T_Y(AAA,SSS,TTT)    'Variation of H2 demand in each region along the year'
   IH2STOVOL_START(AAA,G,SSS)    'Start level of hydrogen storage'
   IH2STOVOL_END(AAA,G,SSS)      'End level of hydrogen storage'
;

PARAMETER IDH2_REGION_SUMST(RRR) 'Variation profile of H2 demand per region';
$ifi %BB1%==yes    IDH2_REGION_SUMST(IR) = SUM((S,T), IHOURSINST(S,T)*DH2_VAR_T(IR,S,T));
$ifi %BB2%==yes    IDH2_REGION_SUMST(IR) = SUM((S,T), IHOURSINST(S,T)*DH2_VAR_T(IR,S,T));
$ifi %BB3%==yes    IDH2_REGION_SUMST(IR) = SUM((SSS,T), IHOURSINST(SSS,T)*DH2_VAR_T(IR,SSS,T));

PARAMETER IDH2_AREA_SUMST(AAA) 'Variation profile of H2 demand per region';
$ifi %BB1%==yes    IDH2_AREA_SUMST(IA) = SUM((S,T), IHOURSINST(S,T)*DH2_VAR_T(IA,S,T));
$ifi %BB2%==yes    IDH2_AREA_SUMST(IA) = SUM((S,T), IHOURSINST(S,T)*DH2_VAR_T(IA,S,T));
$ifi %BB3%==yes    IDH2_AREA_SUMST(IA) = SUM((SSS,T), IHOURSINST(SSS,T)*DH2_VAR_T(IA,SSS,T));
