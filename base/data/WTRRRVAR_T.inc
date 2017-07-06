* of the hydro generation from hydro run-of-river generation technologies for each area.
* PARAMETER WTRRRVAR_T_2 contains the description of the variation over (S,T)
* Units: (none).
*TABLE WTRRRVAR_T(AAA,SSS,TTT)  'Variation of generation of hydro run-of-river'


* hans__   DENNE ER HENTET I VARLOW.inc'
TABLE WTRRRVAR_T(AAA,SSS,TTT)  'Variation of generation of hydro run-of-river'
                          T001
DK_E_Urban.S01             1
;

WTRRRVAR_T(AAA,SSS,TTT)$WTRRRFLH(AAA) = 1 ;





*hans__x:
*LARS: Gjort følgende betinget af FSS
$ifi %FSS%==yes $INCLUDE '../../base/data/HYFXRWNWD.inc';
$ifi %FSS%==yes TABLE HYRRRNWD8(AAA,SSS,TTT,YHYDRONWD) 'Hourly unregulated hydro production in Norway (MWh)'
$ifi %FSS%==yes                          NORM        DRY         WET
$ifi %FSS%==yes $INCLUDE '../../base/data/var2001/NO-HYRR01.inc'
$ifi %FSS%==yes ;

$ifi %FSS%==yes HYRRRNWD8('SE_N_Rural',SSS,T,YHYDRONWD) = 0.6 * HYRRRNWD8('NO_S_Rural',SSS,T,YHYDRONWD);
* PEME: add hoc code to avoid infeasibilities in week one in dry years

$ifi %FSS%==yes HYRRRNWD8('SE_N_Rural',SSS,T,'DRY') = 0.5 * HYRRRNWD8('SE_N_Rural',SSS,T,'DRY');
$ifi %FSS%==yes HYRRRNWD8('NO_N_Rural',SSS,T,'DRY') = 0.5 * HYRRRNWD8('NO_N_Rural',SSS,T,'DRY');
$ifi %FSS%==yes HYRRRNWD8('NO_S_Rural',SSS,T,'DRY') = 0.5 * HYRRRNWD8('NO_S_Rural',SSS,T,'DRY');

$ifi %FSS%==yes HYRRRNWD8('SE_S_Rural',SSS,T,YHYDRONWD)=61/(13068+3304+61)*HYRRRNWD8('SE_N_Rural',SSS,T,YHYDRONWD);
$ifi %FSS%==yes HYRRRNWD8('SE_M_Rural',SSS,T,YHYDRONWD)=3304/(13068+3304+61)*HYRRRNWD8('SE_N_Rural',SSS,T,YHYDRONWD);
$ifi %FSS%==yes HYRRRNWD8('SE_N_Rural',SSS,T,YHYDRONWD)=13068/(13068+3304+61)*HYRRRNWD8('SE_N_Rural',SSS,T,YHYDRONWD);
*HYRRRNWD8('NO_N_Rural',SSS,T,YHYDRONWD)=5024/(18472+4102+5024)*HYRRRNWD8('NO_S_Rural',SSS,T,YHYDRONWD);
*HYRRRNWD8('NO_M_Rural',SSS,T,YHYDRONWD)=4102/(18472+4102+5024)*HYRRRNWD8('NO_S_Rural',SSS,T,YHYDRONWD);
*HYRRRNWD8('NO_S_Rural',SSS,T,YHYDRONWD)=18472/(18472+4102+5024)*HYRRRNWD8('NO_S_Rural',SSS,T,YHYDRONWD);

$ifi %FSS%==yes HYRRRNWD8('NO_N_Rural',SSS,T,YHYDRONWD)=0.075*HYRRRNWD8('NO_S_Rural',SSS,T,YHYDRONWD);
$ifi %FSS%==yes HYRRRNWD8('NO_M_Rural',SSS,T,YHYDRONWD)=0.193*HYRRRNWD8('NO_S_Rural',SSS,T,YHYDRONWD);
$ifi %FSS%==yes HYRRRNWD8('NO_S_Rural',SSS,T,YHYDRONWD)=0.732*HYRRRNWD8('NO_S_Rural',SSS,T,YHYDRONWD);


$ifi %FSS%==yes PARAMETER HYRRRNWD(AAA,S,T,YHYDRONWD);

* hans__x: Flyttet til  fra  balbase13:
$ifi %FSS%==yes  HYRRRNWD(IA,S,T,YHYDRONWD) = HYRRRNWD8(IA,S,T,YHYDRONWD);

