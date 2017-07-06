* File prt4-bb2.inc.
* This file is part of the Balmorel model.

* For specifying printing of results for simulations with endogeneous investments.

* File last time modified 27-09-2002 (rus), 15-05-2003 (hr), 05-08-2003 (sns), 20110508(hr)



* -----------------------------------------------------------------------------
* Contents:

* Each of the following files provides a specific set of output to a
* specific file, cf. the file print2.inc.
* The printing of a specific output may be inactivated by commenting out
* the relevant file below and activated by removing the outcommenting.

*------------------------------------------------------------------------------
* Print for current simulation year:
*------------------------------------------------------------------------------

* Calibration
$include "../../base/output/printout/printinc/dfp_calib.inc";


* Key figures
$include "../../base/output/printout/printinc/bal_1.inc";
$include "../../base/output/printout/printinc/bal_2.inc";
$ifi %GAS%==yes $include "../../base/addons/gas/gasbal_1.inc";


* Electricity generation
$ include "../../base/output/printout/printinc/eg_cy.inc";
$ include "../../base/output/printout/printinc/eg_gfcy.inc";
$ include "../../base/output/printout/printinc/ego_cy.inc";
$ include "../../base/output/printout/printinc/egn_cy.inc";
$ include "../../base/output/printout/printinc/ezgo_cy.inc";
$ include "../../base/output/printout/printinc/ezgn_cy.inc";
$ include "../../base/output/printout/printinc/eg_gat.inc";

* Electricity storage:
$ include "../../base/output/printout/printinc/esto_at.inc";
$ include "../../base/output/printout/printinc/esto2_at.inc";


* Heat generation
$ include "../../base/output/printout/printinc/hg_cy.inc";
$ include "../../base/output/printout/printinc/hgo_cy.inc";
$ include "../../base/output/printout/printinc/hgn_cy.inc";

* Heat storage
$ include "../../base/output/printout/printinc/hsto_at.inc";
$ include "../../base/output/printout/printinc/hsto2_at.inc";

* Import - Export
$ include "../../base/output/printout/printinc/ex_ry.inc";
$ include "../../base/output/printout/printinc/exk_ry.inc";
$ include "../../base/output/printout/printinc/xbottle.inc";

* Fuel consumption
$ include "../../base/output/printout/printinc/ehf_gcy.inc";
$ include "../../base/output/printout/printinc/ehf_gry.inc";
$ include "../../base/output/printout/printinc/ehf_gay.inc";
$ include "../../base/output/printout/printinc/ehf_fcy.inc";
$ include "../../base/output/printout/printinc/f_fcy.inc";
*$ include "../../base/output/printout/printinc/ehf_gfcy.inc";  removed 201105xx.


* Prices
$ include "../../base/output/printout/printinc/ep_ry.inc";
$ include "../../base/output/printout/printinc/ep_rt.inc";
$ include "../../base/output/printout/printinc/epnxt_rt.inc";

$ include "../../base/output/printout/printinc/hp_ay.inc";



* Emissions
$ include "../../base/output/printout/printinc/mco2_cy.inc";
$ include "../../base/output/printout/printinc/mso2_cy.inc";
$ include "../../base/output/printout/printinc/mnox_cy.inc";


* Addons:
* Print files for addons may be included here, or in bb123.sim (matter of style ...).



