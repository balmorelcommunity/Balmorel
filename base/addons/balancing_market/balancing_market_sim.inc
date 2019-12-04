*Balancing market introduced by Juan Gea-Bermudez and Polyneikis Kanellas

*Fixing commitment status from energy dispatch run
$ifi not %SOLVETYPE%==MIP $ifi %UnitComm%==yes VUCON.FX(IY411,IA,IGUC,IS3,T)$((GDATA(IGUC,'GDUCDTMIN') GT WEIGHT_S(IS3) OR GDATA(IGUC,'GDUCUTMIN') GT WEIGHT_S(IS3)) AND GKFX(IY411,IA,IGUC) AND (NOT SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGUC)))) = UCON(IY411,IA,IGUC,IS3,T);
$ifi     %SOLVETYPE%==MIP $ifi %UnitComm%==yes VUCON.FX(IY411,IA,IGUC,IS3,T)$((GDATA(IGUC,'GDUCDTMIN') GT WEIGHT_S(IS3) OR GDATA(IGUC,'GDUCUTMIN') GT WEIGHT_S(IS3)) AND GKFX(IY411,IA,IGUC) AND (NOT SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGUC)))) = ROUND(UCON(IY411,IA,IGUC,IS3,T));


*Limiting maximum back-up power from previous results to estimate additional power reserves need in the market
VUCON.UP(Y,IA,G)$(GDATA(G,'GDTECHGROUP') EQ BACKUP_ELECTRICITY)=SMAX((S,T),GE_T(Y,IA,G,S,T));





