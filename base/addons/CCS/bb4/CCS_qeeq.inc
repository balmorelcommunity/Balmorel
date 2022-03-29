* CCS add-on. Added by Juan Gea Bermudez

*adding electricity demand from carbon capture
+ SUM((IA,G)$(IAGK_HASORPOT(IY411,IA,G) AND RRRAAA(IR,IA) AND CCS_G(G)),
 (VGF_T(IY411,IA,G,IS3,T) * IM_CO2(G)*IOF0001 * IOF3P6 * CCS_CO2CAPTEFF_G(G)*  CCS_DECO2COMP_G(G))/(1-DISLOSS_E_AG(IA,G))
 )

