* installed capacity of the load - the internal parameter includes also the adoption rate
PARAMETER IDR_FX(Y,AAA,DR_TECH);
IDR_FX(Y,IA,DR_TECH) = DR_FX(Y,IA,DR_TECH)  * DR_ADOPTIONRATE(DR_TECH,Y);
$ifi %import_results%==YES $ifi %ADDTECHDEV%==yes  IDR_FX(Y,IA,DR_TECH) = (DR_FX(Y,IA,DR_TECH)  * DR_ADOPTIONRATE(DR_TECH,Y))$(NOT DR_TECH_INVEST(DR_TECH)) + DR_ACCUMNET(Y,IA,DR_TECH)$DR_TECH_INVEST(DR_TECH) ;

PARAMETER ANNUITYDR(DR_TECH) 'Annuity factor for investments in DR technologies';
ANNUITYDR(DR_TECH)$DR_TECH_INVEST(DR_TECH) = 1/((1-(1+DR_DATA(DR_TECH,'DRINTERESTRATE'))**(-DR_DATA(DR_TECH,'DRLIFETIME')))/0.06);



* IDR_RATE - parameter for the usage profiles for demand response technologies
PARAMETER IDR_RATE(AAA,DR_TECH,S,T) 'Hourly rating/availability for downregulation of demand response technologies';

*Initializing all IDR_RATE alternatives
IDR_RATE(IA,DR_TECH,S,T)$SUM((Y),DR_FX(Y,IA,DR_TECH)) = DR_FLH(IA,DR_TECH) / 8760;
IDR_RATE(IA,DR_TECH,S,T)$(SUM((Y),DR_FX(Y,IA,DR_TECH)) AND DR_RATE_T(T,DR_TECH)) = DR_RATE_T(T,DR_TECH) * DR_FLH(IA,DR_TECH) / 8760;
IDR_RATE(IA,DR_TECH,S,T)$(SUM((Y),DR_FX(Y,IA,DR_TECH)) AND DR_RATE_S(IA,DR_TECH,S)) = DR_RATE_S(IA,DR_TECH,S) * DR_FLH(IA,DR_TECH) / 8760;
IDR_RATE(IA,DR_TECH,S,T)$(SUM((Y),DR_FX(Y,IA,DR_TECH)) AND DR_RATE_T(T,DR_TECH) AND DR_RATE_S(IA,DR_TECH,S)) = DR_RATE_S(IA,DR_TECH,S)*DR_RATE_T(T,DR_TECH) * DR_FLH(IA,DR_TECH) / 8760;


