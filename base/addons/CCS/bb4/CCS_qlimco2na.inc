* CCS add-on. Added by Juan Gea Bermudez

*Removing absorbed CO2
* 2026-05-27 code hygiene: added 'AND CCS_G(G)' to the SUM filter. Same
* rationale as CCS_qlimco2c.inc — LP NNZ unchanged, GAMS compile-time
* iteration reduced. Mirrors gating in CCS_qeeq.inc and CCS_qobj.inc.
+SUM(C,SUM((IA,G)$(IAGK_HASORPOT(IY411,IA,G) AND CCS_G(G) AND ICA(C,IA) AND GROUP_AAA(GROUP,IA)), SUM((IS3,T), IHOURSINST(IS3,T) * IHOURFRAC * (IM_CO2(G) + IM_CO2RE(G)) * IOF0001 * IOF3P6 * VGF_T(IY411,IA,G,IS3,T)*CCS_CO2CAPTEFF_G(G))))

