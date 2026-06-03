*-------------------------------------------------------------------------------
* PB_qobj.inc  --  PB add-on contribution to the Balmorel objective function
*-------------------------------------------------------------------------------
* Part of the Balmorel Planetary Boundaries (PB) add-on.
*
* Adds a linear transgression penalty to the Balmorel objective. Each
* Transgression Level variable TL_<CAT>(Y) is multiplied by the penalty
* coefficient 1e13 (a "very high" cost per unit of absolute impact above the
* planetary-boundary threshold) and summed. The optimizer therefore treats
* the PB thresholds as soft constraints: feasibility is always preserved
* (TL is a non-negative slack), but exceeding the threshold is enormously
* expensive in objective terms.
*
* Per-category gating (replaces the former single global TL_ALLOWED):
*   %PB_all%=yes -> each of the 10 lines below is included only if its
*                   own TL_<CAT>_ALLOWED flag (declared in base/model/balopt.opt)
*                   is "yes". A category with TL_<CAT>_ALLOWED empty uses the
*                   hard-bound QPBLIM_<CAT>_TL_NO equation instead and adds
*                   nothing to the objective.
*   %PB_all%=no  -> CO2-only mode: only the CO2 contribution is gated by
*                   TL_CO2_ALLOWED.
*
* The 1e13 coefficient was calibrated for a regime where realistic
* transgression magnitudes stay well below 1 (i.e. impact <= threshold).
* If thresholds are tight enough that TL ends up in the 10s or 100s, the
* linear penalty becomes a soft prohibition; consider a piecewise/convex
* form if more nuanced behavior is wanted.
*
* RADIATION (10th category) was activated 2026-05-16; previously the line
* listed only 8 categories (RESOURCE added 2026-05-15).
*
* CHANGE 2026-05-18: the hard-coded 1e13 multipliers were replaced by the
* scalar PB_PENALTY_COEF (declared in PB_pardeclare.inc, default 1e13).
* The default behavior is unchanged, but the scalar can be set to 0 around
* a specific SOLVE to disable the PB penalty for that solve.
*
* Authors: Theo Balanza & Dhruv Sharma
*-------------------------------------------------------------------------------

* --- Full PB mode: each category contributes only if its TL_<CAT>_ALLOWED is yes
$ifi %PB_all%==yes $ifi %TL_CO2_ALLOWED%==yes                       + TL_CO2(Y)*PB_PENALTY_COEF
$ifi %PB_all%==yes $ifi %TL_OZONE_DEPLETION_ALLOWED%==yes           + TL_OZONE_DEPLETION(Y)*PB_PENALTY_COEF
$ifi %PB_all%==yes $ifi %TL_LU_ALLOWED%==yes                        + TL_LU(Y)*PB_PENALTY_COEF
$ifi %PB_all%==yes $ifi %TL_WU_ALLOWED%==yes                        + TL_WU(Y)*PB_PENALTY_COEF
$ifi %PB_all%==yes $ifi %TL_EUTROPHICATION_FRESHWATER_ALLOWED%==yes + TL_EUTROPHICATION_FRESHWATER(Y)*PB_PENALTY_COEF
$ifi %PB_all%==yes $ifi %TL_ECOTOXICITY_FRESHWATER_ALLOWED%==yes    + TL_ECOTOXICITY_FRESHWATER(Y)*PB_PENALTY_COEF
$ifi %PB_all%==yes $ifi %TL_PM_ALLOWED%==yes                        + TL_PM(Y)*PB_PENALTY_COEF
$ifi %PB_all%==yes $ifi %TL_RADIATION_ALLOWED%==yes                 + TL_RADIATION(Y)*PB_PENALTY_COEF
$ifi %PB_all%==yes $ifi %TL_ACIDIFICATION_ALLOWED%==yes             + TL_ACIDIFICATION(Y)*PB_PENALTY_COEF
$ifi %PB_all%==yes $ifi %TL_RESOURCE_ALLOWED%==yes                  + TL_RESOURCE(Y)*PB_PENALTY_COEF

* --- CO2-only mode: only CO2's penalty contribution ----------------------------
$ifi not %PB_all%==yes $ifi %TL_CO2_ALLOWED%==yes + TL_CO2(Y)*PB_PENALTY_COEF

* --- (2026-05-30) S3 dispatch regularization: tiny per-MWh cost on annual electricity
* --- generation (VGE_AGG) to break the degenerate optimal face -> faster crossover.
* --- Gated default-off (PB_DISPATCH_REG); lossless on cost while EPS is tiny.
$ifi %PB_DISPATCH_REG%==yes + PB_DISPATCH_REG_EPS * SUM((IA,G), VGE_AGG(Y,IA,G))

* --- (2026-05-30) S3-EXT: regularize transmission FLOW + storage CHARGE too (the 2050 degeneracy
* --- is spatial [wheeling] + temporal [cycling], not just generation). Discharge = VGE_T, already
* --- in VGE_AGG above (no double-count). All vars POSITIVE. Gated PB_DISPATCH_REG_EXT; H2 behind %HYDROGEN%.
$ifi %PB_DISPATCH_REG_EXT%==yes + PB_DISPATCH_REG_EPS * SUM((IRRRE,IRRRI,S,T)$IXK_HASORPOT(Y,IRRRE,IRRRI), VX_T(Y,IRRRE,IRRRI,S,T))
$ifi %PB_DISPATCH_REG_EXT%==yes + PB_DISPATCH_REG_EPS * SUM((IA,G,S,T)$IAGK_HASORPOT(Y,IA,G), VESTOLOADT(Y,IA,G,S,T) + VESTOLOADTS(Y,IA,G,S,T))
$ifi %PB_DISPATCH_REG_EXT%==yes $ifi %HYDROGEN%==yes + PB_DISPATCH_REG_EPS * SUM((IRRRE,IRRRI,S,T)$IXH2K_HASORPOT(Y,IRRRE,IRRRI), VXH2_T(Y,IRRRE,IRRRI,S,T))
$ifi %PB_DISPATCH_REG_EXT%==yes $ifi %HYDROGEN%==yes + PB_DISPATCH_REG_EPS * SUM((IA,G,S,T)$IAGK_HASORPOT(Y,IA,G), VHYDROGEN_STOLOADT(Y,IA,G,S,T))

* --- (2026-05-31) Local-first hook: scenario-specific dispatch tilt terms (degeneracy tie-break, Path B).
* --- Inert unless the scenario provides data/PB_qobj_local.inc; base behavior unchanged for all other scenarios.
$if EXIST '../data/PB_qobj_local.inc' $include '../data/PB_qobj_local.inc'

* --- BECCS economic credit: -NEG_EMI_CREDIT(Y) * VBECCS_CREDIT / 1000 (kg->t) -
* NEG_EMI_CREDIT is now Y-indexed (2026-05-27) -- see PB_pardeclare.inc.
$ifi %PB%==yes $ifi %CCS%==yes - NEG_EMI_CREDIT(Y) * VBECCS_CREDIT(Y) / IOF1000
