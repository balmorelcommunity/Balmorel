SETS
IGPOWERPLANT(G) 'Hydropower modules with power production capacity'
IGPUMP(G) 'Pumped storage hydropower plants'
IGHYSTORAGE(G) 'Hydropower reservoirs without own production capacity'
IGHYDISPATCH(G) 'Hydropower that is dispatchable'
IYHYDR(Y) 'Year used as base for inflow calculation'
IAGK_HYDROPOWER(AAA,G) 'areas and technologies with cascading'
DAY 'day of week' /1*7/
IDAY(DAY)
IDAYT(DAY,TTT) 'day of week'
;


IGPUMP(G) = YES$(HDATA(G,'HDTYPE') EQ PUMP);
IGHYSTORAGE(G) =   YES$(HDATA(G,'HDTYPE') EQ STORAGE) ;
IGPOWERPLANT(G) = YES$((GDATA(G,'GDTYPE') EQ GHYRS) AND HDATA(G,'HDTYPE') EQ POWERPLANT);

IYHYDR(Y)$(YVALUE(Y) EQ 2020) = YES;
IAGK_HYDROPOWER(IA,G)$(SUM(HYDROCAS_CCC, ICA(HYDROCAS_CCC,IA)) AND (IGHYRS(G) OR IGHYRR(G))) = YES$(SUM(Y, GKFX(Y,IA,G)) OR AGKN(IA,G));
IGHYDISPATCH(G) = YES$SUM(IA$IAGK_HYDROPOWER(IA,G), HDATA(G,'HDRESERVOIR') OR SUM(IGALIAS$HYDROPOWER_TRANSFER(IA,IGALIAS,G), 1));


execute_unload '../../simex/IAGK.gdx', IAGK_HYDROPOWER;

IDAYT('1',TTT)$(ORD(TTT) < 25) = YES;
IDAYT('2',TTT)$(ORD(TTT) > 24 AND ORD(TTT) <49) = YES;
IDAYT('3',TTT)$(ORD(TTT) > 48 AND ORD(TTT) <73) = YES;
IDAYT('4',TTT)$(ORD(TTT) > 72 AND ORD(TTT) <97) = YES;
IDAYT('5',TTT)$(ORD(TTT) > 96 AND ORD(TTT) <121) = YES;
IDAYT('6',TTT)$(ORD(TTT) > 120 AND ORD(TTT) <145) = YES;
IDAYT('7',TTT)$(ORD(TTT) > 144) = YES;

IDAY(DAY) = YES$SUM(T,IDAYT(DAY,T));


