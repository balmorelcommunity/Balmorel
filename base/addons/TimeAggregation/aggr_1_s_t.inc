* BATINCLUDE aggr_1_s_t.inc:
* This file aggregates a timeseries with:
*        - parameter name (e.g. DE_VAR_T), this is argument %1
*        - one prefixed set (e.g. IA or IR), this is argument %2
*        - seasons (SSS)
*        - time steps (SSS)


* With SSS aggregation:
IMAXIMUM(%2,S) = SMAX((SSS,TTT)$PS2SSS(S,SSS), %1(%2,SSS,TTT));
IMINIMUM(%2,S) = SMIN((SSS,TTT)$PS2SSS(S,SSS), %1(%2,SSS,TTT));
IMEAN(%2,S)    = SUM(SSS$PS2SSS(S,SSS), PS2SSS(S,SSS)*SUM(TTT, %1(%2,SSS,TTT))/CARD(TTT))/COUNTELEMENTS(S);

* With SSS aggregation:
%1(%2,S,T) = Sum(SSS,  PS2SSS(S,SSS)*(SUM(TTT$IT2TTT(SSS,T,TTT), %1(%2,SSS,TTT))/WEIGHT_T(T))$WEIGHT_T(T))/COUNTELEMENTS(S);
%1(%2,SSS,TTT)$(NOT T(TTT))        = 0;
%1(%2,SSS,T)$(NOT S(SSS))          = 0;

* With SSS aggregation:
INEW_MAXIMUM(%2,S) = SMAX(T, %1(%2,S,T));
INEW_MINIMUM(%2,S) = SMIN(T, %1(%2,S,T));
INEW_MEAN(%2,S)    = SUM(SSS$PS2SSS(S,SSS),  SUM(T, %1(%2,S,T)*WEIGHT_T(T))/ISUMWEIGHT)/COUNTELEMENTS(S);

* With SSS aggregation:
IDIFF_MAXIMUM(%2,S) = INEW_MAXIMUM(%2,S)  - IMAXIMUM(%2,S)  ;
IDIFF_MINIMUM(%2,S) = INEW_MINIMUM(%2,S)  - IMINIMUM(%2,S)  ;
IDIFF_MEAN(%2,S)    = IMEAN(%2,S) - INEW_MEAN(%2,S)         ;

* With SSS aggregation:
T_MAX( %2,S,T)=yes$(%1(%2,S,T) = INEW_MAXIMUM(%2,S));
T_MIN( %2,S,T)=yes$(%1(%2,S,T) = INEW_MINIMUM(%2,S));
T_OTH( %2,S,T)=yes$(not (T_MIN( %2,S,T) or T_MAX( %2,S,T)));

* With SSS aggregation:
%1(%2,S,T)$T_MAX(%2,S,T) = IMAXIMUM(%2,S);
%1(%2,S,T)$T_MIN(%2,S,T) = IMINIMUM(%2,S);

* With SSS aggregation:
INEW_MEAN(%2,S)    = SUM(T, %1(%2,S,T)*WEIGHT_T(T))/ISUMWEIGHT;
IDIFF_MEAN(%2,S)   = IMEAN(%2,S) - INEW_MEAN(%2,S)         ;

* With SSS aggregation:
IWEIGHT_OTH(%2,S) = SUM(T$T_OTH(%2,S,T), WEIGHT_T(T));

* With SSS aggregation:
%1(%2,S,T)$T_OTH( %2,S,T) = %1(%2,S,T) + IDIFF_MEAN(%2,S)*ISUMWEIGHT/IWEIGHT_OTH(%2,S);

* With SSS aggregation:
INEW_MEAN(%2,S)     = SUM(T, %1(%2,S,T)*WEIGHT_T(T))/ISUMWEIGHT;
IDIFF_MEAN(%2,S)    = IMEAN(%2,S)-INEW_MEAN(%2,S);


$kill IMAXIMUM
$kill IMINIMUM
$kill IMEAN
$kill INEW_MAXIMUM
$kill INEW_MINIMUM
$kill INEW_MEAN
$kill IWEIGHT_OTH
$kill IDIFF_MAXIMUM
$kill IDIFF_MINIMUM
$kill IDIFF_MEAN

$ontext
* Without SSS aggregation:
$ifi not %AGGRSSS%==yes IMAXIMUM(%2,SSS) = SMAX(TTT, %1(%2,SSS,TTT));
$ifi not %AGGRSSS%==yes IMINIMUM(%2,SSS) = SMIN(TTT, %1(%2,SSS,TTT));
$ifi not %AGGRSSS%==yes IMEAN(%2,SSS)    = SUM(TTT, %1(%2,SSS,TTT))/CARD(TTT);

* Without SSS aggregation:
$ifi not %AGGRSSS%==yes %1(%2,SSS,T) = (SUM(TTT$IT2TTT(SSS,T,TTT), %1(%2,SSS,TTT))/WEIGHT_T(T))$WEIGHT_T(T);
$ifi not %AGGRSSS%==yes %1(%2,SSS,TTT)$(NOT T(TTT))          = 0;


* Without SSS aggregation:
$ifi not %AGGRSSS%==yes INEW_MAXIMUM(%2,SSS) = SMAX(T, %1(%2,SSS,T));
$ifi not %AGGRSSS%==yes INEW_MINIMUM(%2,SSS) = SMIN(T, %1(%2,SSS,T));
$ifi not %AGGRSSS%==yes INEW_MEAN(%2,SSS)    = SUM(T, %1(%2,SSS,T)*WEIGHT_T(T))/ISUMWEIGHT;

* Without SSS aggregation:
$ifi not %AGGRSSS%==yes IDIFF_MAXIMUM(%2,SSS) = INEW_MAXIMUM(%2,SSS)  - IMAXIMUM(%2,SSS)  ;
$ifi not %AGGRSSS%==yes IDIFF_MINIMUM(%2,SSS) = INEW_MINIMUM(%2,SSS)  - IMINIMUM(%2,SSS)  ;
$ifi not %AGGRSSS%==yes IDIFF_MEAN(%2,SSS)    = IMEAN(%2,SSS) - INEW_MEAN(%2,SSS)         ;

* Without SSS aggregation:
$ifi not %AGGRSSS%==yes T_MAX( %2,SSS,T)=yes$(%1(%2,SSS,T) = INEW_MAXIMUM(%2,SSS));
$ifi not %AGGRSSS%==yes T_MIN( %2,SSS,T)=yes$(%1(%2,SSS,T) = INEW_MINIMUM(%2,SSS));
$ifi not %AGGRSSS%==yes T_OTH( %2,SSS,T)=yes$(not (T_MIN( %2,SSS,T) or T_MAX( %2,SSS,T)));

* Without SSS aggregation:
$ifi not %AGGRSSS%==yes %1(%2,SSS,T)$T_MAX(%2,SSS,T) = IMAXIMUM(%2,SSS);
$ifi not %AGGRSSS%==yes %1(%2,SSS,T)$T_MIN(%2,SSS,T) = IMINIMUM(%2,SSS);

* Without SSS aggregation:
$ifi not %AGGRSSS%==yes INEW_MEAN(%2,SSS)    = SUM(T, %1(%2,SSS,T)*WEIGHT_T(T))/ISUMWEIGHT;
$ifi not %AGGRSSS%==yes IDIFF_MEAN(%2,SSS)    = IMEAN(%2,SSS) - INEW_MEAN(%2,SSS)         ;

* Without SSS aggregation:
$ifi not %AGGRSSS%==yes IWEIGHT_OTH(%2,SSS) = SUM(T$T_OTH(%2,SSS,T), WEIGHT_T(T));

* Without SSS aggregation:
$ifi not %AGGRSSS%==yes %1(%2,SSS,T)$T_OTH( %2,SSS,T) = %1(%2,SSS,T) + IDIFF_MEAN(%2,SSS)*ISUMWEIGHT/IWEIGHT_OTH(%2,SSS);

* Without SSS aggregation:
$ifi not %AGGRSSS%==yes INEW_MEAN(%2,SSS)     = SUM(T, %1(%2,SSS,T)*WEIGHT_T(T))/ISUMWEIGHT;
$ifi not %AGGRSSS%==yes IDIFF_MEAN(%2,SSS)    = IMEAN(%2,SSS)-INEW_MEAN(%2,SSS);
$offtext

