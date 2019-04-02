

$ifi not %SCENARIO3OR4%==YES $goto label_scenario3OR4_ISETDECDEF_END
*** 1 TAXES
** 1.1 Set tax levels to zero
*Fuel taxes:
TAX_F_EL(YYY,CCC,GGG)  = 0;
TAX_F_HEAT(YYY,CCC,GGG) = 0;
TAX_F(YYY,CCC,GGG)      = 0;
TAX_G_HEAT(YYY,CCC,GGG)  = 0;
TAX_G_EL(YYY,CCC,GGG)    = 0;
TAX_F_HEAT(YYY,CCC,GGG) = 0;


* Taxes on end-consumption:
TAX_DE(CCC,'PII')       = 0;
*TAX_DH(CCC,'PII')       = 0;                        !! TAX_DH not in use
TAX_DE(CCC,DEUSER)       = 0;            !! $ifi  %SCENARIO4%==YES
*$ifi  %SCENARIO4%==YES    TAX_DH(CCC,DEUSER)       = 0;


$ifi %SCENARIO4%==YES $goto label_SCENARIO4_GR_FC_SC4_end      !! loading the file for scenario 3
EXECUTE_LOAD  "../../simex/GR_FC_1.gdx" TAX_GETOH ;
$LABEL label_SCENARIO4_GR_FC_SC4_end

$ifi not %SCENARIO4%==YES $goto label_SCENARIO4_GR_FC_SC4_end2    !! loading the file for scenario 4
EXECUTE_LOAD  "../../simex/GR_FC_2.gdx" TAX_GETOH ;
$LABEL label_SCENARIO4_GR_FC_SC4_end2




$LABEL label_scenario3OR4_ISETDECDEF_END
