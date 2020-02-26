$if     EXIST '../data/DR_DATAINPUT.inc' $INCLUDE         '../data/DR_DATAINPUT.inc';
$if not EXIST '../data/DR_DATAINPUT.inc' $INCLUDE '../../base/data/DR_DATAINPUT.inc';
%semislash%;

* Move IDR_RATE from dr_ipardefine.inc so it can be used in timeaggr.inc
* IDR_RATE - parameter for the usage profiles for demand response technologies
PARAMETER IDR_RATE(AAA,DR_TECH,SSS,TTT) 'Hourly rating/availability for downregulation of demand response technologies';

*Initializing all IDR_RATE alternatives
$ifi not %timeaggr%==yes IDR_RATE(IA,DR_TECH,S,T)$SUM((Y),DR_FX(Y,IA,DR_TECH)) = DR_FLH(IA,DR_TECH) / 8760;
$ifi not %timeaggr%==yes IDR_RATE(IA,DR_TECH,S,T)$(SUM((Y),DR_FX(Y,IA,DR_TECH)) AND DR_RATE_T(T,DR_TECH)) = DR_RATE_T(T,DR_TECH) * DR_FLH(IA,DR_TECH) / 8760;
$ifi not %timeaggr%==yes IDR_RATE(IA,DR_TECH,S,T)$(SUM((Y),DR_FX(Y,IA,DR_TECH)) AND DR_RATE_S(IA,DR_TECH,S)) = DR_RATE_S(IA,DR_TECH,S) * DR_FLH(IA,DR_TECH) / 8760;
$ifi not %timeaggr%==yes IDR_RATE(IA,DR_TECH,S,T)$(SUM((Y),DR_FX(Y,IA,DR_TECH)) AND DR_RATE_T(T,DR_TECH) AND DR_RATE_S(IA,DR_TECH,S)) = DR_RATE_S(IA,DR_TECH,S)*DR_RATE_T(T,DR_TECH) * DR_FLH(IA,DR_TECH) / 8760;

$ifi %timeaggr%==yes IDR_RATE(IA,DR_TECH,SSS,TTT)$SUM((Y),DR_FX(Y,IA,DR_TECH)) = DR_FLH(IA,DR_TECH) / 8760;
$ifi %timeaggr%==yes IDR_RATE(IA,DR_TECH,SSS,TTT)$(SUM((Y),DR_FX(Y,IA,DR_TECH)) AND DR_RATE_T(TTT,DR_TECH)) = DR_RATE_T(TTT,DR_TECH) * DR_FLH(IA,DR_TECH) / 8760;
$ifi %timeaggr%==yes IDR_RATE(IA,DR_TECH,SSS,TTT)$(SUM((Y),DR_FX(Y,IA,DR_TECH)) AND DR_RATE_S(IA,DR_TECH,SSS)) = DR_RATE_S(IA,DR_TECH,SSS) * DR_FLH(IA,DR_TECH) / 8760;
$ifi %timeaggr%==yes IDR_RATE(IA,DR_TECH,SSS,TTT)$(SUM((Y),DR_FX(Y,IA,DR_TECH)) AND DR_RATE_T(TTT,DR_TECH) AND DR_RATE_S(IA,DR_TECH,SSS)) = DR_RATE_S(IA,DR_TECH,SSS)*DR_RATE_T(TTT,DR_TECH) * DR_FLH(IA,DR_TECH) / 8760;
