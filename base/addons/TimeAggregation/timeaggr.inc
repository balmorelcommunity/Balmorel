* File TIMEAGGR.inc
* This file aggregates time periods from a SSSxTTT=52x168 to a SSSxT, where T is a true subset of TTT.
* The file holds data and code.

* To be used e.g. in relation to balbase1, balbase2, and the interplay between balbase1 and balbase3.
SET IT2TTT(SSS,T,TTT);
PARAMETER PS2SSS(S,SSS),
          COUNTELEMENTS(S);
$ifi %BB3%==yes IT2TTT(SSS,T,T)=yes;
$ifi %BB3%==yes PS2SSS(S,S)=1;

$ifi %bb3%==yes $goto NoAggregation;


SET DAY 'Days of the week'
/
MONDAY
TUESDAY
WEDNESDAY
THURSDAY
FRIDAY
SATURDAY
SUNDAY
/;

SET DAYTTT(DAY,TTT) 'Hours to days relationship'
/
          MONDAY.(T001*T024),
          TUESDAY.(T025*T048),
          WEDNESDAY.(T049*T072),
          THURSDAY.(T073*T096),
          FRIDAY.(T097*T130),
          SATURDAY.(T131*T154),
          SUNDAY.(T155*T168)
/;


SET HOURS24 /HR01*HR24/;



ALIAS(TTT,ITTTALIAS);
IT2TTT(SSS,T,TTT)=YES$(sum((DAY,HOURS24),1$(TINDAY(T,DAY) and T2HOURS24(T,HOURS24) and 24*(ORD(DAY)-1)+ORD(HOURS24)=ORD(TTT))));


$kill weight_t


* LARS: If not all S have been generated use the first. VIRKER IKKE!

WEIGHT_T(T)=sum((S,TTT)$(IT2TTT(S,T,TTT) and ord(S)=1),1);

WEIGHT_S(S)=168*card(SSS)/card(S);
WEIGHT_S(SSS)$(not S(SSS))=0;

PS2SSS(S,SSS)=Max(0,1-Min(1,Max(0,ORD(SSS)-CARD(SSS)/CARD(S)*ORD(S)))-Min(1,max(0,1-(ord(SSS)-CARD(SSS)/CARD(S)*(ORD(S)-1)))));
COUNTELEMENTS(S) = Sum(SSS, PS2SSS(S,SSS));

* The following parameters are used to rescale the time series to maintain previous values of
PARAMETER IMAXIMUM( *,SSS) 'Maximum value of current time series'
          IMINIMUM( *,SSS) 'Minimum value of current time series'
          IMEAN( *,SSS)    'Mean value of current time series'
          INEW_MAXIMUM( *,SSS) 'Maximum value of current time series'
          INEW_MINIMUM( *,SSS) 'Minimum value of current time series'
          INEW_MEAN( *,SSS)    'Mean value of current time series'
          ISUMWEIGHT

          IWEIGHT_OTH( *,SSS)

          IDIFF_MAXIMUM( *,SSS)
          IDIFF_MINIMUM( *,SSS)
          IDIFF_MEAN( *,SSS)
* PARAMETERS FOR aggr_2_s_t.inc
          AREASUM(SSS,TTT)
          AREAWEIGHTSUM
;

SET T_MAX( *,SSS,T) 'Time segment with maximum value'
    T_MIN( *,SSS,T) 'Time segment with minimum value'
    T_OTH( *,SSS,T) 'Time segment with other values'
;

* Remove profiles from geagraphy not in simulation.
DE_VAR_T(RRR,SSS,TTT)$(not IR(RRR)) = 0;
DH_VAR_T(AAA,SSS,TTT)$(not IA(AAA)) = 0;
X3FX_VAR_T(RRR,SSS,TTT)$(not IR(RRR)) = 0;
WND_VAR_T(AAA,SSS,TTT)$(not IA(AAA)) = 0;
SOLE_VAR_T(AAA,SSS,TTT)$(not IA(AAA)) = 0;
SOLH_VAR_T(AAA,SSS,TTT)$(not IA(AAA)) = 0;
WAVE_VAR_T(AAA,SSS,TTT)$(not IA(AAA)) = 0;
WTRRRVAR_T(AAA,SSS,TTT)$(not IA(AAA)) = 0;

ISUMWEIGHT = SUM(T,WEIGHT_T(T));

$batinclude '../../base/model/aggr_1_s_t.inc' DE_VAR_T IR
$batinclude '../../base/model/aggr_1_s_t.inc' DH_VAR_T IA
$batinclude '../../base/model/aggr_1_s_t.inc' X3FX_VAR_T IR
* $batinclude '../../base/model/aggr_1_s_t.inc' WND_VAR_T IA
*$batinclude '../../base/model/aggr_1_s_t.inc' SOLE_VAR_T IA
$batinclude '../../base/model/aggr_1_s_t.inc' SOLH_VAR_T IA
$batinclude '../../base/model/aggr_1_s_t.inc' WAVE_VAR_T IA
$batinclude '../../base/model/aggr_1_s_t.inc' WTRRRVAR_T IA

$batinclude '../../base/model/aggr_2_s_t.inc' WND_VAR_T IA

SOLE_VAR_T(IA,S,T) = Sum(SSS,  PS2SSS(S,SSS)*(SUM(TTT$IT2TTT(SSS,T,TTT), SOLE_VAR_T(IA,SSS,TTT))/WEIGHT_T(T))$WEIGHT_T(T))/COUNTELEMENTS(S);


DEF_STEPS(IR,S,T,DF_QP,DEF)= Sum(SSS,  PS2SSS(S,SSS)*(SUM(TTT$IT2TTT(SSS,T,TTT) ,DEF_STEPS(IR,SSS,TTT,DF_QP,DEF))/WEIGHT_T(T))$WEIGHT_T(T))/COUNTELEMENTS(S) ;
DHF_STEPS(IA,S,T,DF_QP,DHF)= Sum(SSS,  PS2SSS(S,SSS)*(SUM(TTT$IT2TTT(SSS,T,TTT) ,DHF_STEPS(IA,SSS,TTT,DF_QP,DHF))/WEIGHT_T(T))$WEIGHT_T(T))/COUNTELEMENTS(S) ;

(1-GKDERATE(IA,G,S,T)) = Sum(SSS,  PS2SSS(S,SSS)*(SUM(TTT$IT2TTT(SSS,T,TTT) ,(1-GKDERATE(IA,G,SSS,TTT)))/WEIGHT_T(T))$WEIGHT_T(T))/COUNTELEMENTS(S);
*(1-GKDERATE(IA,G,S,T))    = Sum((SSS,TTT),  PS2SSS(S,SSS)*(1-GKDERATE(IA,G,SSS,T)))/COUNTELEMENTS(S);
HYPPROFILS(IA,S)    = Sum(SSS,  PS2SSS(S,SSS)*HYPPROFILS(IA,SSS))/COUNTELEMENTS(S);
* Inflow is given in units of energy, therefore a sum is used, not an average:
WTRRSVAR_S(IA,S)    = Sum(SSS,  PS2SSS(S,SSS)*WTRRSVAR_S(IA,SSS));

$ifi %X3V%==yes X3VPEX(Y,IR,X3VPLACE,X3VSTEP,S,T)= Sum(SSS,  PS2SSS(S,SSS)*(SUM(TTT$IT2TTT(SSS,T,TTT), X3VPEX(Y,IR,X3VPLACE,X3VSTEP,SSS,TTT))/WEIGHT_T(T))$WEIGHT_T(T))/COUNTELEMENTS(S);
$ifi %X3V%==yes X3VPIM(Y,IR,X3VPLACE,X3VSTEP,S,T)= Sum(SSS,  PS2SSS(S,SSS)*(SUM(TTT$IT2TTT(SSS,T,TTT), X3VPIM(Y,IR,X3VPLACE,X3VSTEP,SSS,TTT))/WEIGHT_T(T))$WEIGHT_T(T))/COUNTELEMENTS(S);

* Following doesnt have any functionality, but gives 'ex post' consistent parameters.
DEF_STEPS(IR,SSS,TTT,DF_QP,DEF)$(NOT T(TTT))          = 0;
DHF_STEPS(IA,SSS,TTT,DF_QP,DHF)$(NOT T(TTT))          = 0;
$ifi %X3V%==yes X3VPEX(YYY,IR,X3VPLACE,X3VSTEP,SSS,TTT)$(NOT T(TTT))       = 0;
$ifi %X3V%==yes X3VPIM(YYY,IR,X3VPLACE,X3VSTEP,SSS,TTT)$(NOT T(TTT))       = 0;

GKDERATE(IA,G,SSS,TTT)$(NOT T(TTT))        = 0;


DEF_STEPS(IR,SSS,T,DF_QP,DEF)$(NOT S(SSS))          = 0;
DHF_STEPS(IA,SSS,T,DF_QP,DHF)$(NOT S(SSS))          = 0;
$ifi %X3V%==yes X3VPEX(YYY,IR,X3VPLACE,X3VSTEP,SSS,T)$(NOT S(SSS))       = 0;
$ifi %X3V%==yes X3VPIM(YYY,IR,X3VPLACE,X3VSTEP,SSS,T)$(NOT S(SSS))       = 0;

GKDERATE(IA,G,SSS,TTT)$(NOT S(SSS))       = 0;
HYPPROFILS(IA,SSS)$(NOT S(SSS))       = 0;
WTRRSVAR_S(IA,SSS)$(NOT S(SSS))       = 0;


$label NoAggregation;
