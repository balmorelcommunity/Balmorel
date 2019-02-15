* UC Translated to BB4 by Juan Gea Bermúdez 2018.

* Variables

*==================================================================================================================================================

INTEGER  VARIABLE  VUCON(Y,AAA,G,S,T)    'Unit commitment (0,1) on electricity generation';

POSITIVE VARIABLE  VUCU(Y,AAA,G,S,T)     'Start up, Unit commitment (0,1) on electricity generation';
POSITIVE VARIABLE  VUCD(Y,AAA,G,S,T)     'Unit commitment Shutdown (0,1) on electricity generation';


$ifi not %STEPWISE_RAMPING_UC%==ramp_const_cost $goto STEPWISERAMPING_END
POSITIVE VARIABLE   VRAMPING_UP(Y,AAA,G,RAMPING_RATE,S,T)   'Hourly ramping up for each technology and ramping rate';
POSITIVE VARIABLE   VRAMPING_DOWN(Y,AAA,G,RAMPING_RATE,S,T) 'Hourly Ramping down for each technology and ramping rate';
$label  STEPWISERAMPING_END

