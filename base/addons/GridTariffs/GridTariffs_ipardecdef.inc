PARAMETERS
IGR_PRICE_DEUSER(YYY,RRR,DEUSER,GRDATASET) 'Grid rent rates for consumer groups'
IGR_PRICE_TECH(YYY,RRR,GRDATASET) 'Grid rent rates for balmorel technologies'
IGR_MONTHSINSIM2(MMM) 'months in simulation'
IGR_MONTHSINSIM 'months in simulation'

*** When BB3 is again working:
IGRGETOHLEVEL(YYY,AAA,SSS,TTT)  'Max level of demand charge calculated in BB4'           !! TODO   hooks does not now allow for inter model transfer of data. This parameter should be calculated from VGETOH_CAP.L from BB4 simulation and carried over to BB3.
IGRGETOHLEVEL_1(YYY,AAA,MMM)  'Max level of demand charge calculated in BB4 - for export to BB3'
IGRGETOHLEVEL_2(YYY,AAA,MMM)  'Max level of demand charge calculated in BB4 - for export to BB3'
IGRGETOHLEVEL_Y(YYY,AAA)  'Max level of demand charge calculated in BB4 - for export to BB3'
;

IGR_PRICE_DEUSER(Y,IR,DEUSER,GRDATASET) = SUM(C$CCCRRR(C,IR), GR_PRICE_USER(C,DEUSER,GRDATASET));
IGR_PRICE_TECH(Y,IR,GRDATASET) = SUM(C$CCCRRR(C,IR), GR_PRICE_TECH(C,GRDATASET));

IGR_MONTHSINSIM2(MMM) = SUM((S,T),ISSSTTTMMM(S,T,MMM));
IGR_MONTHSINSIM =SUM(MMM, IGR_MONTHSINSIM2(MMM));
;



$ifi %RollingSeasons%==YES execute_load  "../../simex/IGRGETOHLEVEL.gdx", IGRGETOHLEVEL_1, IGRGETOHLEVEL_2, IGRGETOHLEVEL_Y;

$ifi %RollingSeasons%==YES IGRGETOHLEVEL(Y,IA,S,T)$(SUM(IR$RRRAAA(IR,IA), IGR_PRICE_TECH(Y,IR,'GRDDCW')) OR SUM(IR$RRRAAA(IR,IA), IGR_PRICE_TECH(Y,IR,'GRDDCS')) OR SUM(IR$RRRAAA(IR,IA), IGR_PRICE_TECH(Y,IR,'GRDDC2'))) =   SUM(MMM, IGRGETOHLEVEL_1(Y,IA,MMM) * ISSSTTTMMM(S,T,MMM));
$ifi %RollingSeasons%==YES IGRGETOHLEVEL(Y,IA,S,T)$SUM(IR$RRRAAA(IR,IA), IGR_PRICE_TECH(Y,IR,'GRDDCTOU')) =   SUM(MMM, IGRGETOHLEVEL_2(Y,IA,MMM) * ISSSTTTMMM(S,T,MMM));
$ifi %RollingSeasons%==YES IGRGETOHLEVEL(Y,IA,S,T)$SUM(IR$RRRAAA(IR,IA), IGR_PRICE_TECH(Y,IR,'GRDDCY')) = IGRGETOHLEVEL_Y(Y,IA);