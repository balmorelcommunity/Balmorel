SETS
$ifi not %HYDROCAS%==YES DAY 'day of week' /1*7/
IDAY(DAY)
IDAYT(DAY,TTT) 'day of week'
;


IDAYT('1',TTT)$(ORD(TTT) < 25) = YES;
IDAYT('2',TTT)$(ORD(TTT) > 24 AND ORD(TTT) <49) = YES;
IDAYT('3',TTT)$(ORD(TTT) > 48 AND ORD(TTT) <73) = YES;
IDAYT('4',TTT)$(ORD(TTT) > 72 AND ORD(TTT) <97) = YES;
IDAYT('5',TTT)$(ORD(TTT) > 96 AND ORD(TTT) <121) = YES;
IDAYT('6',TTT)$(ORD(TTT) > 120 AND ORD(TTT) <145) = YES;
IDAYT('7',TTT)$(ORD(TTT) > 144) = YES;

IDAY(DAY) = YES$SUM(T,IDAYT(DAY,T));



set minload_day 'days' /1*7/ ;
set minload_techs(GGG) 'technologies with minload requirements';
set minload_techs_day(GGG) 'technologies with minload requirements';



minload_techs(G)$(GDATA(G,'GDTECHGROUP') = STEAMTURBINE_SUBCRITICAL AND GDATA(G,'GDFUEL') = COAL)  =  YES;
minload_techs(G)$(GDATA(G,'GDTECHGROUP') = COMBINEDCYCLE)  = YES;
minload_techs(G)$(GDATA(G,'GDTECHGROUP') = STEAMTURBINE_SUBCRITICAL AND GDATA(G,'GDFUEL') = LIGNITE)  = YES;


SET iminload_day(minload_day,TTT);
iminload_day('1',TTT)$(ord(TTT) GE 7 AND ord(TTT) LE 22) = YES;
iminload_day('2',TTT)$(ord(TTT) GE 31 AND ord(TTT) LE 46) = YES;
iminload_day('3',TTT)$(ord(TTT) GE 55 AND ord(TTT) LE 70) = YES;
iminload_day('4',TTT)$(ord(TTT) GE 79 AND ord(TTT) LE 94) = YES;
iminload_day('5',TTT)$(ord(TTT) GE 103 AND ord(TTT) LE 118) = YES;
iminload_day('6',TTT)$(ord(TTT) GE 127 AND ord(TTT) LE 142) = YES;
iminload_day('7',TTT)$(ord(TTT) GE 151 AND ord(TTT) LE 166) = YES;





