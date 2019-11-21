*Balancing market introduced by Juan Gea-Bermudez and Polyneikis Kanellas

*Fixing commitment status from energy dispatch run
$ifi not %SOLVETYPE%==MIP $ifi %UnitComm%==yes VUCON.FX(IY411,IA,IGUC,IS3,T)$(GKFX(IY411,IA,IGUC) AND (NOT SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGUC)))) = UCON(IY411,IA,IGUC,IS3,T);
$ifi     %SOLVETYPE%==MIP $ifi %UnitComm%==yes VUCON.FX(IY411,IA,IGUC,IS3,T)$(GKFX(IY411,IA,IGUC) AND (NOT SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGUC)))) = ROUND(UCON(IY411,IA,IGUC,IS3,T));

*Introducing reserves from energy dispatch run
$ifi  %ANC_SERV%==yes  VASSECRES_T.FX(IY411,IA,IASG,IS3,T)=ASSECRES_T(IY411,IA,IASG,IS3,T);
$ifi  %ANC_SERV%==yes  VASTERRES_T.FX(IY411,IA,IASG,IS3,T)=ASTERRES_T(IY411,IA,IASG,IS3,T);


