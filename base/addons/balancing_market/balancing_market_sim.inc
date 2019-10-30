*Balancing market introduced by Juan Gea-Bermudez and Polyneikis Kanellas

*Fixing commitment status of technologies whose minimum on or off times is bigger than the weight of S
$ifi not %SOLVETYPE%==MIP $ifi %UnitComm%==yes VUCON.FX(IY411,IA,IGUC,IS3,T)$(GKFX(IY411,IA,IGUC) AND (NOT SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGUC))) AND ((GDATA(IGUC,'GDUCUTMIN') GT WEIGHT_S(IS3)) OR ((GDATA(IGUC,'GDUCDTMIN') GT WEIGHT_S(IS3))))) = UCON(IY411,IA,IGUC,IS3,T);
$ifi     %SOLVETYPE%==MIP $ifi %UnitComm%==yes VUCON.FX(IY411,IA,IGUC,IS3,T)$(GKFX(IY411,IA,IGUC) AND (NOT SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGUC))) AND ((GDATA(IGUC,'GDUCUTMIN') GT WEIGHT_S(IS3)) OR ((GDATA(IGUC,'GDUCDTMIN') GT WEIGHT_S(IS3))))) = ROUND(UCON(IY411,IA,IGUC,IS3,T));


