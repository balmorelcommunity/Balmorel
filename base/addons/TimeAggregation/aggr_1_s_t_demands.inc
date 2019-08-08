* BATINCLUDE aggr_1_s_t.inc:
* This file aggregates a timeseries with:
*        - parameter name (e.g. DE_VAR_T), this is argument %1
*        - one prefixed set (e.g. IA or IR), this is argument %2
*                - second prefixed set (deuser or dhuser) this is argument %3
*        - seasons (SSS)
*        - time steps (SSS)


* With SSS aggregation:
IMAXIMUM_D(%2,%3,S) = SMAX((SSS,TTT)$PS2SSS(S,SSS), %1(%2,%3,SSS,TTT));
IMINIMUM_D(%2,%3,S) = SMIN((SSS,TTT)$PS2SSS(S,SSS), %1(%2,%3,SSS,TTT));
IMEAN_D(%2,%3,S)    = SUM(SSS$PS2SSS(S,SSS), PS2SSS(S,SSS)*SUM(TTT, %1(%2,%3,SSS,TTT))/CARD(TTT))/COUNTELEMENTS(S);

* With SSS aggregation:
%1(%2,%3,S,T) = Sum(SSS,  PS2SSS(S,SSS)*(SUM(TTT$IT2TTT(SSS,T,TTT), %1(%2,%3,SSS,TTT))/WEIGHT_T(T))$WEIGHT_T(T))/COUNTELEMENTS(S);
%1(%2,%3,SSS,TTT)$(NOT T(TTT))        = 0;
%1(%2,%3,SSS,T)$(NOT S(SSS))          = 0;

* With SSS aggregation:
INEW_MAXIMUM_D(%2,%3,S) = SMAX(T, %1(%2,%3,S,T));
INEW_MINIMUM_D(%2,%3,S) = SMIN(T, %1(%2,%3,S,T));
INEW_MEAN_D(%2,%3,S)    = SUM(SSS$PS2SSS(S,SSS),  SUM(T, %1(%2,%3,S,T)*WEIGHT_T(T))/ISUMWEIGHT)/COUNTELEMENTS(S);

* With SSS aggregation:
IDIFF_MAXIMUM_D(%2,%3,S) = INEW_MAXIMUM_D(%2,%3,S)  - IMAXIMUM_D(%2,%3,S)  ;
IDIFF_MINIMUM_D(%2,%3,S) = INEW_MINIMUM_D(%2,%3,S)  - IMINIMUM_D(%2,%3,S)  ;
IDIFF_MEAN_D(%2,%3,S)    = IMEAN_D(%2,%3,S) - INEW_MEAN_D(%2,%3,S)         ;

* With SSS aggregation:
T_MAX_D( %2,%3,S,T)=yes$(%1(%2,%3,S,T) = INEW_MAXIMUM_D(%2,%3,S));
T_MIN_D( %2,%3,S,T)=yes$(%1(%2,%3,S,T) = INEW_MINIMUM_D(%2,%3,S));
T_OTH_D( %2,%3,S,T)=yes$(not (T_MIN_D( %2,%3,S,T) or T_MAX_D( %2,%3,S,T)));

* With SSS aggregation:
%1(%2,%3,S,T)$T_MAX_D(%2,%3,S,T) = IMAXIMUM_D(%2,%3,S);
%1(%2,%3,S,T)$T_MIN_D(%2,%3,S,T) = IMINIMUM_D(%2,%3,S);

* With SSS aggregation:
INEW_MEAN_D(%2,%3,S)    = SUM(T, %1(%2,%3,S,T)*WEIGHT_T(T))/ISUMWEIGHT;
IDIFF_MEAN_D(%2,%3,S)   = IMEAN_D(%2,%3,S) - INEW_MEAN_D(%2,%3,S)         ;

* With SSS aggregation:
IWEIGHT_OTH_D(%2,%3,S) = SUM(T$T_OTH_D(%2,%3,S,T), WEIGHT_T(T));

* With SSS aggregation:
%1(%2,%3,S,T)$T_OTH_D( %2,%3,S,T) = %1(%2,%3,S,T) + IDIFF_MEAN_D(%2,%3,S)*ISUMWEIGHT/IWEIGHT_OTH_D(%2,%3,S);

* With SSS aggregation:
INEW_MEAN_D(%2,%3,S)     = SUM(T, %1(%2,%3,S,T)*WEIGHT_T(T))/ISUMWEIGHT;
IDIFF_MEAN_D(%2,%3,S)    = IMEAN_D(%2,%3,S)-INEW_MEAN_D(%2,%3,S);


$kill IMAXIMUM_D
$kill IMINIMUM_D
$kill IMEAN_D
$kill INEW_MAXIMUM_D
$kill INEW_MINIMUM_D
$kill INEW_MEAN_D
$kill IWEIGHT_OTH_D
$kill IDIFF_MAXIMUM_D
$kill IDIFF_MINIMUM_D
$kill IDIFF_MEAN_D

$ontext
* Without SSS aggregation:
$ifi not %AGGRSSS%==yes IMAXIMUM(%2,%3,SSS) = SMAX(TTT, %1(%2,%3,SSS,TTT));
$ifi not %AGGRSSS%==yes IMINIMUM(%2,%3,SSS) = SMIN(TTT, %1(%2,%3,SSS,TTT));
$ifi not %AGGRSSS%==yes IMEAN(%2,%3,SSS)    = SUM(TTT, %1(%2,%3,SSS,TTT))/CARD(TTT);

* Without SSS aggregation:
$ifi not %AGGRSSS%==yes %1(%2,%3,SSS,T) = (SUM(TTT$IT2TTT(SSS,T,TTT), %1(%2,%3,SSS,TTT))/WEIGHT_T(T))$WEIGHT_T(T);
$ifi not %AGGRSSS%==yes %1(%2,%3,SSS,TTT)$(NOT T(TTT))          = 0;


* Without SSS aggregation:
$ifi not %AGGRSSS%==yes INEW_MAXIMUM(%2,%3,SSS) = SMAX(T, %1(%2,%3,SSS,T));
$ifi not %AGGRSSS%==yes INEW_MINIMUM(%2,%3,SSS) = SMIN(T, %1(%2,%3,SSS,T));
$ifi not %AGGRSSS%==yes INEW_MEAN(%2,%3,SSS)    = SUM(T, %1(%2,%3,SSS,T)*WEIGHT_T(T))/ISUMWEIGHT;

* Without SSS aggregation:
$ifi not %AGGRSSS%==yes IDIFF_MAXIMUM(%2,%3,SSS) = INEW_MAXIMUM(%2,%3,SSS)  - IMAXIMUM(%2,%3,SSS)  ;
$ifi not %AGGRSSS%==yes IDIFF_MINIMUM(%2,%3,SSS) = INEW_MINIMUM(%2,%3,SSS)  - IMINIMUM(%2,%3,SSS)  ;
$ifi not %AGGRSSS%==yes IDIFF_MEAN(%2,%3,SSS)    = IMEAN(%2,%3,SSS) - INEW_MEAN(%2,%3,SSS)         ;

* Without SSS aggregation:
$ifi not %AGGRSSS%==yes T_MAX( %2,%3,SSS,T)=yes$(%1(%2,%3,SSS,T) =  INEW_MAXIMUM(%2,%3,SSS));
$ifi not %AGGRSSS%==yes T_MIN( %2,%3,SSS,T)=yes$(%1(%2,%3,SSS,T) =  INEW_MINIMUM(%2,%3,SSS));
$ifi not %AGGRSSS%==yes T_OTH( %2,%3,SSS,T)=yes$(not (T_MIN( %2,SSS,T) or T_MAX( %2,%3,SSS,T)));

* Without SSS aggregation:
$ifi not %AGGRSSS%==yes %1(%2,%3,SSS,T)$T_MAX(%2,%3,SSS,T) = IMAXIMUM(%2,%3,SSS);
$ifi not %AGGRSSS%==yes %1(%2,%3,SSS,T)$T_MIN(%2,%3,SSS,T) = IMINIMUM(%2,%3,SSS);

* Without SSS aggregation:
$ifi not %AGGRSSS%==yes INEW_MEAN(%2,%3,SSS)    = SUM(T, %1(%2,%3,SSS,T)*WEIGHT_T(T))/ISUMWEIGHT;
$ifi not %AGGRSSS%==yes IDIFF_MEAN(%2,%3,SSS)    = IMEAN(%2,%3,SSS) - INEW_MEAN(%2,%3,SSS)         ;

* Without SSS aggregation:
$ifi not %AGGRSSS%==yes IWEIGHT_OTH(%2,%3,SSS) = SUM(T$T_OTH(%2,%3,SSS,T), WEIGHT_T(T));

* Without SSS aggregation:
$ifi not %AGGRSSS%==yes %1(%2,%3,SSS,T)$T_OTH( %2,%3,SSS,T) = %1(%2,%3,SSS,T) + IDIFF_MEAN(%2,%3,SSS)*ISUMWEIGHT/IWEIGHT_OTH(%2,%3,SSS);

* Without SSS aggregation:
$ifi not %AGGRSSS%==yes INEW_MEAN(%2,%3,SSS)     = SUM(T, %1(%2,%3,SSS,T)*WEIGHT_T(T))/ISUMWEIGHT;
$ifi not %AGGRSSS%==yes IDIFF_MEAN(%2,%3,SSS)    = IMEAN(%2,%3,SSS)-INEW_MEAN(%2,%3,SSS);
$offtext

