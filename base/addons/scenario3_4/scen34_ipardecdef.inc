

$ifi not %SCENARIO3OR4%==YES $goto label_scenario3OR4_ISETDECDEF_END
*** 1 TAXES
** 1.1 Set tax levels to zero
*Fuel taxes:
TAX_F_EL(YYY,CCC,GGG)$(YYY.val > 2020)  = 0;
TAX_F_HEAT(YYY,CCC,GGG)$(YYY.val > 2020) = 0;
TAX_F(YYY,CCC,GGG)$(YYY.val > 2020)      = 0;
TAX_G_HEAT(YYY,CCC,GGG)$(YYY.val > 2020)  = 0;
TAX_G_EL(YYY,CCC,GGG)$(YYY.val > 2020)    = 0;
TAX_F_HEAT(YYY,CCC,GGG)$(YYY.val > 2020) = 0;


* Taxes on end-consumption:
*TAX_DE(CCC,'PII')       = 0;
*TAX_DH(CCC,DHUSER)       = 0;                        !! TAX_DH not in use
TAX_DE(CCC,DEUSER)       = 0;


** loading the file for scenario 3
*$ifi %SCENARIO3%==YES EXECUTE_LOAD  "../../simex/GR_FC_1.gdx" TAX_GETOH ;

** loading the file for scenario 4
*$ifi %SCENARIO4%==YES EXECUTE_LOAD  "../../simex/GR_FC_2.gdx" TAX_GETOH ;


*** 2 Grid tariffs

** 2.1 Set grid tariff levels to zero

* for Balmorel technologies:
IGR_PRICE_TECH(Y,IR,GRDATASET)$(Y.val > 2020) =0;

* for power intensive industry
*IGR_PRICE_DEUSER(Y,IR,'PII',GRDATASET)$(Y.val > 2020) = 0;
IGR_PRICE_DEUSER(Y,IR,DEUSER,GRDATASET)$(Y.val > 2020) = 0;


** 2.2 Congestion pricing

* Set the grid tariff according to desired level
IGR_PRICE_TECH(Y,IR,'GRDDCY')$(Y.val > 2020) = 00;
IGR_PRICE_DEUSER(Y,IR,'PII','GRDDCY')$(Y.val > 2020) = 00;


** 2.3 capacity pricing (included for P2H only since its the only consumer group have endogenous investments in the model)

** loading the file for scenario 3
$ifi %SCENARIO3%==YES EXECUTE_LOAD  "../../simex/GR_FC_1.gdx" GR_GETOH_VAR_T GR_GETOH_FX GR_GETOH_TOTAL  GR_GETOH_PRICE ;

** loading the file for scenario 4
$ifi %SCENARIO4%==YES EXECUTE_LOAD  "../../simex/GR_FC_2.gdx" GR_GETOH_VAR_T GR_GETOH_FX GR_GETOH_TOTAL  GR_GETOH_PRICE ;


*** Congestion pricing
* calculate sum of demand profile
PARAMETER IDE_SUMSSSTTT(RRR,DEUSER);     IDE_SUMSSSTTT(IR,DEUSER)= SUM((SSS,TTT), DE_VAR_T(IR,DEUSER,SSS,TTT));

* identify peak consumption (excluding P2H, DR and EV, Storage, H2)
PARAMETER DE_VAR_T_PEAK(Y,RRR);
DE_VAR_T_PEAK(Y,IR) = SMAX((SSS,TTT),
$ifi %EV%==YES                        (EV_BEV_Dumb(Y,SSS,TTT,IR)+EV_PHEV_Dumb(Y,SSS,TTT,IR)*(1/EV_PEFF(Y)))
                                     + SUM(DEUSER,     DE_VAR_T(IR,DEUSER,SSS,TTT) * DE(Y,IR,DEUSER) / IDE_SUMSSSTTT(IR,DEUSER))             );


SET IGR_TIME_Y(YYY,GRDATASET,RRR,SSS,TTT) 'hours where consumption is above thershold defined in GR_SCALAR_THRSHOLD';
** identify hours over the 90% consumption threshold
IGR_TIME_Y(Y,'GRDDCY',IR,SSS,TTT) = YES$(
$ifi %EV%==YES                           (EV_BEV_Dumb(Y,SSS,TTT,IR)+EV_PHEV_Dumb(Y,SSS,TTT,IR)*(1/EV_PEFF(Y)))
                                         + SUM(DEUSER, DE_VAR_T(IR,DEUSER,SSS,TTT) * DE(Y,IR,DEUSER) / IDE_SUMSSSTTT(IR,DEUSER))
                                         GE GR_SCALAR_THRESHOLD * DE_VAR_T_PEAK(Y,IR));

**
GR_GETOH_CAPY(Y,C) = SMAX((SSS,TTT),  GR_GETOH_VAR_T(Y,SSS,TTT)$SUM(IR$CCCRRR(C,IR), IGR_TIME_Y(Y,'GRDDCY',IR,SSS,TTT)));
IGR_PRICE_TECH(Y,IR,'GRDSUBS')$(Y.val > 2020) = MAX( (SUM(C$CCCRRR(C,IR), GR_GETOH_PRICE('2030',C))/1000
                             - SUM(C$CCCRRR(C,IR), GR_GETOH_CAPY('2030',C)) * IGR_PRICE_TECH(Y,IR,'GRDDCY') /  GR_GETOH_FX('2030')    !! it can be discussed how to reduce GRDSUBS when also having congestion pricing
),0);


EXECUTE_UNLOAD '../output/scen34.gdx'  IGR_TIME_Y, DE_VAR_T_PEAK, GR_PRICE_TECH, GR_GETOH_CAPY;


$LABEL label_scenario3OR4_ISETDECDEF_END
