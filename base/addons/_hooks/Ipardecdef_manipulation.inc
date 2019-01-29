

$ifi not %SCENARIO3OR4%==YES $goto label_scenario3OR4_ISETDECDEF_END
*** 1 TAXES
** 1.1 Set tax levels to zero
*Fuel taxes:
TAX_F_EL(YYY,CCC,GGG)  = 0;
TAX_F_HEAT(YYY,CCC,GGG) = 0;
TAX_F(YYY,CCC,GGG)      = 0;
TAX_G_HEAT(YYY,CCC,GGG)  = 0;
TAX_G_EL(YYY,CCC,GGG)    = 0;

* Taxes on end-consumption:
TAX_DE(CCC,'PII')       = 0;
*TAX_DH(CCC,'PII')       = 0;                        !! TAX_DH not in use
$ifi  %SCENARIO4%==YES    TAX_DE(CCC,DEUSER)       = 0;
*$ifi  %SCENARIO4%==YES    TAX_DH(CCC,DEUSER)       = 0;


*** Congestion pricing
* calculate sum of demand profile
PARAMETER IDE_SUMSSSTTT(RRR,DEUSER);     IDE_SUMSSSTTT(IR,DEUSER)= SUM((SSS,TTT), DE_VAR_T(IR,DEUSER,SSS,TTT));

* identify peak consumption (excluding P2H, DR and EV, Storage, H2)
PARAMETER DE_VAR_T_PEAK(Y,RRR);          DE_VAR_T_PEAK(Y,IR) = SUM(DEUSER, SMAX((SSS,TTT), DE_VAR_T(IR,DEUSER,SSS,TTT) * DE(Y,IR,DEUSER) / IDE_SUMSSSTTT(IR,DEUSER)));

SET IGR_TIME_Y(YYY,GRDATASET,RRR,SSS,TTT);
** identify hours over the 90% consumption threshold
IGR_TIME_Y(Y,'GRDDCTOU',IR,SSS,TTT) = YES$(SUM(DEUSER, DE_VAR_T(IR,DEUSER,SSS,TTT) * DE(Y,IR,DEUSER) / IDE_SUMSSSTTT(IR,DEUSER)) ge 50 * DE_VAR_T_PEAK(Y,IR));     

$LABEL label_scenario3OR4_ISETDECDEF_END
