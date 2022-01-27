
$ifi not %BALANCINGRUNPURPOSE%==TSOREDISPATCH $goto NO_TSOREDISPATCH
POSITIVE VARIABLE VGE_T_DOWN(Y,AAA,G,S,T) 'Down Dispatch of the commited electricity dispatch with respect to previous runs';
POSITIVE VARIABLE VGH_T_DOWN(Y,AAA,G,S,T) 'Down Dispatch of the commited heat dispatch with respect to previous runs';
$ifi %HYDROGEN%==yes  POSITIVE VARIABLE VGH2_T_DOWN(Y,AAA,G,S,T) 'Down Dispatch of the commited hydrogen dispatch with respect to previous runs';
$ifi %HYDROGEN%==yes  POSITIVE VARIABLE VGBIOMETHANE_T_DOWN(Y,AAA,G,S,T) 'Down Dispatch of the commited biomethane dispatch with respect to previous runs';

POSITIVE VARIABLE VGE_T_DOWN_FORCED(Y,AAA,G,S,T) 'Down Dispatch of the commited electricity dispatch forced with respect to previous runs';
POSITIVE VARIABLE VGH_T_DOWN_FORCED(Y,AAA,G,S,T) 'Down Dispatch of the commited heat dispatch forced with respect to previous runs';
$label NO_TSOREDISPATCH
