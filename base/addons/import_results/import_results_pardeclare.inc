
$ifi %ADDSEASONALTRANSPORTDEMAND%==yes PARAMETER TRANSDEMAND_S(YYY,RRR,SSS) 'Transport demand per region, year, and season (MWh)';
$ifi %ADDPEAKTRANSPORTDEMAND%==yes PARAMETER TRANSDEMAND_T_MAX(Y,RRR)   'Maximum power demand (MW) to be used in future runs';


$ifi %EV%==yes PARAMETER   EV_VSOC_BEV(YYY,RRR,SSS,TTT)        'State of charge of the BEV vehicle fleet to be used in future runs';
$ifi %EV%==yes PARAMETER   EV_VSOC_PHEV(YYY,RRR,SSS,TTT)       'State of charge of the PHEV vehicle fleet to be used in future runs';
$ifi %EV%==yes PARAMETER   EV_BEV_NETCHARGING(YYY,RRR,SSS,TTT)        'Net charging of BEV vehicle fleet to be used in future runs';
$ifi %EV%==yes PARAMETER   EV_PHEV_NETCHARGING(YYY,RRR,SSS,TTT)      'Net charging of PHEV vehicle fleet to be used in future runs';

*Unit Commitemnt data
PARAMETER UCON(YYY,AAA,GGG,SSS,TTT)     "Unit commitment (0,1) on electricity generation to be used in future runs";
PARAMETER UCON_STOLOAD(YYY,AAA,GGG,SSS,TTT)     "Unit commitment (0,1) on storage loading to be used in future runs";
PARAMETER UCONMAINT(YYY,AAA,GGG,SSS)    "Unit commitment maintenance (0,1) on electricity generation to be used in future runs";


