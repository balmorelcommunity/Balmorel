* File earnings.inc.
* The file should generate earnings for each individual plant (aggregate of plants)
* to enable automatic decommisioning thereof.
* This is called by the DECOMEFF option in balopt.opt.
* Author: Lars Bregnbæk
* Revision: 1.0 LB



Rev_E(Y,IAGK_Y(IA,IGE))$IGNOTETOH(IGE)  =        OMONEY*SUM((IR,S,T)$RRRAAA(IR,IA),
                                                     IOF1000000*QEEQ.m(IR,S,T)*(
                                                         VGE_T.l(IA,IGE,S,T))
                                                         )/IOF1000000;

Rev_H(Y,IAGK_Y(IA,IGH))$(IDH_SUMST(IA) NE 0)  =  OMONEY*Sum((S,T),
                                         IOF1000000*QHEQ.m(IA,S,T)*(
                                             VGH_T.l(IA,IGH,S,T)
                                              )
                                         )/IOF1000000;

Fuel_C(Y,IAGK_Y(IA,G)) = OMONEY*(SUM(FFF$(GDATA(G,'GDFUEL') EQ FDATA(FFF,'FDNB')),
                                         IFUELP_Y(IA,FFF) * IOF3P6 * SUM((S,T), IHOURSINST(S,T)*VGE_T.l(IA,G,S,T)/(GDATA(G,'GDFE')* (1-GEFFDERATE(IA,G))))$IGE(G)
                                        +IFUELP_Y(IA,FFF) * IOF3P6 * SUM((S,T), IHOURSINST(S,T)*GDATA(G,'GDCV')*VGH_T.l(IA,G,S,T)/(GDATA(G,'GDFE')*(1-GEFFDERATE(IA,G))=)$IGH(G)
                                         ))/IOF1000000
                                +OMONEY*SUM((IR,S,T)$RRRAAA(IR,IA),
                                   IOF1000000*QEEQ.m(IR,S,T)*(VGE_T.l(IA,G,S,T))/IOF1000000
                                 )$IGETOH(G)    ;

VOM_C(Y,IAGK_Y(IA,G))  = OMONEY*(
                                    GOMVCOST(IA,G) * SUM((S,T), IHOURSINST(S,T)*VGE_T.l(IA,G,S,T))$IGE(G)
                                  + GOMVCOST(IA,G) * SUM((S,T), IHOURSINST(S,T)*GDATA(G,'GDCV')*VGH_T.l(IA,G,S,T))$IGNOTETOH(G)
                                 )/IOF1000000;       ;

FOM_C(Y,IAGK_Y(IA,G))  = OMONEY*IOF1000*((IGKVACCTOY(G,IA) + IGKFX_Y(G,IA) - VDECOM.l(IA,G))*GOMFCOST(IA,G))/IOF1000000        ;

CO2Costs(Y,IAGK_Y(IA,G)) = OMONEY*sum(C$ICA(C,IA), ITAX_CO2_Y(C)*SUM((S,T), IHOURSINST(S,T) * (IM_CO2(G)/1000) * IOF3P6 *
                                (VGE_T.L(IA,G,S,T) + GDATA(G,'GDCV')*VGH_T.L(IA,G,S,T))/
                                                 (GDATA(G,'GDFE')* (1-GEFFDERATE(IA,G)))))/IOF1000000;

Tax_C(Y,IAGK_Y(IA,G))  = OMONEY*(
                                 Sum(C$ICA(C,IA),
                                         ITAX_SO2_Y(C)*SUM((S,T), IHOURSINST(S,T) * (IM_SO2(G)/1000) * IOF3P6 *
                                                 (VGE_T.L(IA,G,S,T)+ GDATA(G,'GDCV')*VGH_T.L(IA,G,S,T)) /
                                                 (GDATA(G,'GDFE')* (1-GEFFDERATE(IA,G))) )

                                        +ITAX_NOX_Y(C)*SUM((S,T), IHOURSINST(S,T) * (GDATA(G,'GDNOX')/1000000)*IOF3P6*
                                                 (VGE_T.L(IA,G,S,T)+ GDATA(G,'GDCV')*VGH_T.L(IA,G,S,T)) /
                                                         (GDATA(G,'GDFE')* (1-GEFFDERATE(IA,G))))

                                        +SUM((FFF,S,T)$(GDATA(G,'GDFUEL') EQ FDATA(FFF,'FDNB')),
                                              IHOURSINST(S,T) * TAX_F(FFF,C) * IOF3P6 * VGE_T.l(IA,G,S,T) / (GDATA(G,'GDFE') * (1-GEFFDERATE(IA,G))))$IGE(G)
                                        +SUM((FFF,S,T)$(GDATA(G,'GDFUEL') EQ FDATA(FFF,'FDNB')),
                                              IHOURSINST(S,T) * TAX_F(FFF,C) * IOF3P6*GDATA(G,'GDCV')* VGH_T.l(IA,G,S,T)/(GDATA(G,'GDFE') * (1-GEFFDERATE(IA,G))))$IGH(G)
                                   )
        + SUM((S,T),  TAX_GH(IA,G) *IHOURSINST(S,T)  * IOF3P6 * VGH_T.l(IA,G,S,T))$IGH(G)
        + SUM((S,T),  TAX_FHO(IA,G)*IHOURSINST(S,T)  * IOF3P6 * GDATA(G,'GDCV')* VGH_T.l(IA,G,S,T)/(GDATA(G,'GDFE') * (1-GEFFDERATE(IA,G))))$(IGHOB(G) or IGETOH(G))

                 )/IOF1000000;

Profitability(Y,IAGK_Y(IA,G)) = Rev_E(Y,IA,G) + Rev_H(Y,IA,G) - Fuel_C(Y,IA,G) - VOM_C(Y,IA,G) - FOM_C(Y,IA,G) - Tax_C(Y,IA,G)-CO2Costs(Y,IA,G) ;
