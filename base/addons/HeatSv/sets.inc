* File sets.inc.
* To be used with add-on HeatSv to the Balmorel model.

SET HeatSv_P   'Building types' /*%semislash%*/;
$if     EXIST '../data/HeatSv_P.inc' $INCLUDE         '../data/HeatSv_P.inc'
$if not EXIST '../data/HeatSv_P.inc' $INCLUDE '../../base/addons/HeatSv/test data/HeatSv_P.inc';
/*%semislash%*/;

SET HeatSv_ELM 'Building elements' /*%semislash%*/;
$if     EXIST '../data/HeatSv_ELM.inc' $INCLUDE         '../data/HeatSv_ELM.inc'
$if not EXIST '../data/HeatSv_ELM.inc' $INCLUDE '../../base/addons/HeatSv/test data/HeatSv_ELM.inc';
/*%semislash%*/;

PARAMETER HeatSv_HSC(YYY,HeatSv_P,HeatSv_ELM)	'Cost for renovation of different building elements in different building types, EUR/m2floor' /*%semislash%*/;
$if     EXIST '../data/HeatSv_HSC.inc' $INCLUDE         '../data/HeatSv_HSC.inc'
$if not EXIST '../data/HeatSv_HSC.inc' $INCLUDE '../../base/addons/HeatSv/test data/HeatSv_HSC.inc';
/*%semislash%*/;

PARAMETER HeatSv_SHP(HeatSv_P,HeatSv_ELM)	'Yearly saving potentials in different building types due to renovation of different elements, kWh/m2floor' /*%semislash%*/;
$if     EXIST '../data/HeatSv_SHP.inc' $INCLUDE         '../data/HeatSv_SHP.inc'
$if not EXIST '../data/HeatSv_SHP.inc' $INCLUDE '../../base/addons/HeatSv/test data/HeatSv_SHP.inc';
/*%semislash%*/;

PARAMETER HeatSv_VAR_T(AAA,SSS,TTT)	'Variation in heat saving' /*%semislash%*/;
$if     EXIST '../data/HeatSv_VAR_T.inc' $INCLUDE         '../data/HeatSv_VAR_T.inc'
$if not EXIST '../data/HeatSv_VAR_T.inc' $INCLUDE '../../base/addons/HeatSv/test data/HeatSv_VAR_T.inc';
/*%semislash%*/;

PARAMETER HeatSv_AR(AAA,HeatSv_P)	'Areas of different building types in Balmorel heating areas, m2'  /*%semislash%*/;
$if     EXIST '../data/HeatSv_AR.inc' $INCLUDE         '../data/HeatSv_AR.inc'
$if not EXIST '../data/HeatSv_AR.inc' $INCLUDE '../../base/addons/HeatSv/test data/HeatSv_AR.inc';
/*%semislash%*/;

PARAMETER HeatSv_AREL(HeatSv_P,HeatSv_ELM)	'Area relations, element area/total area'  /*%semislash%*/;
$if     EXIST '../data/HeatSv_AREL.inc' $INCLUDE         '../data/HeatSv_AREL.inc'
$if not EXIST '../data/HeatSv_AREL.inc' $INCLUDE '../../base/addons/HeatSv/test data/HeatSv_AREL.inc';
/*%semislash%*/;

PARAMETER HeatSv_REN(HeatSv_P)	'Maximum renovation rate, % of existing buildings stock'  /*%semislash%*/;
$if     EXIST '../data/HeatSv_REN.inc' $INCLUDE         '../data/HeatSv_REN.inc'
$if not EXIST '../data/HeatSv_REN.inc' $INCLUDE '../../base/addons/HeatSv/test data/HeatSv_REN.inc';


PARAMETER HeatSv_SHELM(HeatSv_P,HeatSv_ELM)	'Maximum share of buildings that can get renovated a specific building element'  /*%semislash%*/;
$if     EXIST '../data/HeatSv_SHELM.inc' $INCLUDE         '../data/HeatSv_SHELM.inc'
$if not EXIST '../data/HeatSv_SHELM.inc' $INCLUDE '../../base/addons/HeatSv/test data/HeatSv_SHELM.inc';

/*%semislash%*/;

PARAMETER HeatSv_LIFE(HeatSv_ELM)	'Lifetime of heat saving measures in buildings'  /*%semislash%*/;
$if     EXIST '../data/HeatSv_LIFE.inc' $INCLUDE         '../data/HeatSv_LIFE.inc'
$if not EXIST '../data/HeatSv_LIFE.inc' $INCLUDE '../../base/addons/HeatSv/test data/HeatSv_LIFE.inc';
/*%semislash%*/;

SCALAR HeatSv_DR 'discount rate';
$if     EXIST '../data/HeatSv_DR.inc' $INCLUDE         '../data/HeatSv_DR.inc'
$if not EXIST '../data/HeatSv_DR.inc' $INCLUDE '../../base/addons/HeatSv/test data/HeatSv_DR.inc';
/*%semislash%*/;

PARAMETER HeatSv_SAR(YYY,AAA,HeatSv_P,HeatSv_ELM)	'Amount of renovated m2 by bb2 in Y in each area of each type of building';

PARAMETER HeatSv_SARCUM(AAA,HeatSv_P,HeatSv_ELM)	'Cumulative amount of renovated m2 in each area of each type of building'