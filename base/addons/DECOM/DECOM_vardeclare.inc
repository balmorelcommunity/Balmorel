* Decommissioning introduced by Juan Gea Bermúdez 2018.

* Variables

*==================================================================================================================================================

$ifi not %LIFETIME_DECOM_ENDO_G%==yes $ifi not %ECONOMIC_DECOM_ENDO_G%==yes  $goto DECOMMISSIONING_ENDOGENOUS_GENERATION

POSITIVE VARIABLE VDECOM_ENDO(YYY,AAA,G)                "Decommissioned capacity of endogenous technologies(MW)";
POSITIVE VARIABLE VDECOM_ENDO_ACCUM(YYY,AAA,G)          "Accumulated Decommissioned capacity of endogenous technologies(MW)";

$label  LIFETIME_DECOMMISSIONING_ENDOGENOUS_GENERATION


*POSITIVE VARIABLE VDECOM_EXO(YYY,AAA,G)                "Decommissioned capacity of exogenous technologies(MW)";
*POSITIVE VARIABLE VDECOM_EXO_ACCUM(YYY,AAA,G)          "Accumulated Decommissioned capacity of exogenous technologies(MW)";
