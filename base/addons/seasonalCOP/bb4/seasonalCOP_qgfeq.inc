* Seasonal COP addon - Juan Gea Berm�dez 2020.

*Removing previous calculation of fuel consumption
-(GDATA(G,'GDCV')*VGH_T(IY411,IA,G,IS3,T)/(GDATA(G,'GDFE')*(1$(NOT GEFFRATE(IA,G))+GEFFRATE(IA,G))))$IHEATPUMP(G)

*Including new calculation of fuel consumption
+(VGH_T(IY411,IA,G,IS3,T)/(COP(IA,G)*COP_VAR_T(IA,G,IS3,T)/ICOPAVG(IA,G)*(1$(NOT GEFFRATE(IA,G))+GEFFRATE(IA,G))))$IHEATPUMP(G)