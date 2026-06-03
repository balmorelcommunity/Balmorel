*-------------------------------------------------------------------------------
* PB_balbase4.inc  --  Equation registration for the PB add-on
*-------------------------------------------------------------------------------
* Part of the Balmorel Planetary Boundaries (PB) add-on.
*
* Lists the PB equations to be included in the MODEL statement of the
* surrounding Balmorelbb4 problem. Each impact category is registered in a
* uniform block guarded by global flags:
*
*   %PB_all%     yes/no   if "yes", all 10 impact categories are active;
*                         if "no", only CO2 is active (PB_CO2 mode).
*
*   %TL_<CAT>_ALLOWED%    yes/empty   per-category soft/hard switch:
*                         if "yes", uses the soft-bound  QPBLIM_<CAT>_TL
*                         (=E= with TL slack variable, penalized in objective);
*                         if empty, uses the hard-bound  QPBLIM_<CAT>_TL_NO
*                         (=L= threshold, no transgression allowed).
*                         Replaces the former single global TL_ALLOWED. The
*                         10 flags are declared in base/model/balopt.opt.
*
*   %HYDROGEN%   yes/no   gates the QPBSCORE_<CAT>_X_H2 equations
*                         (H2 transmission line construction contribution).
*
*   %EV%         yes/no   gates the QPBSCORE_<CAT>_EV equations
*                         (EV battery contribution).
*
* The category order matches PB_THRESHOLDS_SET.inc: CO2, OZONE_DEPLETION, LU,
* WU, EUTROPHICATION_FRESHWATER, ECOTOXICITY_FRESHWATER, PM, RADIATION,
* ACIDIFICATION, RESOURCE.
*
* Trailing three lines (QVGE_AGG, QVGH_AGG, QVH2_AGG) register the
* matrix-generation accelerator equations defined in PB_eqndecdef.inc.
*
* RADIATION (10th category) was activated 2026-05-16. Previously its
* equations did not exist; only the data layer (IM_Radiation_*, SOS_RADIATION
* threshold) was present.
*
* Authors: Theo Balanza & Dhruv Sharma
*-------------------------------------------------------------------------------

* === Climate Change (CO2) =====================================================
QPBSCORE_CO2
$ifi not %PB_all%==yes $ifi not %TL_CO2_ALLOWED%==yes QPBLIM_CO2_TL_NO
$ifi     %PB_all%==yes $ifi     %TL_CO2_ALLOWED%==yes QPBLIM_CO2_TL
$ifi     %PB_all%==yes $ifi not %TL_CO2_ALLOWED%==yes QPBLIM_CO2_TL_NO
QPBSCORE_CO2_X
$ifi %PB_X_RANKFIX%==yes QPBSCORE_X_BASE
$ifi %HYDROGEN%==yes QPBSCORE_CO2_X_H2
$ifi %HYDROGEN%==yes $ifi %PB_XH2_RANKFIX%==yes QPBSCORE_X_H2_BASE
$ifi %EV%==yes       QPBSCORE_CO2_EV
$ifi %EV%==yes       QPBSCORE_CO2_DIESEL
$ifi %CCS%==yes      QPBSCORE_CO2_CC_PS
$ifi %CCS%==yes      QPBSCORE_CO2_CC_STO

* === Stratospheric Ozone Depletion ============================================
QPBSCORE_OZONE_DEPLETION
$ifi not %PB_all%==yes $ifi not %TL_OZONE_DEPLETION_ALLOWED%==yes QPBLIM_OZONE_DEPLETION_TL_NO
$ifi     %PB_all%==yes $ifi     %TL_OZONE_DEPLETION_ALLOWED%==yes QPBLIM_OZONE_DEPLETION_TL
$ifi     %PB_all%==yes $ifi not %TL_OZONE_DEPLETION_ALLOWED%==yes QPBLIM_OZONE_DEPLETION_TL_NO
QPBSCORE_OZONE_DEPLETION_X
$ifi %HYDROGEN%==yes QPBSCORE_OZONE_DEPLETION_X_H2
$ifi %EV%==yes       QPBSCORE_OZONE_DEPLETION_EV
$ifi %EV%==yes       QPBSCORE_OZONE_DEPLETION_DIESEL
$ifi %CCS%==yes      QPBSCORE_OZONE_DEPLETION_CC_PS
$ifi %CCS%==yes      QPBSCORE_OZONE_DEPLETION_CC_STO

* === Land Use =================================================================
QPBSCORE_LU
$ifi not %PB_all%==yes $ifi not %TL_LU_ALLOWED%==yes QPBLIM_LU_TL_NO
$ifi     %PB_all%==yes $ifi     %TL_LU_ALLOWED%==yes QPBLIM_LU_TL
$ifi     %PB_all%==yes $ifi not %TL_LU_ALLOWED%==yes QPBLIM_LU_TL_NO
QPBSCORE_LU_X
$ifi %HYDROGEN%==yes QPBSCORE_LU_X_H2
$ifi %EV%==yes       QPBSCORE_LU_EV
$ifi %EV%==yes       QPBSCORE_LU_DIESEL
$ifi %CCS%==yes      QPBSCORE_LU_CC_PS
$ifi %CCS%==yes      QPBSCORE_LU_CC_STO

* === Water Use ================================================================
QPBSCORE_WU
$ifi not %PB_all%==yes $ifi not %TL_WU_ALLOWED%==yes QPBLIM_WU_TL_NO
$ifi     %PB_all%==yes $ifi     %TL_WU_ALLOWED%==yes QPBLIM_WU_TL
$ifi     %PB_all%==yes $ifi not %TL_WU_ALLOWED%==yes QPBLIM_WU_TL_NO
QPBSCORE_WU_X
$ifi %HYDROGEN%==yes QPBSCORE_WU_X_H2
$ifi %EV%==yes       QPBSCORE_WU_EV
$ifi %EV%==yes       QPBSCORE_WU_DIESEL
$ifi %CCS%==yes      QPBSCORE_WU_CC_PS
$ifi %CCS%==yes      QPBSCORE_WU_CC_STO

* === Freshwater Eutrophication ================================================
QPBSCORE_EUTROPHICATION_FRESHWATER
$ifi not %PB_all%==yes $ifi not %TL_EUTROPHICATION_FRESHWATER_ALLOWED%==yes QPBLIM_EUTROPHICATION_FRESHWATER_TL_NO
$ifi     %PB_all%==yes $ifi     %TL_EUTROPHICATION_FRESHWATER_ALLOWED%==yes QPBLIM_EUTROPHICATION_FRESHWATER_TL
$ifi     %PB_all%==yes $ifi not %TL_EUTROPHICATION_FRESHWATER_ALLOWED%==yes QPBLIM_EUTROPHICATION_FRESHWATER_TL_NO
QPBSCORE_EUTROPHICATION_FRESHWATER_X
$ifi %HYDROGEN%==yes QPBSCORE_EUTROPHICATION_FRESHWATER_X_H2
$ifi %EV%==yes       QPBSCORE_EUTROPHICATION_FRESHWATER_EV
$ifi %EV%==yes       QPBSCORE_EUTROPHICATION_FRESHWATER_DIESEL
$ifi %CCS%==yes      QPBSCORE_EUTROPHICATION_FRESHWATER_CC_PS
$ifi %CCS%==yes      QPBSCORE_EUTROPHICATION_FRESHWATER_CC_STO

* === Freshwater Ecotoxicity ===================================================
QPBSCORE_ECOTOXICITY_FRESHWATER
$ifi not %PB_all%==yes $ifi not %TL_ECOTOXICITY_FRESHWATER_ALLOWED%==yes QPBLIM_ECOTOXICITY_FRESHWATER_TL_NO
$ifi     %PB_all%==yes $ifi     %TL_ECOTOXICITY_FRESHWATER_ALLOWED%==yes QPBLIM_ECOTOXICITY_FRESHWATER_TL
$ifi     %PB_all%==yes $ifi not %TL_ECOTOXICITY_FRESHWATER_ALLOWED%==yes QPBLIM_ECOTOXICITY_FRESHWATER_TL_NO
QPBSCORE_ECOTOXICITY_FRESHWATER_X
$ifi %HYDROGEN%==yes QPBSCORE_ECOTOXICITY_FRESHWATER_X_H2
$ifi %EV%==yes       QPBSCORE_ECOTOXICITY_FRESHWATER_EV
$ifi %EV%==yes       QPBSCORE_ECOTOXICITY_FRESHWATER_DIESEL
$ifi %CCS%==yes      QPBSCORE_ECOTOXICITY_FRESHWATER_CC_PS
$ifi %CCS%==yes      QPBSCORE_ECOTOXICITY_FRESHWATER_CC_STO

* === Particulate Matter Formation =============================================
QPBSCORE_PM
$ifi not %PB_all%==yes $ifi not %TL_PM_ALLOWED%==yes QPBLIM_PM_TL_NO
$ifi     %PB_all%==yes $ifi     %TL_PM_ALLOWED%==yes QPBLIM_PM_TL
$ifi     %PB_all%==yes $ifi not %TL_PM_ALLOWED%==yes QPBLIM_PM_TL_NO
QPBSCORE_PM_X
$ifi %HYDROGEN%==yes QPBSCORE_PM_X_H2
$ifi %EV%==yes       QPBSCORE_PM_EV
$ifi %EV%==yes       QPBSCORE_PM_DIESEL
$ifi %CCS%==yes      QPBSCORE_PM_CC_PS
$ifi %CCS%==yes      QPBSCORE_PM_CC_STO

* === Ionising Radiation =======================================================
QPBSCORE_RADIATION
$ifi not %PB_all%==yes $ifi not %TL_RADIATION_ALLOWED%==yes QPBLIM_RADIATION_TL_NO
$ifi     %PB_all%==yes $ifi     %TL_RADIATION_ALLOWED%==yes QPBLIM_RADIATION_TL
$ifi     %PB_all%==yes $ifi not %TL_RADIATION_ALLOWED%==yes QPBLIM_RADIATION_TL_NO
QPBSCORE_RADIATION_X
$ifi %HYDROGEN%==yes QPBSCORE_RADIATION_X_H2
$ifi %EV%==yes       QPBSCORE_RADIATION_EV
$ifi %EV%==yes       QPBSCORE_RADIATION_DIESEL
$ifi %CCS%==yes      QPBSCORE_RADIATION_CC_PS
$ifi %CCS%==yes      QPBSCORE_RADIATION_CC_STO

* === Terrestrial Acidification ================================================
QPBSCORE_ACIDIFICATION
$ifi not %PB_all%==yes $ifi not %TL_ACIDIFICATION_ALLOWED%==yes QPBLIM_ACIDIFICATION_TL_NO
$ifi     %PB_all%==yes $ifi     %TL_ACIDIFICATION_ALLOWED%==yes QPBLIM_ACIDIFICATION_TL
$ifi     %PB_all%==yes $ifi not %TL_ACIDIFICATION_ALLOWED%==yes QPBLIM_ACIDIFICATION_TL_NO
QPBSCORE_ACIDIFICATION_X
$ifi %HYDROGEN%==yes QPBSCORE_ACIDIFICATION_X_H2
$ifi %EV%==yes       QPBSCORE_ACIDIFICATION_EV
$ifi %EV%==yes       QPBSCORE_ACIDIFICATION_DIESEL
$ifi %CCS%==yes      QPBSCORE_ACIDIFICATION_CC_PS
$ifi %CCS%==yes      QPBSCORE_ACIDIFICATION_CC_STO

* === Resource Use (Minerals and Metals) =======================================
QPBSCORE_RESOURCE
$ifi not %PB_all%==yes $ifi not %TL_RESOURCE_ALLOWED%==yes QPBLIM_RESOURCE_TL_NO
$ifi     %PB_all%==yes $ifi     %TL_RESOURCE_ALLOWED%==yes QPBLIM_RESOURCE_TL
$ifi     %PB_all%==yes $ifi not %TL_RESOURCE_ALLOWED%==yes QPBLIM_RESOURCE_TL_NO
QPBSCORE_RESOURCE_X
$ifi %HYDROGEN%==yes QPBSCORE_RESOURCE_X_H2
$ifi %EV%==yes       QPBSCORE_RESOURCE_EV
$ifi %EV%==yes       QPBSCORE_RESOURCE_DIESEL
$ifi %CCS%==yes      QPBSCORE_RESOURCE_CC_PS
$ifi %CCS%==yes      QPBSCORE_RESOURCE_CC_STO

* === BECCS credit bound (PB modular CCS layer) ===============================
$ifi %CCS%==yes      QBECCS_CREDIT_BOUND

* === Capture accumulators: total fossil/biogenic CO2 captured, summed once so the
* === CC_PS/CC_STO/credit rows reference 2 vars instead of re-summing all CCS plants ===
$ifi %CCS%==yes      QCO2CAP_BIO
$ifi %CCS%==yes      QCO2CAP_FOS

* === Matrix-generation accelerator equations ==================================
QVGE_AGG
QVGH_AGG
$ifi %HYDROGEN%==yes QVH2_AGG
$ifi %CCS%==yes      QVGF_AGG

* === EU-wide transmission / H2-pipeline capacity caps (optional; off unless set) ===
$if set Elec_TransX_Limit_2040                         QELEC_TRANSX_LIM_2040
$if set Elec_TransX_Limit_2050                         QELEC_TRANSX_LIM_2050
$ifi %H2TransInvest%==yes $if set H2_TransX_Limit_2040 QH2_TRANSX_LIM_2040
$ifi %H2TransInvest%==yes $if set H2_TransX_Limit_2050 QH2_TRANSX_LIM_2050
