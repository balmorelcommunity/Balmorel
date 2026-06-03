* Scenario-local AGKN.inc wrapper: base + A1 heat-area aggregation.
* Declares the AAAGG_* sets here (loaded first); referenced by GKFX.inc + DH.inc.
$INCLUDE '../../base/data/AGKN.inc'

SET AAAGG_DK1(AAA) / DK1_Medium, DK1_MedSmall, DK1_Small, DK1_Rural /;
SET AAAGG_DK2(AAA) / DK2_Medium, DK2_MedSmall, DK2_Small, DK2_Rural /;
SET AAAGG_FI(AAA)  / FI_medium, FI_small, FI_large_gas, FI_medium_gas, FI_small_gas /;
SET AAAGG_SE1(AAA) / SE1_small /;
SET AAAGG_SE2(AAA) / SE2_small /;
SET AAAGG_SE3(AAA) / SE3_medium, SE3_small /;
SET AAAGG_SE4(AAA) / SE4_medium, SE4_small /;
SET AAAGG_EE(AAA)  / EE_Enefit, EE_Kohtla_Jarve, EE_Narva, EE_Parnu, EE_Sillamae, EE_Tartu, EE_Urban /;
SET AAAGG_LT(AAA)  / LT_KauU, LT_KlaU, LT_Panevezys, LT_SiaU, LT_Other_DH /;
SET AAAGG_LV(AAA)  / LV_Other_DH /;

AGKN('DK1_Large',GGG)$(SUM(AAAGG_DK1, 1$AGKN(AAAGG_DK1,GGG))) = YES;
AGKN('DK2_Large',GGG)$(SUM(AAAGG_DK2, 1$AGKN(AAAGG_DK2,GGG))) = YES;
AGKN('FI_large',GGG)$(SUM(AAAGG_FI,  1$AGKN(AAAGG_FI,GGG)))  = YES;
AGKN('SE1_medium',GGG)$(SUM(AAAGG_SE1, 1$AGKN(AAAGG_SE1,GGG))) = YES;
AGKN('SE2_medium',GGG)$(SUM(AAAGG_SE2, 1$AGKN(AAAGG_SE2,GGG))) = YES;
AGKN('SE3_large',GGG)$(SUM(AAAGG_SE3, 1$AGKN(AAAGG_SE3,GGG))) = YES;
AGKN('SE4_large',GGG)$(SUM(AAAGG_SE4, 1$AGKN(AAAGG_SE4,GGG))) = YES;
AGKN('EE_Tallinn',GGG)$(SUM(AAAGG_EE, 1$AGKN(AAAGG_EE,GGG)))  = YES;
AGKN('LT_VilU',GGG)$(SUM(AAAGG_LT, 1$AGKN(AAAGG_LT,GGG)))     = YES;
AGKN('LV_RigaR',GGG)$(SUM(AAAGG_LV, 1$AGKN(AAAGG_LV,GGG)))    = YES;

AGKN(AAAGG_DK1,GGG) = NO;
AGKN(AAAGG_DK2,GGG) = NO;
AGKN(AAAGG_FI,GGG)  = NO;
AGKN(AAAGG_SE1,GGG) = NO;
AGKN(AAAGG_SE2,GGG) = NO;
AGKN(AAAGG_SE3,GGG) = NO;
AGKN(AAAGG_SE4,GGG) = NO;
AGKN(AAAGG_EE,GGG)  = NO;
AGKN(AAAGG_LT,GGG)  = NO;
AGKN(AAAGG_LV,GGG)  = NO;

* --- Stage 3: VRE collapses (A2 + B1) ---
$INCLUDE '../data/vre_drop_sets.inc'

* 2026-05-29 VRE add-back: tracking PV + onshore SP199-HH100 restored; only offshore SP316 kept dropped.
*AGKN(DROP_VRE_TRACKING_PV, GGG)     = NO;
*AGKN(DROP_VRE_ONS_SP199_HH100, GGG) = NO;
AGKN(DROP_VRE_OFF_SP316, GGG)       = NO;

* ============================================================================
* Solution 2 (A1 only, 2026-05-28): realistic biomass-CCS footprint.
* The 05-24 expansion made biomass-CCS investable in ALL ~1,230 areas (~40,590 of
* the 41,010 investable CCS pairs). Base (non-CCS) biomass is ALLOWEDINV-restricted
* to realistic sites; biomass-CCS should follow the same realism. Capture stays
* available wherever biomass generation is realistic -> the joint greenfield BECCS
* option (and its incentive) is preserved. Gas-CCS untouched (already ~420 pairs).
* IGF is built later (Balmorelbb4.inc:741), so we identify biomass fuels here with
* the same test IGF uses: GDATA(G,'GDFUEL') EQ FDATA(FFF,'FDACRONYM')
* (GDATA/FDATA load at bb4datainc:151-217, before this wrapper).
* ============================================================================
SET BIO_FFF(FFF) "biomass CCS feedstock fuels" / WOODCHIPS, WOODPELLETS, STRAW, MUNIWASTE, BIOGAS /;
SET BIO_G(GGG)   "generators burning a biomass feedstock";
BIO_G(GGG)$(SUM(BIO_FFF$(GDATA(GGG,'GDFUEL') EQ FDATA(BIO_FFF,'FDACRONYM')), 1)) = YES;

* --- B1 NOT applied (2026-05-28): with headroom under the 5-7h target, dropping wood
*     pellets is unnecessary; pellets are KEPT, restricted to base-biomass areas by A1. ---

* --- A1: biomass-CCS investable only where base (non-CCS) biomass generation is
*         allowed to invest (ALLOWEDINV) = realistic biomass-plant areas ---
SET BIO_CAP_AAA(AAA) "areas where base (non-CCS) biomass generation is investable";
BIO_CAP_AAA(AAA)$(SUM(GGG$(ALLOWEDINV(AAA,GGG) AND BIO_G(GGG) AND (NOT CCS_G(GGG))), 1)) = YES;
AGKN(AAA,GGG)$(CCS_G(GGG) AND BIO_G(GGG) AND (NOT BIO_CAP_AAA(AAA))) = NO;

* ============================================================================
* B1 (2026-05-31): drop wood-pellet generators from investability.
* GMAXF enters the wood resource identically as WOODCHIPS and WOODPELLETS (same
* per-country values), so allowing both double-counts the same forest. Removing
* the pellet pathway keeps wood counted once (as chips, capped 997 TWh). Techs
* remain in ipardecdef (LCA) but are never built. Same fuel test as BIO_G above.
* Re-enables the B1 deferred on 2026-05-28 (see comment near BIO_FFF).
* ============================================================================
AGKN(AAA,GGG)$(GDATA(GGG,'GDFUEL') EQ FDATA('WOODPELLETS','FDACRONYM')) = NO;
