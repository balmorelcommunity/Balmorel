$ifi %SCENARIO3OR4%==YES $goto label_TAX_postsolve_SCEN34_END

$ifi %SCENARIO2%==YES $goto label_SCENARIO1_GR_FC_SC1_end             !! saving the file for scenario 3
EXECUTE_UNLOAD  "../../simex/TAX_FC_1.gdx"
TAX_F
TAX_F_EL
TAX_F_HEAT
TAX_G_EL
TAX_G_HEAT
$ifi %TAXES%==YES TAX_GETOH
;
$LABEL label_SCENARIO1_GR_FC_SC1_end

$ifi %SCENARIO1%==YES $goto label_SCENARIO2_GR_FC_SC2_end              !! saving the file for scenario 4
EXECUTE_UNLOAD  "../../simex/TAX_FC_2.gdx"
TAX_F
TAX_F_EL
TAX_F_HEAT
TAX_G_EL
TAX_G_HEAT
$ifi %TAXES%==YES TAX_GETOH
;
$LABEL label_SCENARIO2_GR_FC_SC2_end

$LABEL label_TAX_postsolve_SCEN34_END


$ifi %SCENARIO4%==YES $goto label_SCENARIO4_GR_FC_SC4_end         !! loading the file for scenario 3
$ifi %SCENARIO3OR4%==YES  EXECUTE_LOAD "../../simex/TAX_FC_1.gdx"
TAX_F
TAX_F_EL
TAX_F_HEAT
TAX_G_EL
TAX_G_HEAT;
$LABEL label_SCENARIO4_GR_FC_SC4_end

$ifi not %SCENARIO4%==YES $goto label_SCENARIO4_GR_FC_SC4_end2    !! loading the file for scenario 4
$ifi %SCENARIO3OR4%==YES  EXECUTE_LOAD "../../simex/TAX_FC_2.gdx"
TAX_F
TAX_F_EL
TAX_F_HEAT
TAX_G_EL
TAX_G_HEAT;
$LABEL label_SCENARIO4_GR_FC_SC4_end2


EXECUTE_UNLOAD "%relpathoutput%temp/TAX_OUT.gdx", TAX_F, TAX_F_EL, TAX_F_HEAT, TAX_G_EL, TAX_G_HEAT;
