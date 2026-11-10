* Additions to the objective function:


- SUM((C,GROUP), SUM((IA,G)$(ICA(C,IA) AND IAGK_HASORPOT(Y,IA,G) AND CCS_G(G) AND GROUP_AAA(GROUP,IA)), SUM((IS3,T), IHOURSINST(IS3,T) * (IM_CO2(G)*IOF0001) * IOF3P6 * VGF_T(Y,IA,G,IS3,T)*CCS_CO2CAPTEFF_G(G)) * EMI_POL(Y,C,GROUP,"TAX_CO2")*IHOURFRAC))

*Transportation and storage costs, for all captured CO2 incl. the renewable part (bio-CCS); the tax credit above stays on the fossil part
+ SUM(C, SUM((IA,G)$(ICA(C,IA) AND IAGK_HASORPOT(Y,IA,G) AND CCS_G(G)), SUM((IS3,T), IHOURSINST(IS3,T) * ((IM_CO2(G)+IM_CO2RE(G))*IHOURFRAC*IOF0001) * IOF3P6 * VGF_T(Y,IA,G,IS3,T)*CCS_CO2CAPTEFF_G(G)) *CCS_TRANSPORTCOST ))
