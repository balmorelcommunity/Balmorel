* Additional heat production from technoligies in these areas are to be added to the heat balance equation

+(SUM(IAE$AINDN(IA,IAE), VDHFV(IA,IAE,IS3,T))/(1-DISLOSS_H(IA)) )$(not AIND(IA))
-(SUM(IAE$AINDN(IAE,IA), VDHFV(IAE,IA,IS3,T)) )$AIND(IA)
