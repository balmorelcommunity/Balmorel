* Seasonal COP addon - Juan Gea Bermúdez 2020.

*Removing previous calculation of fuel consumption maximum limit
-(
* Fuel consumption at minimum load is defined by Fmin = [ Emin (1-F0) +Emax*F0 ]/FE
  (
* Emin
   VUCON(IY411,IA,IGUC,IS3,T)*GDATA(IGUC,'GDUCGMIN')*GDATA(IGUC,'GDUCUNITSIZE')*(1-GDATA(IGUC,'GDUCF0'))
* Emax
   +VUCON(IY411,IA,IGUC,IS3,T)*GDATA(IGUC,'GDUCUNITSIZE')*GDATA(IGUC,'GDUCF0')
* FE
   )*(1+(1/GDATA(IGUC,'GDCB'))$IGBPR(IGUC))/(1$((NOT IGESTO(IGUC)) AND (NOT IGESTOS(IGUC)) AND (NOT IGHSTO(IGUC)) AND (NOT IGHSTOS(IGUC))) + GDATA(IGUC,'GDSTOHUNLD')$(IGESTO(IGUC) OR IGESTOS(IGUC) OR IGHSTO(IGUC) OR IGHSTOS(IGUC)))
       /(GDATA(IGUC,'GDFE')*(1$(NOT GEFFRATE(IA,IGUC))+GEFFRATE(IA,IGUC)))
)$IHEATPUMP(IGUC)

*Including new calculation of fuel consumption maximum limit
+(
* Fuel consumption at minimum load is defined by Fmin = [ Emin (1-F0) +Emax*F0 ]/FE
  (
* Emin
   VUCON(IY411,IA,IGUC,IS3,T)*GDATA(IGUC,'GDUCGMIN')*GDATA(IGUC,'GDUCUNITSIZE')*(1-GDATA(IGUC,'GDUCF0'))
* Emax
   +VUCON(IY411,IA,IGUC,IS3,T)*GDATA(IGUC,'GDUCUNITSIZE')*GDATA(IGUC,'GDUCF0')
* FE
   )/(COP(IA,IGUC)*COP_VAR_T(IA,IGUC,IS3,T)/ICOPAVG(IA,IGUC)*(1$(NOT GEFFRATE(IA,IGUC))+GEFFRATE(IA,IGUC)))
)$IHEATPUMP(IGUC)



