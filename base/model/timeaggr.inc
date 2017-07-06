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

$ifi %gas%==yes $goto gasdefined;


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


$label gasdefined;
SET HOURS24 /HR01*HR24/;

$ontext
TABLE TINDAY(T,DAY)
      MONDAY TUESDAY WEDNESDAY THURSDAY FRIDAY SATURDAY SUNDAY
T001  1      1       1         1        1
T002  1      1       1         1        1
T003  1      1       1         1        1
T004  1      1       1         1        1
T005  1      1       1         1        1
T006  1      1       1         1        1      1        1
T007                                           1        1
T008                                           1        1
;


TABLE T2HOURS24(T,HOURS24)
      HR01 HR02 HR03 HR04 HR05 HR06 HR07 HR08 HR09 HR10 HR11 HR12 HR13 HR14 HR15 HR16 HR17 HR18 HR19 HR20 HR21 HR22 HR23 HR24
T001                                          1    1    1    1    1
T002                                                                   1    1    1    1         1    1
T003                           1    1                                                                     1    1
T004                                     1
T005                                                                                       1
T006  1    1    1    1    1                                                                                         1    1
T007                           1    1    1                   1    1    1    1    1    1    1    1    1    1    1
T008                                          1    1    1
;

$offtext

* ++++JH hvis man kun skal kare med 5 perioder pr. "uge"/varighedsinddelinger skal de to nedenstaende indkommenteres og de
* to efterfalgende udkommenteres, derudover skal der andres tilsvarende i sets T i sets.inc
*$ontext
TABLE TINDAY(T,DAY)
      MONDAY TUESDAY WEDNESDAY THURSDAY FRIDAY SATURDAY SUNDAY
T001  1      1       1         1        1
T002  1      1       1         1        1
T003  1      1       1         1        1
T004  1      1       1         1        1      1        1
T005                                           1        1
;


TABLE T2HOURS24(T,HOURS24)
      HR01 HR02 HR03 HR04 HR05 HR06 HR07 HR08 HR09 HR10 HR11 HR12 HR13 HR14 HR15 HR16 HR17 HR18 HR19 HR20 HR21 HR22 HR23 HR24
T001                                          1    1    1    1    1
T002                                                                   1    1    1    1    1    1    1
T003                           1    1    1                                                                1    1
T004  1    1    1    1    1                                                                                         1    1
T005                           1    1    1    1    1    1    1    1    1    1    1    1    1    1    1    1    1
;


$ontext
TABLE TINDAY(T,DAY)
      MONDAY TUESDAY WEDNESDAY THURSDAY FRIDAY SATURDAY SUNDAY
T001  1      1
T002  1      1
T003  1      1
T004                 1         1
T005                 1         1
T006                 1         1
T007                                    1
T008                                    1
T009                                    1
T010  1      1       1         1        1      1        1
T011                                           1        1
;


TABLE T2HOURS24(T,HOURS24)
      HR01 HR02 HR03 HR04 HR05 HR06 HR07 HR08 HR09 HR10 HR11 HR12 HR13 HR14 HR15 HR16 HR17 HR18 HR19 HR20 HR21 HR22 HR23 HR24
T001                                          1    1    1    1    1
T002                                                                   1    1    1    1    1    1    1
T003                           1    1    1                                                                1    1
T004                                          1    1    1    1    1
T005                                                                   1    1    1    1    1    1    1
T006                           1    1    1                                                                1    1
T007                                          1    1    1    1    1
T008                                                                   1    1    1    1    1    1    1
T009                           1    1    1                                                                1    1
T010  1    1    1    1    1                                                                                         1    1
T011                           1    1    1    1    1    1    1    1    1    1    1    1    1    1    1    1    1
;
$offtext

ALIAS(TTT,ITTTALIAS);
IT2TTT(SSS,T,TTT)=YES$(sum((DAY,HOURS24),1$(TINDAY(T,DAY) and T2HOURS24(T,HOURS24) and 24*(ORD(DAY)-1)+ORD(HOURS24)=ORD(TTT))));



$kill weight_t
$ifi not %CREATEDTIME%==yes $goto end_skipcreatedtime
$ifi not exist 'TIMERES.gdx' execute_load '../../base/model/TIMERES.gdx' IT2TTT=OT2TTT;
$ifi exist 'TIMERES.gdx' execute_load 'TIMERES.gdx' IT2TTT=OT2TTT;
$label end_skipcreatedtime

* LARS: If not all S have been generated use the first. VIRKER IKKE!
$ifi %CREATEDTIME%==yes IT2TTT(S,T,TTT)$(SUM((ITALIAS,ITTTALIAS)$IT2TTT(S,ITALIAS,ITTTALIAS),1)=0)
$ifi %CREATEDTIME%==yes           = yes$SUM(ISALIAS$(ord(ISALIAS)=1),IT2TTT(ISALIAS,T,TTT));

WEIGHT_T(T)=sum((S,TTT)$(IT2TTT(S,T,TTT) and ord(S)=1),1);

WEIGHT_S(S)=168*card(SSS)/card(S);
WEIGHT_S(SSS)$(not S(SSS))=0;

PS2SSS(S,SSS)=Max(0,1-Min(1,Max(0,ORD(SSS)-CARD(SSS)/CARD(S)*ORD(S)))-Min(1,max(0,1-(ord(SSS)-CARD(SSS)/CARD(S)*(ORD(S)-1)))));
COUNTELEMENTS(S) = Sum(SSS, PS2SSS(S,SSS));

DE_VAR_T(IR,S,T)   = Sum(SSS,  PS2SSS(S,SSS)*(SUM(TTT$IT2TTT(SSS,T,TTT), DE_VAR_T(IR,SSS,TTT))/WEIGHT_T(T))$WEIGHT_T(T))/COUNTELEMENTS(S);
DH_VAR_T(IA,S,T)   = Sum(SSS,  PS2SSS(S,SSS)*(SUM(TTT$IT2TTT(SSS,T,TTT), DH_VAR_T(IA,SSS,TTT))/WEIGHT_T(T))$WEIGHT_T(T))/COUNTELEMENTS(S);
X3FX_VAR_T(IR,S,T) = Sum(SSS,  PS2SSS(S,SSS)*(SUM(TTT$IT2TTT(SSS,T,TTT), X3FX_VAR_T(IR,SSS,TTT))/WEIGHT_T(T))$WEIGHT_T(T))/COUNTELEMENTS(S);
WND_VAR_T(IA,S,T)  = Sum(SSS,  PS2SSS(S,SSS)*(SUM(TTT$IT2TTT(SSS,T,TTT), WND_VAR_T(IA,SSS,TTT))/WEIGHT_T(T))$WEIGHT_T(T))/COUNTELEMENTS(S);
SOLE_VAR_T(IA,S,T) = Sum(SSS,  PS2SSS(S,SSS)*(SUM(TTT$IT2TTT(SSS,T,TTT), SOLE_VAR_T(IA,SSS,TTT))/WEIGHT_T(T))$WEIGHT_T(T))/COUNTELEMENTS(S);
WTRRRVAR_T(IA,S,T) = Sum(SSS,  PS2SSS(S,SSS)*(SUM(TTT$IT2TTT(SSS,T,TTT) ,WTRRRVAR_T(IA,SSS,TTT))/WEIGHT_T(T))$WEIGHT_T(T))/COUNTELEMENTS(S);

DEF_STEPS(IR,S,T,DF_QP,DEF)= Sum(SSS,  PS2SSS(S,SSS)*(SUM(TTT$IT2TTT(SSS,T,TTT) ,DEF_STEPS(IR,SSS,TTT,DF_QP,DEF))/WEIGHT_T(T))$WEIGHT_T(T))/COUNTELEMENTS(S) ;

GKDERATE(IA,G,S)    = Sum(SSS,  PS2SSS(S,SSS)*GKDERATE(IA,G,SSS))/COUNTELEMENTS(S);
HYPPROFILS(IA,S)    = Sum(SSS,  PS2SSS(S,SSS)*HYPPROFILS(IA,SSS))/COUNTELEMENTS(S);
* Inflow is given in units of energy, therefore a sum is used, not an average:
WTRRSVAR_S(IA,S)    = Sum(SSS,  PS2SSS(S,SSS)*WTRRSVAR_S(IA,SSS));

$ifi %X3V%==yes X3VPEX(Y,IR,X3VPLACE,X3VSTEP,S,T)= Sum(SSS,  PS2SSS(S,SSS)*(SUM(TTT$IT2TTT(SSS,T,TTT), X3VPEX(Y,IR,X3VPLACE,X3VSTEP,SSS,TTT))/WEIGHT_T(T))$WEIGHT_T(T))/COUNTELEMENTS(S);
$ifi %X3V%==yes X3VPIM(Y,IR,X3VPLACE,X3VSTEP,S,T)= Sum(SSS,  PS2SSS(S,SSS)*(SUM(TTT$IT2TTT(SSS,T,TTT), X3VPIM(Y,IR,X3VPLACE,X3VSTEP,SSS,TTT))/WEIGHT_T(T))$WEIGHT_T(T))/COUNTELEMENTS(S);

* Ingen funktionalitet men giver 'ex post' konsistente parametre.
DE_VAR_T(IR,SSS,TTT)$(NOT T(TTT))          = 0;
DH_VAR_T(IA,SSS,TTT)$(NOT T(TTT))          = 0;
X3FX_VAR_T(IR,SSS,TTT)$(NOT T(TTT))        = 0;
WND_VAR_T(IA,SSS,TTT) $(NOT T(TTT))        = 0;
SOLE_VAR_T(IA,SSS,TTT)$(NOT T(TTT))        = 0;
WTRRRVAR_T(IA,SSS,TTT)$(NOT T(TTT))        = 0;
DEF_STEPS(IR,SSS,TTT,DF_QP,DEF)$(NOT T(TTT))          = 0;
$ifi %X3V%==yes X3VPEX(YYY,IR,X3VPLACE,X3VSTEP,SSS,TTT)$(NOT T(TTT))       = 0;
$ifi %X3V%==yes X3VPIM(YYY,IR,X3VPLACE,X3VSTEP,SSS,TTT)$(NOT T(TTT))       = 0;

DE_VAR_T(IR,SSS,T)$(NOT S(SSS))         = 0;
DH_VAR_T(IA,SSS,T)$(NOT S(SSS))         = 0;
X3FX_VAR_T(IR,SSS,T)$(NOT S(SSS))       = 0;
WND_VAR_T(IA,SSS,T)$(NOT S(SSS))        = 0;
SOLE_VAR_T(IA,SSS,T)$(NOT S(SSS))       = 0;
WTRRRVAR_T(IA,SSS,T)$(NOT S(SSS))       = 0;
DEF_STEPS(IR,SSS,T,DF_QP,DEF)$(NOT S(SSS))          = 0;
$ifi %X3V%==yes X3VPEX(YYY,IR,X3VPLACE,X3VSTEP,SSS,T)$(NOT S(SSS))       = 0;
$ifi %X3V%==yes X3VPIM(YYY,IR,X3VPLACE,X3VSTEP,SSS,T)$(NOT S(SSS))       = 0;

GKDERATE(IA,G,SSS)$(NOT S(SSS))       = 0;
HYPPROFILS(IA,SSS)$(NOT S(SSS))       = 0;
WTRRSVAR_S(IA,SSS)$(NOT S(SSS))       = 0;


*------------------------------------------------
* Aggregation of time series for add-ons
*------------------------------------------------

$ifi %GAS%==yes DGRES_VAR(IA,S,T)         = Sum(SSS,  PS2SSS(S,SSS)*(SUM(TTT$IT2TTT(SSS,T,TTT), DGRES_VAR(IA,SSS,TTT))/WEIGHT_T(T))$WEIGHT_T(T);
$ifi %GAS%==yes DGOTH_VAR(IA,S,T)         = Sum(SSS,  PS2SSS(S,SSS)*(SUM(TTT$IT2TTT(SSS,T,TTT), DGOTH_VAR(IA,SSS,TTT))/WEIGHT_T(T))$WEIGHT_T(T);

* Ingen funktionalitet men giver 'ex post' konsistente parametre.
$ifi %GAS%==yes DGRES_VAR(IA,SSS,TTT)$(NOT T(TTT))         = 0;
$ifi %GAS%==yes DGOTH_VAR(IA,SSS,TTT)$(NOT T(TTT))         = 0;
$ifi %GAS%==yes SE_DGOTH_VAR_T(IA,SSS,TTT)$(NOT T(TTT))    = 0;
$ifi %GAS%==yes SE_DGRES_VAR_T(IA,SSS,TTT)$(NOT T(TTT))    = 0;

$ifi %GAS%==yes DGRES_VAR(IA,SSS,T)$(NOT S(SSS))         = 0;
$ifi %GAS%==yes DGOTH_VAR(IA,SSS,T)$(NOT S(SSS))         = 0;
$ifi %GAS%==yes SE_DGOTH_VAR_T(IA,SSS,T)$(NOT S(SSS))    = 0;
$ifi %GAS%==yes SE_DGRES_VAR_T(IA,SSS,T)$(NOT S(SSS))    = 0;

$label NoAggregation;
