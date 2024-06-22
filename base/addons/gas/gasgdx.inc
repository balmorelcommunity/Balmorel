

$ifi %bb3%==yes $goto outbb3
$ifi %STORAGEALLOCATIONS%==yes execute_unload '../../base/addons/gas/GSFXW.gdx', GSFXW;
$ifi %STORAGEALLOCATIONS%==yes execute_unload '../../base/addons/gas/SC_Y.gdx',SC_Y;
$ifi %CAPACITYALLOCATIONS%==yes execute_unload '../../base/addons/gas/reserved_capacity.gdx', TC_EX_Y, TC_EX_M, TC_EN_Y, TC_EN_M;

$ifi %MAKEINVEST%==yes execute_unload '../../base/addons/gas/gasinvest.gdx',SUPACC,EXPACC ,INJACC ,EXTACC ,STOREACC, DEVACC;

$goto end_out

$label outbb3

$label end_out