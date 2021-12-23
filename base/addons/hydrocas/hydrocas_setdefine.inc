SET HDATASET  ;
SET HYDROCAS_CCC(CCC) 'countries with hydro cascading';
SET HSEG 'segment of hydropower capacity';
SET WYYY 'Weather year';
SET IWY(WYYY) 'Weather year in simulation';

$onmulti
$if     EXIST '../data/HD_SETS.inc' $INCLUDE         '../data/HD_SETS.inc';
$if not EXIST '../data/HD_SETS.inc' $INCLUDE '../../base/data/HD_SETS.inc';

$offmulti

ACRONYMS RIVER, RIVER_STORAGE, FLEX, PURE, MED_FLEX,PUMPED_STORAGE, PUMP, ROR;

ACRONYMS POWERPLANT, STORAGE;


IWY(WYYY) = YES$(WYYY.VAL EQ %hydroyear%);