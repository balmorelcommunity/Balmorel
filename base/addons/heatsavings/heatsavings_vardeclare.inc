POSITIVE VARIABLE HEATSV_VHS(YYY,AAA,HEATSV_STEPS) 'Heat savings in an area, MW';
POSITIVE VARIABLE HEATSV_VHS_T(YYY,AAA,HEATSV_STEPS,SSS,TTT) 'Heat savings in an area per timestep, MW';
POSITIVE VARIABLE HEATSV_VHSACCUMNET(YYY,AAA,HEATSV_STEPS) 'Accumulated heat savings in an area, MW';
POSITIVE VARIABLE HEATSV_VHSPERCENT(YYY,AAA,HEATSV_STEPS) 'Percentage of heat demand covered by heat savings, %';


$ifi not %INDHEATSAV%==yes $goto endINDHEAT
POSITIVE VARIABLE HEATSV_VINDHEATHS(YYY,INDHEAT_AAA,HEATSV_STEPS) 'Heat savings in an individual heating area, MW';
POSITIVE VARIABLE HEATSV_VINDHEATHS(YYY,INDHEAT_AAA,HEATSV_STEPS,SSS,TTT) 'Heat savings in an individual heating area per timestep, MW';
POSITIVE VARIABLE HEATSV_VINDHEATHSACCUMNET(YYY,INDHEAT_AAA,HEATSV_STEPS) 'Accumulated heat savings in an area of individual heating, MW';
POSITIVE VARIABLE HEATSV_VINDHEATHSPERCENT(YYY,INDHEAT_AAA,HEATSV_STEPS) 'Percentage of heat demand covered by heat savings for individual heating, %';
$label endINDHEAT
