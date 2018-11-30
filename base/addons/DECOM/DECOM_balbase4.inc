* Decommissioning introduced by Juan Gea Bermúdez 2018.

* Additional equations in model definition:

$ifi not %LIFETIME_DECOM_ENDO_G%==yes $ifi not %ECONOMIC_DECOM_ENDO_G%==yes  $goto DECOMMISSIONING_ENDOGENOUS_GENERATION

QDECOM_ENDO_LIM
QDECOM_ENDO_ACCUM
$ifi %LIFETIME_DECOM_ENDO_G%==yes QDECOM_ENDO_ACCUM_REST

$label  DECOMMISSIONING_ENDOGENOUS_GENERATION
