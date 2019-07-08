* Decommissioning introduced by Juan Gea Bermúdez 2018.

* Variables

*==================================================================================================================================================


$ifi not %LIFETIME_DECOM_ENDO_G%==yes $ifi not %ECONOMIC_DECOM_ENDO_G%==yes  $goto DECOMMISSIONING_ENDOGENOUS_GENERATION

POSITIVE VARIABLE VDECOM_ENDO(Y,AAA,G)                "Decommissioned capacity of endogenous technologies(MW)";
POSITIVE VARIABLE VDECOM_ENDO_ACCUM(Y,AAA,G)          "Accumulated Decommissioned capacity of endogenous technologies(MW)";
POSITIVE VARIABLE VDECOM_ENDO_BACK(Y,AAA,G)           "Deccommissioned capacity of endogenous technologies brought back to the energy system (MW)";

$label  DECOMMISSIONING_ENDOGENOUS_GENERATION

POSITIVE VARIABLE VDECOM_EXO(Y,AAA,G)                "Decommissioned capacity of exogenous technologies(MW)";
POSITIVE VARIABLE VDECOM_EXO_ACCUM(Y,AAA,G)          "Accumulated Decommissioned capacity of exogenous technologies(MW)";
POSITIVE VARIABLE VDECOM_EXO_BACK(Y,AAA,G)           "Deccommissioned capacity of exogenous technologies brought back to the energy system (MW)";


