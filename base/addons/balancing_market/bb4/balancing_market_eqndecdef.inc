
RUN OTPIMIZATION SEQUENTLY TO SIMULATE DAYAHEAD MARKETS, OR, AT THE SAME TIME WITH REAL TIME MARKET TO OPTIMIZE INVESTMENTS TAKING INTO ACCOUNT BALANCING COSTS

*If I just want to simulate the DAY-AHEAD market, then I make the "real-timeseries" = "day-ahead teimseries". Simple solution :) 


POSITIVE VARIABLE VGE_T_DAYAHEAD 


VOBJ ADDITION


+VGE_T_DAYAHEAD (Y,IA,G,S,T)*COST


QEEQ_DAYAHEAD(Y,IA,G,S,T)

Variable renewable imbalance
SUM(IA$RRRAAA, VGE_T_DAYAHEAD(Y,IA,G,S,T)-VGE_T(Y,IA,G,S,T))

+ADDITIONAL IMPORTS


=E=
+ADDITIONAL EXPORTS
SUM(DEUSER,DE_DAYAHEAD(Y,IR,DEUSER,S,T)-DE(Y,IR,DEUSER,S,T))


Capacity limitation

GKFX + VGKNACCUMNET =G= +VGE_T_DAYAHEAD 

etc


WHAT TO DO WITH CURTAILMENT? Allow or not allow, that is the question? If I allow it, the model could even balance one technology with the imbalance of another one, which theoretically is difficult... but it is a deterministic model so...


TIMESERIES OF DAYAHEAD
CP(S,T)*/(VGKNACCUMNET(Y,IA,G)+GKFX(Y,IA,G))*GKRATE(IA,G)*WIND_VAR_T_DAYAHEAD(IA,G,S,T) =L= +VGE_T_DAYAHEAD (Y,IA,G,S,T))

RAMPING LIMITATIONS OF DAYAHEAD
VGE_T_REALTIME(T+1)  -  VGE_T_REALTIME(T) >= RAMPING LIMITS






