* Seasonal COP addon - Juan Gea Bermúdez 2020.

PARAMETER COP(AAA,GGG)       'Annual average of COP for heat pumps'    %semislash%
$if     EXIST '../data/SEASONALCOP_COP.inc' $INCLUDE         '../data/SEASONALCOP_COP.inc';
$if not EXIST '../data/SEASONALCOP_COP.inc' $INCLUDE '../../base/data/SEASONALCOP_COP.inc';
%semislash%;
*------------- Any COP additions for addon to be placed here: ----------------
$include "../../base/addons/_hooks/copadditions.inc"

PARAMETER COP_VAR_T(AAA,GGG,SSS,TTT)      'Variation in COP of heat pumps'    %semislash%
$if     EXIST '../data/SEASONALCOP_COP_VAR_T.inc' $INCLUDE         '../data/SEASONALCOP_COP_VAR_T.inc';
$if not EXIST '../data/SEASONALCOP_COP_VAR_T.inc' $INCLUDE '../../base/data/SEASONALCOP_COP_VAR_T.inc';
%semislash%;
*------------- Any COP_VAR_T additions for addon to be placed here: ----------------
$include "../../base/addons/_hooks/cop_var_tadditions.inc"

