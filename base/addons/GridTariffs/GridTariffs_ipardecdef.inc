PARAMETERS
IGR_PRICE_DEUSER(YYY,RRR,DEUSER,GRDATASET) 'Grid rent rates for consumer groups'
IGR_PRICE_TECH(YYY,RRR,GRDATASET) 'Grid rent rates for balmorel technologies'
IGR_MONTHSINSIM2(MMM) 'months in simulation'
IGR_MONTHSINSIM 'months in simulation'

*** When BB3 is again working:
IGRGETOHLEVEL(AAA,SSS,TTT)  'Max level of demand charge calculated in BB4'           !! TODO   hooks does not now allow for inter model transfer of data. This parameter should be calculated from VGETOH_CAP.L from BB4 simulation and carried over to BB3.

* grid tariff cost calculation for output.
GR_FC_OUTPUT_TECH(YYY,YYY,AAA,GGG)
GR_EC_OUTPUT_TECH(YYY,YYY,AAA,GGG)
GR_DC_OUTPUT_TECH(YYY,YYY,AAA)
GR_EC_OUTPUT_USER(YYY,YYY,RRR,DEUSER)
GR_DC_OUTPUT_USER(YYY,YYY,RRR,DEUSER)


;

IGR_PRICE_DEUSER(Y,IR,DEUSER,GRDATASET) = SUM(C$CCCRRR(C,IR), GR_PRICE_USER(C,DEUSER,GRDATASET));
IGR_PRICE_TECH(Y,IR,GRDATASET) = SUM(C$CCCRRR(C,IR), GR_PRICE_TECH(C,GRDATASET));

IGR_MONTHSINSIM2(MMM) = SUM((S,T),ISSSTTTMMM(S,T,MMM));
IGR_MONTHSINSIM =SUM(MMM, IGR_MONTHSINSIM2(MMM));



