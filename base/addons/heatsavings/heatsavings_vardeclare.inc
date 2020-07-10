POSITIVE VARIABLE HEATSV_VHS(YYY,AAA,HEATSV_STEPS) 'Heat savings in an area, MWh/year';
POSITIVE VARIABLE HEATSV_VHS_T(YYY,AAA,SSS,TTT) 'Heat savings in an area per timestep, MWh';
POSITIVE VARIABLE HEATSV_VHSACCUMNET(YYY,AAA,HEATSV_STEPS) 'Accumulated heat savings in an area, MWh/year';
POSITIVE VARIABLE HEATSV_VHSPERCENT(YYY,AAA) 'Ratio of heat demand covered by heat savings';

$ifi not %INDHEATSAV%==yes $goto endINDHEAT
POSITIVE VARIABLE HEATSV_VINDHEATHS(YYY,INDHEAT_AAA,HEATSV_STEPS) 'Heat savings in an individual heating area, MWh/year';
POSITIVE VARIABLE HEATSV_VINDHEATHS_T(YYY,INDHEAT_AAA,INDHEAT_GROUP,SSS,TTT) 'Heat savings in an individual heating area per timestep, MWh';
POSITIVE VARIABLE HEATSV_VINDHEATHSGROUP(YYY,INDHEAT_AAA,INDHEAT_GROUP,HEATSV_STEPS) 'Heat savings in an area and technology group of individual heating, MWh/year';
POSITIVE VARIABLE HEATSV_VINDHEATHSACCUMNET(YYY,INDHEAT_AAA,HEATSV_STEPS) 'Accumulated heat savings in an area of individual heating, MWh/year';
POSITIVE VARIABLE HEATSV_VINDHEATHSPERCENT(YYY,INDHEAT_AAA,INDHEAT_GROUP) 'Ratio of heat demand covered by heat savings for individual heating, %';
$label endINDHEAT
