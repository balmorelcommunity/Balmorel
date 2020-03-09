* Seasonal COP addon - Juan Gea Bermúdez 2020.

*Removing previous calculation
-(
     (
* units under shut down have an expanded gradient
         GDATA(IGUC,'GDUCGMIN')*VUCD(IY411,IA,IGUC,S,T)
* up gradient of units on at t excluding units under shutdown
        + GDATA(IGUC,'GDUCRAMPD')*VUCON(IY411,IA,IGUC,S,T)
* scale unit input capacity
     )*(GDATA(IGUC,'GDUCUNITSIZE')*(1+(1/GDATA(IGUC,'GDCB'))$IGBPR(IGUC))/(1$((NOT IGESTO(IGUC)) AND (NOT IGESTOS(IGUC)) AND (NOT IGHSTO(IGUC)) AND (NOT IGHSTOS(IGUC))) + GDATA(IGUC,'GDSTOHUNLD')$(IGESTO(IGUC) OR IGESTOS(IGUC) OR IGHSTO(IGUC) OR IGHSTOS(IGUC)))
       /(GDATA(IGUC,'GDFE')*(1$(NOT GEFFRATE(IA,IGUC))+GEFFRATE(IA,IGUC))))*CHRONOHOUR(S,T)
)$IHEATPUMP(IGUC)

*Including new calculation
+(
     (
* units under shut down have an expanded gradient
         GDATA(IGUC,'GDUCGMIN')*VUCD(IY411,IA,IGUC,S,T)
* up gradient of units on at t excluding units under shutdown
        + GDATA(IGUC,'GDUCRAMPD')*VUCON(IY411,IA,IGUC,S,T)
* scale unit input capacity
     )*(GDATA(IGUC,'GDUCUNITSIZE')/(COP(IA,IGUC)*COP_VAR_T(IA,IGUC,S,T)/ICOPAVG(IA,IGUC))*(1$(NOT GEFFRATE(IA,IGUC))+GEFFRATE(IA,IGUC)))*CHRONOHOUR(S,T)

)$IHEATPUMP(IGUC)


