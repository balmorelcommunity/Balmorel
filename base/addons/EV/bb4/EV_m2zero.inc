* When using VQdebug variables, the only interesting thins if whether the value (the level, .L) is zero or not.
* Therefore reset the marginal value (.M) to zero.


$ifi %EV_infeas%==yes VQEV_BEV_BEBALANCE.M(IY411,IR,S,T,IPLUSMINUS)= 0;
$ifi %EV_infeas%==yes VQEV_PHEV_BEBALANCE.M(IY411,IR,S,T,IPLUSMINUS)= 0;
