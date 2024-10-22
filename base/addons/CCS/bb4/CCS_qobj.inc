* Additions to the objective function:


- SUM((C,GROUP), SUM((IA,G)$(ICA(C,IA) AND IAGK_HASORPOT(Y,IA,G) AND CCS_G(G) AND GROUP_AAA(GROUP,IA)), SUM((IS3,T), IHOURSINST(IS3,T) * IM_CO2(G) * IOF0001 * IOF3P6 * VGF_T(Y,IA,G,IS3,T)*CCS_CO2CAPTEFF_G(G)) * EMI_POL(Y,C,GROUP,"TAX_CO2")*IHOURFRAC))

*Transportation and storage costs
*(Right now only what is stored finally - think about how the CCU carbon is priced. Here, or in OptiFlow?)
+ SUM(C, SUM((IA,G)$(ICA(C,IA) AND IAGK_HASORPOT(Y,IA,G) AND CCS_G(G)), SUM((IS3,T), IHOURSINST(IS3,T) * (IM_CO2(G) + IM_CO2RE(G))*IHOURFRAC*IOF0001 * IOF3P6 * VGF_T(Y,IA,G,IS3,T)*CCS_CO2CAPTEFF_G(G)) *CCS_TRANSPORTCOST))


