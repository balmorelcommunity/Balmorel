POSITIVE VARIABLE         IS_CO2(Y)        'Impact score of the carrying capacity Climate Change';
POSITIVE VARIABLE         IS_CO2_G(Y,G)    'Impact score of the carrying capacity Climate Change per generator';
POSITIVE VARIABLE         IS_CO2_X(Y)      'Impact score of the carrying capacity Climate Change for trasmission capacity';
POSITIVE VARIABLE         IS_CO2_X_H2(Y)   'Impact score of the carrying capacity Climate Change for H2 transmission capacity';
POSITIVE VARIABLE         IS_CO2_F(Y,FFF)  'Impact score of the carrying capacity Climate Change per fuel';    
POSITIVE VARIABLE         TL_CO2(Y)        'Transgression level of the carrying capacity Climate Change';


POSITIVE VARIABLE         IS_OZONE_DEPLETION(Y)        'Impact score of the carrying capacity ozone depletion';
POSITIVE VARIABLE         IS_OZONE_DEPLETION_G(Y,G)    'Impact score of the carrying capacity ozone depletion per generator';
POSITIVE VARIABLE         IS_OZONE_DEPLETION_X(Y)      'Impact score of the carrying capacity ozone depletion for trasmission capacity';
POSITIVE VARIABLE         IS_OZONE_DEPLETION_X_H2(Y)   'Impact score of the carrying capacity Climate Change for H2 transmission capacity';
POSITIVE VARIABLE         IS_OZONE_DEPLETION_F(Y,FFF)  'Impact score of the carrying capacity ozone depletion per fuel';
*$ifi  %PB_all%==yes $ifi %TL_ALLOWED%==yes         
POSITIVE VARIABLE         TL_OZONE_DEPLETION(Y)        'Transgression level of the carrying capacity ozone depletion';

POSITIVE VARIABLE         IS_LU(Y)        'Impact score of the carrying capacity land use';
POSITIVE VARIABLE         IS_LU_G(Y,G)    'Impact score of the carrying capacity land use per generator';
POSITIVE VARIABLE         IS_LU_X(Y)      'Impact score of the carrying capacity land use for trasmission capacity';
POSITIVE VARIABLE         IS_LU_X_H2(Y)   'Impact score of the carrying capacity Climate Change for H2 transmission capacity';
POSITIVE VARIABLE         IS_LU_F(Y,FFF)  'Impact score of the carrying capacity land use per fuel';
*$ifi  %PB_all%==yes  $ifi %TL_ALLOWED%==yes   
POSITIVE VARIABLE         TL_LU(Y)        'Transgression level of the carrying capacity land use';

POSITIVE VARIABLE         IS_WU(Y)        'Impact score of the carrying capacity water use';
POSITIVE VARIABLE         IS_WU_G(Y,G)    'Impact score of the carrying capacity water use per generator';
POSITIVE VARIABLE         IS_WU_X(Y)      'Impact score of the carrying capacity water use for trasmission capacity';
POSITIVE VARIABLE         IS_WU_X_H2(Y)   'Impact score of the carrying capacity Climate Change for H2 transmission capacity';
POSITIVE VARIABLE         IS_WU_F(Y,FFF)  'Impact score of the carrying capacity water use per fuel';
*$ifi  %PB_all%==yes $ifi %TL_ALLOWED%==yes 
POSITIVE VARIABLE         TL_WU(Y)        'Transgression level of the carrying capacity water use';

POSITIVE VARIABLE         IS_EUTROPHICATION_FRESHWATER(Y)        'Impact score of the carrying capacity eutrophication freshwater';
POSITIVE VARIABLE         IS_EUTROPHICATION_FRESHWATER_G(Y,G)    'Impact score of the carrying capacity eutrophication freshwater per generator';
POSITIVE VARIABLE         IS_EUTROPHICATION_FRESHWATER_X(Y)      'Impact score of the carrying capacity eutrophication freshwater for trasmission capacity';
POSITIVE VARIABLE         IS_EUTROPHICATION_FRESHWATER_X_H2(Y)   'Impact score of the carrying capacity Climate Change for H2 transmission capacity';
POSITIVE VARIABLE         IS_EUTROPHICATION_FRESHWATER_F(Y,FFF)  'Impact score of the carrying capacity eutrophication freshwater per fuel';
*$ifi  %PB_all%==yes $ifi %TL_ALLOWED%==yes 
POSITIVE VARIABLE         TL_EUTROPHICATION_FRESHWATER(Y)        'Transgression level excess of the carrying capacity eutrophication freshwater';


POSITIVE VARIABLE         IS_ECOTOXICITY_FRESHWATER(Y)        'Impact score of the carrying capacity ecotoxicity freshwater';
POSITIVE VARIABLE         IS_ECOTOXICITY_FRESHWATER_G(Y,G)    'Impact score of the carrying capacity ecotoxicity freshwater per generator';
POSITIVE VARIABLE         IS_ECOTOXICITY_FRESHWATER_X(Y)      'Impact score of the carrying capacity ecotoxicity freshwater for trasmission capacity';
POSITIVE VARIABLE         IS_ECOTOXICITY_FRESHWATER_X_H2(Y)   'Impact score of the carrying capacity Climate Change for H2 transmission capacity';
POSITIVE VARIABLE         IS_ECOTOXICITY_FRESHWATER_F(Y,FFF)  'Impact score of the carrying capacity ecotoxicity freshwater per fuel';
*$ifi  %PB_all%==yes $ifi %TL_ALLOWED%==yes 
POSITIVE VARIABLE         TL_ECOTOXICITY_FRESHWATER(Y)        'Transgression level of the carrying capacity ecotoxicity freshwater';

POSITIVE VARIABLE         IS_PM(Y)        'Impact score of the carrying capacity particulate matter';
POSITIVE VARIABLE         IS_PM_G(Y,G)    'Impact score of the carrying capacity particulate matter per generator';
POSITIVE VARIABLE         IS_PM_X(Y)      'Impact score of the carrying capacity particulate matter for trasmission capacity';
POSITIVE VARIABLE         IS_PM_X_H2(Y)   'Impact score of the carrying capacity Climate Change for H2 transmission capacity';
POSITIVE VARIABLE         IS_PM_F(Y,FFF)  'Impact score of the carrying capacity particulate matter per fuel';
*$ifi  %PB_all%==yes $ifi %TL_ALLOWED%==yes 
POSITIVE VARIABLE         TL_PM(Y)        'Transgression level of the carrying capacity particulate matter' ;


POSITIVE VARIABLE         IS_ACIDIFICATION(Y)        'Impact score of the carrying capacity acidification';
POSITIVE VARIABLE         IS_ACIDIFICATION_G(Y,G)    'Impact score of the carrying capacity acidification per generator';
POSITIVE VARIABLE         IS_ACIDIFICATION_X(Y)      'Impact score of the carrying capacity acidification for trasmission capacity';
POSITIVE VARIABLE         IS_ACIDIFICATION_X_H2(Y)   'Impact score of the carrying capacity Climate Change for H2 transmission capacity';
POSITIVE VARIABLE         IS_ACIDIFICATION_F(Y,FFF)  'Impact score of the carrying capacity acidification per fuel';
*$ifi  %PB_all%==yes  $ifi %TL_ALLOWED%==yes 
POSITIVE VARIABLE         TL_ACIDIFICATION(Y)        'Transgression level of the carrying capacity acidification';

POSITIVE VARIABLE         IS_RESOURCE(Y)        'Impact score of the carrying capacity resource use, minerals and metals';
POSITIVE VARIABLE         IS_RESOURCE_G(Y,G)    'Impact score of the carrying capacity resource use, minerals and metals per generator';
POSITIVE VARIABLE         IS_RESOURCE_X(Y)      'Impact score of the carrying capacity resource use, minerals and metals for trasmission capacity';
POSITIVE VARIABLE         IS_RESOURCE_X_H2(Y)   'Impact score of the carrying capacity Climate Change for H2 transmission capacity';
POSITIVE VARIABLE         IS_RESOURCE_F(Y,FFF)  'Impact score of the carrying capacity resource use, minerals and metals per fuel';
*$ifi  %PB_all%==yes $ifi %TL_ALLOWED%==yes 
POSITIVE VARIABLE         TL_RESOURCE(Y)        'Transgression level of the carrying capacity resource use, minerals and metals';
