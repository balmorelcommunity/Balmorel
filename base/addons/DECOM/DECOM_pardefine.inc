* Decommissioning introduced by Juan Gea Bermúdez 2018.


$ifi not %LIFETIME_DECOM_ENDO_G%==yes  $goto LIFETIME_DECOMMISSIONING_ENDOGENOUS_GENERATION

*Decommissioning definition has to be included after all AGKN parameters have been defined
PARAMETER DECOM_G(YYY,YYY,GGG)    'DECOMMISIONING YEAR OF ENDOGENOUS GENERATION INVESTMENTS' %semislash%
$if     EXIST '../data/DECOM_G.inc' $INCLUDE      '../data/DECOM_G.inc';
$if not EXIST '../data/DECOM_G.inc' $INCLUDE '../../base/data/DECOM_G.inc';
%semislash%;

$label  LIFETIME_DECOMMISSIONING_ENDOGENOUS_GENERATION
