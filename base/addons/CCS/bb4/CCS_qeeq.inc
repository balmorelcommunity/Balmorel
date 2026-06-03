* CCS add-on. Added by Juan Gea Bermudez

*adding electricity demand from carbon capture
* 2026-05-24: include biogenic CO2 via IM_CO2RE -- compression energy is mass-based,
* applies regardless of CO2 origin. Pattern aligns with CCS_qlimco2c, CCS_qlimco2na,
* CCS_qobj (transport cost), and CCS_eqndecdef (QFLOWCO2LIM), all of which use
* (IM_CO2 + IM_CO2RE) for captured-mass expressions. Original code (Juan Gea Bermudez)
* used IM_CO2 only, which gave zero compression-energy demand for biomass-CCS plants.
+ SUM((IA,G)$(IAGK_HASORPOT(IY411,IA,G) AND RRRAAA(IR,IA) AND CCS_G(G)),
 (VGF_T(IY411,IA,G,IS3,T) * (IM_CO2(G) + IM_CO2RE(G))*IOF0001 * IOF3P6 * CCS_CO2CAPTEFF_G(G)*  CCS_DECO2COMP_G(G))/(1-DISLOSS_E_AG(IA,G))
 )

