
$ifi %IND%==yes $goto skip_netinvested
$ifi not %USENETINVESTED%==yes NETINVESTED(IA,IAI,STEPP)$(AINDN(IA,IAI) and VIHFV.up(IA,IAI,STEPP) and (VIHFV.up(IA,IAI,STEPP) < inf)) = VIHFV.l(IA,IAI,STEPP)/VIHFV.up(IA,IAI,STEPP);
$ifi not %USENETINVESTED%==yes DISPLAY  NETINVESTED;
$ifi not %USENETINVESTED%==yes execute_unload '../printout/NETINVESTED.gdx', NETINVESTED;
$label skip_netinvested