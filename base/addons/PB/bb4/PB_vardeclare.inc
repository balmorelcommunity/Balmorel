*-------------------------------------------------------------------------------
* PB_vardeclare.inc  --  Variable declarations for the PB add-on
*-------------------------------------------------------------------------------
* Part of the Balmorel Planetary Boundaries (PB) add-on.
*
* Declares the impact-score (IS_*) and transgression-level (TL_*) variables
* for the 10 active PB impact categories, plus three matrix-generation
* accelerator variables (V*_AGG).
*
* IMPACT CATEGORIES (10)
*   CO2                            Climate change                    (kg CO2-eq)
*   OZONE_DEPLETION                Stratospheric ozone depletion     (kg CFC-11-eq)
*   LU                             Land use                          (Pt)
*   WU                             Water use                         (m3 water-eq)
*   EUTROPHICATION_FRESHWATER      Freshwater eutrophication         (kg P-eq)
*   ECOTOXICITY_FRESHWATER         Freshwater ecotoxicity            (CTUe)
*   PM                             Particulate matter formation      (disease incidence)
*   RADIATION                      Ionising radiation                (kBq U-235-eq)
*   ACIDIFICATION                  Terrestrial acidification         (mol H+-eq)
*   RESOURCE                       Resource use (minerals/metals)    (kg Sb-eq)
*
* VARIABLE FAMILIES (per category)
*   IS_<CAT>(Y)         Energy-system aggregate impact score
*   IS_<CAT>_X(Y)       Sub-score from electricity transmission construction
*   IS_<CAT>_X_H2(Y)    Sub-score from H2 transmission construction
*   IS_<CAT>_EV(Y)      Sub-score from EV batteries (chassis + cyclic deg.)
*   TL_<CAT>(Y)         Transgression level: TL = (sum of IS_* sub-scores) /
*                       threshold, set by the QPBLIM_<CAT>_TL equation.
*                       TL > 1 means the planetary boundary is crossed.
*
* RADIATION (10th category) was activated 2026-05-16; previously the
* PB_LCA_DATA tables and per-generator IM_Radiation_* values existed in the
* data layer but no IS_RADIATION_* / TL_RADIATION variables were declared
* and no QPBSCORE_RADIATION / QPBLIM_RADIATION equations existed.
*
* Authors: Theo Balanza & Dhruv Sharma
*-------------------------------------------------------------------------------

* === Climate Change (CO2) ====================================================
POSITIVE VARIABLE IS_CO2(Y)         "Impact score: climate change";
POSITIVE VARIABLE IS_X_BASE(Y)      "Elec-transmission LCA rank-1 base (geomean-weighted line build); IS_<cat>_X = intensity(cat) * this under PB_X_RANKFIX";
POSITIVE VARIABLE IS_CO2_X(Y)       "Impact score: climate change, electricity transmission construction";
POSITIVE VARIABLE IS_X_H2_BASE(Y)   "H2-transmission LCA rank-1 base (geomean-weighted line build); IS_<cat>_X_H2 = intensity(cat) * this under PB_XH2_RANKFIX";
POSITIVE VARIABLE IS_CO2_X_H2(Y)    "Impact score: climate change, H2 transmission construction";
POSITIVE VARIABLE IS_CO2_EV(Y)      "Impact score: climate change, EV batteries";
POSITIVE VARIABLE TL_CO2(Y)         "Transgression level: climate change (TL = IS_total / threshold)";

* === Stratospheric Ozone Depletion ===========================================
POSITIVE VARIABLE IS_OZONE_DEPLETION(Y)         "Impact score: ozone depletion";
POSITIVE VARIABLE IS_OZONE_DEPLETION_X(Y)       "Impact score: ozone depletion, electricity transmission construction";
POSITIVE VARIABLE IS_OZONE_DEPLETION_X_H2(Y)    "Impact score: ozone depletion, H2 transmission construction";
POSITIVE VARIABLE IS_OZONE_DEPLETION_EV(Y)      "Impact score: ozone depletion, EV batteries";
POSITIVE VARIABLE TL_OZONE_DEPLETION(Y)         "Transgression level: ozone depletion (TL = IS_total / threshold)";

* === Land Use ================================================================
POSITIVE VARIABLE IS_LU(Y)         "Impact score: land use";
POSITIVE VARIABLE IS_LU_X(Y)       "Impact score: land use, electricity transmission construction";
POSITIVE VARIABLE IS_LU_X_H2(Y)    "Impact score: land use, H2 transmission construction";
POSITIVE VARIABLE IS_LU_EV(Y)      "Impact score: land use, EV batteries";
POSITIVE VARIABLE TL_LU(Y)         "Transgression level: land use (TL = IS_total / threshold)";

* === Water Use ===============================================================
POSITIVE VARIABLE IS_WU(Y)         "Impact score: water use";
POSITIVE VARIABLE IS_WU_X(Y)       "Impact score: water use, electricity transmission construction";
POSITIVE VARIABLE IS_WU_X_H2(Y)    "Impact score: water use, H2 transmission construction";
POSITIVE VARIABLE IS_WU_EV(Y)      "Impact score: water use, EV batteries";
POSITIVE VARIABLE TL_WU(Y)         "Transgression level: water use (TL = IS_total / threshold)";

* === Freshwater Eutrophication ===============================================
POSITIVE VARIABLE IS_EUTROPHICATION_FRESHWATER(Y)         "Impact score: freshwater eutrophication";
POSITIVE VARIABLE IS_EUTROPHICATION_FRESHWATER_X(Y)       "Impact score: freshwater eutrophication, electricity transmission construction";
POSITIVE VARIABLE IS_EUTROPHICATION_FRESHWATER_X_H2(Y)    "Impact score: freshwater eutrophication, H2 transmission construction";
POSITIVE VARIABLE IS_EUTROPHICATION_FRESHWATER_EV(Y)      "Impact score: freshwater eutrophication, EV batteries";
POSITIVE VARIABLE TL_EUTROPHICATION_FRESHWATER(Y)         "Transgression level: freshwater eutrophication (TL = IS_total / threshold)";

* === Freshwater Ecotoxicity ==================================================
POSITIVE VARIABLE IS_ECOTOXICITY_FRESHWATER(Y)         "Impact score: freshwater ecotoxicity";
POSITIVE VARIABLE IS_ECOTOXICITY_FRESHWATER_X(Y)       "Impact score: freshwater ecotoxicity, electricity transmission construction";
POSITIVE VARIABLE IS_ECOTOXICITY_FRESHWATER_X_H2(Y)    "Impact score: freshwater ecotoxicity, H2 transmission construction";
POSITIVE VARIABLE IS_ECOTOXICITY_FRESHWATER_EV(Y)      "Impact score: freshwater ecotoxicity, EV batteries";
POSITIVE VARIABLE TL_ECOTOXICITY_FRESHWATER(Y)         "Transgression level: freshwater ecotoxicity (TL = IS_total / threshold)";

* === Particulate Matter Formation ============================================
POSITIVE VARIABLE IS_PM(Y)         "Impact score: particulate matter formation";
POSITIVE VARIABLE IS_PM_X(Y)       "Impact score: particulate matter, electricity transmission construction";
POSITIVE VARIABLE IS_PM_X_H2(Y)    "Impact score: particulate matter, H2 transmission construction";
POSITIVE VARIABLE IS_PM_EV(Y)      "Impact score: particulate matter, EV batteries";
POSITIVE VARIABLE TL_PM(Y)         "Transgression level: particulate matter (TL = IS_total / threshold)";

* === Ionising Radiation ======================================================
POSITIVE VARIABLE IS_RADIATION(Y)         "Impact score: ionising radiation";
POSITIVE VARIABLE IS_RADIATION_X(Y)       "Impact score: ionising radiation, electricity transmission construction";
POSITIVE VARIABLE IS_RADIATION_X_H2(Y)    "Impact score: ionising radiation, H2 transmission construction";
POSITIVE VARIABLE IS_RADIATION_EV(Y)      "Impact score: ionising radiation, EV batteries";
POSITIVE VARIABLE TL_RADIATION(Y)         "Transgression level: ionising radiation (TL = IS_total / threshold)";

* === Terrestrial Acidification ===============================================
POSITIVE VARIABLE IS_ACIDIFICATION(Y)         "Impact score: terrestrial acidification";
POSITIVE VARIABLE IS_ACIDIFICATION_X(Y)       "Impact score: terrestrial acidification, electricity transmission construction";
POSITIVE VARIABLE IS_ACIDIFICATION_X_H2(Y)    "Impact score: terrestrial acidification, H2 transmission construction";
POSITIVE VARIABLE IS_ACIDIFICATION_EV(Y)      "Impact score: terrestrial acidification, EV batteries";
POSITIVE VARIABLE TL_ACIDIFICATION(Y)         "Transgression level: terrestrial acidification (TL = IS_total / threshold)";

* === Resource Use (Minerals and Metals) ======================================
POSITIVE VARIABLE IS_RESOURCE(Y)         "Impact score: resource use (minerals and metals)";
POSITIVE VARIABLE IS_RESOURCE_X(Y)       "Impact score: resource use, electricity transmission construction";
POSITIVE VARIABLE IS_RESOURCE_X_H2(Y)    "Impact score: resource use, H2 transmission construction";
POSITIVE VARIABLE IS_RESOURCE_EV(Y)      "Impact score: resource use, EV batteries";
POSITIVE VARIABLE TL_RESOURCE(Y)         "Transgression level: resource use (TL = IS_total / threshold)";

* === CAR_DIESEL (Component 2, 2026-05-26): exogenous diesel-car fleet impacts =
* One IS_<CAT>_DIESEL per category. Set by QPBSCORE_<CAT>_DIESEL when EV add-on
* is active (drives IDIESEL_AVAILABLE > 0); when EV=no the equations aren't
* registered (PB_balbase4.inc gates them) and the LP settles these at 0.
POSITIVE VARIABLE IS_CO2_DIESEL(Y)                         "Impact score: climate change, diesel cars (kg CO2-eq)";
POSITIVE VARIABLE IS_OZONE_DEPLETION_DIESEL(Y)             "Impact score: ozone depletion, diesel cars (kg CFC11-eq)";
POSITIVE VARIABLE IS_LU_DIESEL(Y)                          "Impact score: land use, diesel cars (Pt)";
POSITIVE VARIABLE IS_WU_DIESEL(Y)                          "Impact score: water use, diesel cars (m3 dep.)";
POSITIVE VARIABLE IS_EUTROPHICATION_FRESHWATER_DIESEL(Y)   "Impact score: freshwater eutrophication, diesel cars (kg P-eq)";
POSITIVE VARIABLE IS_ECOTOXICITY_FRESHWATER_DIESEL(Y)      "Impact score: freshwater ecotoxicity, diesel cars (CTUe)";
POSITIVE VARIABLE IS_PM_DIESEL(Y)                          "Impact score: particulate matter, diesel cars (DI)";
POSITIVE VARIABLE IS_RADIATION_DIESEL(Y)                   "Impact score: ionising radiation, diesel cars (kBq U-235-eq)";
POSITIVE VARIABLE IS_ACIDIFICATION_DIESEL(Y)               "Impact score: acidification, diesel cars (mol H+-eq)";
POSITIVE VARIABLE IS_RESOURCE_DIESEL(Y)                    "Impact score: resource use, diesel cars (kg Sb-eq)";

* === Matrix-generation accelerator: (S,T)-aggregated production variables ====
* Each V*_AGG is defined by a tight =E= equation against the per-timeslice
* generation variables (see QVGE_AGG / QVGH_AGG / QVH2_AGG in PB_eqndecdef.inc),
* so CPLEX presolve substitutes them out. The point is to collapse the
* (IS3,T) inner sum in QPBSCORE_<CAT> equations from a 192-deep nested sum
* down to a single linear term, drastically reducing GAMS matrix-generation
* time. Added 2026-05-11 as part of PB performance work; together with the
* IM_*-coefficient filter and the QPBLIM reformulation, gives the ~25x
* speedup over the upstream PB add-on on the EU run.
POSITIVE VARIABLE VGE_AGG(Y,AAA,G)   "Annual (IS3,T)-weighted electricity generation per (Y, AAA, G)";
POSITIVE VARIABLE VGH_AGG(Y,AAA,G)   "Annual (IS3,T)-weighted heat generation per (Y, AAA, G)";
$ifi %HYDROGEN%==yes POSITIVE VARIABLE VH2_AGG(Y,AAA,G)   "Annual (IS3,T)-weighted H2/biomethane flows per (Y, AAA, G) (sum of GH2_T + GBIOMETH_T + GBIOGASMETHANATION_T + GBIOGASUPGRADING_T)";
$ifi %CCS%==yes POSITIVE VARIABLE VGF_AGG(Y,AAA,G)   "Annual (IS3,T)-weighted fuel input per (Y, AAA, G); used by PB modular CCS layer (CC_PS/CC_STO/BECCS) for CCS_G plants only (2026-05-26)";

* --- PB modular CCS layer: capture-process / storage-process / BECCS credit ---
* IS_<CAT>_CC_PS:  capture-process LCA on all captured CO2
* IS_<CAT>_CC_STO: storage-process LCA on stored CO2 (captured - utilized)
* VBECCS_CREDIT:   negative-emission credit, capped at biogenic stored
$ifi %CCS%==yes POSITIVE VARIABLE IS_CO2_CC_PS(Y)                          "CC_PS impact: climate change (kg CO2-eq)";
$ifi %CCS%==yes POSITIVE VARIABLE IS_CO2_CC_STO(Y)                         "CC_STO impact: climate change (kg CO2-eq)";
$ifi %CCS%==yes POSITIVE VARIABLE IS_OZONE_DEPLETION_CC_PS(Y)              "CC_PS impact: ozone depletion (kg CFC11-eq)";
$ifi %CCS%==yes POSITIVE VARIABLE IS_OZONE_DEPLETION_CC_STO(Y)             "CC_STO impact: ozone depletion (kg CFC11-eq)";
$ifi %CCS%==yes POSITIVE VARIABLE IS_LU_CC_PS(Y)                           "CC_PS impact: land use (Pt)";
$ifi %CCS%==yes POSITIVE VARIABLE IS_LU_CC_STO(Y)                          "CC_STO impact: land use (Pt)";
$ifi %CCS%==yes POSITIVE VARIABLE IS_WU_CC_PS(Y)                           "CC_PS impact: water use (m3 dep.)";
$ifi %CCS%==yes POSITIVE VARIABLE IS_WU_CC_STO(Y)                          "CC_STO impact: water use (m3 dep.)";
$ifi %CCS%==yes POSITIVE VARIABLE IS_EUTROPHICATION_FRESHWATER_CC_PS(Y)    "CC_PS impact: freshwater eutrophication (kg P-eq)";
$ifi %CCS%==yes POSITIVE VARIABLE IS_EUTROPHICATION_FRESHWATER_CC_STO(Y)   "CC_STO impact: freshwater eutrophication (kg P-eq)";
$ifi %CCS%==yes POSITIVE VARIABLE IS_ECOTOXICITY_FRESHWATER_CC_PS(Y)       "CC_PS impact: freshwater ecotoxicity (CTUe)";
$ifi %CCS%==yes POSITIVE VARIABLE IS_ECOTOXICITY_FRESHWATER_CC_STO(Y)      "CC_STO impact: freshwater ecotoxicity (CTUe)";
$ifi %CCS%==yes POSITIVE VARIABLE IS_PM_CC_PS(Y)                           "CC_PS impact: particulate matter (DI)";
$ifi %CCS%==yes POSITIVE VARIABLE IS_PM_CC_STO(Y)                          "CC_STO impact: particulate matter (DI)";
$ifi %CCS%==yes POSITIVE VARIABLE IS_RADIATION_CC_PS(Y)                    "CC_PS impact: ionising radiation (kBq U-235-eq)";
$ifi %CCS%==yes POSITIVE VARIABLE IS_RADIATION_CC_STO(Y)                   "CC_STO impact: ionising radiation (kBq U-235-eq)";
$ifi %CCS%==yes POSITIVE VARIABLE IS_ACIDIFICATION_CC_PS(Y)                "CC_PS impact: acidification (mol H+-eq)";
$ifi %CCS%==yes POSITIVE VARIABLE IS_ACIDIFICATION_CC_STO(Y)               "CC_STO impact: acidification (mol H+-eq)";
$ifi %CCS%==yes POSITIVE VARIABLE IS_RESOURCE_CC_PS(Y)                     "CC_PS impact: resource use (kg Sb-eq)";
$ifi %CCS%==yes POSITIVE VARIABLE IS_RESOURCE_CC_STO(Y)                    "CC_STO impact: resource use (kg Sb-eq)";
$ifi %CCS%==yes POSITIVE VARIABLE VBECCS_CREDIT(Y)                         "BECCS credit (kg CO2-eq), bounded by biogenic stored";
* --- Capture accumulators (2026-05-28): total fossil/biogenic CO2 captured, summed ONCE
* --- in QCO2CAP_{FOS,BIO}. The CC_PS/CC_STO/credit score rows reference these 2 vars
* --- instead of each re-summing ~41k CCS plants -> collapses ~20 dense rows to 2.
$ifi %CCS%==yes POSITIVE VARIABLE VCO2CAP_FOS(Y)                           "Total fossil  CO2 captured by CCS plants (kg CO2)";
$ifi %CCS%==yes POSITIVE VARIABLE VCO2CAP_BIO(Y)                           "Total biogenic CO2 captured by CCS plants (kg CO2)";
