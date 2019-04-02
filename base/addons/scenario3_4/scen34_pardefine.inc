*** Manipulation to inputdata for Flex4RES scenario 3 and 4
** Scenario 3 only affects large consumers wheras scenario 4 affects also small consumers



********* SCENARIO 3 or 4 ***********
$ifi not %SCENARIO3OR4%==YES $goto label_scenario3OR4_DATAMANIPULATION_END
** Assumed full load hours for p2h technologies:
*PARAMETER P2HFLH(TECH_GROUP) /BOILER 278, HEATPUMP 2245/;
SCALAR SP2HFLH /0.845/;

*** 2 Grid tariffs

** 2.1 Set grid tariff levels to zero

* for Balmorel technologies:
GR_PRICE_TECH(CCC,GRDATASET) =0;

* for power intensive industry
GR_PRICE_USER(CCC,'PII',GRDATASET) = 0;
GR_PRICE_USER(CCC,DEUSER,GRDATASET) = 0;   !!$ifi  %SCENARIO4%==YES


** 2.2 Congestion pricing

* Set the grid tariff according to desired level
GR_PRICE_TECH(C,'GRDDCY') = 00;
GR_PRICE_USER(C,'PII','GRDDCY') = 00;


** 2.3 capacity pricing (included for P2H only since its the only consumer group have endogenous investments in the model)



$ifi %SCENARIO4%==YES $goto label_SCENARIO4_GR_FC_SC4_end      !! loading the file for scenario 3
EXECUTE_LOAD  "../../simex/GR_FC_1.gdx" GR_GETOH_VAR_T GR_GETOH_FX GR_GETOH_TOTAL  GR_GETOH_PRICE ;
$LABEL label_SCENARIO4_GR_FC_SC4_end

$ifi not %SCENARIO4%==YES $goto label_SCENARIO4_GR_FC_SC4_end2      !! loading the file for scenario 3
EXECUTE_LOAD  "../../simex/GR_FC_2.gdx" GR_GETOH_VAR_T GR_GETOH_FX GR_GETOH_TOTAL  GR_GETOH_PRICE ;
$LABEL label_SCENARIO4_GR_FC_SC4_end2



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
GR_PRICE_TECH(C,'GRDSUBS') = MAX( (GR_GETOH_PRICE('2030',C)/1000
                             - GR_GETOH_CAPY('2030',C) * GR_PRICE_TECH(C,'GRDDCY') /  GR_GETOH_FX('2030')    !! it can be discussed how to reduce GRDSUBS when also having congestion pricing
),0);


EXECUTE_UNLOAD '../output/scen34.gdx'  IGR_TIME_Y, DE_VAR_T_PEAK, GR_PRICE_TECH, GR_GETOH_CAPY;

$ifi  %SCENARIO4%==YES    GR_PRICE_USER(C,DEUSER,'GRDDCY') = 50;

$LABEL label_scenario3OR4_DATAMANIPULATION_END


