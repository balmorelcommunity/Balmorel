*Balancing market introduced by Juan Gea-Bermudez and Polyneikis Kanellas

*Adding tertiary reserves
$ifi not %ADDENERGYDISPATCH%==yes $goto No_energydispatch
-(
   (
   ASTERRES_T(IY411,IA,IGUC,IS3,T)
   )*(1+(1/GDATA(IGUC,'GDCB'))$IGBPR(IGUC))/(1$((NOT IGESTO(IGUC)) AND (NOT IGESTOS(IGUC)) AND (NOT IGHSTO(IGUC)) AND (NOT IGHSTOS(IGUC))) + GDATA(IGUC,'GDSTOHUNLD')$(IGESTO(IGUC) OR IGESTOS(IGUC) OR IGHSTO(IGUC) OR IGHSTOS(IGUC)))
         /(GDATA(IGUC,'GDFE')*(1$(NOT GEFFRATE(IA,IGUC))+GEFFRATE(IA,IGUC)))
 )$IASG(IGUC)

$label No_energydispatch
