

$ifi not %SCENARIO3OR4%==YES $goto label_scenario3OR4_ISETDECDEF_END
*** 1 TAXES
** 1.1 Set tax levels to zero
*Fuel taxes:
*TAX_F_EL(YYY,CCC,GGG)  = 0;
*TAX_F_HEAT(YYY,CCC,GGG) = 0;
*TAX_F(YYY,CCC,GGG)      = 0;
*TAX_G_HEAT(YYY,CCC,GGG)  = 0;
*TAX_G_EL(YYY,CCC,GGG)    = 0;
TAX_F_HEAT(YYY,CCC,IGETOH) = 0;


* Taxes on end-consumption:
TAX_DE(CCC,'PII')       = 0;
*TAX_DH(CCC,'PII')       = 0;                        !! TAX_DH not in use
$ifi  %SCENARIO4%==YES    TAX_DE(CCC,DEUSER)       = 0;
*$ifi  %SCENARIO4%==YES    TAX_DH(CCC,DEUSER)       = 0;



EXECUTE_LOAD  "../../simex/GR_FC.gdx" TAX_GETOH ;







$LABEL label_scenario3OR4_ISETDECDEF_END
