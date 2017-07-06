* File uc_vars.inc
* Unit commitment add-on to Balmorel.
* Implemented by Hans Ravn 2006-2007.
* Revised and enhanced by Lars Bregnsbæk 2011.

* Variables

*==================================================================================================================================================

INTEGER  VARIABLE  VUCON(AAA,G,S,T)    'Unit commitment (0,1) on electricity generation, existing units';
INTEGER  VARIABLE  VUCONN(AAA,G,S,T)   'Unit commitment (0,1) on electricity generation, new units';

POSITIVE VARIABLE  VUCU(AAA,G,S,T)     'Start up, Unit commitment (0,1) on electricity generation, existing units';
POSITIVE VARIABLE  VUCD(AAA,G,S,T)     'Unit commitment Shutdown (0,1) on electricity generation, existing units';
POSITIVE VARIABLE  VUCUN(AAA,G,S,T)    'Start up, Unit commitment (0,1) on electricity generation, new units';
POSITIVE VARIABLE  VUCDN(AAA,G,S,T)    'Unit commitment Shutdown (0,1) on electricity generation, new units';


