* File mkcompare.inc.
* This file is an extension to the welfare calculation module for the Balmorel model.
* Created by Jens Hauch and Thomas E. Pedersen, COWI A/S (DK).
* Adapted for Balmorel version 2.10, 2.13 by Hans Ravn.
* Extended to for the gas add-on by Lars Bregnbæk, X-mas 2006.


*===============================================================================
*                Overview
*===============================================================================

* Intermediate parameter values are printed to files for later use.
* The parameter values were calculated in gascompprint3.inc, as ..,..,.., etc.
* They are here saved under names ...00, ...00, ...00, etc.

*===============================================================================
*                Overview end
*===============================================================================


$libinclude gams2prm residualcosts residualcosts00
$libinclude gams2prm othercosts othercosts00
