* File uc_qobjadd.inc
* Unit commitment add-on to Balmorel.
* Implemented by Hans Ravn 2006-2007.
* Revised and enhanced by Lars Bregnsbæk 2011.

* The following expressions are added to the objective function,
* (inside the multiplication by IOF0000001):


+ SUM((IA,IGUC,IS3,T)$(IAGK_Y(IA,IGUC)),  VUCU(IA,IGUC,IS3,T)*GDATA(IGUC,'GDUCUCOST')*GDATA(IGUC,'GDUCUNITSIZE')  !! startup cost
                                         +VUCD(IA,IGUC,IS3,T)*GDATA(IGUC,'GDUCDCOST')*GDATA(IGUC,'GDUCUNITSIZE')  !! shutdown cost
                                         +VUCON(IA,IGUC,IS3,T)*GDATA(IGUC,'GDUCCOST0')*GDATA(IGUC,'GDUCUNITSIZE') !! fixed hourly cost
)
+ SUM((IA,IGUC,IS3,T)$(IAGKN(IA,IGUC)),  VUCUN(IA,IGUC,IS3,T)*GDATA(IGUC,'GDUCUCOST')*GDATA(IGUC,'GDUCUNITSIZE')  !! startup cost
                                        +VUCDN(IA,IGUC,IS3,T)*GDATA(IGUC,'GDUCDCOST')*GDATA(IGUC,'GDUCUNITSIZE')  !! shutdown cost
                                        +VUCONN(IA,IGUC,IS3,T)*GDATA(IGUC,'GDUCCOST0')*GDATA(IGUC,'GDUCUNITSIZE') !! fixed hourly cost
)
