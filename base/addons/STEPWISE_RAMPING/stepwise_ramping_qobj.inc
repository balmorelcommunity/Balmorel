* Stepwise ramping Juan Gea Bermúdez 2018.

* The following expressions are added to the objective function,
* (inside the multiplication by IOF0000001):


+ SUM((IA,IGUC,IS3,T)$IAGK_HASORPOT(Y,IA,IGUC), IHOURSINST(IS3,T)*(
                 +SUM(RAMPING_RATE,VRAMPING_DOWN(Y,IA,IGUC,RAMPING_RATE,IS3,T)*IRAMPING_G_COSTS_DOWN(IGUC,RAMPING_RATE)+VRAMPING_UP(Y,IA,IGUC,RAMPING_RATE,IS3,T)*IRAMPING_G_COSTS_UP(IGUC,RAMPING_RATE))  !! ramping cost
))


