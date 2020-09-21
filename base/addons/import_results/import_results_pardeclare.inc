
$ifi %ADDSEASONALTRANSPORTDEMAND%==yes PARAMETER TRANSDEMAND_S(YYY,CCC,SSS) 'Transport demand per country, year, and season (MWh)';
$ifi %ADDPEAKTRANSPORTDEMAND%==yes PARAMETER TRANSDEMAND_T_MAX(Y,RRR)   'Maximum power demand (MW) to be used in future runs';


$ifi %EV%==yes PARAMETER   EV_VSOC_BEV(YYY,RRR,SSS,TTT)        'State of charge of the BEV vehicle fleet to be used in future runs';
$ifi %EV%==yes PARAMETER   EV_VSOC_PHEV(YYY,RRR,SSS,TTT)       'State of charge of the PHEV vehicle fleet to be used in future runs';




