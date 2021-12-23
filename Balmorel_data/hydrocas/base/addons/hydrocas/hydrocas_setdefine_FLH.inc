SET HYDROCAS_CCC(CCC) 'countries with hydro cascading' /NORWAY,SWEDEN/;
SET HSEG 'segment of hydropower capacity' /1*4/;


$onmulti
$if     EXIST '../data/HYDROCAS_GGG_FLH.inc' $INCLUDE         '../data/HYDROCAS_GGG_FLH.inc';
$if not EXIST '../data/HYDROCAS_GGG_FLH.inc' $INCLUDE '../../base/data/HYDROCAS_GGG_FLH.inc';

$if     EXIST '../data/HYDROCAS_G_FLH.inc' $INCLUDE         '../data/HYDROCAS_G_FLH.inc';
$if not EXIST '../data/HYDROCAS_G_FLH.inc' $INCLUDE '../../base/data/HYDROCAS_G_FLH.inc';

$offmulti

ACRONYMS RIVER, RIVER_STORAGE, FLEX, PURE, MED_FLEX,PUMPED_STORAGE, PUMP, ROR;

ACRONYMS POWERPLANT, STORAGE;
