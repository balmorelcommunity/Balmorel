* File prt3-bb1.inc.
* For updating parameters holding results for simulations without endogeneous investments.

* File last time modified 27-09-2002 (rus), 15-05-2003 (hrv), 08-08-2003 (hrv)

* This file is part of the Balmorel model, version 2.10 Alpha (May 2003)


* ------------------------------------------------------------------------------
* Contents:

* This file contains routines for handling of intermediate information that may
* be usefull output.

* ------------------------------------------------------------------------------
* Since the simulation is without endogeneous investments there is no need
* to calculate results for new investments.
* This simplification has not been done (yet), the savings in calculation time
* will be insignificant.
* Presently therefore the file  prt3-bb2.inc  is used:

$include "../../base/output/printout/printinc/prt3-bb2.inc"

* ------------------------------------------------------------------------------