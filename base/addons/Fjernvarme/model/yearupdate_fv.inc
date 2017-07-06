* Alternative: $ (VIHFV.l(AFV,STEPP) = VIHFV.up(AFV,STEPP));
* Do something else with: $ (VIHFV.l(AFV,STEPP) > VIHFV.l(AFV,STEPP);
* Perhaps better alternative: VIHFV.u(AFV,STEPP) = VIHFV.u(AFV,STEPP) - VIHFV.l(AFV,STEPP);
* - but still make sure that the extra investment is utilized in balance eqn (could be looking for VIHF's with ub = 0)

$ifi not %IND%==yes VIHFV.up(IA,IAI,STEPP)$AINDN(IA,IAI) = DHFV(IAI,STEPP);
$ifi not %IND%==yes VIHFV.lo(IA,IAI,STEPP)$AINDN(IA,IAI) = VIHFV.l(IA,IAI,STEPP);

$ifi %USENETINVESTED%==yes VIHFV.fx(IA,IAI,STEPP)$AINDN(IA,IAI) = max(0,(YVALUE(Y)-2012)/(2025-2012)*VIHFV.up(IA,IAI,STEPP)*NETINVESTED(IA,IAI,STEPP)*DH(Y,IAI)/DH('2025',IAI));