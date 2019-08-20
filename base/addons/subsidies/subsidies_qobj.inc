* Subsidy on fuel use for electricity generation
    - SUM((C,IS3,T), SUM(IAGK_HASORPOT(Y,IA,G)$(ICA(C,IA) AND IGE(G) AND SUBSIDIES_F_EL(Y,C,G)),
         IHOURSINST(IS3,T) * SUBSIDIES_F_EL(Y,C,G)  * VGE_T(Y,IA,G,IS3,T)/ (GDATA(G,'GDFE') * GEFFRATE(IA,G))))

* Subsidy on fuel use for heat generation
    - SUM((C,IS3,T), SUM(IAGK_HASORPOT(Y,IA,G)$(ICA(C,IA) AND IGH(G) AND SUBSIDIES_F_HEAT(Y,C,G)),
         IHOURSINST(IS3,T) * SUBSIDIES_F_HEAT(Y,C,G) * GDATA(G,'GDCV') * VGH_T(Y,IA,G,IS3,T)/ (GDATA(G,'GDFE') * GEFFRATE(IA,G))))

* Subsidy on fuel use
    - SUM((C,IS3,T), SUM(IAGK_HASORPOT(Y,IA,G)$(ICA(C,IA) AND SUBSIDIES_F(Y,C,G)),
         IHOURSINST(IS3,T) * SUBSIDIES_F(Y,C,G)  * VGF_T(Y,IA,G,IS3,T)))

* Subsidy on heat generation
    - SUM((C,IS3,T), SUM(IAGK_HASORPOT(Y,IA,G)$(ICA(C,IA) AND SUBSIDIES_G_HEAT(Y,C,G)),
         IHOURSINST(IS3,T) * SUBSIDIES_G_HEAT(Y,C,G)  * VGH_T(Y,IA,G,IS3,T)))

* Subsidy on electricity generation
    - SUM((C,IS3,T), SUM(IAGK_HASORPOT(Y,IA,G)$(ICA(C,IA) AND SUBSIDIES_G_EL(Y,C,G)),
         IHOURSINST(IS3,T) * SUBSIDIES_G_EL(Y,C,G)  * VGE_T(Y,IA,G,IS3,T)))

* Subsidy on electricity consumption
    - SUM((C,DEUSER), SUBSIDIES_DE(C,DEUSER) * SUM(IR$CCCRRR(C,IR), DE(Y,IR,DEUSER)))

* Subsidy on heat consumption
    - SUM((C,DHUSER), SUBSIDIES_DH(C,DHUSER) * SUM(IA$ICA(C,IA), DH(Y,IA,DHUSER)))


