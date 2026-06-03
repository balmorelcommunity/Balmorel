* CCS add-on. Added by Juan Gea Bermudez

*Removing absorbed CO2
* 2026-05-27 code hygiene: added 'AND CCS_G(G)' to the SUM filter.
* The coefficient CCS_CO2CAPTEFF_G(G) is zero for non-CCS plants, so LP NNZ
* is unchanged (GAMS skips zero coefs at compile time). Tightening the gate
* saves GAMS compile-time iteration over non-CCS generators. Mirrors gating
* in CCS_qeeq.inc and CCS_qobj.inc which already include CCS_G(G).
+SUM((IA,G)$(IAGK_HASORPOT(IY411,IA,G) AND CCS_G(G) AND ICA(C,IA) AND GROUP_AAA(GROUP,IA)), SUM((IS3,T), IHOURSINST(IS3,T) * IHOURFRAC * (IM_CO2(G) + IM_CO2RE(G)) * IOF0001 * IOF3P6 * VGF_T(IY411,IA,G,IS3,T)*CCS_CO2CAPTEFF_G(G)))

