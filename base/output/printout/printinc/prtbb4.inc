* File prtbb4.inc.
* This file is part of the Balmorel model.

* For specifying printing of results for simulations with endogeneous investments.

* File last time modified 20150430(Weiming)



* -----------------------------------------------------------------------------
* Contents:

* Each of the following files provides a specific set of output to a
* specific file, cf. the file print2.inc.
* The printing of a specific output may be inactivated by commenting out
* the relevant file below and activated by removing the outcommenting.

* This file is for BB4 only:
$ifi not %BB4%==yes $goto endofprtbb4


* Skip the remaining part of the file if the model did not solve properly:

$ifi %BB4%==yes IF(BALBASE4.MODELSTAT GT 2, Put logfile; PUT "Skipped file prtBB2.inc" / / ;  ELSE



*------------------------------------------------------------------------------
* Print for current simulation year:
*------------------------------------------------------------------------------

$ontext
* Calibration
$ifi %DEFPCALIB%==yes $include "../../base/output/printout/printinc/dfp_calib.inc";


* Key figures
$include "../../base/output/printout/printinc/bal_1.inc";
* Note: the file bal_2.inc  is temporarily not included due to unresolved syntax errors:
*$include "../../base/output/printout/printinc/bal_2.inc";

$ifi %GAS%==yes $include "../../base/addons/gas/gasbal_1.inc";


* Electricity generation
$include "../../base/output/printout/printinc/eg_cy.inc";
*$include "../../base/output/printout/printinc/eg_gfcy.inc";
$include "../../base/output/printout/printinc/ego_cy.inc";
$include "../../base/output/printout/printinc/egn_cy.inc";
$include "../../base/output/printout/printinc/ezgo_cy.inc";
$include "../../base/output/printout/printinc/ezgn_cy.inc";
$include "../../base/output/printout/printinc/eg_gat.inc";

* Electricity storage:
$include "../../base/output/printout/printinc/esto_at.inc";
$include "../../base/output/printout/printinc/esto2_at.inc";


* Heat generation
$include "../../base/output/printout/printinc/hg_cy.inc";
$include "../../base/output/printout/printinc/hgo_cy.inc";
$include "../../base/output/printout/printinc/hgn_cy.inc";

* Heat storage
$include "../../base/output/printout/printinc/hsto_at.inc";
$include "../../base/output/printout/printinc/hsto2_at.inc";

* Import - Export
$include "../../base/output/printout/printinc/ex_ry.inc";
$include "../../base/output/printout/printinc/exk_ry.inc";
$include "../../base/output/printout/printinc/xbottle.inc";

* Fuel consumption
$include "../../base/output/printout/printinc/ehf_gcy.inc";
$include "../../base/output/printout/printinc/ehf_gry.inc";
$include "../../base/output/printout/printinc/ehf_gay.inc";
$include "../../base/output/printout/printinc/ehf_fcy.inc";
$include "../../base/output/printout/printinc/f_fcy.inc";
*$include "../../base/output/printout/printinc/ehf_gfcy.inc";  removed 201105xx.
$include "../../base/output/printout/printinc/hyrs_as.inc";


$offtext

*Weiming

* Electrcity Prices
$include "../../base/output/printout/printinc/ep_yrt.inc";!! Must be before ep_yr.inc in next line
$include "../../base/output/printout/printinc/ep_yr.inc";
$include "../../base/output/printout/printinc/ep_yc.inc";
$include "../../base/output/printout/printinc/ep_yna.inc";
$include "../../base/output/printout/printinc/hp_yat.inc";!! Must be before ep_yr.inc in next line
$include "../../base/output/printout/printinc/hp_ya.inc"
$include "../../base/output/printout/printinc/hp_yc.inc";
$include "../../base/output/printout/printinc/hp_yna.inc";

*Averaged electricity prices (annual cost/demand)
$include "../../base/output/printout/printinc/aep_yna.inc";

* Generations
$include "../../base/output/printout/printinc/eg_yat.inc";
$include "../../base/output/printout/printinc/eg_yr.inc";
$include "../../base/output/printout/printinc/eg_yc.inc";
$include "../../base/output/printout/printinc/eg_yna.inc"; !! National summary by technology
$include "../../base/output/printout/printinc/eg_ynaf.inc";!! National summary by fuel

* Endogenous investments
$include "../../base/output/printout/printinc/gkn_yag.inc";
* Endogenous investments by fuels of aggregated countries
$include "../../base/output/printout/printinc/gkn_ynaf.inc";

* Endogenous investments and exogenous capacities
$include "../../base/output/printout/printinc/gk_yag.inc";
* Endogenous investments and exogenous capacities by countries
$include "../../base/output/printout/printinc/gk_ycg.inc";
* Endogenous investments and exogenous capacities by technogies of aggregated countries
$include "../../base/output/printout/printinc/gk_ynag.inc";
* Endogenous investments and exogenous capacities by fuels of aggregated countries
$include "../../base/output/printout/printinc/gk_ynaf.inc";



* Emissions
$include "../../base/output/printout/printinc/mco2_yc.inc";!!country level
$include "../../base/output/printout/printinc/mco2_yna.inc";!! aggregated countries
$include "../../base/output/printout/printinc/mpco2_yc.inc"; !!co2 shadow price (RMB/ton)
$include "../../base/output/printout/printinc/mpco2_yna.inc"; !!national co2 shadow price (RMB/ton)

*Demand
$include "../../base/output/printout/printinc/de_yc.inc";!!country level
$include "../../base/output/printout/printinc/de_yna.inc";!!aggregated country level


$ontext


* Emissions
$include "../../base/output/printout/printinc/mco2_cy.inc";
$include "../../base/output/printout/printinc/mso2_cy.inc";
$include "../../base/output/printout/printinc/mnox_cy.inc";


$offtext

* Addons:
* Print files for addons may be included here, or in bb123.sim (matter of style ...).

$include "../../base/addons/_hooks/output.inc"

* Skipped to here if the model did not solve properly:
$ifi %BB4%==yes  );

* This file is for BB4 only
$label endofprtbb4



