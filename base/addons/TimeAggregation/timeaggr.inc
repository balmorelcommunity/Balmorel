* File TIMEAGGR.inc
* This file aggregates time periods from a (SSS,TTT)=(52,168) to a (SSSxT), where T is a true subset of TTT.
* The file holds data and code.
* To be used e.g. in relation to balbase1, balbase2, and the interplay between balbase1 and balbase3.
* Created by Lars Bregnbæk.

$ifi not %timeaggr%==yes  $goto  NoAggregation
$ifi %bb3%==yes $goto NoAggregation;


IF( ((CARD(TTT) NE 168) OR (CARD(SSS) NE 52)),
  abort "Addon timeaggr: assumptions (CARD(TTT) EQ 168) and (CARD(SSS) EQ 52) are violated";
);


SET IT2TTT(SSS,T,TTT)   "Mapping between aggregated T and all TTT, by SSS";
PARAMETER PS2SSS(S,SSS) "Mapping/weighting of SSS to S - Sequence of Card(S) from SSS maps to each S",
          COUNTELEMENTS(S) "";
$ifi %BB3%==yes IT2TTT(SSS,T,T)=yes;  !! Should not come here according to an above $goto
$ifi %BB3%==yes PS2SSS(S,S)=1;        !! Should not come here according to an above $goto


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

SET DAYTTT(DAY,TTT) 'Days to hours mapping. Assuming (SSS,TTT)=(52,168), and that first hour of year is first hour in first Monday - NOT IN USE '
/
  MONDAY.(T001*T024),
  TUESDAY.(T025*T048),
  WEDNESDAY.(T049*T072),
  THURSDAY.(T073*T096),
  FRIDAY.(T097*T130),
  SATURDAY.(T131*T154),
  SUNDAY.(T155*T168)
/;


$ontext
* ------------------------------------------------------------------------------
* Example data.
* This dataset distinguishes between workdays and weekdays.
* It does not attempt to maintain strict chronology.

abort$(CARD(T) NE 6) "Addon timeaggr, file timeaggr.inc: This data TINDAY assumes (CARD(T) EQ 6)";

TABLE TINDAY(T,DAY) "T to DAY mapping"
      MONDAY TUESDAY WEDNESDAY THURSDAY FRIDAY SATURDAY SUNDAY
T001  1      1       1         1        1
T002  1      1       1         1        1
T003  1      1       1         1        1
T004  1      1       1         1        1
T005  1      1       1         1        1      1        1
T006                                           1        1
;

SET HOURS24 "24 hours" /HR01*HR24/;
abort$(CARD(HOURS24) NE 24) "Addon timeaggr, file timeaggr.inc: This data HOURS24 assumes (CARD(HOURS24) EQ 24)";

TABLE T2HOURS24(T,HOURS24) "T to HOURS24 relationship"
      HR01 HR02 HR03 HR04 HR05 HR06 HR07 HR08 HR09 HR10 HR11 HR12 HR13 HR14 HR15 HR16 HR17 HR18 HR19 HR20 HR21 HR22 HR23 HR24
T001                                          1    1    1    1    1
T002                                                                   1    1    1    1         1    1
T003                           1    1    1                                                                1    1
T004                                                                                       1
T005  1    1    1    1    1                                                                                         1    1
T006                           1    1    1    1    1    1    1    1    1    1    1    1    1    1    1    1    1
;
* ------------------------------------------------------------------------------
$offtext

$ontext
* ------------------------------------------------------------------------------
* Example data.
* This dataset adds same hours within each day (24 hours cycle) within the SSS relvant for this S (cf. PS2SSS).
* It does not distinguish between workdays and weekend.
* It does maintain chronology within each 24 hours cycle.

abort$(ARD(T) NE 24) "Addon timeaggr, file timeaggr.inc: This data TINDAY assumes (CARD(T) EQ 24)";

PARAMETER TINDAY(T,DAY) "T to DAY mapping";
TINDAY(T,DAY)=YES;

SET HOURS24 "24 hours" /HR01*HR24/;
abort$(CARD(HOURS24) NE 24) "Addon timeaggr, file timeaggr.inc: This data HOURS24 assumes (CARD(HOURS24) EQ 24)";

PARAMETER T2HOURS24(T,HOURS24) "T to HOURS24 relationship";
T2HOURS24(T,HOURS24) = YES$(ORD(T) EQ ORD(HOURS24));

* ------------------------------------------------------------------------------
$offtext

*$ontext
* ------------------------------------------------------------------------------
* Example data.
* This dataset adds same 2-hours within each day (24 hours cycle) within the SSS relvant for this S (cf. PS2SSS).
* It does not distinguish between workdays and weekend.
* It does maintain chronology within each 24 hours cycle.

abort$(CARD(T) NE 12) "Addon timeaggr, file timeaggr.inc: This data TINDAY assumes (CARD(T) EQ 12)";

PARAMETER TINDAY(T,DAY) "T to DAY mapping";
TINDAY(T,DAY)=YES;

SET HOURS24 "24 hours" /HR01*HR24/;
abort$(CARD(HOURS24) NE 24) "Addon timeaggr, file timeaggr.inc: This data HOURS24 assumes (CARD(HOURS24) EQ 24)";

TABLE T2HOURS24(T,HOURS24) "T to HOURS24 relationship"
      HR01 HR02 HR03 HR04 HR05 HR06 HR07 HR08 HR09 HR10 HR11 HR12 HR13 HR14 HR15 HR16 HR17 HR18 HR19 HR20 HR21 HR22 HR23 HR24
T001    1    1
T002              1    1
T003                        1    1
T004                                  1    1
T005                                            1    1
T006                                                      1    1
T007                                                                1    1
T008                                                                          1    1
T009                                                                                    1    1
T010                                                                                              1    1
T011                                                                                                        1    1
T012                                                                                                                  1    1
;

* ------------------------------------------------------------------------------
*$offtext

$ontext
* ------------------------------------------------------------------------------
* Example data.
* This dataset adds same 4-hours intervals within each day (24 hours cycle) within the SSS relvant for this S (cf. PS2SSS).
* It does not distinguish between workdays and weekend.
* It does maintain chronology within each 24 hours cycle.

abort$(CARD(T) NE 6) "Addon timeaggr, file timeaggr.inc: This data TINDAY assumes (CARD(T) EQ 6)";

PARAMETER TINDAY(T,DAY) "T to DAY mapping";
TINDAY(T,DAY)=YES;

SET HOURS24 "24 hours" /HR01*HR24/;
abort$(CARD(HOURS24) NE 24) "Addon timeaggr, file timeaggr.inc: This data HOURS24 assumes (CARD(HOURS24) EQ 24)";

TABLE T2HOURS24(T,HOURS24) "T to HOURS24 relationship"
      HR01 HR02 HR03 HR04 HR05 HR06 HR07 HR08 HR09 HR10 HR11 HR12 HR13 HR14 HR15 HR16 HR17 HR18 HR19 HR20 HR21 HR22 HR23 HR24
T001    1    1    1    1
T002                        1    1    1    1
T003                                            1    1    1    1
T004                                                                1    1    1    1
T005                                                                                    1    1    1    1
T006                                                                                                        1    1    1    1
;
* ------------------------------------------------------------------------------
$offtext

* Convenient to abort here if errors in the above
$ifi not errorfree $abort "Balmorel execution aborted because of errors in addon timeaggr"



ALIAS(TTT,ITTTALIAS);
IT2TTT(SSS,T,TTT)=YES$(sum((DAY,HOURS24),1$(TINDAY(T,DAY) and T2HOURS24(T,HOURS24) and 24*(ORD(DAY)-1)+ORD(HOURS24)=ORD(TTT))));

$kill weight_t


* LARS: If not all S have been generated use the first.
* Set relative time weights of T to the number of elements in IT2TTT
WEIGHT_T(T)=sum((S,TTT)$(IT2TTT(S,T,TTT) and ord(S)=1),1);
* Set relative time weights of S identical
WEIGHT_S(S)=168*card(SSS)/card(S);
WEIGHT_S(SSS)$(not S(SSS))=0;

PS2SSS(S,SSS)=Max(0,1-Min(1,Max(0,ORD(SSS)-(CARD(SSS)/CARD(S))*ORD(S)))-Min(1,max(0,1-(ord(SSS)-(CARD(SSS)/CARD(S))*(ORD(S)-1)))));

COUNTELEMENTS(S) = Sum(SSS, PS2SSS(S,SSS));

* The following parameters are used to rescale the time series to maintain previous values of
PARAMETER IMAXIMUM( *,SSS)     'Maximum value of current time series'
          IMINIMUM( *,SSS)     'Minimum value of current time series'
          IMEAN( *,SSS)        'Mean value of current time series'
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

* Remove profiles from geography not in simulation.
DE_VAR_T(RRR,SSS,TTT)$(not IR(RRR)) = 0;
DH_VAR_T(AAA,SSS,TTT)$(not IA(AAA)) = 0;
X3FX_VAR_T(RRR,SSS,TTT)$(not IR(RRR)) = 0;
WND_VAR_T(AAA,SSS,TTT)$(not IA(AAA)) = 0;
SOLE_VAR_T(AAA,SSS,TTT)$(not IA(AAA)) = 0;
SOLH_VAR_T(AAA,SSS,TTT)$(not IA(AAA)) = 0;
WAVE_VAR_T(AAA,SSS,TTT)$(not IA(AAA)) = 0;
WTRRRVAR_T(AAA,SSS,TTT)$(not IA(AAA)) = 0;

ISUMWEIGHT = SUM(T,WEIGHT_T(T));


$batinclude '../../base/addons/timeaggregation/aggr_1_s_t.inc' DE_VAR_T IR
$batinclude '../../base/addons/timeaggregation/aggr_1_s_t.inc' DH_VAR_T IA
$batinclude '../../base/addons/timeaggregation/aggr_1_s_t.inc' X3FX_VAR_T IR
* $batinclude '../../base/addons/timeaggregation/aggr_1_s_t.inc' WND_VAR_T IA
*$batinclude '../../base/addons/timeaggregation/aggr_1_s_t.inc' SOLE_VAR_T IA
$batinclude '../../base/addons/timeaggregation/aggr_1_s_t.inc' SOLH_VAR_T IA
$batinclude '../../base/addons/timeaggregation/aggr_1_s_t.inc' WAVE_VAR_T IA
$batinclude '../../base/addons/timeaggregation/aggr_1_s_t.inc' WTRRRVAR_T IA
$batinclude '../../base/addons/timeaggregation/aggr_2_s_t.inc' WND_VAR_T IA

SOLE_VAR_T(IA,S,T) = Sum(SSS,  PS2SSS(S,SSS)*(SUM(TTT$IT2TTT(SSS,T,TTT), SOLE_VAR_T(IA,SSS,TTT))/WEIGHT_T(T))$WEIGHT_T(T))/COUNTELEMENTS(S);

DEF_STEPS(IR,S,T,DF_QP,DEF)= Sum(SSS,  PS2SSS(S,SSS)*(SUM(TTT$IT2TTT(SSS,T,TTT) ,DEF_STEPS(IR,SSS,TTT,DF_QP,DEF))/WEIGHT_T(T))$WEIGHT_T(T))/COUNTELEMENTS(S) ;
DHF_STEPS(IA,S,T,DF_QP,DHF)= Sum(SSS,  PS2SSS(S,SSS)*(SUM(TTT$IT2TTT(SSS,T,TTT) ,DHF_STEPS(IA,SSS,TTT,DF_QP,DHF))/WEIGHT_T(T))$WEIGHT_T(T))/COUNTELEMENTS(S) ;

$ifi %GKRATE_DOL%==AAA_GGG_SSS_TTT GKRATE(IA,G,S,T) = Sum(SSS, PS2SSS(S,SSS)*(SUM(TTT$IT2TTT(SSS,T,TTT), GKRATE(IA,G,SSS,TTT))/WEIGHT_T(T))$WEIGHT_T(T))/COUNTELEMENTS(S);
$ifi %GKRATE_DOL%==AAA_GGG_SSS     GKRATE(IA,G,S)   = Sum(SSS, PS2SSS(S,SSS)*GKRATE(IA,G,SSS))/COUNTELEMENTS(S);

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

$ifi %GKRATE_DOL%==AAA_GGG_SSS_TTT  GKRATE(IA,G,SSS,TTT)$(NOT T(TTT))      = 0;


DEF_STEPS(IR,SSS,T,DF_QP,DEF)$(NOT S(SSS))          = 0;
DHF_STEPS(IA,SSS,T,DF_QP,DHF)$(NOT S(SSS))          = 0;
$ifi %X3V%==yes X3VPEX(YYY,IR,X3VPLACE,X3VSTEP,SSS,T)$(NOT S(SSS))       = 0;
$ifi %X3V%==yes X3VPIM(YYY,IR,X3VPLACE,X3VSTEP,SSS,T)$(NOT S(SSS))       = 0;

$ifi %GKRATE_DOL%==AAA_GGG_SSS_TTT  GKRATE(IA,G,SSS,TTT)$(NOT S(SSS))    = 0;
$ifi %GKRATE_DOL%==AAA_GGG_SSS      GKRATE(IA,G,SSS)$(NOT S(SSS))        = 0;
HYPPROFILS(IA,SSS)$(NOT S(SSS))       = 0;
WTRRSVAR_S(IA,SSS)$(NOT S(SSS))       = 0;


$label NoAggregation
