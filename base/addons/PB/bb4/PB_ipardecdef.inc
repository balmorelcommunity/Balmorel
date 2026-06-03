*-------------------------------------------------------------------------------
* PB_ipardecdef.inc  --  Stub that loads precomputed per-generator IM_* values
*-------------------------------------------------------------------------------
* Part of the Balmorel Planetary Boundaries (PB) add-on.
*
* PURPOSE
*   This thin stub replaces the slow GAMS LOOP/IF logic that lived in the
*   original addons/PB/bb4/PB_ipardecdef.inc. It $INCLUDEs a per-scenario
*   precomputed file generated offline by a Python preprocessor, so that GAMS
*   loads the IM_<Category>_* parameters as direct assignments instead of
*   recomputing them via a 5-dimensional Cartesian-product loop on every
*   model run.
*
* PIPELINE
*   1. Python preprocessor reads:
*        - GDATA.inc, HYDROGEN_GDATA.inc, GDATA_renewable.inc,
*          COMBTECH_GDATA.inc, INDIVUSERS_GDATA.inc  (generator -> TG/FFF/GDTYPE)
*        - CCS_CCS_G.inc                             (CCS generator subset)
*        - PB_LCA_DATA_<scenario>.inc                (main LCA values)
*        - PB_LCA_DATA_H2_<scenario>.inc             (H2 LCA additions)
*        - PB_LCA_DATA_CCS_<scenario>.inc            (CCS LCA values)
*        - PB_LCA_DATA_H2_STO_CAV_<scenario>.inc     (H2 cavern overrides)
*      ... and emits PB_ipardecdef_<scenario>.inc per scenario.
*
*   2. Each generated .inc declares 30 IM_<Category>_* parameters (10 impact
*      categories x {prod_elec, prod_heat, constr}) with their values, plus
*      $ifi-guarded HYDROGEN and CCS overrides that mirror the original
*      conditional logic. The 10 categories are CO2, OZONE_DEPLETION, LU,
*      WU, EUTROPHICATION_FRESHWATER, ECOTOXICITY_FRESHWATER, PM, RADIATION,
*      ACIDIFICATION, RESOURCE.
*
*   3. This stub picks the right file at runtime based on %IAM_Scenario%.
*
* DEPLOYMENT (one-time)
*   1. Generate the per-scenario files:
*        cd /work3/dhrsh/Balmorel/2_PreProcessing_ipardecdef
*        python3 preprocess_ipardecdef.py --scenario all
*
*   2. Stage the generated files into the model's data directory:
*        cp Outputs/PB_ipardecdef_*.inc \
*           <root>/base/data/
*
*   3. Replace the original addon file with this stub:
*        cp Outputs/PB_ipardecdef.inc \
*           <root>/base/addons/PB/bb4/PB_ipardecdef.inc
*
*   4. Run Balmorel as usual. Confirm runtime improvement on the
*      compilation/preprocessing phase.
*
* RE-RUNNING AFTER LCA / GDATA UPDATES
*   Repeat steps 1 and 2 only. This stub itself never changes.
*
* COMPATIBILITY NOTES
*   - The CCS overrides remain $ifi-guarded by %CCS%, so a model run with
*     CCS=no behaves exactly as before.
*   - The H2 LCA additions are $ifi-guarded by %HYDROGEN%, mirroring the
*     conditional include at the bottom of PB_LCA_DATA_<scenario>.inc.
*   - The auxiliary set ILCA(Y,G,TECH_GROUP,FFF,PB_GDTYPE_SET) is no longer
*     declared (audit confirmed it was never referenced outside the original
*     file). If a future addon needs it, restore its declaration here.
*   - The original CO2-cavern bug (line 22 of the deprecated file read
*     'LCA_CO2_prod_elec' instead of 'LCA_CO2_constr') is silently fixed in
*     the precomputed output. Numerical IM_CO2_constr values for H2 caverns
*     will differ from a strict re-run of the original LOOP/IF code.
*
* Authors: Theo Balanza & Dhruv Sharma
*-------------------------------------------------------------------------------

* --- 10 biogenic + 10 fossil CC_STO aggregate-scalar declarations -----------
* Declared HERE (before the $INCLUDE) because the per-scenario .inc populates
* them via direct value assignments (2026-05-26 refactor: moved aggregation
* offline into the Python preprocessor, replacing the prior capacity-weighted
* SUM(G,...)/SUM(G,...) computed below). Arithmetic mean per group; matches
* the original GAMS calc exactly in green-field where GKFX=0.
$ifi %CCS%==yes PARAMETER IM_CC_STO_CO2_biogenic(YYY)                       'Group-mean biogenic CC_STO LCA (kg CO2-eq per kg CO2 stored)';
$ifi %CCS%==yes PARAMETER IM_CC_STO_CO2_fossil(YYY)                         'Group-mean fossil   CC_STO LCA (kg CO2-eq per kg CO2 stored)';
$ifi %CCS%==yes PARAMETER IM_CC_STO_Ozone_depletion_biogenic(YYY)           'Group-mean biogenic CC_STO LCA (kg CFC11-eq per kg CO2 stored)';
$ifi %CCS%==yes PARAMETER IM_CC_STO_Ozone_depletion_fossil(YYY)             'Group-mean fossil   CC_STO LCA (kg CFC11-eq per kg CO2 stored)';
$ifi %CCS%==yes PARAMETER IM_CC_STO_LU_biogenic(YYY)                        'Group-mean biogenic CC_STO LCA (Pt per kg CO2 stored)';
$ifi %CCS%==yes PARAMETER IM_CC_STO_LU_fossil(YYY)                          'Group-mean fossil   CC_STO LCA (Pt per kg CO2 stored)';
$ifi %CCS%==yes PARAMETER IM_CC_STO_WU_biogenic(YYY)                        'Group-mean biogenic CC_STO LCA (m3 dep. per kg CO2 stored)';
$ifi %CCS%==yes PARAMETER IM_CC_STO_WU_fossil(YYY)                          'Group-mean fossil   CC_STO LCA (m3 dep. per kg CO2 stored)';
$ifi %CCS%==yes PARAMETER IM_CC_STO_Eutrophication_freshwater_biogenic(YYY) 'Group-mean biogenic CC_STO LCA (kg P-eq per kg CO2 stored)';
$ifi %CCS%==yes PARAMETER IM_CC_STO_Eutrophication_freshwater_fossil(YYY)   'Group-mean fossil   CC_STO LCA (kg P-eq per kg CO2 stored)';
$ifi %CCS%==yes PARAMETER IM_CC_STO_Ecotoxicity_freshwater_biogenic(YYY)    'Group-mean biogenic CC_STO LCA (CTUe per kg CO2 stored)';
$ifi %CCS%==yes PARAMETER IM_CC_STO_Ecotoxicity_freshwater_fossil(YYY)      'Group-mean fossil   CC_STO LCA (CTUe per kg CO2 stored)';
$ifi %CCS%==yes PARAMETER IM_CC_STO_PM_biogenic(YYY)                        'Group-mean biogenic CC_STO LCA (disease incidence per kg CO2 stored)';
$ifi %CCS%==yes PARAMETER IM_CC_STO_PM_fossil(YYY)                          'Group-mean fossil   CC_STO LCA (disease incidence per kg CO2 stored)';
$ifi %CCS%==yes PARAMETER IM_CC_STO_Radiation_biogenic(YYY)                 'Group-mean biogenic CC_STO LCA (kBq U-235-eq per kg CO2 stored)';
$ifi %CCS%==yes PARAMETER IM_CC_STO_Radiation_fossil(YYY)                   'Group-mean fossil   CC_STO LCA (kBq U-235-eq per kg CO2 stored)';
$ifi %CCS%==yes PARAMETER IM_CC_STO_Acidification_biogenic(YYY)             'Group-mean biogenic CC_STO LCA (mol H+-eq per kg CO2 stored)';
$ifi %CCS%==yes PARAMETER IM_CC_STO_Acidification_fossil(YYY)               'Group-mean fossil   CC_STO LCA (mol H+-eq per kg CO2 stored)';
$ifi %CCS%==yes PARAMETER IM_CC_STO_Resource_biogenic(YYY)                  'Group-mean biogenic CC_STO LCA (kg Sb-eq per kg CO2 stored)';
$ifi %CCS%==yes PARAMETER IM_CC_STO_Resource_fossil(YYY)                    'Group-mean fossil   CC_STO LCA (kg Sb-eq per kg CO2 stored)';

$if     EXIST '../data/PB_ipardecdef_%IAM_Scenario%.inc' $INCLUDE         '../data/PB_ipardecdef_%IAM_Scenario%.inc';
$if not EXIST '../data/PB_ipardecdef_%IAM_Scenario%.inc' $INCLUDE '../../base/data/PB_ipardecdef_%IAM_Scenario%.inc';

* --- Disable AGKN/GKFX for CCS_G plants with NO LCA values (2026-05-26) ------
* Per plan A14, certain CCS_G plants (currently the 5 BGASCCS plants with the
* (BOILER, BIOGAS, GHOB) triple) have no main_lca twin, so the preprocessor
* emits IM_CO2_constr = IM_CO2_prod_elec = IM_CO2_prod_heat = 0 across all
* years for them.  Keeping them in CCS_G but with zero LCA would:
*   - allow the LP to invest in them via AGKN at zero PB-construction cost,
*   - bloat the LP matrix via IAGK_HASORPOT references in QVGF_AGG, QPBSCORE_*,
*     and CCS_qeeq/qlimco2/qobj even though their PB / CCS contribution is ~0.
* The defensive fix: identify these plants from the loaded IM_CO2_* parameters
* and zero out AGKN and GKFX for them. With AGKN/GKFX = 0 they fall out of
* IAGK_HASORPOT (computed later in Balmorelbb4.inc), dropping cleanly from the
* LP matrix.  In current Nordic data they already have empty AGKN and GKFX so
* this is a no-op; the value is future-proofing against data refreshes that
* enable them and against scenarios where they might be set.
$ifi %CCS%==yes SET IGEN_NO_LCA(GGG) "CCS_G plants with no LCA values, disabled from LP (2026-05-26)";
$ifi %CCS%==yes IGEN_NO_LCA(G) = YES$(CCS_G(G) AND
$ifi %CCS%==yes   (NOT SUM(Y, IM_CO2_constr(Y,G) + IM_CO2_prod_elec(Y,G) + IM_CO2_prod_heat(Y,G))));
$ifi %CCS%==yes AGKN(IA, G)$IGEN_NO_LCA(G)    = NO;
$ifi %CCS%==yes GKFX(Y, IA, G)$IGEN_NO_LCA(G) = 0;
$ifi %CCS%==yes DISPLAY "Disabled CCS_G plants without LCA values (AGKN=NO, GKFX=0):", IGEN_NO_LCA;
