* Scenario-local GKFX_renewable.inc wrapper: base + Stage 3 VRE drops.
* DROP_VRE_* sets are declared in scenario AGKN.inc (loaded before this).
$INCLUDE '../../base/data/GKFX_renewable.inc'

* 2026-05-29 VRE add-back: tracking PV + onshore SP199-HH100 restored; only offshore SP316 kept dropped.
*GKFX(YYY, DROP_VRE_TRACKING_PV, GGG)     = 0;
*GKFX(YYY, DROP_VRE_ONS_SP199_HH100, GGG) = 0;
GKFX(YYY, DROP_VRE_OFF_SP316, GGG)       = 0;
