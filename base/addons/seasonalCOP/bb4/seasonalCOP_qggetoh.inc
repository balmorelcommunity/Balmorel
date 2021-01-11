* Seasonal COP addon - Juan Gea Bermúdez 2020.

*Removing previous calculation of fuel consumption
-(VGH_T(IY411,IA,IGETOH,IS3,T) / GDATA(IGETOH,'GDFE'))$IHEATPUMP(IGETOH)

*Including new calculation of fuel consumption
+(VGH_T(IY411,IA,IGETOH,IS3,T)/(COP(IA,IGETOH)*COP_VAR_T(IA,IGETOH,IS3,T)/ICOPAVG(IA,IGETOH)))$IHEATPUMP(IGETOH)
