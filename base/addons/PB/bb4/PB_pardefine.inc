*-------------------------------------------------------------------------------
* PB_pardefine.inc  --  Populate PB LCA and threshold parameters from data files
*-------------------------------------------------------------------------------
* Part of the Balmorel Planetary Boundaries (PB) add-on.
*
* Loads the PB LCA-data tables and SOS thresholds for the active IAM scenario
* (selected via %IAM_Scenario% global, e.g. IMAGE_SSP2_RCP26). Each block uses
* the standard "scenario overrides base" lookup pattern:
*     if  ../data/<file> exists in the active scenario, use that;
*     else fall back to the canonical copy in ../../base/data/<file>.
*
* CCS and EV blocks are gated on the %CCS% and %EV% global flags so the
* respective data files are only loaded when the corresponding add-ons are
* active. The SOS thresholds load unconditionally (every PB run needs them).
*
* Note: PB_LCA_DATA_H2_<scenario>.inc is no longer loaded here. H2 LCA
* additions are bundled into the per-scenario PB_LCA_DATA_<scenario>.inc
* (and routed through PB_LCA_DATA_H2_STO_CAV_<scenario>.inc for cavern
* storage). The dead $onmulti block has been removed.
*
* Authors: Theo Balanza & Dhruv Sharma
*-------------------------------------------------------------------------------

* --- LCA data: main generator construction/operation tables -------------------
$onmulti
$if     EXIST '../data/PB_LCA_DATA_%IAM_Scenario%.inc' $INCLUDE         '../data/PB_LCA_DATA_%IAM_Scenario%.inc';
$if not EXIST '../data/PB_LCA_DATA_%IAM_Scenario%.inc' $INCLUDE '../../base/data/PB_LCA_DATA_%IAM_Scenario%.inc';
$offmulti

* --- LCA data: electricity transmission line construction ---------------------
$onmulti
$if     EXIST '../data/PB_LCA_DATA_X_%IAM_Scenario%.inc' $INCLUDE         '../data/PB_LCA_DATA_X_%IAM_Scenario%.inc';
$if not EXIST '../data/PB_LCA_DATA_X_%IAM_Scenario%.inc' $INCLUDE '../../base/data/PB_LCA_DATA_X_%IAM_Scenario%.inc';
$offmulti

* --- LCA data: H2 storage caverns ---------------------------------------------
$onmulti
$if     EXIST '../data/PB_LCA_DATA_H2_STO_CAV_%IAM_Scenario%.inc' $INCLUDE         '../data/PB_LCA_DATA_H2_STO_CAV_%IAM_Scenario%.inc';
$if not EXIST '../data/PB_LCA_DATA_H2_STO_CAV_%IAM_Scenario%.inc' $INCLUDE '../../base/data/PB_LCA_DATA_H2_STO_CAV_%IAM_Scenario%.inc';
$offmulti

* --- LCA data: H2 transmission line construction ------------------------------
$onmulti
$if     EXIST '../data/PB_LCA_DATA_X_H2_%IAM_Scenario%.inc' $INCLUDE         '../data/PB_LCA_DATA_X_H2_%IAM_Scenario%.inc';
$if not EXIST '../data/PB_LCA_DATA_X_H2_%IAM_Scenario%.inc' $INCLUDE '../../base/data/PB_LCA_DATA_X_H2_%IAM_Scenario%.inc';
$offmulti

* --- H2-transmission LCA rank-1 factorisation (2026-05-30, for PB_XH2_RANKFIX) ---
* PB_LCA_DATA_X_H2 is rank-1 per year; factor it into a neutral per-line geomean scale
* x a per-category intensity, so the 10 _X_H2 score eqns become one base coupling + 9
* exact scalings (see PB_pardeclare note). Lossless to ~1e-10. Geomean is over the
* populated (>0) categories only, to avoid log(0) on unused PB_LCA_DATASET labels.
PB_XH2_NCAT(IRRRE,IRRRI,YYY) = SUM(PB_LCA_DATASET$(PB_LCA_DATA_X_H2(IRRRE,IRRRI,YYY,PB_LCA_DATASET) GT 0), 1);
PB_XH2_LINE_SCALE(IRRRE,IRRRI,YYY)$(PB_XH2_NCAT(IRRRE,IRRRI,YYY) GT 0)
    = exp( SUM(PB_LCA_DATASET$(PB_LCA_DATA_X_H2(IRRRE,IRRRI,YYY,PB_LCA_DATASET) GT 0),
               log(PB_LCA_DATA_X_H2(IRRRE,IRRRI,YYY,PB_LCA_DATASET))) / PB_XH2_NCAT(IRRRE,IRRRI,YYY) );
PB_XH2_INTENSITY(YYY,PB_LCA_DATASET)$(SUM((IRRRE,IRRRI), PB_XH2_LINE_SCALE(IRRRE,IRRRI,YYY)) GT 0)
    = SUM((IRRRE,IRRRI), PB_LCA_DATA_X_H2(IRRRE,IRRRI,YYY,PB_LCA_DATASET))
    / SUM((IRRRE,IRRRI), PB_XH2_LINE_SCALE(IRRRE,IRRRI,YYY));

* --- Elec-transmission LCA rank-1 factorisation (2026-05-30, for PB_X_RANKFIX) ---
* PB_LCA_DATA_X (loaded above) is rank-1 per year (verified CV~2e-9); identical lossless
* factorisation as the H2 block. Geomean over populated (>0) categories only.
PB_X_NCAT(IRRRE,IRRRI,YYY) = SUM(PB_LCA_DATASET$(PB_LCA_DATA_X(IRRRE,IRRRI,YYY,PB_LCA_DATASET) GT 0), 1);
PB_X_LINE_SCALE(IRRRE,IRRRI,YYY)$(PB_X_NCAT(IRRRE,IRRRI,YYY) GT 0)
    = exp( SUM(PB_LCA_DATASET$(PB_LCA_DATA_X(IRRRE,IRRRI,YYY,PB_LCA_DATASET) GT 0),
               log(PB_LCA_DATA_X(IRRRE,IRRRI,YYY,PB_LCA_DATASET))) / PB_X_NCAT(IRRRE,IRRRI,YYY) );
PB_X_INTENSITY(YYY,PB_LCA_DATASET)$(SUM((IRRRE,IRRRI), PB_X_LINE_SCALE(IRRRE,IRRRI,YYY)) GT 0)
    = SUM((IRRRE,IRRRI), PB_LCA_DATA_X(IRRRE,IRRRI,YYY,PB_LCA_DATASET))
    / SUM((IRRRE,IRRRI), PB_X_LINE_SCALE(IRRRE,IRRRI,YYY));

* --- CCS LCA data: load disabled (modular CCS layer uses ipardecdef instead) --
$ifi not %CCS%==yes $goto No_CCS
$label No_CCS

* --- LCA data: electric vehicles (only when EV add-on active) -----------------
$onmulti
$ifi not %EV%==yes $goto No_EV
$if     EXIST '../data/PB_LCA_DATA_EV_%IAM_Scenario%.inc' $INCLUDE         '../data/PB_LCA_DATA_EV_%IAM_Scenario%.inc';
$if not EXIST '../data/PB_LCA_DATA_EV_%IAM_Scenario%.inc' $INCLUDE '../../base/data/PB_LCA_DATA_EV_%IAM_Scenario%.inc';
$label No_EV
$offmulti

* --- Diesel car fleet (Option A: static 250M EU fleet, regionally distributed)
* When EV add-on is active, distribute the 250M EU passenger car stock across
* regions using the 2050 BEV column of EV_BEV_available as the per-region
* share proxy. Constant across YYY. Pre-staged here for the planned diesel-car
* implementation (PB_CCS_CAR_DIESEL_COMBTECH_PLAN.md, Component 2); harmless
* dead weight until consumed. When EV is off, ITOTAL_CAR_FLEET stays at the
* GAMS default (0) -- makes the eventual IDIESEL_AVAILABLE = 0 ("silent
* inert" per plan doc convention A9).
$ifi not %EV%==yes $goto No_DIESEL_FLEET
ITOTAL_CAR_FLEET(YYY, RRR) = ITOTAL_FLEET_EU
    * SUM(IYYYALIAS$(IYYYALIAS.val = 2050), EV_BEV_available(IYYYALIAS, RRR))
    / SUM((IYYYALIAS, IRRRE)$(IYYYALIAS.val = 2050), EV_BEV_available(IYYYALIAS, IRRRE));

* --- Diesel car count (= total - BEV - PHEV, floored at 0) -------------------
* Per CAR_DIESEL Component 2 (landed 2026-05-26): IDIESEL_AVAILABLE feeds the
* QPBSCORE_<CAT>_DIESEL equations. MAX(0, ...) defends against years where
* EV deployment overshoots the total-fleet projection.
IDIESEL_AVAILABLE(Y, IR) = MAX(0, ITOTAL_CAR_FLEET(Y, IR)
                                  - EV_BEV_available(Y, IR)
                                  - EV_PHEV_available(Y, IR));
$label No_DIESEL_FLEET

* --- Sector-level SOS thresholds (always loaded) ------------------------------
$onmulti
$if     EXIST '../data/PB_THRESHOLDS_DATA.inc' $INCLUDE         '../data/PB_THRESHOLDS_DATA.inc';
$if not EXIST '../data/PB_THRESHOLDS_DATA.inc' $INCLUDE '../../base/data/PB_THRESHOLDS_DATA.inc';
$offmulti

* --- Exogenous capacity additions per commission year (NEW_GKFX) -------------
* Positive year-on-year delta of GKFX -- i.e., MW (or MWh for storage) that
* came online exogenously in year YYY. Used by the cohort-frozen-IM
* construction term in QPBSCORE_<IMPACT> equations when PB_COHORT_CONSTR=yes.
* The MAX(0, ...) drops negative deltas (decommissioning); we only credit
* positive additions to the new-build cohort. For ORD(YYY)=1 the SUM has no
* matching prior year and evaluates to 0, so NEW_GKFX at the earliest YYY
* element equals GKFX itself (a reasonable convention since there is no prior
* state to subtract). The simulation year set Y(YYY) typically starts at 2025
* or later, so the earliest-YYY corner case (e.g., 2012 in the data file) is
* not consumed by the cohort sum in the QPBSCORE equations.
NEW_GKFX(YYY,IA,G) = MAX(0,
        GKFX(YYY,IA,G)
      - SUM(IYYYALIAS $ (ORD(IYYYALIAS) = ORD(YYY) - 1), GKFX(IYYYALIAS,IA,G))
);

* CC_STO biogenic/fossil aggregate scalars are precomputed offline by the
* Python preprocessor and assigned in the included PB_ipardecdef_<scenario>.inc
* (2026-05-26 refactor: replaced runtime SUM-over-G capacity-weighted aggregation).

* --- QPBSCORE row-scale factors (2026-05-29, LOSSLESS conditioning) -------------
* Assigned HERE (pardefine runs after the ipardecdef threshold load, so
* PB_THRESHOLDS_SET is populated -> the default below is a real assignment, not a
* 0-over-empty-set no-op). Declaration + rationale in PB_pardeclare.inc; derivation
* in PB_rowscale_STAGED.md. Default 1 = no-op (bit-identical to pre-patch);
* f_CAT = 1/(geomean IM_<CAT>_prod_elec*1000) applied only if PB_ROWSCALE_ON=yes.
PB_ROWSCALE(PB_THRESHOLDS_SET) = 1;
$ifi %PB_ROWSCALE_ON%==yes PB_ROWSCALE('SOS_CO2_sector')                       = 1.573e-2;
$ifi %PB_ROWSCALE_ON%==yes PB_ROWSCALE('SOS_Ozone_depletion_sector')           = 4.120e5;
$ifi %PB_ROWSCALE_ON%==yes PB_ROWSCALE('SOS_LU_sector')                        = 6.736e-3;
$ifi %PB_ROWSCALE_ON%==yes PB_ROWSCALE('SOS_WU_sector')                        = 1.483e-1;
$ifi %PB_ROWSCALE_ON%==yes PB_ROWSCALE('SOS_EUTROPHICATION_FRESHWATER_sector') = 1.188e2;
$ifi %PB_ROWSCALE_ON%==yes PB_ROWSCALE('SOS_ECOTOXICITY_FRESHWATER_sector')    = 6.802e-3;
$ifi %PB_ROWSCALE_ON%==yes PB_ROWSCALE('SOS_PM_sector')                        = 1.937e5;
$ifi %PB_ROWSCALE_ON%==yes PB_ROWSCALE('SOS_RADIATION_sector')                 = 2.098;
$ifi %PB_ROWSCALE_ON%==yes PB_ROWSCALE('SOS_ACIDIFICATION_sector')             = 4.537;
$ifi %PB_ROWSCALE_ON%==yes PB_ROWSCALE('SOS_RESOURCE_sector')                  = 1.429e4;

* --- Transmission sub-equation row-scale factors (2026-05-29) -------------------
* Same lossless mechanism as PB_ROWSCALE, for the VXKNACCUMNET / VXH2KNACCUMNET columns
* (cross-category spread ~9.6 / ~9.8 OOM). f = 1/(geomean LCA * 1000/IXKLIFETIME).
PB_ROWSCALE_X(PB_THRESHOLDS_SET)    = 1;
PB_ROWSCALE_X_H2(PB_THRESHOLDS_SET) = 1;
$ifi %PB_ROWSCALE_ON%==yes PB_ROWSCALE_X('SOS_CO2_sector')    = 2.7357e-04;
$ifi %PB_ROWSCALE_ON%==yes PB_ROWSCALE_X('SOS_Ozone_depletion_sector')    = 3.3264e+04;
$ifi %PB_ROWSCALE_ON%==yes PB_ROWSCALE_X('SOS_LU_sector')    = 2.0672e-05;
$ifi %PB_ROWSCALE_ON%==yes PB_ROWSCALE_X('SOS_WU_sector')    = 9.4619e-04;
$ifi %PB_ROWSCALE_ON%==yes PB_ROWSCALE_X('SOS_EUTROPHICATION_FRESHWATER_sector')    = 2.8582e-01;
$ifi %PB_ROWSCALE_ON%==yes PB_ROWSCALE_X('SOS_ECOTOXICITY_FRESHWATER_sector')    = 9.0750e-06;
$ifi %PB_ROWSCALE_ON%==yes PB_ROWSCALE_X('SOS_PM_sector')    = 3.8138e+03;
$ifi %PB_ROWSCALE_ON%==yes PB_ROWSCALE_X('SOS_RADIATION_sector')    = 3.4945e-03;
$ifi %PB_ROWSCALE_ON%==yes PB_ROWSCALE_X('SOS_ACIDIFICATION_sector')    = 3.0354e-02;
$ifi %PB_ROWSCALE_ON%==yes PB_ROWSCALE_X('SOS_RESOURCE_sector')    = 2.9840e+00;
$ifi %PB_ROWSCALE_ON%==yes PB_ROWSCALE_X_H2('SOS_CO2_sector') = 6.9163e-04;
$ifi %PB_ROWSCALE_ON%==yes PB_ROWSCALE_X_H2('SOS_Ozone_depletion_sector') = 1.0704e+05;
$ifi %PB_ROWSCALE_ON%==yes PB_ROWSCALE_X_H2('SOS_LU_sector') = 8.9248e-05;
$ifi %PB_ROWSCALE_ON%==yes PB_ROWSCALE_X_H2('SOS_WU_sector') = 1.0699e-03;
$ifi %PB_ROWSCALE_ON%==yes PB_ROWSCALE_X_H2('SOS_EUTROPHICATION_FRESHWATER_sector') = 8.9746e-01;
$ifi %PB_ROWSCALE_ON%==yes PB_ROWSCALE_X_H2('SOS_ECOTOXICITY_FRESHWATER_sector') = 1.8256e-05;
$ifi %PB_ROWSCALE_ON%==yes PB_ROWSCALE_X_H2('SOS_PM_sector') = 1.0848e+04;
$ifi %PB_ROWSCALE_ON%==yes PB_ROWSCALE_X_H2('SOS_RADIATION_sector') = 1.3050e-02;
$ifi %PB_ROWSCALE_ON%==yes PB_ROWSCALE_X_H2('SOS_ACIDIFICATION_sector') = 1.7321e-01;
$ifi %PB_ROWSCALE_ON%==yes PB_ROWSCALE_X_H2('SOS_RESOURCE_sector') = 7.1090e+01;

* --- EV sub-equation row-scale factors (2026-05-29) -----------------------------
* Normalises the VEV_G2V_BEV column (cross-category spread ~8.3 OOM). f = 1/geomean
* (PB_LCA_DATA_EV('CAR_EV_ONLY_BATTERY','LCA_<CAT>_constr')).
PB_ROWSCALE_EV(PB_THRESHOLDS_SET) = 1;
$ifi %PB_ROWSCALE_ON%==yes PB_ROWSCALE_EV('SOS_CO2_sector') = 2.010e-2;
$ifi %PB_ROWSCALE_ON%==yes PB_ROWSCALE_EV('SOS_Ozone_depletion_sector') = 7.225e+4;
$ifi %PB_ROWSCALE_ON%==yes PB_ROWSCALE_EV('SOS_LU_sector') = 1.698e-3;
$ifi %PB_ROWSCALE_ON%==yes PB_ROWSCALE_EV('SOS_WU_sector') = 1.350e-2;
$ifi %PB_ROWSCALE_ON%==yes PB_ROWSCALE_EV('SOS_EUTROPHICATION_FRESHWATER_sector') = 1.778e+1;
$ifi %PB_ROWSCALE_ON%==yes PB_ROWSCALE_EV('SOS_ECOTOXICITY_FRESHWATER_sector') = 8.237e-4;
$ifi %PB_ROWSCALE_ON%==yes PB_ROWSCALE_EV('SOS_PM_sector') = 1.717e+5;
$ifi %PB_ROWSCALE_ON%==yes PB_ROWSCALE_EV('SOS_RADIATION_sector') = 1.032e-1;
$ifi %PB_ROWSCALE_ON%==yes PB_ROWSCALE_EV('SOS_ACIDIFICATION_sector') = 1.123e+0;
$ifi %PB_ROWSCALE_ON%==yes PB_ROWSCALE_EV('SOS_RESOURCE_sector') = 1.136e+2;

* PB_ROWSCALE_EXT toggles the transmission/EV row-scale EXTENSION (the 10-eqn main
* PB_ROWSCALE above stays active regardless). Set --PB_ROWSCALE_EXT=off to neutralize
* the _X / _X_H2 / _EV row-scale families back to 1. Default 'on'.
$if not set PB_ROWSCALE_EXT $setglobal PB_ROWSCALE_EXT on
$ifi %PB_ROWSCALE_EXT%==off PB_ROWSCALE_X(PB_THRESHOLDS_SET)    = 1;
$ifi %PB_ROWSCALE_EXT%==off PB_ROWSCALE_X_H2(PB_THRESHOLDS_SET) = 1;
$ifi %PB_ROWSCALE_EXT%==off PB_ROWSCALE_EV(PB_THRESHOLDS_SET)   = 1;
