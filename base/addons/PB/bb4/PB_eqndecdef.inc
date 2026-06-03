*-------------------------------------------------------------------------------
* PB_eqndecdef.inc  --  Equation declarations and definitions for the PB add-on
*-------------------------------------------------------------------------------
* Part of the Balmorel Planetary Boundaries (PB) add-on.
*
* Defines the impact-score equations (QPBSCORE_<CAT>_*) and the
* transgression-limit equations (QPBLIM_<CAT>_TL / _TL_NO) for the 10 active
* planetary-boundary impact categories, plus three matrix-generation
* accelerator equations (QV*_AGG) that aggregate per-timeslice production
* variables for use in the impact-score equations.
*
* ORGANIZATION
*   1. EQUATIONS declarations block (lines ~50-110)
*   2. QPBLIM reformulation explanation (lines ~115-160) -- read this first
*      if you intend to consume the .m shadow prices on QPBLIM equations.
*   3. Per-category definition blocks: 10 categories x 5 equations each,
*      in the order  CO2, OZONE_DEPLETION, LU, WU, EUTROPHICATION_FRESHWATER,
*      ECOTOXICITY_FRESHWATER, PM, RADIATION, ACIDIFICATION, RESOURCE.
*      Each category block contains:
*         QPBSCORE_<CAT>          main score (Sum over generators of
*                                 IM_*_prod_elec/_prod_heat/_constr times
*                                 the relevant production/capacity variable)
*         QPBSCORE_<CAT>_X        electricity transmission construction
*         QPBSCORE_<CAT>_X_H2     H2 transmission construction (HYDROGEN only)
*         QPBSCORE_<CAT>_EV       EV battery contribution (EV only)
*         QPBLIM_<CAT>_TL_NO      hard upper bound = threshold  (=L=)
*         QPBLIM_<CAT>_TL         soft bound: IS_sum =E= threshold * TL
*   4. Aggregator equation definitions (QVGE_AGG, QVGH_AGG, QVH2_AGG)
*
* EQUATION STRUCTURE (for one category, the others mirror it)
*
*   QPBSCORE_<CAT>(Y)..
*     Sum over generators (IA, G) where the (Y, IA, G) capacity bucket is
*     active (IAGK_HASORPOT filter) of the four contributions:
*       (a) electricity production:  IM_*_prod_elec * 1000 * VGE_AGG
*       (b) H2 production:           IM_*_prod_elec * 1000 * VH2_AGG  [HYDROGEN]
*       (c) heat production:         IM_*_prod_heat * 1000 * VGH_AGG
*       (d) construction:            VGKNACCUMNET * 1000 * IM_*_constr / lifetime
*     equals IS_<CAT>(Y).
*
*     NOTE on term (b): The H2-production term reuses the SAME IM_*_prod_elec
*     coefficient as electricity (a), not a separate IM_*_prod_h2. This is
*     INTENTIONAL: the per-kWh-of-output direct-emission factor for an H2-
*     producing generator captures whatever direct emissions accompany H2
*     output (e.g. ~0 for electrolysers powered by clean grid, non-zero for
*     SMR / biomethane). For electrolysers, the upstream electricity emissions
*     are accounted by the ELECTRICITY-PRODUCING generator's own term (a),
*     NOT by this term (b), so there is no double-counting.
*     IM_*_prod_elec for electrolysers is empirically near zero (e.g.
*     IM_CO2_prod_elec(GNR_ELYS_ELEC_AEC) ~ 5e-4 kg/kWh), reflecting only
*     direct (non-grid) emissions during operation.
*
*   QPBSCORE_<CAT>_X(Y)..
*     Sum over transmission corridors (IRE -> IRI) of
*         VXKNACCUMNET(Y, IRE, IRI) * 1000 / IXKLIFETIME
*           * PB_LCA_DATA_X(IRE, IRI, Y, 'LCA_<CAT>_constr')
*     equals IS_<CAT>_X(Y).
*
*   QPBSCORE_<CAT>_X_H2(Y)..  symmetric, using PB_LCA_DATA_X_H2.
*
*   QPBSCORE_<CAT>_EV(Y)..
*     Two-part sum across regions IR:
*       (a) chassis impact:  PB_LCA_DATA_EV('CAR_EV_WITHOUT_BATTERY', ...) / 30
*                            * EV_BEV_available(Y, IR)
*       (b) cyclic battery degradation:
*             Sum (IS3, T) of IHOURSINST * IHOURFRAC
*               * PB_LCA_DATA_EV('CAR_EV_ONLY_BATTERY', ...)
*               / EV_BEV_batsize(Y)
*               * EV_BEV_degcyc(Y)
*               * VEV_G2V_BEV(Y, IR, IS3, T)
*     equals IS_<CAT>_EV(Y).
*
*   QPBLIM_<CAT>_TL_NO(Y)..   IS_sum =L= PB_THRESHOLDS_DATA(Y, sector);
*   QPBLIM_<CAT>_TL(Y)..      IS_sum =E= PB_THRESHOLDS_DATA(Y, sector) * TL_<CAT>;
*
* where IS_sum = IS_<CAT> + IS_<CAT>_X + IS_<CAT>_X_H2 + IS_<CAT>_EV.
*
* RADIATION (10th category, 2026-05-16): previously absent. The IM_Radiation_*
* parameters and LCA_Radiation_* data columns existed in the data layer but
* no model equations referenced them. Now added in full, mirroring all other
* categories.
*
* Authors: Theo Balanza & Dhruv Sharma
*-------------------------------------------------------------------------------


* =============================================================================
* SECTION 1: EQUATIONS DECLARATIONS
* =============================================================================

Equations
* --- Climate Change (CO2) ---
QPBSCORE_CO2(Y)         "Annual impact score: climate change (kg CO2-eq)"
QPBSCORE_CO2_X(Y)
QPBSCORE_X_BASE(Y)     "Elec-transmission LCA rank-1 base coupling (PB_X_RANKFIX)"
QPBSCORE_CO2_X_H2(Y)
QPBSCORE_X_H2_BASE(Y)  "H2-transmission LCA rank-1 base coupling (PB_XH2_RANKFIX)"
QPBSCORE_CO2_EV(Y)
QPBLIM_CO2_TL_NO(Y)     "Hard PB limit for climate change"
QPBLIM_CO2_TL(Y)        "Soft PB limit for climate change (with transgression slack)"

* --- Stratospheric Ozone Depletion ---
QPBSCORE_OZONE_DEPLETION(Y)         "Annual impact score: ozone depletion (kg CFC11-eq)"
QPBSCORE_OZONE_DEPLETION_X(Y)
QPBSCORE_OZONE_DEPLETION_X_H2(Y)
QPBSCORE_OZONE_DEPLETION_EV(Y)
QPBLIM_OZONE_DEPLETION_TL_NO(Y)     "Hard PB limit for ozone depletion"
QPBLIM_OZONE_DEPLETION_TL(Y)        "Soft PB limit for ozone depletion"

* --- Land Use ---
QPBSCORE_LU(Y)          "Annual impact score: land use (Pt)"
QPBSCORE_LU_X(Y)
QPBSCORE_LU_X_H2(Y)
QPBSCORE_LU_EV(Y)
QPBLIM_LU_TL_NO(Y)      "Hard PB limit for land use"
QPBLIM_LU_TL(Y)         "Soft PB limit for land use"

* --- Water Use ---
QPBSCORE_WU(Y)          "Annual impact score: water use (m3 deprivation)"
QPBSCORE_WU_X(Y)
QPBSCORE_WU_X_H2(Y)
QPBSCORE_WU_EV(Y)
QPBLIM_WU_TL_NO(Y)      "Hard PB limit for water use"
QPBLIM_WU_TL(Y)         "Soft PB limit for water use"

* --- Freshwater Eutrophication ---
QPBSCORE_EUTROPHICATION_FRESHWATER(Y)         "Annual impact score: freshwater eutrophication (kg P-eq)"
QPBSCORE_EUTROPHICATION_FRESHWATER_X(Y)
QPBSCORE_EUTROPHICATION_FRESHWATER_X_H2(Y)
QPBSCORE_EUTROPHICATION_FRESHWATER_EV(Y)
QPBLIM_EUTROPHICATION_FRESHWATER_TL_NO(Y)     "Hard PB limit for freshwater eutrophication"
QPBLIM_EUTROPHICATION_FRESHWATER_TL(Y)        "Soft PB limit for freshwater eutrophication"

* --- Freshwater Ecotoxicity ---
QPBSCORE_ECOTOXICITY_FRESHWATER(Y)         "Annual impact score: freshwater ecotoxicity (CTUe)"
QPBSCORE_ECOTOXICITY_FRESHWATER_X(Y)
QPBSCORE_ECOTOXICITY_FRESHWATER_X_H2(Y)
QPBSCORE_ECOTOXICITY_FRESHWATER_EV(Y)
QPBLIM_ECOTOXICITY_FRESHWATER_TL_NO(Y)     "Hard PB limit for freshwater ecotoxicity"
QPBLIM_ECOTOXICITY_FRESHWATER_TL(Y)        "Soft PB limit for freshwater ecotoxicity"

* --- Particulate Matter Formation ---
QPBSCORE_PM(Y)          "Annual impact score: particulate matter (disease incidence)"
QPBSCORE_PM_X(Y)
QPBSCORE_PM_X_H2(Y)
QPBSCORE_PM_EV(Y)
QPBLIM_PM_TL_NO(Y)      "Hard PB limit for particulate matter"
QPBLIM_PM_TL(Y)         "Soft PB limit for particulate matter"

* --- Ionising Radiation ---
QPBSCORE_RADIATION(Y)          "Annual impact score: ionising radiation (kBq U-235-eq)"
QPBSCORE_RADIATION_X(Y)
QPBSCORE_RADIATION_X_H2(Y)
QPBSCORE_RADIATION_EV(Y)
QPBLIM_RADIATION_TL_NO(Y)      "Hard PB limit for ionising radiation"
QPBLIM_RADIATION_TL(Y)         "Soft PB limit for ionising radiation"

* --- Terrestrial Acidification ---
QPBSCORE_ACIDIFICATION(Y)          "Annual impact score: acidification (mol H+-eq)"
QPBSCORE_ACIDIFICATION_X(Y)
QPBSCORE_ACIDIFICATION_X_H2(Y)
QPBSCORE_ACIDIFICATION_EV(Y)
QPBLIM_ACIDIFICATION_TL_NO(Y)      "Hard PB limit for acidification"
QPBLIM_ACIDIFICATION_TL(Y)         "Soft PB limit for acidification"

* --- Resource Use (Minerals and Metals) ---
QPBSCORE_RESOURCE(Y)          "Annual impact score: resource use (kg Sb-eq)"
QPBSCORE_RESOURCE_X(Y)
QPBSCORE_RESOURCE_X_H2(Y)
QPBSCORE_RESOURCE_EV(Y)
QPBLIM_RESOURCE_TL_NO(Y)      "Hard PB limit for resource use"
QPBLIM_RESOURCE_TL(Y)         "Soft PB limit for resource use"

* --- CAR_DIESEL (Component 2, 2026-05-26): one per PB category ---
QPBSCORE_CO2_DIESEL(Y)                         "Diesel car contribution to climate change IS (annualized)"
QPBSCORE_OZONE_DEPLETION_DIESEL(Y)             "Diesel car contribution to ozone depletion IS"
QPBSCORE_LU_DIESEL(Y)                          "Diesel car contribution to land use IS"
QPBSCORE_WU_DIESEL(Y)                          "Diesel car contribution to water use IS"
QPBSCORE_EUTROPHICATION_FRESHWATER_DIESEL(Y)   "Diesel car contribution to freshwater eutrophication IS"
QPBSCORE_ECOTOXICITY_FRESHWATER_DIESEL(Y)      "Diesel car contribution to freshwater ecotoxicity IS"
QPBSCORE_PM_DIESEL(Y)                          "Diesel car contribution to particulate matter IS"
QPBSCORE_RADIATION_DIESEL(Y)                   "Diesel car contribution to ionising radiation IS"
QPBSCORE_ACIDIFICATION_DIESEL(Y)               "Diesel car contribution to acidification IS"
QPBSCORE_RESOURCE_DIESEL(Y)                    "Diesel car contribution to resource use IS"

QPBSCORE_CO2_CC_PS(Y)                          "CC_PS contribution to climate change impact score"
QPBSCORE_CO2_CC_STO(Y)                         "CC_STO contribution to climate change impact score"
QPBSCORE_OZONE_DEPLETION_CC_PS(Y)              "CC_PS contribution to ozone depletion IS"
QPBSCORE_OZONE_DEPLETION_CC_STO(Y)             "CC_STO contribution to ozone depletion IS"
QPBSCORE_LU_CC_PS(Y)                           "CC_PS contribution to land use IS"
QPBSCORE_LU_CC_STO(Y)                          "CC_STO contribution to land use IS"
QPBSCORE_WU_CC_PS(Y)                           "CC_PS contribution to water use IS"
QPBSCORE_WU_CC_STO(Y)                          "CC_STO contribution to water use IS"
QPBSCORE_EUTROPHICATION_FRESHWATER_CC_PS(Y)    "CC_PS contribution to freshwater eutrophication IS"
QPBSCORE_EUTROPHICATION_FRESHWATER_CC_STO(Y)   "CC_STO contribution to freshwater eutrophication IS"
QPBSCORE_ECOTOXICITY_FRESHWATER_CC_PS(Y)       "CC_PS contribution to freshwater ecotoxicity IS"
QPBSCORE_ECOTOXICITY_FRESHWATER_CC_STO(Y)      "CC_STO contribution to freshwater ecotoxicity IS"
QPBSCORE_PM_CC_PS(Y)                           "CC_PS contribution to particulate matter IS"
QPBSCORE_PM_CC_STO(Y)                          "CC_STO contribution to particulate matter IS"
QPBSCORE_RADIATION_CC_PS(Y)                    "CC_PS contribution to ionising radiation IS"
QPBSCORE_RADIATION_CC_STO(Y)                   "CC_STO contribution to ionising radiation IS"
QPBSCORE_ACIDIFICATION_CC_PS(Y)                "CC_PS contribution to acidification IS"
QPBSCORE_ACIDIFICATION_CC_STO(Y)               "CC_STO contribution to acidification IS"
QPBSCORE_RESOURCE_CC_PS(Y)                     "CC_PS contribution to resource use IS"
QPBSCORE_RESOURCE_CC_STO(Y)                    "CC_STO contribution to resource use IS"
QBECCS_CREDIT_BOUND(Y)                         "BECCS credit upper bound = biogenic stored CO2"
QCO2CAP_BIO(Y)                                 "Accumulator: total biogenic CO2 captured by CCS plants"
QCO2CAP_FOS(Y)                                 "Accumulator: total fossil CO2 captured by CCS plants"

* --- Matrix-generation accelerator equations ---
QVGE_AGG(Y,AAA,G)       "Defines VGE_AGG as the annual (S,T)-weighted sum of electricity production"
QVGH_AGG(Y,AAA,G)       "Defines VGH_AGG as the annual (S,T)-weighted sum of heat production"
$ifi %HYDROGEN%==yes QVH2_AGG(Y,AAA,G)    "Defines VH2_AGG as the annual (S,T)-weighted sum of H2 + biomethane flows"
$ifi %CCS%==yes QVGF_AGG(Y,AAA,G)         "Defines VGF_AGG as the annual (S,T)-weighted sum of fuel input for CCS_G plants (PB modular CCS accelerator, 2026-05-26)"
;


* =============================================================================
* SECTION 1b: GENERATOR-CONSTRUCTION FACTOR FIX (2026-05-17)
* -----------------------------------------------------------------------------
* The original upstream PB add-on had the generator-construction term
*     (VGKNACCUMNET(Y,IA,G) * 1000 * 1000) * IM_*_constr(Y,G) / GDATA(G,'GDLIFETIME')
* with a factor of 10^6 on capacity. Given the documented units:
*     VGKNACCUMNET in MW,  IM_*_constr in kg/kW (or impact/kW),  lifetime in yr,
* the correct conversion is MW * 1000 (kW/MW) * (kg/kW) / yr = kg/yr -- only
* a single 10^3 factor is needed (MW -> kW). The original 10^6 over-counted
* construction emissions/impacts by 1000x.
*
* The transmission analogue QPBSCORE_<CAT>_X already uses the correct factor:
*     SUM((IRE,IRI), VXKNACCUMNET(Y,IRE,IRI) * 1000 / IXKLIFETIME * PB_LCA_DATA_X(...))
* (VXKNACCUMNET in MW, 1000 converts to kW, /IXKLIFETIME is transmission lifetime,
*  PB_LCA_DATA_X in impact/kW). This served as the reference for the fix.
*
* Effect on past results: in the previous EU run with x100 multiplied
* thresholds, ~80% of IS_CO2 came from this over-counted construction term;
* TL_CO2 was reported as 0.64 but is ~5x smaller (0.13) after the fix.
* With Mescal physical thresholds, this fix is critical -- otherwise
* TL values would be roughly 5x inflated.
* =============================================================================


* =============================================================================
* SECTION 2: QPBLIM EQUATION REFORMULATION (read before consuming .m values)
* -----------------------------------------------------------------------------
* QPBLIM equations were reformulated 2026-05-15 for numerical conditioning.
*
* ORIGINAL FORM (do not uncomment; archived in PB_eqndecdef.inc.bak files):
*     (IS_sum) / PB_THRESHOLDS_DATA(Y, sector) =E= TL(Y);     [TL form]
*     (IS_sum) / PB_THRESHOLDS_DATA(Y, sector) =L= 1;         [hard form, _NO]
*
* PROBLEM with the original form: PB_THRESHOLDS_DATA values are very large
* (e.g. Ecotoxicity = 6.46e+15 with the old x100 multipliers, or ~5e+12 with
* realistic downscaled values). Dividing by them puts a coefficient on the
* order of 1.55e-16 on the IS_* variables in the CPLEX constraint matrix --
* that's effectively at the noise floor of IEEE-754 double-precision
* arithmetic (machine epsilon ~2e-16). CPLEX's barrier method then loses
* precision during KKT factorization and crossover gets stuck in pivot hell.
* Empirical: the EU run took 71 hours under the original formulation.
*
* NEW FORM (used below): multiply both sides by PB_THRESHOLDS_DATA.
*   Coefficients on IS_* become 1 (clean).
*   Coefficients on TL become the threshold value itself (large but
*   well-behaved, ~1e15 max). CPLEX handles large coefficients via row
*   scaling without precision loss.
* Empirical: the EU run completes in 2h 50m under the new formulation,
* with bit-identical objective. ~25x speedup.
*
* IMPORTANT FOR ANYONE READING SHADOW PRICES (.m):
*   In the ORIGINAL form, QPBLIM_<CAT>_TL.m had units of
*       "objective change per unit fraction-of-threshold-transgressed"
*       (a dimensionless quantity).
*   In the NEW form, QPBLIM_<CAT>_TL.m has units of
*       "objective change per unit of absolute impact (kg CO2, kg PM, etc.)"
*   To recover the ORIGINAL interpretation (the "old" shadow price), do:
*       old_marginal = QPBLIM_<CAT>_TL.m * PB_THRESHOLDS_DATA(Y, sector)
*
*   In plain language: the old shadow price said "how much does the objective
*   change if the system transgresses by 1% more of its threshold?" The new
*   shadow price says "how much does the objective change if the system
*   emits 1 more kg (or m3, etc.)?" They differ by the threshold value --
*   multiply to convert new -> old.
*
*   Variable LEVELS (.l) are unchanged: TL_<CAT>.l and IS_<CAT>.l mean
*   exactly what they meant before.
* =============================================================================


* =============================================================================
* SECTION 2b: COHORT-FROZEN-IM CONSTRUCTION CONVENTION (PB_COHORT_CONSTR flag)
* -----------------------------------------------------------------------------
* The construction term in each QPBSCORE_<CAT>(Y) equation has two forms,
* selected at compile time by the PB_COHORT_CONSTR global (declared in
* base/model/balopt.opt; default empty = legacy form).
*
* LEGACY FORM (PB_COHORT_CONSTR empty, default):
*     + (VGKNACCUMNET(Y, IA, G) * 1000) * IM_<CAT>_constr(Y, G) / lifetime
*   Uses the cumulative-capacity stock at Y and the accounting-year's
*   prospective IM factor. Because IM_<CAT>_constr(Y, G) varies with Y
*   (typically a 10-35% decline 2025 -> 2050 as the upstream system
*   decarbonises), the legacy form does NOT preserve total construction
*   emissions across an asset's lifetime: a 2030-built asset contributes
*   IM_<CAT>_constr(2030, G)/lifetime at Y=2030 but only
*   IM_<CAT>_constr(2050, G)/lifetime at Y=2050.
*
* COHORT-FROZEN-IM FORM (PB_COHORT_CONSTR=yes):
*     + SUM(IYALIAS2 $ (YVALUE(IYALIAS2) LE YVALUE(Y) AND
*                       YVALUE(Y) - YVALUE(IYALIAS2) LT GDATA(G,'GDLIFETIME')),
*           (VGKN(IYALIAS2, IA, G) + NEW_GKFX(IYALIAS2, IA, G)) * 1000
*           * IM_<CAT>_constr(IYALIAS2, G) / GDATA(G,'GDLIFETIME'))
*   Per-cohort summation: each cohort T (commission year) contributes its own
*   frozen-IM annual amortised share for every Y within [T, T + lifetime).
*   Total construction emissions over the asset's life = capacity *
*   IM_<CAT>_constr(T, G), matching the physical truth of when the construction
*   event occurred. This mirrors the convention Balmorel already uses for
*   investment costs in OUTPUT_SUMMARY.inc (per-cohort sum with frozen
*   ANNUITYCG and GINVCOST per generator). The IYALIAS2 alias of Y is
*   declared in Balmorelbb4.inc:143.
*
* COMPONENTS OF THE COHORT SUM
*   VGKN(T, IA, G)       LP-endogenous new investment committed at cohort
*                        year T. Preserved per-cohort across rolling-foresight
*                        iterations (verified empirically in all_endofmodel.gdx
*                        of the 4_Scenario_Nordic_RF_2025_30_40_50_Bank run).
*   NEW_GKFX(T, IA, G)   Exogenous additions in year T (positive
*                        year-on-year GKFX delta). Declared in PB_pardeclare.inc,
*                        assigned in PB_pardefine.inc, captured once before
*                        any SOLVE.
*
* PRE-PLANNING-HORIZON LEGACY CAPACITY (e.g., 1970 hydro, 1980 nuclear)
*   The cohort sum iterates T over the simulation set Y(YYY). T values before
*   Y[1] (typically 2025) are NOT in the sum, so legacy capacity that was
*   in service before the earliest simulation year contributes ZERO to the
*   construction term. This is intentional: the PB threshold
*   (PB_THRESHOLDS_DATA, calibrated from the Exiobase 2024 trajectory)
*   already accounts for emissions through 2024, so legacy plants'
*   construction emissions are considered pre-charged. Their operational
*   impact in 2025+ is still counted via the IM_<CAT>_prod_elec / _prod_heat
*   terms whenever they are dispatched (unchanged from the legacy form).
*
* INDEPENDENT OF PB_ROLLING_FORESIGHT
*   The cohort sum references only Y, IYALIAS2, VGKN, NEW_GKFX, and the
*   compile-time PB_COHORT_CONSTR flag -- none of which depend on the
*   rolling-foresight machinery. The convention works identically with
*   PB_ROLLING_FORESIGHT yes (cohort sum inside each rolling window's IY411)
*   or empty (cohort sum inside the standard myopic-recursive LOOP).
* =============================================================================


* =============================================================================
* SECTION 3: EQUATION DEFINITIONS (per impact category)
* =============================================================================


*------------------------------------------------------------------------------
* Climate Change (CO2)
*------------------------------------------------------------------------------
QPBSCORE_CO2(Y)..
    PB_ROWSCALE('SOS_CO2_sector') * SUM((IA,G)$IAGK_HASORPOT(Y,IA,G),
            IM_CO2_prod_elec(Y,G) * 1000 * VGE_AGG(Y,IA,G)
$ifi %HYDROGEN%==yes  + IM_CO2_prod_elec(Y,G) * 1000 * VH2_AGG(Y,IA,G)
          + IM_CO2_prod_heat(Y,G) * 1000 * VGH_AGG(Y,IA,G)
*         --- Construction term: cohort-frozen-IM (PB_COHORT_CONSTR=yes) or
*         --- legacy VGKNACCUMNET form (default). See SECTION 2b for rationale.
$ifi     %PB_COHORT_CONSTR%==yes          + SUM(IYALIAS2 $ ((YVALUE(IYALIAS2) LE YVALUE(Y)) AND (YVALUE(Y) - YVALUE(IYALIAS2) LT GDATA(G,'GDLIFETIME'))), (VGKN(IYALIAS2,IA,G) + NEW_GKFX(IYALIAS2,IA,G)) * 1000 * IM_CO2_constr(IYALIAS2,G) / GDATA(G,'GDLIFETIME'))
$ifi not %PB_COHORT_CONSTR%==yes          + (VGKNACCUMNET(Y,IA,G) * 1000) * IM_CO2_constr(Y,G) / GDATA(G,'GDLIFETIME')
    )
    =e= PB_ROWSCALE('SOS_CO2_sector') * IS_CO2(Y);

*
* --- RANK-FIX TOGGLE (2026-05-30): PB_X_RANKFIX collapses the rank-1 _X (elec transmission)
* --- score block, exactly as PB_XH2_RANKFIX does for _X_H2. PB_LCA_DATA_X is also EXACTLY
* --- rank-1 per year (verified: category ratios constant to ~2e-9 across all 206 elec
* --- line-pairs), so the 10 IS_<cat>_X are scalar multiples -> rank-deficient block. It
* --- stays well-conditioned while the grid actively builds (2030) but goes singular as the
* --- grid matures and lines hit bounds (2040/2050) -- the confirmed later-cohort stall.
* --- RANKFIX=yes routes the single Sigma-over-lines coupling into IS_X_BASE and recovers
* --- each category by IS_<cat>_X = PB_X_INTENSITY(cat) * IS_X_BASE (lossless ~1e-9); all 10
* --- IS_<cat>_X stay LIVE in QPBLIM. Default 'no' => byte-identical to the original form.
$if not set PB_X_RANKFIX $setglobal PB_X_RANKFIX no
*
* QPBSCORE_X_BASE: single rank-1 base coupling to the elec grid (registered only under RANKFIX).
QPBSCORE_X_BASE(Y)..
    IS_X_BASE(Y) =e= SUM((IRE,IRI), VXKNACCUMNET(Y,IRE,IRI) * 1000 / IXKLIFETIME * PB_X_LINE_SCALE(IRE,IRI,Y))
;
QPBSCORE_CO2_X(Y)..
    PB_ROWSCALE_X('SOS_CO2_sector') * IS_CO2_X(Y) =e=
$ifi     %PB_X_RANKFIX%==yes          PB_ROWSCALE_X('SOS_CO2_sector') * PB_X_INTENSITY(Y,'LCA_CO2_constr') * IS_X_BASE(Y)
$ifi not %PB_X_RANKFIX%==yes          PB_ROWSCALE_X('SOS_CO2_sector') * SUM((IRE,IRI), VXKNACCUMNET(Y,IRE,IRI) * 1000 / IXKLIFETIME * PB_LCA_DATA_X(IRE,IRI,Y,'LCA_CO2_constr'))
;

* QPBSCORE_CO2_X_H2: H2 transmission construction CO2. Uses the H2 line variable
* VXH2KNACCUMNET (NOT the elec VXKNACCUMNET -- they are distinct; coupling this term
* to the elec variable would wrongly make it ride on elec capacity x H2 LCA). Gated
* on H2TransInvest: with H2 transmission investment off there are no H2 lines, so
* IS_CO2_X_H2 = 0. IXKLIFETIME (50yr) is shared with the elec _X term by design.
*
* PB_XH2_ACCUM selects which accumulation variable the 10 _X_H2 score equations
* couple to. Default VXH2KNACCUMNET (the physically-correct H2-line accumulation).
$if not set PB_XH2_ACCUM $setglobal PB_XH2_ACCUM VXH2KNACCUMNET
*
* --- RANK-FIX TOGGLE (2026-05-30): PB_XH2_RANKFIX collapses the rank-1 _X_H2 block.
* --- PB_LCA_DATA_X_H2 is exactly rank-1 per year, so all 10 IS_<cat>_X_H2 are scalar
* --- multiples of ONE base coupling -> rank-deficient block -> basis singularity when
* --- the H2 grid is near-empty. RANKFIX=yes feeds the single Sigma-over-lines coupling
* --- into IS_X_H2_BASE and recovers each category by the EXACT scaling
* --- IS_<cat>_X_H2 = PB_XH2_INTENSITY(cat) * IS_X_H2_BASE (lossless ~1e-10), keeping all
* --- 10 IS_<cat>_X_H2 LIVE in QPBLIM so the H2-pipeline optimisation is unchanged.
* --- Default 'no' => byte-identical to the current Sigma form.
$if not set PB_XH2_RANKFIX $setglobal PB_XH2_RANKFIX no
* PB_XH2_SUMTERM: original per-category Sigma fires only when H2 transmission is on AND
* the rank-fix is off (mutually exclusive with the IS_X_H2_BASE scaling term).
$setglobal PB_XH2_SUMTERM %H2TransInvest%
$ifi %PB_XH2_RANKFIX%==yes $setglobal PB_XH2_SUMTERM no
*
* QPBSCORE_X_H2_BASE: the single rank-1 base coupling to the H2 grid (registered only
* under RANKFIX). IS_X_H2_BASE = Sigma_lines accumulated-H2-capacity * neutral line-scale.
QPBSCORE_X_H2_BASE(Y)..
    IS_X_H2_BASE(Y) =e= 0
$ifi %H2TransInvest%==yes  + SUM((IRE,IRI), %PB_XH2_ACCUM%(Y,IRE,IRI) * 1000 / IXKLIFETIME * PB_XH2_LINE_SCALE(IRE,IRI,Y))
;
QPBSCORE_CO2_X_H2(Y)..
    PB_ROWSCALE_X_H2('SOS_CO2_sector') * IS_CO2_X_H2(Y) =e= 0
$ifi %PB_XH2_RANKFIX%==yes  + PB_ROWSCALE_X_H2('SOS_CO2_sector') * PB_XH2_INTENSITY(Y,'LCA_CO2_constr') * IS_X_H2_BASE(Y)
$ifi %PB_XH2_SUMTERM%==yes  + PB_ROWSCALE_X_H2('SOS_CO2_sector') * SUM((IRE,IRI), %PB_XH2_ACCUM%(Y,IRE,IRI) * 1000 / IXKLIFETIME * PB_LCA_DATA_X_H2(IRE,IRI,Y,'LCA_CO2_constr'))
;

QPBSCORE_CO2_EV(Y)..
    PB_ROWSCALE_EV('SOS_CO2_sector') * IS_CO2_EV(Y) =e=
        PB_ROWSCALE_EV('SOS_CO2_sector') * SUM(IR,
            PB_LCA_DATA_EV('CAR_EV_WITHOUT_BATTERY',Y,'LCA_CO2_constr')/IEV_CHASSIS_LIFETIME
              * EV_BEV_available(Y,IR)
          + SUM((IS3,T),
                IHOURSINST(IS3,T) * IHOURFRAC
                  * PB_LCA_DATA_EV('CAR_EV_ONLY_BATTERY',Y,'LCA_CO2_constr')
                  / EV_BEV_batsize(Y) * EV_BEV_degcyc(Y)
                  * VEV_G2V_BEV(Y,IR,IS3,T))
        );

QPBLIM_CO2_TL_NO(Y)..
    (IS_CO2(Y) + IS_CO2_X(Y) + IS_CO2_X_H2(Y) + IS_CO2_EV(Y) + IS_CO2_DIESEL(Y)
     + IS_CO2_CC_PS(Y) + IS_CO2_CC_STO(Y)
     - VBECCS_CREDIT(Y)
    )   =L= PB_THRESHOLDS_DATA(Y,'SOS_CO2_sector');

QPBLIM_CO2_TL(Y)..
    (IS_CO2(Y) + IS_CO2_X(Y) + IS_CO2_X_H2(Y) + IS_CO2_EV(Y) + IS_CO2_DIESEL(Y)
     + IS_CO2_CC_PS(Y) + IS_CO2_CC_STO(Y)
     - VBECCS_CREDIT(Y)
    )   =E= PB_THRESHOLDS_DATA(Y,'SOS_CO2_sector') * TL_CO2(Y);


*------------------------------------------------------------------------------
* Stratospheric Ozone Depletion
*------------------------------------------------------------------------------
QPBSCORE_OZONE_DEPLETION(Y)..
    PB_ROWSCALE('SOS_Ozone_depletion_sector') * SUM((IA,G)$IAGK_HASORPOT(Y,IA,G),
            IM_Ozone_depletion_prod_elec(Y,G) * 1000 * VGE_AGG(Y,IA,G)
$ifi %HYDROGEN%==yes  + IM_Ozone_depletion_prod_elec(Y,G) * 1000 * VH2_AGG(Y,IA,G)
          + IM_Ozone_depletion_prod_heat(Y,G) * 1000 * VGH_AGG(Y,IA,G)
*         --- Construction term: cohort-frozen-IM (PB_COHORT_CONSTR=yes) or
*         --- legacy VGKNACCUMNET form (default). See SECTION 2b for rationale.
$ifi     %PB_COHORT_CONSTR%==yes          + SUM(IYALIAS2 $ ((YVALUE(IYALIAS2) LE YVALUE(Y)) AND (YVALUE(Y) - YVALUE(IYALIAS2) LT GDATA(G,'GDLIFETIME'))), (VGKN(IYALIAS2,IA,G) + NEW_GKFX(IYALIAS2,IA,G)) * 1000 * IM_Ozone_depletion_constr(IYALIAS2,G) / GDATA(G,'GDLIFETIME'))
$ifi not %PB_COHORT_CONSTR%==yes          + (VGKNACCUMNET(Y,IA,G) * 1000) * IM_Ozone_depletion_constr(Y,G) / GDATA(G,'GDLIFETIME')
    )
    =e= PB_ROWSCALE('SOS_Ozone_depletion_sector') * IS_OZONE_DEPLETION(Y);

QPBSCORE_OZONE_DEPLETION_X(Y)..
    PB_ROWSCALE_X('SOS_Ozone_depletion_sector') * IS_OZONE_DEPLETION_X(Y) =e=
$ifi     %PB_X_RANKFIX%==yes          PB_ROWSCALE_X('SOS_Ozone_depletion_sector') * PB_X_INTENSITY(Y,'LCA_Ozone_depletion_constr') * IS_X_BASE(Y)
$ifi not %PB_X_RANKFIX%==yes          PB_ROWSCALE_X('SOS_Ozone_depletion_sector') * SUM((IRE,IRI), VXKNACCUMNET(Y,IRE,IRI) * 1000 / IXKLIFETIME * PB_LCA_DATA_X(IRE,IRI,Y,'LCA_Ozone_depletion_constr'))
;

QPBSCORE_OZONE_DEPLETION_X_H2(Y)..
    PB_ROWSCALE_X_H2('SOS_Ozone_depletion_sector') * IS_OZONE_DEPLETION_X_H2(Y) =e= 0
$ifi %PB_XH2_RANKFIX%==yes  + PB_ROWSCALE_X_H2('SOS_Ozone_depletion_sector') * PB_XH2_INTENSITY(Y,'LCA_Ozone_depletion_constr') * IS_X_H2_BASE(Y)
$ifi %PB_XH2_SUMTERM%==yes  + PB_ROWSCALE_X_H2('SOS_Ozone_depletion_sector') * SUM((IRE,IRI), %PB_XH2_ACCUM%(Y,IRE,IRI) * 1000 / IXKLIFETIME * PB_LCA_DATA_X_H2(IRE,IRI,Y,'LCA_Ozone_depletion_constr'))
;

QPBSCORE_OZONE_DEPLETION_EV(Y)..
    PB_ROWSCALE_EV('SOS_Ozone_depletion_sector') * IS_OZONE_DEPLETION_EV(Y) =e=
        PB_ROWSCALE_EV('SOS_Ozone_depletion_sector') * SUM(IR,
            PB_LCA_DATA_EV('CAR_EV_WITHOUT_BATTERY',Y,'LCA_Ozone_depletion_constr')/IEV_CHASSIS_LIFETIME
              * EV_BEV_available(Y,IR)
          + SUM((IS3,T),
                IHOURSINST(IS3,T) * IHOURFRAC
                  * PB_LCA_DATA_EV('CAR_EV_ONLY_BATTERY',Y,'LCA_Ozone_depletion_constr')
                  / EV_BEV_batsize(Y) * EV_BEV_degcyc(Y)
                  * VEV_G2V_BEV(Y,IR,IS3,T))
        );

QPBLIM_OZONE_DEPLETION_TL_NO(Y)..
    (IS_OZONE_DEPLETION(Y) + IS_OZONE_DEPLETION_X(Y) + IS_OZONE_DEPLETION_X_H2(Y) + IS_OZONE_DEPLETION_EV(Y) + IS_OZONE_DEPLETION_DIESEL(Y)
     + IS_OZONE_DEPLETION_CC_PS(Y) + IS_OZONE_DEPLETION_CC_STO(Y)
    )   =L= PB_THRESHOLDS_DATA(Y,'SOS_Ozone_depletion_sector');

QPBLIM_OZONE_DEPLETION_TL(Y)..
    (IS_OZONE_DEPLETION(Y) + IS_OZONE_DEPLETION_X(Y) + IS_OZONE_DEPLETION_X_H2(Y) + IS_OZONE_DEPLETION_EV(Y) + IS_OZONE_DEPLETION_DIESEL(Y)
     + IS_OZONE_DEPLETION_CC_PS(Y) + IS_OZONE_DEPLETION_CC_STO(Y)
    )   =E= PB_THRESHOLDS_DATA(Y,'SOS_Ozone_depletion_sector') * TL_OZONE_DEPLETION(Y);


*------------------------------------------------------------------------------
* Land Use
*------------------------------------------------------------------------------
QPBSCORE_LU(Y)..
    PB_ROWSCALE('SOS_LU_sector') * SUM((IA,G)$IAGK_HASORPOT(Y,IA,G),
            IM_LU_prod_elec(Y,G) * 1000 * VGE_AGG(Y,IA,G)
$ifi %HYDROGEN%==yes  + IM_LU_prod_elec(Y,G) * 1000 * VH2_AGG(Y,IA,G)
          + IM_LU_prod_heat(Y,G) * 1000 * VGH_AGG(Y,IA,G)
*         --- Construction term: cohort-frozen-IM (PB_COHORT_CONSTR=yes) or
*         --- legacy VGKNACCUMNET form (default). See SECTION 2b for rationale.
$ifi     %PB_COHORT_CONSTR%==yes          + SUM(IYALIAS2 $ ((YVALUE(IYALIAS2) LE YVALUE(Y)) AND (YVALUE(Y) - YVALUE(IYALIAS2) LT GDATA(G,'GDLIFETIME'))), (VGKN(IYALIAS2,IA,G) + NEW_GKFX(IYALIAS2,IA,G)) * 1000 * IM_LU_constr(IYALIAS2,G) / GDATA(G,'GDLIFETIME'))
$ifi not %PB_COHORT_CONSTR%==yes          + (VGKNACCUMNET(Y,IA,G) * 1000) * IM_LU_constr(Y,G) / GDATA(G,'GDLIFETIME')
    )
    =e= PB_ROWSCALE('SOS_LU_sector') * IS_LU(Y);

QPBSCORE_LU_X(Y)..
    PB_ROWSCALE_X('SOS_LU_sector') * IS_LU_X(Y) =e=
$ifi     %PB_X_RANKFIX%==yes          PB_ROWSCALE_X('SOS_LU_sector') * PB_X_INTENSITY(Y,'LCA_LU_constr') * IS_X_BASE(Y)
$ifi not %PB_X_RANKFIX%==yes          PB_ROWSCALE_X('SOS_LU_sector') * SUM((IRE,IRI), VXKNACCUMNET(Y,IRE,IRI) * 1000 / IXKLIFETIME * PB_LCA_DATA_X(IRE,IRI,Y,'LCA_LU_constr'))
;

QPBSCORE_LU_X_H2(Y)..
    PB_ROWSCALE_X_H2('SOS_LU_sector') * IS_LU_X_H2(Y) =e= 0
$ifi %PB_XH2_RANKFIX%==yes  + PB_ROWSCALE_X_H2('SOS_LU_sector') * PB_XH2_INTENSITY(Y,'LCA_LU_constr') * IS_X_H2_BASE(Y)
$ifi %PB_XH2_SUMTERM%==yes  + PB_ROWSCALE_X_H2('SOS_LU_sector') * SUM((IRE,IRI), %PB_XH2_ACCUM%(Y,IRE,IRI) * 1000 / IXKLIFETIME * PB_LCA_DATA_X_H2(IRE,IRI,Y,'LCA_LU_constr'))
;

QPBSCORE_LU_EV(Y)..
    PB_ROWSCALE_EV('SOS_LU_sector') * IS_LU_EV(Y) =e=
        PB_ROWSCALE_EV('SOS_LU_sector') * SUM(IR,
            PB_LCA_DATA_EV('CAR_EV_WITHOUT_BATTERY',Y,'LCA_LU_constr')/IEV_CHASSIS_LIFETIME
              * EV_BEV_available(Y,IR)
          + SUM((IS3,T),
                IHOURSINST(IS3,T) * IHOURFRAC
                  * PB_LCA_DATA_EV('CAR_EV_ONLY_BATTERY',Y,'LCA_LU_constr')
                  / EV_BEV_batsize(Y) * EV_BEV_degcyc(Y)
                  * VEV_G2V_BEV(Y,IR,IS3,T))
        );

QPBLIM_LU_TL_NO(Y)..
    (IS_LU(Y) + IS_LU_X(Y) + IS_LU_X_H2(Y) + IS_LU_EV(Y) + IS_LU_DIESEL(Y)
     + IS_LU_CC_PS(Y) + IS_LU_CC_STO(Y)
    )   =L= PB_THRESHOLDS_DATA(Y,'SOS_LU_sector');

QPBLIM_LU_TL(Y)..
    (IS_LU(Y) + IS_LU_X(Y) + IS_LU_X_H2(Y) + IS_LU_EV(Y) + IS_LU_DIESEL(Y)
     + IS_LU_CC_PS(Y) + IS_LU_CC_STO(Y)
    )   =E= PB_THRESHOLDS_DATA(Y,'SOS_LU_sector') * TL_LU(Y);


*------------------------------------------------------------------------------
* Water Use
*------------------------------------------------------------------------------
QPBSCORE_WU(Y)..
    PB_ROWSCALE('SOS_WU_sector') * SUM((IA,G)$IAGK_HASORPOT(Y,IA,G),
            IM_WU_prod_elec(Y,G) * 1000 * VGE_AGG(Y,IA,G)
$ifi %HYDROGEN%==yes  + IM_WU_prod_elec(Y,G) * 1000 * VH2_AGG(Y,IA,G)
          + IM_WU_prod_heat(Y,G) * 1000 * VGH_AGG(Y,IA,G)
*         --- Construction term: cohort-frozen-IM (PB_COHORT_CONSTR=yes) or
*         --- legacy VGKNACCUMNET form (default). See SECTION 2b for rationale.
$ifi     %PB_COHORT_CONSTR%==yes          + SUM(IYALIAS2 $ ((YVALUE(IYALIAS2) LE YVALUE(Y)) AND (YVALUE(Y) - YVALUE(IYALIAS2) LT GDATA(G,'GDLIFETIME'))), (VGKN(IYALIAS2,IA,G) + NEW_GKFX(IYALIAS2,IA,G)) * 1000 * IM_WU_constr(IYALIAS2,G) / GDATA(G,'GDLIFETIME'))
$ifi not %PB_COHORT_CONSTR%==yes          + (VGKNACCUMNET(Y,IA,G) * 1000) * IM_WU_constr(Y,G) / GDATA(G,'GDLIFETIME')
    )
    =e= PB_ROWSCALE('SOS_WU_sector') * IS_WU(Y);

QPBSCORE_WU_X(Y)..
    PB_ROWSCALE_X('SOS_WU_sector') * IS_WU_X(Y) =e=
$ifi     %PB_X_RANKFIX%==yes          PB_ROWSCALE_X('SOS_WU_sector') * PB_X_INTENSITY(Y,'LCA_WU_constr') * IS_X_BASE(Y)
$ifi not %PB_X_RANKFIX%==yes          PB_ROWSCALE_X('SOS_WU_sector') * SUM((IRE,IRI), VXKNACCUMNET(Y,IRE,IRI) * 1000 / IXKLIFETIME * PB_LCA_DATA_X(IRE,IRI,Y,'LCA_WU_constr'))
;

QPBSCORE_WU_X_H2(Y)..
    PB_ROWSCALE_X_H2('SOS_WU_sector') * IS_WU_X_H2(Y) =e= 0
$ifi %PB_XH2_RANKFIX%==yes  + PB_ROWSCALE_X_H2('SOS_WU_sector') * PB_XH2_INTENSITY(Y,'LCA_WU_constr') * IS_X_H2_BASE(Y)
$ifi %PB_XH2_SUMTERM%==yes  + PB_ROWSCALE_X_H2('SOS_WU_sector') * SUM((IRE,IRI), %PB_XH2_ACCUM%(Y,IRE,IRI) * 1000 / IXKLIFETIME * PB_LCA_DATA_X_H2(IRE,IRI,Y,'LCA_WU_constr'))
;

QPBSCORE_WU_EV(Y)..
    PB_ROWSCALE_EV('SOS_WU_sector') * IS_WU_EV(Y) =e=
        PB_ROWSCALE_EV('SOS_WU_sector') * SUM(IR,
            PB_LCA_DATA_EV('CAR_EV_WITHOUT_BATTERY',Y,'LCA_WU_constr')/IEV_CHASSIS_LIFETIME
              * EV_BEV_available(Y,IR)
          + SUM((IS3,T),
                IHOURSINST(IS3,T) * IHOURFRAC
                  * PB_LCA_DATA_EV('CAR_EV_ONLY_BATTERY',Y,'LCA_WU_constr')
                  / EV_BEV_batsize(Y) * EV_BEV_degcyc(Y)
                  * VEV_G2V_BEV(Y,IR,IS3,T))
        );

QPBLIM_WU_TL_NO(Y)..
    (IS_WU(Y) + IS_WU_X(Y) + IS_WU_X_H2(Y) + IS_WU_EV(Y) + IS_WU_DIESEL(Y)
     + IS_WU_CC_PS(Y) + IS_WU_CC_STO(Y)
    )   =L= PB_THRESHOLDS_DATA(Y,'SOS_WU_sector');

QPBLIM_WU_TL(Y)..
    (IS_WU(Y) + IS_WU_X(Y) + IS_WU_X_H2(Y) + IS_WU_EV(Y) + IS_WU_DIESEL(Y)
     + IS_WU_CC_PS(Y) + IS_WU_CC_STO(Y)
    )   =E= PB_THRESHOLDS_DATA(Y,'SOS_WU_sector') * TL_WU(Y);


*------------------------------------------------------------------------------
* Freshwater Eutrophication
*------------------------------------------------------------------------------
QPBSCORE_EUTROPHICATION_FRESHWATER(Y)..
    PB_ROWSCALE('SOS_EUTROPHICATION_FRESHWATER_sector') * SUM((IA,G)$IAGK_HASORPOT(Y,IA,G),
            IM_Eutrophication_freshwater_prod_elec(Y,G) * 1000 * VGE_AGG(Y,IA,G)
$ifi %HYDROGEN%==yes  + IM_Eutrophication_freshwater_prod_elec(Y,G) * 1000 * VH2_AGG(Y,IA,G)
          + IM_Eutrophication_freshwater_prod_heat(Y,G) * 1000 * VGH_AGG(Y,IA,G)
*         --- Construction term: cohort-frozen-IM (PB_COHORT_CONSTR=yes) or
*         --- legacy VGKNACCUMNET form (default). See SECTION 2b for rationale.
$ifi     %PB_COHORT_CONSTR%==yes          + SUM(IYALIAS2 $ ((YVALUE(IYALIAS2) LE YVALUE(Y)) AND (YVALUE(Y) - YVALUE(IYALIAS2) LT GDATA(G,'GDLIFETIME'))), (VGKN(IYALIAS2,IA,G) + NEW_GKFX(IYALIAS2,IA,G)) * 1000 * IM_Eutrophication_freshwater_constr(IYALIAS2,G) / GDATA(G,'GDLIFETIME'))
$ifi not %PB_COHORT_CONSTR%==yes          + (VGKNACCUMNET(Y,IA,G) * 1000) * IM_Eutrophication_freshwater_constr(Y,G) / GDATA(G,'GDLIFETIME')
    )
    =e= PB_ROWSCALE('SOS_EUTROPHICATION_FRESHWATER_sector') * IS_EUTROPHICATION_FRESHWATER(Y);

QPBSCORE_EUTROPHICATION_FRESHWATER_X(Y)..
    PB_ROWSCALE_X('SOS_EUTROPHICATION_FRESHWATER_sector') * IS_EUTROPHICATION_FRESHWATER_X(Y) =e=
$ifi     %PB_X_RANKFIX%==yes          PB_ROWSCALE_X('SOS_EUTROPHICATION_FRESHWATER_sector') * PB_X_INTENSITY(Y,'LCA_Eutrophication_freshwater_constr') * IS_X_BASE(Y)
$ifi not %PB_X_RANKFIX%==yes          PB_ROWSCALE_X('SOS_EUTROPHICATION_FRESHWATER_sector') * SUM((IRE,IRI), VXKNACCUMNET(Y,IRE,IRI) * 1000 / IXKLIFETIME * PB_LCA_DATA_X(IRE,IRI,Y,'LCA_Eutrophication_freshwater_constr'))
;

QPBSCORE_EUTROPHICATION_FRESHWATER_X_H2(Y)..
    PB_ROWSCALE_X_H2('SOS_EUTROPHICATION_FRESHWATER_sector') * IS_EUTROPHICATION_FRESHWATER_X_H2(Y) =e= 0
$ifi %PB_XH2_RANKFIX%==yes  + PB_ROWSCALE_X_H2('SOS_EUTROPHICATION_FRESHWATER_sector') * PB_XH2_INTENSITY(Y,'LCA_Eutrophication_freshwater_constr') * IS_X_H2_BASE(Y)
$ifi %PB_XH2_SUMTERM%==yes  + PB_ROWSCALE_X_H2('SOS_EUTROPHICATION_FRESHWATER_sector') * SUM((IRE,IRI), %PB_XH2_ACCUM%(Y,IRE,IRI) * 1000 / IXKLIFETIME * PB_LCA_DATA_X_H2(IRE,IRI,Y,'LCA_Eutrophication_freshwater_constr'))
;

QPBSCORE_EUTROPHICATION_FRESHWATER_EV(Y)..
    PB_ROWSCALE_EV('SOS_EUTROPHICATION_FRESHWATER_sector') * IS_EUTROPHICATION_FRESHWATER_EV(Y) =e=
        PB_ROWSCALE_EV('SOS_EUTROPHICATION_FRESHWATER_sector') * SUM(IR,
            PB_LCA_DATA_EV('CAR_EV_WITHOUT_BATTERY',Y,'LCA_Eutrophication_freshwater_constr')/IEV_CHASSIS_LIFETIME
              * EV_BEV_available(Y,IR)
          + SUM((IS3,T),
                IHOURSINST(IS3,T) * IHOURFRAC
                  * PB_LCA_DATA_EV('CAR_EV_ONLY_BATTERY',Y,'LCA_Eutrophication_freshwater_constr')
                  / EV_BEV_batsize(Y) * EV_BEV_degcyc(Y)
                  * VEV_G2V_BEV(Y,IR,IS3,T))
        );

QPBLIM_EUTROPHICATION_FRESHWATER_TL_NO(Y)..
    (IS_EUTROPHICATION_FRESHWATER(Y) + IS_EUTROPHICATION_FRESHWATER_X(Y)
       + IS_EUTROPHICATION_FRESHWATER_X_H2(Y) + IS_EUTROPHICATION_FRESHWATER_EV(Y) + IS_EUTROPHICATION_FRESHWATER_DIESEL(Y)
     + IS_EUTROPHICATION_FRESHWATER_CC_PS(Y) + IS_EUTROPHICATION_FRESHWATER_CC_STO(Y)
    )   =L= PB_THRESHOLDS_DATA(Y,'SOS_EUTROPHICATION_FRESHWATER_sector');

QPBLIM_EUTROPHICATION_FRESHWATER_TL(Y)..
    (IS_EUTROPHICATION_FRESHWATER(Y) + IS_EUTROPHICATION_FRESHWATER_X(Y)
       + IS_EUTROPHICATION_FRESHWATER_X_H2(Y) + IS_EUTROPHICATION_FRESHWATER_EV(Y) + IS_EUTROPHICATION_FRESHWATER_DIESEL(Y)
     + IS_EUTROPHICATION_FRESHWATER_CC_PS(Y) + IS_EUTROPHICATION_FRESHWATER_CC_STO(Y)
    )   =E= PB_THRESHOLDS_DATA(Y,'SOS_EUTROPHICATION_FRESHWATER_sector') * TL_EUTROPHICATION_FRESHWATER(Y);


*------------------------------------------------------------------------------
* Freshwater Ecotoxicity
*------------------------------------------------------------------------------
QPBSCORE_ECOTOXICITY_FRESHWATER(Y)..
    PB_ROWSCALE('SOS_ECOTOXICITY_FRESHWATER_sector') * SUM((IA,G)$IAGK_HASORPOT(Y,IA,G),
            IM_Ecotoxicity_freshwater_prod_elec(Y,G) * 1000 * VGE_AGG(Y,IA,G)
$ifi %HYDROGEN%==yes  + IM_Ecotoxicity_freshwater_prod_elec(Y,G) * 1000 * VH2_AGG(Y,IA,G)
          + IM_Ecotoxicity_freshwater_prod_heat(Y,G) * 1000 * VGH_AGG(Y,IA,G)
*         --- Construction term: cohort-frozen-IM (PB_COHORT_CONSTR=yes) or
*         --- legacy VGKNACCUMNET form (default). See SECTION 2b for rationale.
$ifi     %PB_COHORT_CONSTR%==yes          + SUM(IYALIAS2 $ ((YVALUE(IYALIAS2) LE YVALUE(Y)) AND (YVALUE(Y) - YVALUE(IYALIAS2) LT GDATA(G,'GDLIFETIME'))), (VGKN(IYALIAS2,IA,G) + NEW_GKFX(IYALIAS2,IA,G)) * 1000 * IM_Ecotoxicity_freshwater_constr(IYALIAS2,G) / GDATA(G,'GDLIFETIME'))
$ifi not %PB_COHORT_CONSTR%==yes          + (VGKNACCUMNET(Y,IA,G) * 1000) * IM_Ecotoxicity_freshwater_constr(Y,G) / GDATA(G,'GDLIFETIME')
    )
    =e= PB_ROWSCALE('SOS_ECOTOXICITY_FRESHWATER_sector') * IS_ECOTOXICITY_FRESHWATER(Y);

QPBSCORE_ECOTOXICITY_FRESHWATER_X(Y)..
    PB_ROWSCALE_X('SOS_ECOTOXICITY_FRESHWATER_sector') * IS_ECOTOXICITY_FRESHWATER_X(Y) =e=
$ifi     %PB_X_RANKFIX%==yes          PB_ROWSCALE_X('SOS_ECOTOXICITY_FRESHWATER_sector') * PB_X_INTENSITY(Y,'LCA_Ecotoxicity_freshwater_constr') * IS_X_BASE(Y)
$ifi not %PB_X_RANKFIX%==yes          PB_ROWSCALE_X('SOS_ECOTOXICITY_FRESHWATER_sector') * SUM((IRE,IRI), VXKNACCUMNET(Y,IRE,IRI) * 1000 / IXKLIFETIME * PB_LCA_DATA_X(IRE,IRI,Y,'LCA_Ecotoxicity_freshwater_constr'))
;

QPBSCORE_ECOTOXICITY_FRESHWATER_X_H2(Y)..
    PB_ROWSCALE_X_H2('SOS_ECOTOXICITY_FRESHWATER_sector') * IS_ECOTOXICITY_FRESHWATER_X_H2(Y) =e= 0
$ifi %PB_XH2_RANKFIX%==yes  + PB_ROWSCALE_X_H2('SOS_ECOTOXICITY_FRESHWATER_sector') * PB_XH2_INTENSITY(Y,'LCA_Ecotoxicity_freshwater_constr') * IS_X_H2_BASE(Y)
$ifi %PB_XH2_SUMTERM%==yes  + PB_ROWSCALE_X_H2('SOS_ECOTOXICITY_FRESHWATER_sector') * SUM((IRE,IRI), %PB_XH2_ACCUM%(Y,IRE,IRI) * 1000 / IXKLIFETIME * PB_LCA_DATA_X_H2(IRE,IRI,Y,'LCA_Ecotoxicity_freshwater_constr'))
;

QPBSCORE_ECOTOXICITY_FRESHWATER_EV(Y)..
    PB_ROWSCALE_EV('SOS_ECOTOXICITY_FRESHWATER_sector') * IS_ECOTOXICITY_FRESHWATER_EV(Y) =e=
        PB_ROWSCALE_EV('SOS_ECOTOXICITY_FRESHWATER_sector') * SUM(IR,
            PB_LCA_DATA_EV('CAR_EV_WITHOUT_BATTERY',Y,'LCA_Ecotoxicity_freshwater_constr')/IEV_CHASSIS_LIFETIME
              * EV_BEV_available(Y,IR)
          + SUM((IS3,T),
                IHOURSINST(IS3,T) * IHOURFRAC
                  * PB_LCA_DATA_EV('CAR_EV_ONLY_BATTERY',Y,'LCA_Ecotoxicity_freshwater_constr')
                  / EV_BEV_batsize(Y) * EV_BEV_degcyc(Y)
                  * VEV_G2V_BEV(Y,IR,IS3,T))
        );

QPBLIM_ECOTOXICITY_FRESHWATER_TL_NO(Y)..
    (IS_ECOTOXICITY_FRESHWATER(Y) + IS_ECOTOXICITY_FRESHWATER_X(Y)
       + IS_ECOTOXICITY_FRESHWATER_X_H2(Y) + IS_ECOTOXICITY_FRESHWATER_EV(Y) + IS_ECOTOXICITY_FRESHWATER_DIESEL(Y)
     + IS_ECOTOXICITY_FRESHWATER_CC_PS(Y) + IS_ECOTOXICITY_FRESHWATER_CC_STO(Y)
    )   =L= PB_THRESHOLDS_DATA(Y,'SOS_ECOTOXICITY_FRESHWATER_sector');

QPBLIM_ECOTOXICITY_FRESHWATER_TL(Y)..
    (IS_ECOTOXICITY_FRESHWATER(Y) + IS_ECOTOXICITY_FRESHWATER_X(Y)
       + IS_ECOTOXICITY_FRESHWATER_X_H2(Y) + IS_ECOTOXICITY_FRESHWATER_EV(Y) + IS_ECOTOXICITY_FRESHWATER_DIESEL(Y)
     + IS_ECOTOXICITY_FRESHWATER_CC_PS(Y) + IS_ECOTOXICITY_FRESHWATER_CC_STO(Y)
    )   =E= PB_THRESHOLDS_DATA(Y,'SOS_ECOTOXICITY_FRESHWATER_sector') * TL_ECOTOXICITY_FRESHWATER(Y);


*------------------------------------------------------------------------------
* Particulate Matter Formation
*------------------------------------------------------------------------------
QPBSCORE_PM(Y)..
    PB_ROWSCALE('SOS_PM_sector') * SUM((IA,G)$IAGK_HASORPOT(Y,IA,G),
            IM_PM_prod_elec(Y,G) * 1000 * VGE_AGG(Y,IA,G)
$ifi %HYDROGEN%==yes  + IM_PM_prod_elec(Y,G) * 1000 * VH2_AGG(Y,IA,G)
          + IM_PM_prod_heat(Y,G) * 1000 * VGH_AGG(Y,IA,G)
*         --- Construction term: cohort-frozen-IM (PB_COHORT_CONSTR=yes) or
*         --- legacy VGKNACCUMNET form (default). See SECTION 2b for rationale.
$ifi     %PB_COHORT_CONSTR%==yes          + SUM(IYALIAS2 $ ((YVALUE(IYALIAS2) LE YVALUE(Y)) AND (YVALUE(Y) - YVALUE(IYALIAS2) LT GDATA(G,'GDLIFETIME'))), (VGKN(IYALIAS2,IA,G) + NEW_GKFX(IYALIAS2,IA,G)) * 1000 * IM_PM_constr(IYALIAS2,G) / GDATA(G,'GDLIFETIME'))
$ifi not %PB_COHORT_CONSTR%==yes          + (VGKNACCUMNET(Y,IA,G) * 1000) * IM_PM_constr(Y,G) / GDATA(G,'GDLIFETIME')
    )
    =e= PB_ROWSCALE('SOS_PM_sector') * IS_PM(Y);

QPBSCORE_PM_X(Y)..
    PB_ROWSCALE_X('SOS_PM_sector') * IS_PM_X(Y) =e=
$ifi     %PB_X_RANKFIX%==yes          PB_ROWSCALE_X('SOS_PM_sector') * PB_X_INTENSITY(Y,'LCA_PM_constr') * IS_X_BASE(Y)
$ifi not %PB_X_RANKFIX%==yes          PB_ROWSCALE_X('SOS_PM_sector') * SUM((IRE,IRI), VXKNACCUMNET(Y,IRE,IRI) * 1000 / IXKLIFETIME * PB_LCA_DATA_X(IRE,IRI,Y,'LCA_PM_constr'))
;

QPBSCORE_PM_X_H2(Y)..
    PB_ROWSCALE_X_H2('SOS_PM_sector') * IS_PM_X_H2(Y) =e= 0
$ifi %PB_XH2_RANKFIX%==yes  + PB_ROWSCALE_X_H2('SOS_PM_sector') * PB_XH2_INTENSITY(Y,'LCA_PM_constr') * IS_X_H2_BASE(Y)
$ifi %PB_XH2_SUMTERM%==yes  + PB_ROWSCALE_X_H2('SOS_PM_sector') * SUM((IRE,IRI), %PB_XH2_ACCUM%(Y,IRE,IRI) * 1000 / IXKLIFETIME * PB_LCA_DATA_X_H2(IRE,IRI,Y,'LCA_PM_constr'))
;

QPBSCORE_PM_EV(Y)..
    PB_ROWSCALE_EV('SOS_PM_sector') * IS_PM_EV(Y) =e=
        PB_ROWSCALE_EV('SOS_PM_sector') * SUM(IR,
            PB_LCA_DATA_EV('CAR_EV_WITHOUT_BATTERY',Y,'LCA_PM_constr')/IEV_CHASSIS_LIFETIME
              * EV_BEV_available(Y,IR)
          + SUM((IS3,T),
                IHOURSINST(IS3,T) * IHOURFRAC
                  * PB_LCA_DATA_EV('CAR_EV_ONLY_BATTERY',Y,'LCA_PM_constr')
                  / EV_BEV_batsize(Y) * EV_BEV_degcyc(Y)
                  * VEV_G2V_BEV(Y,IR,IS3,T))
        );

QPBLIM_PM_TL_NO(Y)..
    (IS_PM(Y) + IS_PM_X(Y) + IS_PM_X_H2(Y) + IS_PM_EV(Y) + IS_PM_DIESEL(Y)
     + IS_PM_CC_PS(Y) + IS_PM_CC_STO(Y)
    )   =L= PB_THRESHOLDS_DATA(Y,'SOS_PM_sector');

QPBLIM_PM_TL(Y)..
    (IS_PM(Y) + IS_PM_X(Y) + IS_PM_X_H2(Y) + IS_PM_EV(Y) + IS_PM_DIESEL(Y)
     + IS_PM_CC_PS(Y) + IS_PM_CC_STO(Y)
    )   =E= PB_THRESHOLDS_DATA(Y,'SOS_PM_sector') * TL_PM(Y);


*------------------------------------------------------------------------------
* Ionising Radiation
*------------------------------------------------------------------------------
QPBSCORE_RADIATION(Y)..
    PB_ROWSCALE('SOS_RADIATION_sector') * SUM((IA,G)$IAGK_HASORPOT(Y,IA,G),
            IM_Radiation_prod_elec(Y,G) * 1000 * VGE_AGG(Y,IA,G)
$ifi %HYDROGEN%==yes  + IM_Radiation_prod_elec(Y,G) * 1000 * VH2_AGG(Y,IA,G)
          + IM_Radiation_prod_heat(Y,G) * 1000 * VGH_AGG(Y,IA,G)
*         --- Construction term: cohort-frozen-IM (PB_COHORT_CONSTR=yes) or
*         --- legacy VGKNACCUMNET form (default). See SECTION 2b for rationale.
$ifi     %PB_COHORT_CONSTR%==yes          + SUM(IYALIAS2 $ ((YVALUE(IYALIAS2) LE YVALUE(Y)) AND (YVALUE(Y) - YVALUE(IYALIAS2) LT GDATA(G,'GDLIFETIME'))), (VGKN(IYALIAS2,IA,G) + NEW_GKFX(IYALIAS2,IA,G)) * 1000 * IM_Radiation_constr(IYALIAS2,G) / GDATA(G,'GDLIFETIME'))
$ifi not %PB_COHORT_CONSTR%==yes          + (VGKNACCUMNET(Y,IA,G) * 1000) * IM_Radiation_constr(Y,G) / GDATA(G,'GDLIFETIME')
    )
    =e= PB_ROWSCALE('SOS_RADIATION_sector') * IS_RADIATION(Y);

QPBSCORE_RADIATION_X(Y)..
    PB_ROWSCALE_X('SOS_RADIATION_sector') * IS_RADIATION_X(Y) =e=
$ifi     %PB_X_RANKFIX%==yes          PB_ROWSCALE_X('SOS_RADIATION_sector') * PB_X_INTENSITY(Y,'LCA_Radiation_constr') * IS_X_BASE(Y)
$ifi not %PB_X_RANKFIX%==yes          PB_ROWSCALE_X('SOS_RADIATION_sector') * SUM((IRE,IRI), VXKNACCUMNET(Y,IRE,IRI) * 1000 / IXKLIFETIME * PB_LCA_DATA_X(IRE,IRI,Y,'LCA_Radiation_constr'))
;

QPBSCORE_RADIATION_X_H2(Y)..
    PB_ROWSCALE_X_H2('SOS_RADIATION_sector') * IS_RADIATION_X_H2(Y) =e= 0
$ifi %PB_XH2_RANKFIX%==yes  + PB_ROWSCALE_X_H2('SOS_RADIATION_sector') * PB_XH2_INTENSITY(Y,'LCA_Radiation_constr') * IS_X_H2_BASE(Y)
$ifi %PB_XH2_SUMTERM%==yes  + PB_ROWSCALE_X_H2('SOS_RADIATION_sector') * SUM((IRE,IRI), %PB_XH2_ACCUM%(Y,IRE,IRI) * 1000 / IXKLIFETIME * PB_LCA_DATA_X_H2(IRE,IRI,Y,'LCA_Radiation_constr'))
;

QPBSCORE_RADIATION_EV(Y)..
    PB_ROWSCALE_EV('SOS_RADIATION_sector') * IS_RADIATION_EV(Y) =e=
        PB_ROWSCALE_EV('SOS_RADIATION_sector') * SUM(IR,
            PB_LCA_DATA_EV('CAR_EV_WITHOUT_BATTERY',Y,'LCA_Radiation_constr')/IEV_CHASSIS_LIFETIME
              * EV_BEV_available(Y,IR)
          + SUM((IS3,T),
                IHOURSINST(IS3,T) * IHOURFRAC
                  * PB_LCA_DATA_EV('CAR_EV_ONLY_BATTERY',Y,'LCA_Radiation_constr')
                  / EV_BEV_batsize(Y) * EV_BEV_degcyc(Y)
                  * VEV_G2V_BEV(Y,IR,IS3,T))
        );

QPBLIM_RADIATION_TL_NO(Y)..
    (IS_RADIATION(Y) + IS_RADIATION_X(Y) + IS_RADIATION_X_H2(Y) + IS_RADIATION_EV(Y) + IS_RADIATION_DIESEL(Y)
     + IS_RADIATION_CC_PS(Y) + IS_RADIATION_CC_STO(Y)
    )   =L= PB_THRESHOLDS_DATA(Y,'SOS_RADIATION_sector');

QPBLIM_RADIATION_TL(Y)..
    (IS_RADIATION(Y) + IS_RADIATION_X(Y) + IS_RADIATION_X_H2(Y) + IS_RADIATION_EV(Y) + IS_RADIATION_DIESEL(Y)
     + IS_RADIATION_CC_PS(Y) + IS_RADIATION_CC_STO(Y)
    )   =E= PB_THRESHOLDS_DATA(Y,'SOS_RADIATION_sector') * TL_RADIATION(Y);


*------------------------------------------------------------------------------
* Terrestrial Acidification
*------------------------------------------------------------------------------
QPBSCORE_ACIDIFICATION(Y)..
    PB_ROWSCALE('SOS_ACIDIFICATION_sector') * SUM((IA,G)$IAGK_HASORPOT(Y,IA,G),
            IM_Acidification_prod_elec(Y,G) * 1000 * VGE_AGG(Y,IA,G)
$ifi %HYDROGEN%==yes  + IM_Acidification_prod_elec(Y,G) * 1000 * VH2_AGG(Y,IA,G)
          + IM_Acidification_prod_heat(Y,G) * 1000 * VGH_AGG(Y,IA,G)
*         --- Construction term: cohort-frozen-IM (PB_COHORT_CONSTR=yes) or
*         --- legacy VGKNACCUMNET form (default). See SECTION 2b for rationale.
$ifi     %PB_COHORT_CONSTR%==yes          + SUM(IYALIAS2 $ ((YVALUE(IYALIAS2) LE YVALUE(Y)) AND (YVALUE(Y) - YVALUE(IYALIAS2) LT GDATA(G,'GDLIFETIME'))), (VGKN(IYALIAS2,IA,G) + NEW_GKFX(IYALIAS2,IA,G)) * 1000 * IM_Acidification_constr(IYALIAS2,G) / GDATA(G,'GDLIFETIME'))
$ifi not %PB_COHORT_CONSTR%==yes          + (VGKNACCUMNET(Y,IA,G) * 1000) * IM_Acidification_constr(Y,G) / GDATA(G,'GDLIFETIME')
    )
    =e= PB_ROWSCALE('SOS_ACIDIFICATION_sector') * IS_ACIDIFICATION(Y);

QPBSCORE_ACIDIFICATION_X(Y)..
    PB_ROWSCALE_X('SOS_ACIDIFICATION_sector') * IS_ACIDIFICATION_X(Y) =e=
$ifi     %PB_X_RANKFIX%==yes          PB_ROWSCALE_X('SOS_ACIDIFICATION_sector') * PB_X_INTENSITY(Y,'LCA_Acidification_constr') * IS_X_BASE(Y)
$ifi not %PB_X_RANKFIX%==yes          PB_ROWSCALE_X('SOS_ACIDIFICATION_sector') * SUM((IRE,IRI), VXKNACCUMNET(Y,IRE,IRI) * 1000 / IXKLIFETIME * PB_LCA_DATA_X(IRE,IRI,Y,'LCA_Acidification_constr'))
;

QPBSCORE_ACIDIFICATION_X_H2(Y)..
    PB_ROWSCALE_X_H2('SOS_ACIDIFICATION_sector') * IS_ACIDIFICATION_X_H2(Y) =e= 0
$ifi %PB_XH2_RANKFIX%==yes  + PB_ROWSCALE_X_H2('SOS_ACIDIFICATION_sector') * PB_XH2_INTENSITY(Y,'LCA_Acidification_constr') * IS_X_H2_BASE(Y)
$ifi %PB_XH2_SUMTERM%==yes  + PB_ROWSCALE_X_H2('SOS_ACIDIFICATION_sector') * SUM((IRE,IRI), %PB_XH2_ACCUM%(Y,IRE,IRI) * 1000 / IXKLIFETIME * PB_LCA_DATA_X_H2(IRE,IRI,Y,'LCA_Acidification_constr'))
;

QPBSCORE_ACIDIFICATION_EV(Y)..
    PB_ROWSCALE_EV('SOS_ACIDIFICATION_sector') * IS_ACIDIFICATION_EV(Y) =e=
        PB_ROWSCALE_EV('SOS_ACIDIFICATION_sector') * SUM(IR,
            PB_LCA_DATA_EV('CAR_EV_WITHOUT_BATTERY',Y,'LCA_Acidification_constr')/IEV_CHASSIS_LIFETIME
              * EV_BEV_available(Y,IR)
          + SUM((IS3,T),
                IHOURSINST(IS3,T) * IHOURFRAC
                  * PB_LCA_DATA_EV('CAR_EV_ONLY_BATTERY',Y,'LCA_Acidification_constr')
                  / EV_BEV_batsize(Y) * EV_BEV_degcyc(Y)
                  * VEV_G2V_BEV(Y,IR,IS3,T))
        );

QPBLIM_ACIDIFICATION_TL_NO(Y)..
    (IS_ACIDIFICATION(Y) + IS_ACIDIFICATION_X(Y) + IS_ACIDIFICATION_X_H2(Y) + IS_ACIDIFICATION_EV(Y) + IS_ACIDIFICATION_DIESEL(Y)
     + IS_ACIDIFICATION_CC_PS(Y) + IS_ACIDIFICATION_CC_STO(Y)
    )   =L= PB_THRESHOLDS_DATA(Y,'SOS_ACIDIFICATION_sector');

QPBLIM_ACIDIFICATION_TL(Y)..
    (IS_ACIDIFICATION(Y) + IS_ACIDIFICATION_X(Y) + IS_ACIDIFICATION_X_H2(Y) + IS_ACIDIFICATION_EV(Y) + IS_ACIDIFICATION_DIESEL(Y)
     + IS_ACIDIFICATION_CC_PS(Y) + IS_ACIDIFICATION_CC_STO(Y)
    )   =E= PB_THRESHOLDS_DATA(Y,'SOS_ACIDIFICATION_sector') * TL_ACIDIFICATION(Y);


*------------------------------------------------------------------------------
* Resource Use (Minerals and Metals)
*------------------------------------------------------------------------------
QPBSCORE_RESOURCE(Y)..
    PB_ROWSCALE('SOS_RESOURCE_sector') * SUM((IA,G)$IAGK_HASORPOT(Y,IA,G),
            IM_Resource_prod_elec(Y,G) * 1000 * VGE_AGG(Y,IA,G)
$ifi %HYDROGEN%==yes  + IM_Resource_prod_elec(Y,G) * 1000 * VH2_AGG(Y,IA,G)
          + IM_Resource_prod_heat(Y,G) * 1000 * VGH_AGG(Y,IA,G)
*         --- Construction term: cohort-frozen-IM (PB_COHORT_CONSTR=yes) or
*         --- legacy VGKNACCUMNET form (default). See SECTION 2b for rationale.
$ifi     %PB_COHORT_CONSTR%==yes          + SUM(IYALIAS2 $ ((YVALUE(IYALIAS2) LE YVALUE(Y)) AND (YVALUE(Y) - YVALUE(IYALIAS2) LT GDATA(G,'GDLIFETIME'))), (VGKN(IYALIAS2,IA,G) + NEW_GKFX(IYALIAS2,IA,G)) * 1000 * IM_Resource_constr(IYALIAS2,G) / GDATA(G,'GDLIFETIME'))
$ifi not %PB_COHORT_CONSTR%==yes          + (VGKNACCUMNET(Y,IA,G) * 1000) * IM_Resource_constr(Y,G) / GDATA(G,'GDLIFETIME')
    )
    =e= PB_ROWSCALE('SOS_RESOURCE_sector') * IS_RESOURCE(Y);

QPBSCORE_RESOURCE_X(Y)..
    PB_ROWSCALE_X('SOS_RESOURCE_sector') * IS_RESOURCE_X(Y) =e=
$ifi     %PB_X_RANKFIX%==yes          PB_ROWSCALE_X('SOS_RESOURCE_sector') * PB_X_INTENSITY(Y,'LCA_Resource_constr') * IS_X_BASE(Y)
$ifi not %PB_X_RANKFIX%==yes          PB_ROWSCALE_X('SOS_RESOURCE_sector') * SUM((IRE,IRI), VXKNACCUMNET(Y,IRE,IRI) * 1000 / IXKLIFETIME * PB_LCA_DATA_X(IRE,IRI,Y,'LCA_Resource_constr'))
;

QPBSCORE_RESOURCE_X_H2(Y)..
    PB_ROWSCALE_X_H2('SOS_RESOURCE_sector') * IS_RESOURCE_X_H2(Y) =e= 0
$ifi %PB_XH2_RANKFIX%==yes  + PB_ROWSCALE_X_H2('SOS_RESOURCE_sector') * PB_XH2_INTENSITY(Y,'LCA_Resource_constr') * IS_X_H2_BASE(Y)
$ifi %PB_XH2_SUMTERM%==yes  + PB_ROWSCALE_X_H2('SOS_RESOURCE_sector') * SUM((IRE,IRI), %PB_XH2_ACCUM%(Y,IRE,IRI) * 1000 / IXKLIFETIME * PB_LCA_DATA_X_H2(IRE,IRI,Y,'LCA_Resource_constr'))
;

QPBSCORE_RESOURCE_EV(Y)..
    PB_ROWSCALE_EV('SOS_RESOURCE_sector') * IS_RESOURCE_EV(Y) =e=
        PB_ROWSCALE_EV('SOS_RESOURCE_sector') * SUM(IR,
            PB_LCA_DATA_EV('CAR_EV_WITHOUT_BATTERY',Y,'LCA_Resource_constr')/IEV_CHASSIS_LIFETIME
              * EV_BEV_available(Y,IR)
          + SUM((IS3,T),
                IHOURSINST(IS3,T) * IHOURFRAC
                  * PB_LCA_DATA_EV('CAR_EV_ONLY_BATTERY',Y,'LCA_Resource_constr')
                  / EV_BEV_batsize(Y) * EV_BEV_degcyc(Y)
                  * VEV_G2V_BEV(Y,IR,IS3,T))
        );

QPBLIM_RESOURCE_TL_NO(Y)..
    (IS_RESOURCE(Y) + IS_RESOURCE_X(Y) + IS_RESOURCE_X_H2(Y) + IS_RESOURCE_EV(Y) + IS_RESOURCE_DIESEL(Y)
     + IS_RESOURCE_CC_PS(Y) + IS_RESOURCE_CC_STO(Y)
    )   =L= PB_THRESHOLDS_DATA(Y,'SOS_RESOURCE_sector');

QPBLIM_RESOURCE_TL(Y)..
    (IS_RESOURCE(Y) + IS_RESOURCE_X(Y) + IS_RESOURCE_X_H2(Y) + IS_RESOURCE_EV(Y) + IS_RESOURCE_DIESEL(Y)
     + IS_RESOURCE_CC_PS(Y) + IS_RESOURCE_CC_STO(Y)
    )   =E= PB_THRESHOLDS_DATA(Y,'SOS_RESOURCE_sector') * TL_RESOURCE(Y);


* =============================================================================
* SECTION 3b: PB MODULAR CCS LAYER -- CC_PS / CC_STO / BECCS CREDIT EQUATIONS
* -----------------------------------------------------------------------------
* captured(Y,IA,G) = (IM_CO2 + IM_CO2RE) * IOF3P6 * VGF_T * CCS_CO2CAPTEFF_G
*                   summed over (IS3,T) weighted by IHOURSINST*IHOURFRAC [kg/yr]
*
* QPBSCORE_<CAT>_CC_PS:  captured x per-G IM_CC_PS_<CAT>_constr  (all captured)
* QPBSCORE_<CAT>_CC_STO: (captured - utilized) x biogenic/fossil scalar
*                        utilized via $ifi %OPTIFLOW%==yes-gated VFLOWSOURCE
* QBECCS_CREDIT_BOUND:   VBECCS_CREDIT <= biogenic_captured - biogenic_utilized
*
* Activation via PB_balbase4.inc registration ($ifi %CCS%==yes).
* =============================================================================

* === Capture accumulators (2026-05-28): total fossil / biogenic CO2 captured by CCS
* === plants, summed ONCE here. All CC_PS / CC_STO / BECCS-credit rows below reference
* === VCO2CAP_{FOS,BIO} instead of repeating this ~41k-plant sum -> collapses ~20 dense
* === rows to these 2. Single-line on purpose (so the bulk rewrite below cannot match it).
QCO2CAP_BIO(Y).. VCO2CAP_BIO(Y) =E= SUM((IA,G)$(IAGK_HASORPOT(Y,IA,G) AND CCS_G(G) AND IM_CO2RE(G)), VGF_AGG(Y,IA,G) * IM_CO2RE(G) * IOF3P6 * CCS_CO2CAPTEFF_G(G));
QCO2CAP_FOS(Y).. VCO2CAP_FOS(Y) =E= SUM((IA,G)$(IAGK_HASORPOT(Y,IA,G) AND CCS_G(G) AND IM_CO2(G)), VGF_AGG(Y,IA,G) * IM_CO2(G) * IOF3P6 * CCS_CO2CAPTEFF_G(G));

* --- Climate Change (CO2) ---
QPBSCORE_CO2_CC_PS(Y)..
    IS_CO2_CC_PS(Y) =E=
        SUM((IA,G)$(IAGK_HASORPOT(Y,IA,G) AND CCS_G(G)),
            VGF_AGG(Y,IA,G) * (IM_CO2(G) + IM_CO2RE(G)) * IOF3P6 * CCS_CO2CAPTEFF_G(G)
            * IM_CC_PS_CO2_constr(Y,G));

QPBSCORE_CO2_CC_STO(Y)..
    IS_CO2_CC_STO(Y) =E=
        IM_CC_STO_CO2_biogenic(Y) *
            VCO2CAP_BIO(Y)
$ifi %OPTIFLOW%==yes      - IM_CC_STO_CO2_biogenic(Y) * SUM((IR,IA)$(RRRAAA(IR,IA) AND AAAOPTIFLOW(IA)), SUM((IS3,T), IHOURSINST(IS3,T) * IHOURFRAC * 1000 * VFLOWSOURCE(Y,IA,'CO2_Source_Biogen','CO2_SOURCE_FLOW_BIOGEN',IS3,T)))
     + IM_CC_STO_CO2_fossil(Y) *
            VCO2CAP_FOS(Y)
$ifi %OPTIFLOW%==yes      - IM_CC_STO_CO2_fossil(Y) * SUM((IR,IA)$(RRRAAA(IR,IA) AND AAAOPTIFLOW(IA)), SUM((IS3,T), IHOURSINST(IS3,T) * IHOURFRAC * 1000 * VFLOWSOURCE(Y,IA,'CO2_Source_Fossil','CO2_SOURCE_FLOW_FOSSIL',IS3,T)))
;

* --- Stratospheric Ozone Depletion ---
QPBSCORE_OZONE_DEPLETION_CC_PS(Y)..
    IS_OZONE_DEPLETION_CC_PS(Y) =E=
        SUM((IA,G)$(IAGK_HASORPOT(Y,IA,G) AND CCS_G(G)),
            VGF_AGG(Y,IA,G) * (IM_CO2(G) + IM_CO2RE(G)) * IOF3P6 * CCS_CO2CAPTEFF_G(G)
            * IM_CC_PS_Ozone_depletion_constr(Y,G));

QPBSCORE_OZONE_DEPLETION_CC_STO(Y)..
    IS_OZONE_DEPLETION_CC_STO(Y) =E=
        IM_CC_STO_Ozone_depletion_biogenic(Y) *
            VCO2CAP_BIO(Y)
$ifi %OPTIFLOW%==yes      - IM_CC_STO_Ozone_depletion_biogenic(Y) * SUM((IR,IA)$(RRRAAA(IR,IA) AND AAAOPTIFLOW(IA)), SUM((IS3,T), IHOURSINST(IS3,T) * IHOURFRAC * 1000 * VFLOWSOURCE(Y,IA,'CO2_Source_Biogen','CO2_SOURCE_FLOW_BIOGEN',IS3,T)))
     + IM_CC_STO_Ozone_depletion_fossil(Y) *
            VCO2CAP_FOS(Y)
$ifi %OPTIFLOW%==yes      - IM_CC_STO_Ozone_depletion_fossil(Y) * SUM((IR,IA)$(RRRAAA(IR,IA) AND AAAOPTIFLOW(IA)), SUM((IS3,T), IHOURSINST(IS3,T) * IHOURFRAC * 1000 * VFLOWSOURCE(Y,IA,'CO2_Source_Fossil','CO2_SOURCE_FLOW_FOSSIL',IS3,T)))
;

* --- Land Use ---
QPBSCORE_LU_CC_PS(Y)..
    IS_LU_CC_PS(Y) =E=
        SUM((IA,G)$(IAGK_HASORPOT(Y,IA,G) AND CCS_G(G)),
            VGF_AGG(Y,IA,G) * (IM_CO2(G) + IM_CO2RE(G)) * IOF3P6 * CCS_CO2CAPTEFF_G(G)
            * IM_CC_PS_LU_constr(Y,G));

QPBSCORE_LU_CC_STO(Y)..
    IS_LU_CC_STO(Y) =E=
        IM_CC_STO_LU_biogenic(Y) *
            VCO2CAP_BIO(Y)
$ifi %OPTIFLOW%==yes      - IM_CC_STO_LU_biogenic(Y) * SUM((IR,IA)$(RRRAAA(IR,IA) AND AAAOPTIFLOW(IA)), SUM((IS3,T), IHOURSINST(IS3,T) * IHOURFRAC * 1000 * VFLOWSOURCE(Y,IA,'CO2_Source_Biogen','CO2_SOURCE_FLOW_BIOGEN',IS3,T)))
     + IM_CC_STO_LU_fossil(Y) *
            VCO2CAP_FOS(Y)
$ifi %OPTIFLOW%==yes      - IM_CC_STO_LU_fossil(Y) * SUM((IR,IA)$(RRRAAA(IR,IA) AND AAAOPTIFLOW(IA)), SUM((IS3,T), IHOURSINST(IS3,T) * IHOURFRAC * 1000 * VFLOWSOURCE(Y,IA,'CO2_Source_Fossil','CO2_SOURCE_FLOW_FOSSIL',IS3,T)))
;

* --- Water Use ---
QPBSCORE_WU_CC_PS(Y)..
    IS_WU_CC_PS(Y) =E=
        SUM((IA,G)$(IAGK_HASORPOT(Y,IA,G) AND CCS_G(G)),
            VGF_AGG(Y,IA,G) * (IM_CO2(G) + IM_CO2RE(G)) * IOF3P6 * CCS_CO2CAPTEFF_G(G)
            * IM_CC_PS_WU_constr(Y,G));

QPBSCORE_WU_CC_STO(Y)..
    IS_WU_CC_STO(Y) =E=
        IM_CC_STO_WU_biogenic(Y) *
            VCO2CAP_BIO(Y)
$ifi %OPTIFLOW%==yes      - IM_CC_STO_WU_biogenic(Y) * SUM((IR,IA)$(RRRAAA(IR,IA) AND AAAOPTIFLOW(IA)), SUM((IS3,T), IHOURSINST(IS3,T) * IHOURFRAC * 1000 * VFLOWSOURCE(Y,IA,'CO2_Source_Biogen','CO2_SOURCE_FLOW_BIOGEN',IS3,T)))
     + IM_CC_STO_WU_fossil(Y) *
            VCO2CAP_FOS(Y)
$ifi %OPTIFLOW%==yes      - IM_CC_STO_WU_fossil(Y) * SUM((IR,IA)$(RRRAAA(IR,IA) AND AAAOPTIFLOW(IA)), SUM((IS3,T), IHOURSINST(IS3,T) * IHOURFRAC * 1000 * VFLOWSOURCE(Y,IA,'CO2_Source_Fossil','CO2_SOURCE_FLOW_FOSSIL',IS3,T)))
;

* --- Freshwater Eutrophication ---
QPBSCORE_EUTROPHICATION_FRESHWATER_CC_PS(Y)..
    IS_EUTROPHICATION_FRESHWATER_CC_PS(Y) =E=
        SUM((IA,G)$(IAGK_HASORPOT(Y,IA,G) AND CCS_G(G)),
            VGF_AGG(Y,IA,G) * (IM_CO2(G) + IM_CO2RE(G)) * IOF3P6 * CCS_CO2CAPTEFF_G(G)
            * IM_CC_PS_Eutrophication_freshwater_constr(Y,G));

QPBSCORE_EUTROPHICATION_FRESHWATER_CC_STO(Y)..
    IS_EUTROPHICATION_FRESHWATER_CC_STO(Y) =E=
        IM_CC_STO_Eutrophication_freshwater_biogenic(Y) *
            VCO2CAP_BIO(Y)
$ifi %OPTIFLOW%==yes      - IM_CC_STO_Eutrophication_freshwater_biogenic(Y) * SUM((IR,IA)$(RRRAAA(IR,IA) AND AAAOPTIFLOW(IA)), SUM((IS3,T), IHOURSINST(IS3,T) * IHOURFRAC * 1000 * VFLOWSOURCE(Y,IA,'CO2_Source_Biogen','CO2_SOURCE_FLOW_BIOGEN',IS3,T)))
     + IM_CC_STO_Eutrophication_freshwater_fossil(Y) *
            VCO2CAP_FOS(Y)
$ifi %OPTIFLOW%==yes      - IM_CC_STO_Eutrophication_freshwater_fossil(Y) * SUM((IR,IA)$(RRRAAA(IR,IA) AND AAAOPTIFLOW(IA)), SUM((IS3,T), IHOURSINST(IS3,T) * IHOURFRAC * 1000 * VFLOWSOURCE(Y,IA,'CO2_Source_Fossil','CO2_SOURCE_FLOW_FOSSIL',IS3,T)))
;

* --- Freshwater Ecotoxicity ---
QPBSCORE_ECOTOXICITY_FRESHWATER_CC_PS(Y)..
    IS_ECOTOXICITY_FRESHWATER_CC_PS(Y) =E=
        SUM((IA,G)$(IAGK_HASORPOT(Y,IA,G) AND CCS_G(G)),
            VGF_AGG(Y,IA,G) * (IM_CO2(G) + IM_CO2RE(G)) * IOF3P6 * CCS_CO2CAPTEFF_G(G)
            * IM_CC_PS_Ecotoxicity_freshwater_constr(Y,G));

QPBSCORE_ECOTOXICITY_FRESHWATER_CC_STO(Y)..
    IS_ECOTOXICITY_FRESHWATER_CC_STO(Y) =E=
        IM_CC_STO_Ecotoxicity_freshwater_biogenic(Y) *
            VCO2CAP_BIO(Y)
$ifi %OPTIFLOW%==yes      - IM_CC_STO_Ecotoxicity_freshwater_biogenic(Y) * SUM((IR,IA)$(RRRAAA(IR,IA) AND AAAOPTIFLOW(IA)), SUM((IS3,T), IHOURSINST(IS3,T) * IHOURFRAC * 1000 * VFLOWSOURCE(Y,IA,'CO2_Source_Biogen','CO2_SOURCE_FLOW_BIOGEN',IS3,T)))
     + IM_CC_STO_Ecotoxicity_freshwater_fossil(Y) *
            VCO2CAP_FOS(Y)
$ifi %OPTIFLOW%==yes      - IM_CC_STO_Ecotoxicity_freshwater_fossil(Y) * SUM((IR,IA)$(RRRAAA(IR,IA) AND AAAOPTIFLOW(IA)), SUM((IS3,T), IHOURSINST(IS3,T) * IHOURFRAC * 1000 * VFLOWSOURCE(Y,IA,'CO2_Source_Fossil','CO2_SOURCE_FLOW_FOSSIL',IS3,T)))
;

* --- Particulate Matter Formation ---
QPBSCORE_PM_CC_PS(Y)..
    IS_PM_CC_PS(Y) =E=
        SUM((IA,G)$(IAGK_HASORPOT(Y,IA,G) AND CCS_G(G)),
            VGF_AGG(Y,IA,G) * (IM_CO2(G) + IM_CO2RE(G)) * IOF3P6 * CCS_CO2CAPTEFF_G(G)
            * IM_CC_PS_PM_constr(Y,G));

QPBSCORE_PM_CC_STO(Y)..
    IS_PM_CC_STO(Y) =E=
        IM_CC_STO_PM_biogenic(Y) *
            VCO2CAP_BIO(Y)
$ifi %OPTIFLOW%==yes      - IM_CC_STO_PM_biogenic(Y) * SUM((IR,IA)$(RRRAAA(IR,IA) AND AAAOPTIFLOW(IA)), SUM((IS3,T), IHOURSINST(IS3,T) * IHOURFRAC * 1000 * VFLOWSOURCE(Y,IA,'CO2_Source_Biogen','CO2_SOURCE_FLOW_BIOGEN',IS3,T)))
     + IM_CC_STO_PM_fossil(Y) *
            VCO2CAP_FOS(Y)
$ifi %OPTIFLOW%==yes      - IM_CC_STO_PM_fossil(Y) * SUM((IR,IA)$(RRRAAA(IR,IA) AND AAAOPTIFLOW(IA)), SUM((IS3,T), IHOURSINST(IS3,T) * IHOURFRAC * 1000 * VFLOWSOURCE(Y,IA,'CO2_Source_Fossil','CO2_SOURCE_FLOW_FOSSIL',IS3,T)))
;

* --- Ionising Radiation ---
QPBSCORE_RADIATION_CC_PS(Y)..
    IS_RADIATION_CC_PS(Y) =E=
        SUM((IA,G)$(IAGK_HASORPOT(Y,IA,G) AND CCS_G(G)),
            VGF_AGG(Y,IA,G) * (IM_CO2(G) + IM_CO2RE(G)) * IOF3P6 * CCS_CO2CAPTEFF_G(G)
            * IM_CC_PS_Radiation_constr(Y,G));

QPBSCORE_RADIATION_CC_STO(Y)..
    IS_RADIATION_CC_STO(Y) =E=
        IM_CC_STO_Radiation_biogenic(Y) *
            VCO2CAP_BIO(Y)
$ifi %OPTIFLOW%==yes      - IM_CC_STO_Radiation_biogenic(Y) * SUM((IR,IA)$(RRRAAA(IR,IA) AND AAAOPTIFLOW(IA)), SUM((IS3,T), IHOURSINST(IS3,T) * IHOURFRAC * 1000 * VFLOWSOURCE(Y,IA,'CO2_Source_Biogen','CO2_SOURCE_FLOW_BIOGEN',IS3,T)))
     + IM_CC_STO_Radiation_fossil(Y) *
            VCO2CAP_FOS(Y)
$ifi %OPTIFLOW%==yes      - IM_CC_STO_Radiation_fossil(Y) * SUM((IR,IA)$(RRRAAA(IR,IA) AND AAAOPTIFLOW(IA)), SUM((IS3,T), IHOURSINST(IS3,T) * IHOURFRAC * 1000 * VFLOWSOURCE(Y,IA,'CO2_Source_Fossil','CO2_SOURCE_FLOW_FOSSIL',IS3,T)))
;

* --- Terrestrial Acidification ---
QPBSCORE_ACIDIFICATION_CC_PS(Y)..
    IS_ACIDIFICATION_CC_PS(Y) =E=
        SUM((IA,G)$(IAGK_HASORPOT(Y,IA,G) AND CCS_G(G)),
            VGF_AGG(Y,IA,G) * (IM_CO2(G) + IM_CO2RE(G)) * IOF3P6 * CCS_CO2CAPTEFF_G(G)
            * IM_CC_PS_Acidification_constr(Y,G));

QPBSCORE_ACIDIFICATION_CC_STO(Y)..
    IS_ACIDIFICATION_CC_STO(Y) =E=
        IM_CC_STO_Acidification_biogenic(Y) *
            VCO2CAP_BIO(Y)
$ifi %OPTIFLOW%==yes      - IM_CC_STO_Acidification_biogenic(Y) * SUM((IR,IA)$(RRRAAA(IR,IA) AND AAAOPTIFLOW(IA)), SUM((IS3,T), IHOURSINST(IS3,T) * IHOURFRAC * 1000 * VFLOWSOURCE(Y,IA,'CO2_Source_Biogen','CO2_SOURCE_FLOW_BIOGEN',IS3,T)))
     + IM_CC_STO_Acidification_fossil(Y) *
            VCO2CAP_FOS(Y)
$ifi %OPTIFLOW%==yes      - IM_CC_STO_Acidification_fossil(Y) * SUM((IR,IA)$(RRRAAA(IR,IA) AND AAAOPTIFLOW(IA)), SUM((IS3,T), IHOURSINST(IS3,T) * IHOURFRAC * 1000 * VFLOWSOURCE(Y,IA,'CO2_Source_Fossil','CO2_SOURCE_FLOW_FOSSIL',IS3,T)))
;

* --- Resource Use (Minerals and Metals) ---
QPBSCORE_RESOURCE_CC_PS(Y)..
    IS_RESOURCE_CC_PS(Y) =E=
        SUM((IA,G)$(IAGK_HASORPOT(Y,IA,G) AND CCS_G(G)),
            VGF_AGG(Y,IA,G) * (IM_CO2(G) + IM_CO2RE(G)) * IOF3P6 * CCS_CO2CAPTEFF_G(G)
            * IM_CC_PS_Resource_constr(Y,G));

QPBSCORE_RESOURCE_CC_STO(Y)..
    IS_RESOURCE_CC_STO(Y) =E=
        IM_CC_STO_Resource_biogenic(Y) *
            VCO2CAP_BIO(Y)
$ifi %OPTIFLOW%==yes      - IM_CC_STO_Resource_biogenic(Y) * SUM((IR,IA)$(RRRAAA(IR,IA) AND AAAOPTIFLOW(IA)), SUM((IS3,T), IHOURSINST(IS3,T) * IHOURFRAC * 1000 * VFLOWSOURCE(Y,IA,'CO2_Source_Biogen','CO2_SOURCE_FLOW_BIOGEN',IS3,T)))
     + IM_CC_STO_Resource_fossil(Y) *
            VCO2CAP_FOS(Y)
$ifi %OPTIFLOW%==yes      - IM_CC_STO_Resource_fossil(Y) * SUM((IR,IA)$(RRRAAA(IR,IA) AND AAAOPTIFLOW(IA)), SUM((IS3,T), IHOURSINST(IS3,T) * IHOURFRAC * 1000 * VFLOWSOURCE(Y,IA,'CO2_Source_Fossil','CO2_SOURCE_FLOW_FOSSIL',IS3,T)))
;

* --- BECCS credit bound: VBECCS_CREDIT <= biogenic_captured - biogenic_utilized
QBECCS_CREDIT_BOUND(Y)..
    VBECCS_CREDIT(Y) =L=
        VCO2CAP_BIO(Y)
$ifi %OPTIFLOW%==yes      - SUM((IR,IA)$(RRRAAA(IR,IA) AND AAAOPTIFLOW(IA)), SUM((IS3,T), IHOURSINST(IS3,T) * IHOURFRAC * 1000 * VFLOWSOURCE(Y,IA,'CO2_Source_Biogen','CO2_SOURCE_FLOW_BIOGEN',IS3,T)))
;


* =============================================================================
* SECTION 3c: CAR_DIESEL EQUATIONS (Component 2, 2026-05-26)
* -----------------------------------------------------------------------------
* Exogenous diesel-car impact contributions per PB category. Annualized per
* car: chassis amortized over IDIESEL_CHASSIS_LIFETIME, operation taken
* directly from PB_LCA_DATA_EV('CAR_DIESEL', Y, 'LCA_<CAT>_prod_elec') which
* is already kg <impact-eq>/yr/car (no km multiplier needed -- the value bakes
* in MESCAL's reference annual mileage).
*
* IDIESEL_AVAILABLE(Y, IR) = MAX(0, ITOTAL_CAR_FLEET - EV_BEV - EV_PHEV).
* When EV add-on is off, IDIESEL_AVAILABLE stays at 0 -> IS_<CAT>_DIESEL = 0.
* Activation gated via PB_balbase4.inc with $ifi %EV%==yes.
*
* No inner (IS3,T) sums and no LP-variable references: the entire equation
* is parametric coefficient * IDIESEL_AVAILABLE. LP-matrix impact: one nnz
* per (Y, IR) coefficient column per equation = negligible.
* =============================================================================

QPBSCORE_CO2_DIESEL(Y)..
    IS_CO2_DIESEL(Y) =E=
        SUM(IR,
            PB_LCA_DATA_EV('CAR_DIESEL',Y,'LCA_CO2_constr') / IDIESEL_CHASSIS_LIFETIME * IDIESEL_AVAILABLE(Y,IR)
          + PB_LCA_DATA_EV('CAR_DIESEL',Y,'LCA_CO2_prod_elec') * IDIESEL_AVAILABLE(Y,IR));

QPBSCORE_OZONE_DEPLETION_DIESEL(Y)..
    IS_OZONE_DEPLETION_DIESEL(Y) =E=
        SUM(IR,
            PB_LCA_DATA_EV('CAR_DIESEL',Y,'LCA_Ozone_depletion_constr') / IDIESEL_CHASSIS_LIFETIME * IDIESEL_AVAILABLE(Y,IR)
          + PB_LCA_DATA_EV('CAR_DIESEL',Y,'LCA_Ozone_depletion_prod_elec') * IDIESEL_AVAILABLE(Y,IR));

QPBSCORE_LU_DIESEL(Y)..
    IS_LU_DIESEL(Y) =E=
        SUM(IR,
            PB_LCA_DATA_EV('CAR_DIESEL',Y,'LCA_LU_constr') / IDIESEL_CHASSIS_LIFETIME * IDIESEL_AVAILABLE(Y,IR)
          + PB_LCA_DATA_EV('CAR_DIESEL',Y,'LCA_LU_prod_elec') * IDIESEL_AVAILABLE(Y,IR));

QPBSCORE_WU_DIESEL(Y)..
    IS_WU_DIESEL(Y) =E=
        SUM(IR,
            PB_LCA_DATA_EV('CAR_DIESEL',Y,'LCA_WU_constr') / IDIESEL_CHASSIS_LIFETIME * IDIESEL_AVAILABLE(Y,IR)
          + PB_LCA_DATA_EV('CAR_DIESEL',Y,'LCA_WU_prod_elec') * IDIESEL_AVAILABLE(Y,IR));

QPBSCORE_EUTROPHICATION_FRESHWATER_DIESEL(Y)..
    IS_EUTROPHICATION_FRESHWATER_DIESEL(Y) =E=
        SUM(IR,
            PB_LCA_DATA_EV('CAR_DIESEL',Y,'LCA_Eutrophication_freshwater_constr') / IDIESEL_CHASSIS_LIFETIME * IDIESEL_AVAILABLE(Y,IR)
          + PB_LCA_DATA_EV('CAR_DIESEL',Y,'LCA_Eutrophication_freshwater_prod_elec') * IDIESEL_AVAILABLE(Y,IR));

QPBSCORE_ECOTOXICITY_FRESHWATER_DIESEL(Y)..
    IS_ECOTOXICITY_FRESHWATER_DIESEL(Y) =E=
        SUM(IR,
            PB_LCA_DATA_EV('CAR_DIESEL',Y,'LCA_Ecotoxicity_freshwater_constr') / IDIESEL_CHASSIS_LIFETIME * IDIESEL_AVAILABLE(Y,IR)
          + PB_LCA_DATA_EV('CAR_DIESEL',Y,'LCA_Ecotoxicity_freshwater_prod_elec') * IDIESEL_AVAILABLE(Y,IR));

QPBSCORE_PM_DIESEL(Y)..
    IS_PM_DIESEL(Y) =E=
        SUM(IR,
            PB_LCA_DATA_EV('CAR_DIESEL',Y,'LCA_PM_constr') / IDIESEL_CHASSIS_LIFETIME * IDIESEL_AVAILABLE(Y,IR)
          + PB_LCA_DATA_EV('CAR_DIESEL',Y,'LCA_PM_prod_elec') * IDIESEL_AVAILABLE(Y,IR));

QPBSCORE_RADIATION_DIESEL(Y)..
    IS_RADIATION_DIESEL(Y) =E=
        SUM(IR,
            PB_LCA_DATA_EV('CAR_DIESEL',Y,'LCA_Radiation_constr') / IDIESEL_CHASSIS_LIFETIME * IDIESEL_AVAILABLE(Y,IR)
          + PB_LCA_DATA_EV('CAR_DIESEL',Y,'LCA_Radiation_prod_elec') * IDIESEL_AVAILABLE(Y,IR));

QPBSCORE_ACIDIFICATION_DIESEL(Y)..
    IS_ACIDIFICATION_DIESEL(Y) =E=
        SUM(IR,
            PB_LCA_DATA_EV('CAR_DIESEL',Y,'LCA_Acidification_constr') / IDIESEL_CHASSIS_LIFETIME * IDIESEL_AVAILABLE(Y,IR)
          + PB_LCA_DATA_EV('CAR_DIESEL',Y,'LCA_Acidification_prod_elec') * IDIESEL_AVAILABLE(Y,IR));

QPBSCORE_RESOURCE_DIESEL(Y)..
    IS_RESOURCE_DIESEL(Y) =E=
        SUM(IR,
            PB_LCA_DATA_EV('CAR_DIESEL',Y,'LCA_Resource_constr') / IDIESEL_CHASSIS_LIFETIME * IDIESEL_AVAILABLE(Y,IR)
          + PB_LCA_DATA_EV('CAR_DIESEL',Y,'LCA_Resource_prod_elec') * IDIESEL_AVAILABLE(Y,IR));


* =============================================================================
* SECTION 4: MATRIX-GENERATION ACCELERATOR EQUATIONS
* -----------------------------------------------------------------------------
* The three QV*_AGG equations define annual (S,T)-weighted aggregates of the
* per-timeslice generation variables. The QPBSCORE_* equations above use the
* aggregates (V*_AGG) instead of nested SUM((IS3,T), ...) over the original
* time-resolved variables, collapsing a 192-deep nested sum to a single term
* per category-equation and reducing GAMS matrix-generation time by orders
* of magnitude. CPLEX presolve substitutes the aggregator variables out, so
* the final LP solved by CPLEX is unchanged in structure (just much faster
* to build).
*
* The IHOURSINST weighting matches the standard Balmorel time-weighting used
* in dispatch equations, so the aggregates have units of "MWh per year".
* =============================================================================

QVGE_AGG(Y,IA,G)$IAGK_HASORPOT(Y,IA,G)..
    VGE_AGG(Y,IA,G) =E= SUM((IS3,T), IHOURSINST(IS3,T) * IHOURFRAC * VGE_T(Y,IA,G,IS3,T));

QVGH_AGG(Y,IA,G)$IAGK_HASORPOT(Y,IA,G)..
    VGH_AGG(Y,IA,G) =E= SUM((IS3,T), IHOURSINST(IS3,T) * IHOURFRAC * VGH_T(Y,IA,G,IS3,T));

* QVH2_AGG (2026-05-27 refinement): the equation now fires only for (Y,IA,G)
* tuples where G is in at least one of the 4 relevant H2 tech subsets, AND
* each per-timeslice variable reference inside the SUM is gated by its own
* tech subset. Pre-refinement, the equation fired for ALL IAGK_HASORPOT
* tuples (~5M at EU scale) and the RHS referenced 4 H2 variables × 192
* timeslots = ~768 NNZ/row for every row, instantiating LP columns for
* non-H2 generators (e.g., VGBIOMETH_T(2030, FR, COAL_PLANT, *, *)). Adding
* the tech-subset gates limits the row generation AND the variable
* instantiations to only meaningful tuples.
$ifi %HYDROGEN%==yes QVH2_AGG(Y,IA,G)$(IAGK_HASORPOT(Y,IA,G) AND (
$ifi %HYDROGEN%==yes     IHYDROGEN_GCH4TOH2(G) OR IHYDROGEN_GH2STO(G) OR
$ifi %HYDROGEN%==yes     IHYDROGEN_GH2TOBIOMETH(G) OR
$ifi %HYDROGEN%==yes     IHYDROGEN_GBIOGASMETHANATION(G) OR
$ifi %HYDROGEN%==yes     IHYDROGEN_GBIOGASUPGRADING(G)))..
$ifi %HYDROGEN%==yes     VH2_AGG(Y,IA,G) =E= SUM((IS3,T), IHOURSINST(IS3,T) * IHOURFRAC * (
$ifi %HYDROGEN%==yes         VHYDROGEN_GH2_T(Y,IA,G,IS3,T)$(IHYDROGEN_GCH4TOH2(G) OR IHYDROGEN_GH2STO(G))
$ifi %HYDROGEN%==yes       + VGBIOMETH_T(Y,IA,G,IS3,T)$IHYDROGEN_GH2TOBIOMETH(G)
$ifi %HYDROGEN%==yes       + VGBIOGASMETHANATION_T(Y,IA,G,IS3,T)$IHYDROGEN_GBIOGASMETHANATION(G)
$ifi %HYDROGEN%==yes       + VGBIOGASUPGRADING_T(Y,IA,G,IS3,T)$IHYDROGEN_GBIOGASUPGRADING(G)));

* QVGF_AGG: per-CCS_G annual fuel input aggregator (PB modular CCS accelerator).
* Restricted to CCS_G plants because only the PB CC_PS / CC_STO / BECCS equations
* need it; non-CCS plants don't reference VGF_AGG.
* Declared and defined unconditionally per modular CCS convention; activation is
* gated via PB_balbase4.inc with $ifi %CCS%==yes (matching QPBSCORE_*_CC_PS pattern).
QVGF_AGG(Y,IA,G)$(IAGK_HASORPOT(Y,IA,G) AND CCS_G(G))..
    VGF_AGG(Y,IA,G) =E= SUM((IS3,T), IHOURSINST(IS3,T) * IHOURFRAC * VGF_T(Y,IA,G,IS3,T));

* === EU-wide transmission / H2-pipeline capacity caps (PB add-on, optional) ====
* Per-year HARD caps (=L=) on TOTAL installed interconnector capacity, summed
* EU-wide, in the matching cohort solve (IY411 = the current Balbase4 year):
*   elec = exogenous XKFX + endogenous accumulated VXKNACCUMNET  (= reported X_CAP)
*   H2   = endogenous accumulated VXH2KNACCUMNET                 (= reported XH2_CAP;
*          this scenario has no exogenous XH2KFX and no NG-to-H2 pipelines)
* The cap value is a scenario global in GW; "* 1000" converts it to the model's MW.
* Gated by "$if set": leaving a global unset/empty => its equation is never
* declared, i.e. no cap for that year. H2 caps also need %H2TransInvest%==yes
* (VXH2KNACCUMNET is declared only then).

$ifThen.etx40 set Elec_TransX_Limit_2040
EQUATION QELEC_TRANSX_LIM_2040(Y) "EU-wide total elec transmission capacity cap, 2040";
QELEC_TRANSX_LIM_2040(IY411)$(SAMEAS(IY411,'2040'))..
    SUM((IRE,IRI), XKFX(IY411,IRE,IRI) + VXKNACCUMNET(IY411,IRE,IRI))
        =L= %Elec_TransX_Limit_2040% * 1000;
$endIf.etx40

$ifThen.etx50 set Elec_TransX_Limit_2050
EQUATION QELEC_TRANSX_LIM_2050(Y) "EU-wide total elec transmission capacity cap, 2050";
QELEC_TRANSX_LIM_2050(IY411)$(SAMEAS(IY411,'2050'))..
    SUM((IRE,IRI), XKFX(IY411,IRE,IRI) + VXKNACCUMNET(IY411,IRE,IRI))
        =L= %Elec_TransX_Limit_2050% * 1000;
$endIf.etx50

$ifThen.htx40 set H2_TransX_Limit_2040
$ifThenI.htx40h %H2TransInvest%==yes
EQUATION QH2_TRANSX_LIM_2040(Y) "EU-wide total H2 pipeline capacity cap, 2040";
QH2_TRANSX_LIM_2040(IY411)$(SAMEAS(IY411,'2040'))..
    SUM((IRE,IRI), VXH2KNACCUMNET(IY411,IRE,IRI))
        =L= %H2_TransX_Limit_2040% * 1000;
$endIf.htx40h
$endIf.htx40

$ifThen.htx50 set H2_TransX_Limit_2050
$ifThenI.htx50h %H2TransInvest%==yes
EQUATION QH2_TRANSX_LIM_2050(Y) "EU-wide total H2 pipeline capacity cap, 2050";
QH2_TRANSX_LIM_2050(IY411)$(SAMEAS(IY411,'2050'))..
    SUM((IRE,IRI), VXH2KNACCUMNET(IY411,IRE,IRI))
        =L= %H2_TransX_Limit_2050% * 1000;
$endIf.htx50h
$endIf.htx50

* Compile-time confirmation of which caps are active (gated; logs once per run).
$if set Elec_TransX_Limit_2040 $log >>> PB CAP ACTIVE: Elec transmission 2040 <= %Elec_TransX_Limit_2040% GW
$if set Elec_TransX_Limit_2050 $log >>> PB CAP ACTIVE: Elec transmission 2050 <= %Elec_TransX_Limit_2050% GW
$ifi %H2TransInvest%==yes $if set H2_TransX_Limit_2040 $log >>> PB CAP ACTIVE: H2 pipeline 2040 <= %H2_TransX_Limit_2040% GW
$ifi %H2TransInvest%==yes $if set H2_TransX_Limit_2050 $log >>> PB CAP ACTIVE: H2 pipeline 2050 <= %H2_TransX_Limit_2050% GW
