*-------------------------------------------------------------------------------
* PB_pardeclare.inc  --  Parameter declarations for the PB add-on
*-------------------------------------------------------------------------------
* Part of the Balmorel Planetary Boundaries (PB) add-on.
*
* Declares the planetary-boundary threshold parameter and the family of
* Life-Cycle Assessment (LCA) data parameters used by the impact-score
* equations (QPBSCORE_*) and limit equations (QPBLIM_*).
*
* Generator-level coefficients (IM_<Category>_prod_elec, IM_<Category>_prod_heat,
* IM_<Category>_constr, for the 10 active impact categories) are NOT declared
* here -- they are declared inside the precomputed per-scenario file loaded
* by PB_ipardecdef.inc (see that file's header for the preprocessing
* pipeline).
*
* Authors: Theo Balanza & Dhruv Sharma
*-------------------------------------------------------------------------------

* --- Sector-level Safe Operating Space (SOS) thresholds -----------------------
PARAMETER PB_THRESHOLDS_DATA(YYY, PB_THRESHOLDS_SET) "Planetary Boundaries thresholds downscaled to the energy sector";

* --- QPBSCORE row-scale factor (2026-05-29, LOSSLESS conditioning) -------------
* Each main QPBSCORE_<CAT> is multiplied by PB_ROWSCALE(cat) on BOTH sides in
* PB_eqndecdef.inc (f*SUM =e= f*IS) so f cancels: IS_<CAT>.l/TL/thresholds/QPBLIM/
* outputs unchanged. f_CAT (assigned in PB_pardefine.inc, after the threshold set
* is populated) = 1/(geomean IM_<CAT>_prod_elec*1000) -> ~1 on the VGE_AGG column,
* collapsing the cross-category spread behind the 2040 unscaled-infeasibility.
* Default 1 = no-op (existing runs bit-identical). Enable: $setglobal PB_ROWSCALE_ON yes
$if not set PB_ROWSCALE_ON $setglobal PB_ROWSCALE_ON 0
PARAMETER PB_ROWSCALE(PB_THRESHOLDS_SET) "QPBSCORE row-scale factor (1=off); lossless conditioning";
PARAMETER PB_ROWSCALE_X(PB_THRESHOLDS_SET)    "QPBSCORE_<CAT>_X (elec transmission) row-scale factor (1=off)";
PARAMETER PB_ROWSCALE_X_H2(PB_THRESHOLDS_SET) "QPBSCORE_<CAT>_X_H2 (H2 transmission) row-scale factor (1=off)";
PARAMETER PB_ROWSCALE_EV(PB_THRESHOLDS_SET)    "QPBSCORE_<CAT>_EV (EV battery, VEV_G2V_BEV column) row-scale factor (1=off)";

* --- LCA data: generator construction and operation ---------------------------
PARAMETER PB_LCA_DATA(TECH_GROUP, FFF, PB_GDTYPE_SET, YYY, PB_LCA_DATASET) "LCA data for construction and operation of generator G in (TECH_GROUP, FFF) for Elec, Heat, CHP";
PARAMETER PB_LCA_DATA_H2(TECH_GROUP, FFF, PB_GDTYPE_SET, YYY, PB_LCA_DATASET) "LCA data for construction and operation of generator G in (TECH_GROUP, FFF) for H2";
PARAMETER PB_LCA_DATA_CCS(TECH_GROUP, FFF, PB_GDTYPE_SET, YYY, PB_LCA_DATASET) "LCA data for construction and operation of generator G in (TECH_GROUP, FFF) for CCS";
PARAMETER PB_LCA_DATA_H2_STO_CAV(TECH_GROUP, FFF, PB_GDTYPE_SET, YYY, PB_LCA_DATASET) "LCA data for construction and operation of H2 storage caverns";

* --- LCA data: transmission construction --------------------------------------
PARAMETER PB_LCA_DATA_X(IRRRE, IRRRI, YYY, PB_LCA_DATASET) "LCA data for construction of electricity transmission lines";
* --- Elec-transmission LCA rank-1 factorisation (2026-05-30, for PB_X_RANKFIX) -------
* PB_LCA_DATA_X is EXACTLY rank-1 per year (verified: category ratios constant to ~2e-9
* across all 206 elec line-pairs) -- identical structure to PB_LCA_DATA_X_H2. The 10
* IS_<cat>_X are scalar multiples -> rank-deficient block; safe while the grid actively
* builds (2030) but goes singular as it matures/saturates (2040/2050). Same lossless
* collapse as the H2 block, gated by PB_X_RANKFIX.
PARAMETER PB_X_NCAT(IRRRE, IRRRI, YYY)        "Elec-line rank-fix: # populated LCA categories per line-year (=10)";
PARAMETER PB_X_LINE_SCALE(IRRRE, IRRRI, YYY)  "Elec-line rank-fix: neutral per-line scale = geomean over categories";
PARAMETER PB_X_INTENSITY(YYY, PB_LCA_DATASET) "Elec-line rank-fix: per-category intensity (constant across lines) = LCA_cat / line-scale";
PARAMETER PB_LCA_DATA_X_H2(IRRRE, IRRRI, YYY, PB_LCA_DATASET) "LCA data for construction of H2 transmission lines";
* --- H2-transmission LCA rank-1 factorisation (2026-05-30, for PB_XH2_RANKFIX) -------
* PB_LCA_DATA_X_H2 is EXACTLY rank-1 within each year: LCA_cat(line) = scale(line) *
* intensity(cat) (verified: per-category ratios constant to ~1e-10 across all 206 H2
* line-pairs/year -- physically line-size * a fixed per-category LCA-intensity vector).
* The 10 IS_<cat>_X_H2 score vars are therefore exact scalar multiples -> a rank-1 block
* dressed as 10 DOF -> singular simplex basis when the H2 grid is near-empty (2030). The
* rank-fix routes the single Sigma-over-lines coupling into one base var (IS_X_H2_BASE)
* and recovers each category by an exact scaling -- lossless to ~1e-10.
PARAMETER PB_XH2_NCAT(IRRRE, IRRRI, YYY)        "H2-line rank-fix: # populated LCA categories per line-year (=10)";
PARAMETER PB_XH2_LINE_SCALE(IRRRE, IRRRI, YYY)  "H2-line rank-fix: neutral per-line scale = geomean over categories";
PARAMETER PB_XH2_INTENSITY(YYY, PB_LCA_DATASET) "H2-line rank-fix: per-category intensity (constant across lines) = LCA_cat / line-scale";

* --- LCA data: electric vehicles ----------------------------------------------
PARAMETER PB_LCA_DATA_EV(PB_GDTYPE_SET, YYY, PB_LCA_DATASET) "LCA data for electric-vehicle batteries (chassis and cyclic degradation)";

* --- Lifetime assumptions (previously hardcoded as magic numbers /50 /30) -----
* Used by QPBSCORE_<CAT>_X, QPBSCORE_<CAT>_X_H2 (transmission), and
* QPBSCORE_<CAT>_EV (EV chassis) to amortise lifetime construction impact into
* an annual rate. Generator construction uses GDATA(G,'GDLIFETIME') per generator.
SCALAR IXKLIFETIME          'Transmission line lifetime, used in QPBSCORE_<CAT>_X / _X_H2 (years)' / 50 /;
SCALAR IEV_CHASSIS_LIFETIME 'EV chassis lifetime, used in QPBSCORE_<CAT>_EV (years)'                / 30 /;

* --- Diesel car fleet (parametric, Option A: static EU fleet) ----------------
* Total passenger car fleet assumed constant across Y at the Eurostat EU
* aggregate (~252M EU-27 in 2022, treated constant). PB_pardefine.inc
* distributes this across regions using the 2050 BEV column of
* EV_BEV_available as the per-region share proxy (the IEA scenario in the EV
* data projects ~full BEV transition by 2050, so its 2050 column approximates
* total per-region fleet). The planned diesel-car implementation
* (PB_CCS_CAR_DIESEL_COMBTECH_PLAN.md, Component 2) will consume this as
*   IDIESEL_AVAILABLE = max(0, ITOTAL_CAR_FLEET - EV_BEV_available - EV_PHEV_available).
SCALAR    ITOTAL_FLEET_EU            'EU passenger car stock (Eurostat ~252M, treated constant)' / 250e6 /;
PARAMETER ITOTAL_CAR_FLEET(YYY, RRR) 'Total passenger car fleet by (year, region) -- Option A: 250M EU, regionally distributed';

* --- Diesel car parameters (CAR_DIESEL Component 2, landed 2026-05-26) --------
* IDIESEL_AVAILABLE is populated in PB_pardefine.inc as
*   MAX(0, ITOTAL_CAR_FLEET - EV_BEV_available - EV_PHEV_available).
* PB_LCA_DATA_EV's 'CAR_DIESEL' row has annualized prod_elec values (kg CO2-eq /
* yr / car), so QPBSCORE_<CAT>_DIESEL multiplies prod_elec * IDIESEL_AVAILABLE
* directly -- no km/yr factor needed.
SCALAR    IDIESEL_CHASSIS_LIFETIME   'Diesel car chassis lifetime (years), used in QPBSCORE_<CAT>_DIESEL' / 20 /;
PARAMETER IDIESEL_AVAILABLE(YYY, RRR) 'Diesel car count by (year, region) (= max(0, total - BEV - PHEV))';

* --- PB transgression penalty coefficient -------------------------------------
* Used in PB_qobj.inc as the multiplier on each TL_<CAT>(Y) variable in the
* objective. Default 1e13 acts as a soft prohibition on transgressing the PB
* threshold while keeping the LP feasible (TL is a non-negative slack on the
* IS = threshold * TL constraint).
$if not set PB_PENALTY_VALUE          $setglobal PB_PENALTY_VALUE 1e13
SCALAR PB_PENALTY_COEF      'Penalty coefficient on TL_<CAT>(Y) in the objective (PB_qobj.inc); 1e13 = soft prohibition, 0 = no PB pressure' / %PB_PENALTY_VALUE% /;
* --- PB_PENALTY_COEF is overridable via $setglobal PB_PENALTY_VALUE (default 1e13);
* --- lower values (e.g. 1e12) reduce the objective imbalance while keeping PB primary.
* --- PB_DISPATCH_REG: optional tiny per-MWh regularization on annual generation (VGE_AGG)
* --- to break the degenerate optimal face -> faster crossover. Default-off.
$if not set PB_DISPATCH_REG            $setglobal PB_DISPATCH_REG no
$if not set PB_DISPATCH_REG_EXT        $setglobal PB_DISPATCH_REG_EXT no
$if not set PB_DISPATCH_REG_EPS_VALUE  $setglobal PB_DISPATCH_REG_EPS_VALUE 0
SCALAR PB_DISPATCH_REG_EPS  'S3 dispatch-regularization coefficient (per-MWh cost on VGE_AGG; activated by PB_DISPATCH_REG=yes in PB_qobj.inc)' / %PB_DISPATCH_REG_EPS_VALUE% /;

* --- BECCS economic credit -- Y-indexed trajectory (refactored 2026-05-27) ----
* Methodological consistency: NEG_EMI_CREDIT(Y) tracks the EMI_POL TAX_CO2(Y)
* trajectory (EUR15/tCO2). This enforces the no-arbitrage condition between
* explicit CO2 pricing and BECCS reward -- BECCS stores 1 tCO2, the credit
* should equal what an equivalent tCO2 emission would cost.
*
* Note: EMI_POL TAX_CO2(Y, *, *, 'TAX_CO2') is still commented out in
* base/data/EMI_POL.inc (so the explicit tax does NOT enter QOBJ -- the PB
* shadow price on QPBLIM_CO2 remains the sole carbon-cost mechanism, avoiding
* double pricing). The trajectory below is lifted from those commented values
* and serves as INPUT DATA for the BECCS credit only.
*
* Supersedes the prior SCALAR NEG_EMI_CREDIT / %NEG_EMI_CREDIT_DEFAULT% /
* mechanism. Scenarios with `$setglobal NEG_EMI_CREDIT_DEFAULT N` in their
* balopt.opt are now no-ops (the macro is set but no longer referenced); the
* trajectory below is the canonical source.
*
* Gated by %CCS%==yes (matches original $ifi pattern + PB_qobj.inc usage gate).
$ifi not %CCS%==yes $goto skip_nec_traj
PARAMETER NEG_EMI_CREDIT(YYY) 'Per-tCO2 credit for stored biogenic CO2 (BECCS, EUR15/tCO2); Y-indexed = EMI_POL TAX_CO2 trajectory'
/
2012  7.59
2013  4.85
2014  6.35
2015  7.49
2016  5.95
2017  5.79
2018  5.95
2019  5.93
2020  78
2021  84.2
2022  90.4
2023  96.6
2024  102.8
2025  109
2026  115.2
2027  121.4
2028  127.6
2029  133.8
2030  140
2031  146.5
2032  153
2033  159.5
2034  166
2035  172.5
2036  179
2037  185.5
2038  192
2039  198.5
2040  205
2041  209.5
2042  214
2043  218.5
2044  223
2045  227.5
2046  232
2047  236.5
2048  241
2049  245.5
2050  250
/;
$label skip_nec_traj

* --- Exogenous capacity additions per commission year (for cohort accounting) -
* Captures positive year-on-year deltas in GKFX(YYY, IA, G) -- i.e., capacity
* that came online exogenously in year YYY (vs. prior year). Used by the
* cohort-frozen-IM construction term in QPBSCORE_<IMPACT> equations
* (gated by PB_COHORT_CONSTR=yes in balopt.opt). Populated once before any
* SOLVE in PB_pardefine.inc.
PARAMETER NEW_GKFX(YYY,AAA,GGG) "Exogenous capacity commissioned in year YYY -- positive GKFX year-on-year delta (MW; MWh for storages, same units as GKFX)";

* --- Rolling-foresight declarations (singleton sets, snapshot, banking, log) --
* Active only under PB_ROLLING_FORESIGHT. Brought in here so the sets and
* parameters are declared once, at compile time, before any LOOP. The runtime
* update logic (PB_threshold_update.inc) is included per-window from
* Balmorelbb5.sim (Stage 2) and uses only assignments / put statements.
$ifi %PB_ROLLING_FORESIGHT%==yes $include "../../base/addons/PB/bb4/PB_rolling_foresight_decls.inc";
