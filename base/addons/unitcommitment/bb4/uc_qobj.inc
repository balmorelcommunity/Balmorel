* UC Translated to BB4 by Juan Gea Bermúdez 2018.

* The following expressions are added to the objective function,
* (inside the multiplication by IOF0000001):


+ SUM((IA,IGUC,IS3,T)$IAGK_HASORPOT(Y,IA,IGUC), IHOURSINST(IS3,T)*(
                                                 VUCU(Y,IA,IGUC,IS3,T)*GDATA(IGUC,'GDUCUCOST')*GDATA(IGUC,'GDUCUNITSIZE')  !! startup cost
                                                 +VUCD(Y,IA,IGUC,IS3,T)*GDATA(IGUC,'GDUCDCOST')*GDATA(IGUC,'GDUCUNITSIZE')  !! shutdown cost
                                                 +VUCON(Y,IA,IGUC,IS3,T)*GDATA(IGUC,'GDUCCOST0')*GDATA(IGUC,'GDUCUNITSIZE') !! fixed hourly cost
$ifi %STEPWISERAMPING%==yes                      +SUM(RAMPING_RATE,V_RAMPING_DOWN(Y,IA,IGUC,RAMPING_RATE,IS3,T)*IRAMPING_G_COSTS_DOWN(IGUC,RAMPING_RATE)+V_RAMPING_UP(Y,IA,IGUC,RAMPING_RATE,IS3,T)*IRAMPING_G_COSTS_UP(IGUC,RAMPING_RATE))  !! ramping cost
))


