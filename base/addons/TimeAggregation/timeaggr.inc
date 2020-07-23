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

*$ontext
* ------------------------------------------------------------------------------
* Example data.
* This dataset distinguishes between workdays and weekdays.
* It does not attempt to maintain strict chronology.

abort$(CARD(T) NE 24) "Addon timeaggr, file timeaggr.inc: This data TINDAY assumes (CARD(T) EQ 24)";

TABLE TINDAY(T,DAY) "T to DAY mapping"
         MONDAY     TUESDAY     WEDNESDAY     THURSDAY     FRIDAY     SATURDAY     SUNDAY
T001     1          1           1             1            1
T002     1          1           1             1            1
T003     1          1           1             1            1
T004     1          1           1             1            1
T005     1          1           1             1            1
T006     1          1           1             1            1
T007     1          1           1             1            1
T008     1          1           1             1            1
T009     1          1           1             1            1
T010     1          1           1             1            1
T011     1          1           1             1            1
T012     1          1           1             1            1
T013                                                       1          1            1
T014                                                       1          1            1
T015                                                       1          1            1
T016                                                       1          1            1
T017                                                       1          1            1
T018                                                       1          1            1
T019                                                       1          1            1
T020                                                       1          1            1
T021                                                       1          1            1
T022                                                       1          1            1
T023                                                       1          1            1
T024                                                       1          1            1

;

SET HOURS24 "24 hours" /HR01*HR24/;
abort$(CARD(HOURS24) NE 24) "Addon timeaggr, file timeaggr.inc: This data HOURS24 assumes (CARD(HOURS24) EQ 24)";

TABLE T2HOURS24(T,HOURS24) "T to HOURS24 relationship"
         HR01     HR02     HR03     HR04     HR05     HR06     HR07     HR08     HR09     HR10     HR11     HR12     HR13     HR14     HR15     HR16     HR17     HR18     HR19     HR20     HR21     HR22     HR23     HR24
T001     1        1
T002                       1        1
T003                                         1        1
T004                                                           1        1
T005                                                                             1        1
T006                                                                                               1        1
T007                                                                                                                 1        1
T008                                                                                                                                   1        1
T009                                                                                                                                                     1        1
T010                                                                                                                                                                       1        1
T011                                                                                                                                                                                         1        1
T012                                                                                                                                                                                                           1        1
T013     1        1
T014                       1        1
T015                                         1        1
T016                                                           1        1
T017                                                                             1        1
T018                                                                                               1        1
T019                                                                                                                 1        1
T020                                                                                                                                   1        1
T021                                                                                                                                                     1        1
T022                                                                                                                                                                       1        1
T023                                                                                                                                                                                         1        1
T024                                                                                                                                                                                                           1        1
;
* ------------------------------------------------------------------------------
*$offtext


$ontext
* ------------------------------------------------------------------------------
* Example data.
* This dataset distinguishes between workdays and weekdays.
* It does not attempt to maintain strict chronology.

abort$(CARD(T) NE 72) "Addon timeaggr, file timeaggr.inc: This data TINDAY assumes (CARD(T) EQ 72)";

TABLE TINDAY(T,DAY) "T to DAY mapping"
         MONDAY     TUESDAY     WEDNESDAY     THURSDAY     FRIDAY     SATURDAY     SUNDAY
T001     1          1           1
T002     1          1           1
T003     1          1           1
T004     1          1           1
T005     1          1           1
T006     1          1           1
T007     1          1           1
T008     1          1           1
T009     1          1           1
T010     1          1           1
T011     1          1           1
T012     1          1           1
T013     1          1           1
T014     1          1           1
T015     1          1           1
T016     1          1           1
T017     1          1           1
T018     1          1           1
T019     1          1           1
T020     1          1           1
T021     1          1           1
T022     1          1           1
T023     1          1           1
T024     1          1           1
T025                                          1            1
T026                                          1            1
T027                                          1            1
T028                                          1            1
T029                                          1            1
T030                                          1            1
T031                                          1            1
T032                                          1            1
T033                                          1            1
T034                                          1            1
T035                                          1            1
T036                                          1            1
T037                                          1            1
T038                                          1            1
T039                                          1            1
T040                                          1            1
T041                                          1            1
T042                                          1            1
T043                                          1            1
T044                                          1            1
T045                                          1            1
T046                                          1            1
T047                                          1            1
T048                                          1            1
T121                                                                  1            1
T122                                                                  1            1
T123                                                                  1            1
T124                                                                  1            1
T125                                                                  1            1
T126                                                                  1            1
T127                                                                  1            1
T128                                                                  1            1
T129                                                                  1            1
T130                                                                  1            1
T131                                                                  1            1
T132                                                                  1            1
T133                                                                  1            1
T134                                                                  1            1
T135                                                                  1            1
T136                                                                  1            1
T137                                                                  1            1
T138                                                                  1            1
T139                                                                  1            1
T140                                                                  1            1
T141                                                                  1            1
T142                                                                  1            1
T143                                                                  1            1
T144                                                                  1            1

;

SET HOURS24 "24 hours" /HR01*HR24/;
abort$(CARD(HOURS24) NE 24) "Addon timeaggr, file timeaggr.inc: This data HOURS24 assumes (CARD(HOURS24) EQ 24)";
TABLE T2HOURS24(T,HOURS24) "T to HOURS24 relationship"

         HR01     HR02     HR03     HR04     HR05     HR06     HR07     HR08     HR09     HR10     HR11     HR12     HR13     HR14     HR15     HR16     HR17     HR18     HR19     HR20     HR21     HR22     HR23     HR24
T001     1
T002              1
T003                       1
T004                                1
T005                                         1
T006                                                  1
T007                                                           1
T008                                                                    1
T009                                                                             1
T010                                                                                      1
T011                                                                                               1
T012                                                                                                        1
T013                                                                                                                 1
T014                                                                                                                          1
T015                                                                                                                                   1
T016                                                                                                                                            1
T017                                                                                                                                                     1
T018                                                                                                                                                              1
T019                                                                                                                                                                       1
T020                                                                                                                                                                                1
T021                                                                                                                                                                                         1
T022                                                                                                                                                                                                  1
T023                                                                                                                                                                                                           1
T024                                                                                                                                                                                                                    1
T025     1
T026              1
T027                       1
T028                                1
T029                                         1
T030                                                  1
T031                                                           1
T032                                                                    1
T033                                                                             1
T034                                                                                      1
T035                                                                                               1
T036                                                                                                        1
T037                                                                                                                 1
T038                                                                                                                          1
T039                                                                                                                                   1
T040                                                                                                                                            1
T041                                                                                                                                                     1
T042                                                                                                                                                              1
T043                                                                                                                                                                       1
T044                                                                                                                                                                                1
T045                                                                                                                                                                                         1
T046                                                                                                                                                                                                  1
T047                                                                                                                                                                                                           1
T048                                                                                                                                                                                                                    1
T121     1
T122              1
T123                       1
T124                                1
T125                                         1
T126                                                  1
T127                                                           1
T128                                                                    1
T129                                                                             1
T130                                                                                      1
T131                                                                                               1
T132                                                                                                        1
T133                                                                                                                 1
T134                                                                                                                          1
T135                                                                                                                                   1
T136                                                                                                                                            1
T137                                                                                                                                                     1
T138                                                                                                                                                              1
T139                                                                                                                                                                       1
T140                                                                                                                                                                                1
T141                                                                                                                                                                                         1
T142                                                                                                                                                                                                  1
T143                                                                                                                                                                                                           1
T144                                                                                                                                                                                                                    1
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

$ontext
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
$offtext

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
WEIGHT_T(TTT)$(not T(TTT))=0;
* Set relative time weights of S identical
WEIGHT_S(S)=168*card(SSS)/card(S);
WEIGHT_S(SSS)$(not S(SSS))=0;
* Change size of hour in each season.
CHRONOHOUR(S,T) = SUM(HOURS24,T2HOURS24(T,HOURS24));

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

*fro aggregating demands - one extra dimension
PARAMETER IMAXIMUM_D( *,*,SSS)     'Maximum value of current time series'
          IMINIMUM_D( *,*,SSS)     'Minimum value of current time series'
          IMEAN_D( *,*,SSS)        'Mean value of current time series'
          INEW_MAXIMUM_D( *,*,SSS) 'Maximum value of current time series'
          INEW_MINIMUM_D( *,*,SSS) 'Minimum value of current time series'
          INEW_MEAN_D( *,*,SSS)    'Mean value of current time series'

          IWEIGHT_OTH_D( *,*,SSS)

          IDIFF_MAXIMUM_D( *,*,SSS)
          IDIFF_MINIMUM_D( *,*,SSS)
          IDIFF_MEAN_D( *,*,SSS)

* PARAMETERS FOR aggr_2_s_t.inc
          AREASUM(SSS,TTT)
          AREAWEIGHTSUM
;

SET T_MAX( *,SSS,T) 'Time segment with maximum value'
    T_MIN( *,SSS,T) 'Time segment with minimum value'
    T_OTH( *,SSS,T) 'Time segment with other values'

        T_MAX_D( *,*,SSS,T) 'Time segment with maximum value'
    T_MIN_D( *,*,SSS,T) 'Time segment with minimum value'
    T_OTH_D( *,*,SSS,T) 'Time segment with other values'
;

* Remove profiles from geography not in simulation.
DE_VAR_T(RRR,DEUSER,SSS,TTT)$(not IR(RRR)) = 0;
DH_VAR_T(AAA,DHUSER,SSS,TTT)$(not IA(AAA)) = 0;
X3FX_VAR_T(RRR,SSS,TTT)$(not IR(RRR)) = 0;
WND_VAR_T(AAA,SSS,TTT)$(not IA(AAA)) = 0;
SOLE_VAR_T(AAA,SSS,TTT)$(not IA(AAA)) = 0;
SOLH_VAR_T(AAA,SSS,TTT)$(not IA(AAA)) = 0;
WAVE_VAR_T(AAA,SSS,TTT)$(not IA(AAA)) = 0;
WTRRRVAR_T(AAA,SSS,TTT)$(not IA(AAA)) = 0;
TEMP_VAR_T(RRR,SSS,TTT)$(not IR(RRR)) = 0;

$ifi %HYDROGEN%==yes HYDROGEN_DH2_VAR_T(RRR,SSS,TTT)$(not IR(RRR)) = 0;

ISUMWEIGHT = SUM(T,WEIGHT_T(T));


$batinclude "../../base/addons/TimeAggregation/aggr_1_s_t_demands.inc" DE_VAR_T IR DEUSER
$batinclude "../../base/addons/TimeAggregation/aggr_1_s_t_demands.inc" DH_VAR_T IA DHUSER
$ifi %HYDROGEN%==yes  $batinclude "../../base/addons/TimeAggregation/aggr_1_s_t.inc" HYDROGEN_DH2_VAR_T IR
$batinclude "../../base/addons/TimeAggregation/aggr_1_s_t.inc" X3FX_VAR_T IR

* $batinclude "../../base/addons/TimeAggregation/aggr_1_s_t.inc" WND_VAR_T IA
*$batinclude "../../base/addons/TimeAggregation/aggr_1_s_t.inc" SOLE_VAR_T IA
*$batinclude "../../base/addons/TimeAggregation/aggr_1_s_t.inc" SOLH_VAR_T IA
$batinclude "../../base/addons/TimeAggregation/aggr_1_s_t.inc" WAVE_VAR_T IA
*$batinclude "../../base/addons/TimeAggregation/aggr_1_s_t.inc" WTRRRVAR_T IA
$batinclude "../../base/addons/TimeAggregation/aggr_2_s_t.inc" WND_VAR_T IA

TEMP_VAR_T(IR,S,T) = Sum(SSS,  PS2SSS(S,SSS)*(SUM(TTT$IT2TTT(SSS,T,TTT), TEMP_VAR_T(IR,SSS,TTT))/WEIGHT_T(T))$WEIGHT_T(T))/COUNTELEMENTS(S);

SOLE_VAR_T(IA,S,T) = Sum(SSS,  PS2SSS(S,SSS)*(SUM(TTT$IT2TTT(SSS,T,TTT), SOLE_VAR_T(IA,SSS,TTT))/WEIGHT_T(T))$WEIGHT_T(T))/COUNTELEMENTS(S);
SOLH_VAR_T(IA,S,T) = Sum(SSS,  PS2SSS(S,SSS)*(SUM(TTT$IT2TTT(SSS,T,TTT), SOLH_VAR_T(IA,SSS,TTT))/WEIGHT_T(T))$WEIGHT_T(T))/COUNTELEMENTS(S);

WTRRRVAR_T(IA,S,T) = Sum(SSS,  PS2SSS(S,SSS)*(SUM(TTT$IT2TTT(SSS,T,TTT), WTRRRVAR_T(IA,SSS,TTT))/WEIGHT_T(T))$WEIGHT_T(T))/COUNTELEMENTS(S);

*DEF_STEPS(IR,S,T,DF_QP,DEF)= Sum(SSS,  PS2SSS(S,SSS)*(SUM(TTT$IT2TTT(SSS,T,TTT) ,DEF_STEPS(IR,SSS,TTT,DF_QP,DEF))/WEIGHT_T(T))$WEIGHT_T(T))/COUNTELEMENTS(S) ;
*DHF_STEPS(IA,S,T,DF_QP,DHF)= Sum(SSS,  PS2SSS(S,SSS)*(SUM(TTT$IT2TTT(SSS,T,TTT) ,DHF_STEPS(IA,SSS,TTT,DF_QP,DHF))/WEIGHT_T(T))$WEIGHT_T(T))/COUNTELEMENTS(S) ;


GMAXFS(Y,CCCRRRAAA,FFF,S)   = Sum(SSS, PS2SSS(S,SSS)*GMAXFS(Y,CCCRRRAAA,FFF,SSS) )/COUNTELEMENTS(S);
GMINF_S(Y,IA,FFF,S) = Sum(SSS, PS2SSS(S,SSS)*GMINF_S(Y,IA,FFF,S) )/COUNTELEMENTS(S);

$ifi %GKRATE_DOL%==AAA_GGG_SSS_TTT GKRATE(IA,G,S,T) = Sum(SSS, PS2SSS(S,SSS)*(SUM(TTT$IT2TTT(SSS,T,TTT), GKRATE(IA,G,SSS,TTT))/WEIGHT_T(T))$WEIGHT_T(T))/COUNTELEMENTS(S);
$ifi %GKRATE_DOL%==AAA_GGG_SSS     GKRATE(IA,G,S)   = Sum(SSS, PS2SSS(S,SSS)*GKRATE(IA,G,SSS))/COUNTELEMENTS(S);

*$ifi %XKRATE_DOL%==IRRRE_IRRRI_SSS_TTT XKRATE(IRRRE,IRRRI,S,T)  = Sum(SSS, PS2SSS(S,SSS)*(SUM(TTT$IT2TTT(SSS,T,TTT), XKRATE(IRRRE,IRRRI,SSS,TTT))/WEIGHT_T(T))$WEIGHT_T(T))/COUNTELEMENTS(S);
*$ifi %XKRATE_DOL%==IRRRE_IRRRI_SSS     XKRATE(IRRRE,IRRRI,S)    = Sum(SSS, PS2SSS(S,SSS)*XKRATE(IRRRE,IRRRI,SSS))/COUNTELEMENTS(S);

HYPPROFILS(IA,S)    = Sum(SSS,  PS2SSS(S,SSS)*HYPPROFILS(IA,SSS))/COUNTELEMENTS(S);
* Inflow is given in units of energy, therefore a sum is used, not an average:
WTRRSVAR_S(IA,S)    = Sum(SSS,  PS2SSS(S,SSS)*WTRRSVAR_S(IA,SSS));

HYRSDATA(IA,'HYRSMAXVOL',S) = Sum(SSS,  PS2SSS(S,SSS)*HYRSDATA(IA,'HYRSMAXVOL',SSS))/COUNTELEMENTS(S);
HYRSDATA(IA,'HYRSMINVOL',S) = Sum(SSS,  PS2SSS(S,SSS)*HYRSDATA(IA,'HYRSMINVOL',SSS))/COUNTELEMENTS(S);

$ifi %X3V%==yes X3VPEX(Y,IR,X3VPLACE,X3VSTEP,S,T)= Sum(SSS,  PS2SSS(S,SSS)*(SUM(TTT$IT2TTT(SSS,T,TTT), X3VPEX(Y,IR,X3VPLACE,X3VSTEP,SSS,TTT))/WEIGHT_T(T))$WEIGHT_T(T))/COUNTELEMENTS(S);
$ifi %X3V%==yes X3VPIM(Y,IR,X3VPLACE,X3VSTEP,S,T)= Sum(SSS,  PS2SSS(S,SSS)*(SUM(TTT$IT2TTT(SSS,T,TTT), X3VPIM(Y,IR,X3VPLACE,X3VSTEP,SSS,TTT))/WEIGHT_T(T))$WEIGHT_T(T))/COUNTELEMENTS(S);

$ifi not  %GRIDTARIFFS%==yes    $goto nogridtariffstimeaggr
*assign seasons to months
SSSTTTMMM(S,T) =FLOOR(Sum(SSS,  PS2SSS(S,SSS)*SUM(TTT$IT2TTT(SSS,T,TTT), SSSTTTMMM(SSS,TTT)))/WEIGHT_T(T)$WEIGHT_T(T)/COUNTELEMENTS(S));
SSSTTTMMM(SSS,TTT)$(NOT T(TTT) OR NOT S(SSS))          = 0;
GRTIME_T(CCC,GRDATASET,T)$TINDAY(T,'MONDAY') = 1$SUM((TTT,SSS)$(IT2TTT(SSS,T,TTT) AND ORD(TTT) LE 120), GRTIME_T(CCC,GRDATASET,TTT))  ;
GRTIME_T(CCC,GRDATASET,T)$TINDAY(T,'SUNDAY') = 1$SUM((TTT,SSS)$(IT2TTT(SSS,T,TTT) AND ORD(TTT) GE 121), GRTIME_T(CCC,GRDATASET,TTT)) ;
GRTIME_T(CCC,GRDATASET,TTT)$(NOT T(TTT) )          = 0;
$label nogridtariffstimeaggr

* Following doesnt have any functionality, but gives 'ex post' consistent parameters.
*DEF_STEPS(IR,SSS,TTT,DF_QP,DEF)$(NOT T(TTT))          = 0;
*DHF_STEPS(IA,SSS,TTT,DF_QP,DHF)$(NOT T(TTT))          = 0;
$ifi %X3V%==yes X3VPEX(YYY,IR,X3VPLACE,X3VSTEP,SSS,TTT)$(NOT T(TTT))       = 0;
$ifi %X3V%==yes X3VPIM(YYY,IR,X3VPLACE,X3VSTEP,SSS,TTT)$(NOT T(TTT))       = 0;

$ifi %GKRATE_DOL%==AAA_GGG_SSS_TTT  GKRATE(IA,G,SSS,TTT)$(NOT T(TTT))      = 0;
$ifi %XKRATE_DOL%==IRRRE_IRRRI_SSS_TTT  XKRATE(IRRRE,IRRRI,SSS,TTT)$(NOT T(TTT))      = 0;


*DEF_STEPS(IR,SSS,T,DF_QP,DEF)$(NOT S(SSS))          = 0;
*DHF_STEPS(IA,SSS,T,DF_QP,DHF)$(NOT S(SSS))          = 0;
$ifi %X3V%==yes X3VPEX(YYY,IR,X3VPLACE,X3VSTEP,SSS,T)$(NOT S(SSS))       = 0;
$ifi %X3V%==yes X3VPIM(YYY,IR,X3VPLACE,X3VSTEP,SSS,T)$(NOT S(SSS))       = 0;

$ifi %GKRATE_DOL%==AAA_GGG_SSS_TTT  GKRATE(IA,G,SSS,TTT)$(NOT S(SSS))    = 0;
$ifi %GKRATE_DOL%==AAA_GGG_SSS      GKRATE(IA,G,SSS)$(NOT S(SSS))        = 0;

$ifi %XKRATE_DOL%==IRRRE_IRRRI_SSS_TTT XKRATE(IRRRE,IRRRI,SSS,TTT)$(NOT S(SSS))    = 0;
$ifi %XKRATE_DOL%==IRRRE_IRRRI_SSS     XKRATE(IRRRE,IRRRI,SSS)$(NOT S(SSS))        = 0;
execute_unload 'gkrate.gdx', gkrate;
HYPPROFILS(IA,SSS)$(NOT S(SSS))       = 0;
WTRRSVAR_S(IA,SSS)$(NOT S(SSS))       = 0;
HYRSDATA(IA,'HYRSMAXVOL',SSS)$(NOT S(SSS)) =0;
HYRSDATA(IA,'HYRSMINVOL',SSS)$(NOT S(SSS)) =0;
TEMP_VAR_T(IR,SSS,TTT)$(NOT T(TTT) OR NOT S(SSS))       = 0;

SOLH_VAR_T(IA,S,T)$(SOLH_VAR_T(IA,S,T) LE 0) =0;

$ifi %DEMANDRESPONSE%==yes IDR_RATE(IA,DR_TECH,S,T) = Sum(SSS,  PS2SSS(S,SSS)*(SUM(TTT$IT2TTT(SSS,T,TTT), IDR_RATE(IA,DR_TECH,SSS,TTT))/WEIGHT_T(T))$WEIGHT_T(T))/COUNTELEMENTS(S);
$ifi %DEMANDRESPONSE%==yes IDR_RATE(IA,DR_TECH,SSS,TTT)$(NOT T(TTT) OR NOT S(SSS))       = 0;

$ifi not %INDHEAT%==yes    $goto noindheattimeaggr
INDHEAT_DH_VAR_T(INDHEAT_AAA,INDHEAT_DHUSER,SSS,TTT)$(not INDHEAT_IA(INDHEAT_AAA)) = 0;
INDHEAT_SOLH_VAR_T(INDHEAT_AAA,SSS,TTT)$(not INDHEAT_IA(INDHEAT_AAA)) = 0;
*$batinclude "../../base/addons/TimeAggregation/aggr_1_s_t_demands.inc" INDHEAT_DH_VAR_T INDHEAT_IA INDHEAT_DHUSER
INDHEAT_DH_VAR_T(INDHEAT_IA,INDHEAT_DHUSER,S,T) = Sum(SSS,  PS2SSS(S,SSS)*(SUM(TTT$IT2TTT(SSS,T,TTT), INDHEAT_DH_VAR_T(INDHEAT_IA,INDHEAT_DHUSER,SSS,TTT))/WEIGHT_T(T))$WEIGHT_T(T))/COUNTELEMENTS(S);
INDHEAT_SOLH_VAR_T(INDHEAT_IA,S,T) = Sum(SSS,  PS2SSS(S,SSS)*(SUM(TTT$IT2TTT(SSS,T,TTT), INDHEAT_SOLH_VAR_T(INDHEAT_IA,SSS,TTT))/WEIGHT_T(T))$WEIGHT_T(T))/COUNTELEMENTS(S);
INDHEAT_SOLH_VAR_T(INDHEAT_IA,S,T)$(INDHEAT_SOLH_VAR_T(INDHEAT_IA,S,T) LE 0) =0;

INDHEAT_DH_VAR_T(INDHEAT_IA,INDHEAT_DHUSER,SSS,TTT)$(NOT T(TTT) OR NOT S(SSS))       = 0;
INDHEAT_SOLH_VAR_T(INDHEAT_IA,SSS,TTT)$(NOT T(TTT) OR NOT S(SSS))       = 0;
$label noindheattimeaggr

$ifi not %EV%==yes    $goto noevtimeaggr
EV_BEV_Avail(YYY,S,T,IR) = Sum(SSS,  PS2SSS(S,SSS)*(SUM(TTT$IT2TTT(SSS,T,TTT), EV_BEV_Avail(YYY,S,T,IR))/WEIGHT_T(T))$WEIGHT_T(T))/COUNTELEMENTS(S);
EV_BEV_Dumb(YYY,S,T,IR) = Sum(SSS,  PS2SSS(S,SSS)*(SUM(TTT$IT2TTT(SSS,T,TTT), EV_BEV_Dumb(YYY,S,T,IR))/WEIGHT_T(T))$WEIGHT_T(T))/COUNTELEMENTS(S);
EV_BEV_Flex(YYY,S,T,IR) = Sum(SSS,  PS2SSS(S,SSS)*(SUM(TTT$IT2TTT(SSS,T,TTT), EV_BEV_Flex(YYY,S,T,IR))/WEIGHT_T(T))$WEIGHT_T(T))/COUNTELEMENTS(S);
EV_BEV_Inflex(YYY,S,T,IR) = Sum(SSS,  PS2SSS(S,SSS)*(SUM(TTT$IT2TTT(SSS,T,TTT), EV_BEV_Inflex(YYY,S,T,IR))/WEIGHT_T(T))$WEIGHT_T(T))/COUNTELEMENTS(S);
EV_BEV_Max(YYY,S,T,IR) = Sum(SSS,  PS2SSS(S,SSS)*(SUM(TTT$IT2TTT(SSS,T,TTT), EV_BEV_Max(YYY,S,T,IR))/WEIGHT_T(T))$WEIGHT_T(T))/COUNTELEMENTS(S);
EV_BEV_Min(YYY,S,T,IR) = Sum(SSS,  PS2SSS(S,SSS)*(SUM(TTT$IT2TTT(SSS,T,TTT), EV_BEV_Min(YYY,S,T,IR))/WEIGHT_T(T))$WEIGHT_T(T))/COUNTELEMENTS(S);
EV_BEV_SOCDumb(YYY,S,T,IR) = Sum(SSS,  PS2SSS(S,SSS)*(SUM(TTT$IT2TTT(SSS,T,TTT), EV_BEV_SOCDumb(YYY,S,T,IR))/WEIGHT_T(T))$WEIGHT_T(T))/COUNTELEMENTS(S);
EV_BEV_SOCFlex(YYY,S,T,IR) = Sum(SSS,  PS2SSS(S,SSS)*(SUM(TTT$IT2TTT(SSS,T,TTT), EV_BEV_SOCFlex(YYY,S,T,IR))/WEIGHT_T(T))$WEIGHT_T(T))/COUNTELEMENTS(S);
EV_PHEV_Avail(YYY,S,T,IR) = Sum(SSS,  PS2SSS(S,SSS)*(SUM(TTT$IT2TTT(SSS,T,TTT), EV_PHEV_Avail(YYY,S,T,IR))/WEIGHT_T(T))$WEIGHT_T(T))/COUNTELEMENTS(S);
EV_PHEV_Dumb(YYY,S,T,IR) = Sum(SSS,  PS2SSS(S,SSS)*(SUM(TTT$IT2TTT(SSS,T,TTT), EV_PHEV_Dumb(YYY,S,T,IR))/WEIGHT_T(T))$WEIGHT_T(T))/COUNTELEMENTS(S);
EV_PHEV_Flex(YYY,S,T,IR) = Sum(SSS,  PS2SSS(S,SSS)*(SUM(TTT$IT2TTT(SSS,T,TTT), EV_PHEV_Flex(YYY,S,T,IR))/WEIGHT_T(T))$WEIGHT_T(T))/COUNTELEMENTS(S);
EV_PHEV_Inflex(YYY,S,T,IR) = Sum(SSS,  PS2SSS(S,SSS)*(SUM(TTT$IT2TTT(SSS,T,TTT), EV_PHEV_Inflex(YYY,S,T,IR))/WEIGHT_T(T))$WEIGHT_T(T))/COUNTELEMENTS(S);
EV_PHEV_Max(YYY,S,T,IR) = Sum(SSS,  PS2SSS(S,SSS)*(SUM(TTT$IT2TTT(SSS,T,TTT), EV_PHEV_Max(YYY,S,T,IR))/WEIGHT_T(T))$WEIGHT_T(T))/COUNTELEMENTS(S);
EV_PHEV_Min(YYY,S,T,IR) = Sum(SSS,  PS2SSS(S,SSS)*(SUM(TTT$IT2TTT(SSS,T,TTT), EV_PHEV_Min(YYY,S,T,IR))/WEIGHT_T(T))$WEIGHT_T(T))/COUNTELEMENTS(S);
EV_PHEV_SOCDumb(YYY,S,T,IR) = Sum(SSS,  PS2SSS(S,SSS)*(SUM(TTT$IT2TTT(SSS,T,TTT), EV_PHEV_SOCDumb(YYY,S,T,IR))/WEIGHT_T(T))$WEIGHT_T(T))/COUNTELEMENTS(S);
EV_PHEV_SOCFlex(YYY,S,T,IR) = Sum(SSS,  PS2SSS(S,SSS)*(SUM(TTT$IT2TTT(SSS,T,TTT), EV_PHEV_SOCFlex(YYY,S,T,IR))/WEIGHT_T(T))$WEIGHT_T(T))/COUNTELEMENTS(S);
EV_BEV_Avail(YYY,SSS,TTT,RRR)$(NOT T(TTT) OR NOT S(SSS) OR NOT Y(YYY))       = 0;
EV_BEV_Dumb(YYY,SSS,TTT,RRR)$(NOT T(TTT) OR NOT S(SSS) OR NOT Y(YYY))       = 0;
EV_BEV_Flex(YYY,SSS,TTT,RRR)$(NOT T(TTT) OR NOT S(SSS) OR NOT Y(YYY))       = 0;
EV_BEV_Inflex(YYY,SSS,TTT,RRR)$(NOT T(TTT) OR NOT S(SSS) OR NOT Y(YYY))       = 0;
EV_BEV_Max(YYY,SSS,TTT,RRR)$(NOT T(TTT) OR NOT S(SSS) OR NOT Y(YYY))       = 0;
EV_BEV_Min(YYY,SSS,TTT,RRR)$(NOT T(TTT) OR NOT S(SSS) OR NOT Y(YYY))       = 0;
EV_BEV_SOCDumb(YYY,SSS,TTT,RRR)$(NOT T(TTT) OR NOT S(SSS) OR NOT Y(YYY))       = 0;
EV_BEV_SOCFlex(YYY,SSS,TTT,RRR)$(NOT T(TTT) OR NOT S(SSS) OR NOT Y(YYY))       = 0;
EV_PHEV_Avail(YYY,SSS,TTT,RRR)$(NOT T(TTT) OR NOT S(SSS) OR NOT Y(YYY))       = 0;
EV_PHEV_Dumb(YYY,SSS,TTT,RRR)$(NOT T(TTT) OR NOT S(SSS) OR NOT Y(YYY))       = 0;
EV_PHEV_Flex(YYY,SSS,TTT,RRR)$(NOT T(TTT) OR NOT S(SSS) OR NOT Y(YYY))       = 0;
EV_PHEV_Inflex(YYY,SSS,TTT,RRR)$(NOT T(TTT) OR NOT S(SSS) OR NOT Y(YYY))       = 0;
EV_PHEV_Max(YYY,SSS,TTT,RRR)$(NOT T(TTT) OR NOT S(SSS) OR NOT Y(YYY))       = 0;
EV_PHEV_Min(YYY,SSS,TTT,RRR)$(NOT T(TTT) OR NOT S(SSS) OR NOT Y(YYY))       = 0;
EV_PHEV_SOCDumb(YYY,SSS,TTT,RRR)$(NOT T(TTT) OR NOT S(SSS) OR NOT Y(YYY))       = 0;
EV_PHEV_SOCFlex(YYY,SSS,TTT,RRR)$(NOT T(TTT) OR NOT S(SSS) OR NOT Y(YYY))       = 0;
$label noevtimeaggr
$label NoAggregation;
