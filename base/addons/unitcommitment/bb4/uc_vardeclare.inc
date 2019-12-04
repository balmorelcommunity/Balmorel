* UC Translated to BB4 by Juan Gea Bermúdez 2018.

* Variables

*==================================================================================================================================================

$ifi %SOLVETYPE%==MIP          INTEGER  VARIABLE    VUCON(Y,AAA,G,S,T)    'Unit commitment (0,1) on electricity generation';
$ifi not %SOLVETYPE%==MIP      POSITIVE VARIABLE    VUCON(Y,AAA,G,S,T)    'Unit commitment (0,1) on electricity generation';
$ifi %SOLVETYPE%==MIP          INTEGER  VARIABLE    VUCON_STOLOAD(Y,AAA,G,S,T)    'Unit commitment (0,1) on electricity generation for storage loading';
$ifi not %SOLVETYPE%==MIP      POSITIVE VARIABLE    VUCON_STOLOAD(Y,AAA,G,S,T)    'Unit commitment (0,1) on electricity generation for storage loading';

POSITIVE VARIABLE  VUCU(Y,AAA,G,S,T)     'Start up, Unit commitment (0,1) on electricity generation';
POSITIVE VARIABLE  VUCD(Y,AAA,G,S,T)     'Unit commitment Shutdown (0,1) on electricity generation';

POSITIVE VARIABLE  VUCU_STOLOAD(Y,AAA,G,S,T)     'Start up, Unit commitment (0,1) on electricity generation for storage loading';
POSITIVE VARIABLE  VUCD_STOLOAD(Y,AAA,G,S,T)     'Unit commitment Shutdown (0,1) on electricity generation for storage loading';


$ifi not %STEPWISE_RAMPING_UC%==ramp_const_cost $goto STEPWISERAMPING_END
POSITIVE VARIABLE   VRAMPING_UP(Y,AAA,G,RAMPING_RATE,S,T)   'Hourly ramping up for each technology and ramping rate';
POSITIVE VARIABLE   VRAMPING_DOWN(Y,AAA,G,RAMPING_RATE,S,T) 'Hourly Ramping down for each technology and ramping rate';
$label  STEPWISERAMPING_END


$ifi not %PLANNED_MAINTENANCE%==yes $goto NO_PLANNED_MAINTENANCE
$ifi %SOLVETYPE%==MIP        INTEGER  VARIABLE  VUCONMAINT(Y,AAA,G,S)    'Unit commitment maintenance (0,1) on electricity generation';
$ifi not %SOLVETYPE%==MIP    POSITIVE  VARIABLE  VUCONMAINT(Y,AAA,G,S)    'Unit commitment maintenance (0,1) on electricity generation';

POSITIVE VARIABLE  VUCUMAINT(Y,AAA,G,S)     'Start up maintenance, Unit commitment (0,1) on  electricity generation';
POSITIVE VARIABLE  VUCDMAINT(Y,AAA,G,S)     'Unit commitment Shutdown maintenance (0,1) on maintenance electricity generation';


$label NO_PLANNED_MAINTENANCE
