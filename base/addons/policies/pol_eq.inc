* Addon for securing that Policy requrements are forfilled

EQUATIONS

QPOLSHAREGROSS (POLAREA,POLICY)    'Inshures requrements on share of electricity generation for policy area and tecnology group, compared to electricity demand in the area'

QPOLSHARENET   (POLAREA,POLICY)    'Inshures requrements on share of electricity generation for policy area and tecnology group, compared to total electricity generation in the area'

QPOLMAXCO2     (POLAREA,POLICY)    'Inshures requrements on maximal CO2 emmision for policy area'

QPOLMINPROD    (POLAREA,POLICY)    'Inshures requrements on minimal production for policy ares and tecnology group'

QPOLCAPTARGET  (POLAREA,POLICY)    'Inshures requrements on electricity generation capacity in policy area and technology group'

;


QPOLSHAREGROSS(POLAREA,POLICY)$(IPOLREQ_Y(POLAREA,POLICY) and POLTYP(POLICY,'SHAREGROSS')) ..


         (SUM(CCCRRRAAA$(POLAREAGEO(POLAREA,CCCRRRAAA)),
                 SUM(G$(POLTECH(POLICY,G)),
                         SUM(C$(sameas(C,CCCRRRAAA)),
                                 SUM((IA,IS3,T)$(IAGK_Y(IA,G) AND ICA(C,IA)),       IHOURSINST(IS3,T)*VGE_T(IA,G,IS3,T) )
                                 + SUM((IA,IS3,T)$(IAGKN(IA,G) AND ICA(C,IA)),      IHOURSINST(IS3,T)*VGEN_T(IA,G,IS3,T))
                                 )
                         + SUM(IR$(sameas(IR,CCCRRRAAA)),
                                 SUM((IA,IS3,T)$(IAGK_Y(IA,G) AND RRRAAA(IR,IA)),   IHOURSINST(IS3,T)*VGE_T(IA,G,IS3,T) )
                                 + SUM((IA,IS3,T)$(IAGKN(IA,G) AND RRRAAA(IR,IA)),  IHOURSINST(IS3,T)*VGEN_T(IA,G,IS3,T))
                                 )
                         + SUM(IA$(sameas(IA,CCCRRRAAA)),
                                 SUM((IS3,T)$(IAGK_Y(IA,G)),                        IHOURSINST(IS3,T)*VGE_T(IA,G,IS3,T) )
                                 + SUM((IS3,T)$(IAGKN(IA,G)),                       IHOURSINST(IS3,T)*VGEN_T(IA,G,IS3,T))
                                 )
                 )
         ))
         /
         (SUM(CCCRRRAAA$(POLAREAGEO(POLAREA,CCCRRRAAA)),
                         SUM(C$(sameas(C,CCCRRRAAA)),
                                 SUM((IR,IS3,T)$( CCCRRR(C,IR) ),  IHOURSINST(IS3,T)* IDE_T_Y(IR,IS3,T)/(1-DISLOSS_E(IR)) )
                         )
                         + SUM(IR$(sameas(IR,CCCRRRAAA)),
                                 SUM((IS3,T), IHOURSINST(IS3,T)* IDE_T_Y(IR,IS3,T)/(1-DISLOSS_E(IR)) )
                         )
         ))
        + VQPOLSHAREGROSS(POLAREA,POLICY)
                   =G=
         IPOLREQ_Y(POLAREA,POLICY)
;



QPOLSHARENET(POLAREA,POLICY)$(IPOLREQ_Y(POLAREA,POLICY) and POLTYP(POLICY,'SHARENETTO')) ..


         (SUM(CCCRRRAAA$(POLAREAGEO(POLAREA,CCCRRRAAA)),
                 SUM(G$(POLTECH(POLICY,G)),
                         SUM(C$(sameas(C,CCCRRRAAA)),
                                 SUM((IA,IS3,T)$(IAGK_Y(IA,G) AND ICA(C,IA)),       IHOURSINST(IS3,T)*VGE_T(IA,G,IS3,T) )
                                 + SUM((IA,IS3,T)$(IAGKN(IA,G) AND ICA(C,IA)),      IHOURSINST(IS3,T)*VGEN_T(IA,G,IS3,T))
                                 )
                         + SUM(IR$(sameas(IR,CCCRRRAAA)),
                                 SUM((IA,IS3,T)$(IAGK_Y(IA,G) AND RRRAAA(IR,IA)),   IHOURSINST(IS3,T)*VGE_T(IA,G,IS3,T) )
                                 + SUM((IA,IS3,T)$(IAGKN(IA,G) AND RRRAAA(IR,IA)),  IHOURSINST(IS3,T)*VGEN_T(IA,G,IS3,T))
                                 )
                         + SUM(IA$(sameas(IA,CCCRRRAAA)),
                                 SUM((IS3,T)$(IAGK_Y(IA,G)),                        IHOURSINST(IS3,T)*VGE_T(IA,G,IS3,T) )
                                 + SUM((IS3,T)$(IAGKN(IA,G)),                       IHOURSINST(IS3,T)*VGEN_T(IA,G,IS3,T))
                                 )
                 )
         ))
         /
         (SUM(CCCRRRAAA$(POLAREAGEO(POLAREA,CCCRRRAAA)),
                         SUM(C$(sameas(C,CCCRRRAAA)),
                                 SUM((IR,IS3,T)$( CCCRRR(C,IR) ),  IHOURSINST(IS3,T)* IDE_T_Y(IR,IS3,T) )
                         )
                         + SUM(IR$(sameas(IR,CCCRRRAAA)),
                                 SUM((IS3,T), IHOURSINST(IS3,T)* IDE_T_Y(IR,IS3,T))
                         )
         ))
        + VQPOLSHARENET(POLAREA,POLICY)
                   =G=
         IPOLREQ_Y(POLAREA,POLICY)
;




QPOLMAXCO2(POLAREA,POLICY)$(IPOLREQ_Y(POLAREA,POLICY) and POLTYP(POLICY,'MAXCO2')) ..

         SUM(CCCRRRAAA$(POLAREAGEO(POLAREA,CCCRRRAAA)),
                 SUM(G$(IGE(G) and IM_CO2(G)),
                         SUM(C$(sameas(C,CCCRRRAAA)),
                                 SUM((IA,IS3,T)$(IAGK_Y(IA,G) AND ICA(C,IA)),       IHOURSINST(IS3,T) * (IM_CO2(G)/IOF1000) * IOF3P6 * VGF_T(IA,G,IS3,T))
                                 + SUM((IA,IS3,T)$(IAGKN(IA,G) AND ICA(C,IA)),      IHOURSINST(IS3,T) * (IM_CO2(G)/IOF1000) * IOF3P6 * VGFN_T(IA,G,IS3,T))
                                 )
                         + SUM(IR$(sameas(IR,CCCRRRAAA)),
                                 SUM((IA,IS3,T)$(IAGK_Y(IA,G) AND RRRAAA(IR,IA)),   IHOURSINST(IS3,T) * (IM_CO2(G)/IOF1000) * IOF3P6 * VGF_T(IA,G,IS3,T))
                                 + SUM((IA,IS3,T)$(IAGKN(IA,G) AND RRRAAA(IR,IA)),  IHOURSINST(IS3,T) * (IM_CO2(G)/IOF1000) * IOF3P6 * VGFN_T(IA,G,IS3,T))
                                 )
                         + SUM(IA$(sameas(IA,CCCRRRAAA)),
                                 SUM((IS3,T)$(IAGK_Y(IA,G)),                        IHOURSINST(IS3,T) * (IM_CO2(G)/IOF1000) * IOF3P6 * VGF_T(IA,G,IS3,T))
                                 + SUM((IS3,T)$(IAGKN(IA,G)),                       IHOURSINST(IS3,T) * (IM_CO2(G)/IOF1000) * IOF3P6 * VGFN_T(IA,G,IS3,T))
                                 )
                 )
         )

                   =L=
         IPOLREQ_Y(POLAREA,POLICY)
         + VQPOLMAXCO2(POLAREA,POLICY)
;



QPOLMINPROD (POLAREA,POLICY)$(IPOLREQ_Y(POLAREA,POLICY) and POLTYP(POLICY,'MINPROD')) ..

         SUM(CCCRRRAAA$(POLAREAGEO(POLAREA,CCCRRRAAA)),
                 SUM(G$(POLTECH(POLICY,G)),
                         SUM(C$(sameas(C,CCCRRRAAA)),
                                 SUM((IA,IS3,T)$(IAGK_Y(IA,G) AND ICA(C,IA)),       IHOURSINST(IS3,T)*VGE_T(IA,G,IS3,T) )
                                 + SUM((IA,IS3,T)$(IAGKN(IA,G) AND ICA(C,IA)),      IHOURSINST(IS3,T)*VGEN_T(IA,G,IS3,T))
                                 )
                         + SUM(IR$(sameas(IR,CCCRRRAAA)),
                                 SUM((IA,IS3,T)$(IAGK_Y(IA,G) AND RRRAAA(IR,IA)),   IHOURSINST(IS3,T)*VGE_T(IA,G,IS3,T) )
                                 + SUM((IA,IS3,T)$(IAGKN(IA,G) AND RRRAAA(IR,IA)),  IHOURSINST(IS3,T)*VGEN_T(IA,G,IS3,T))
                                 )
                         + SUM(IA$(sameas(IA,CCCRRRAAA)),
                                 SUM((IS3,T)$(IAGK_Y(IA,G)),                        IHOURSINST(IS3,T)*VGE_T(IA,G,IS3,T) )
                                 + SUM((IS3,T)$(IAGKN(IA,G)),                       IHOURSINST(IS3,T)*VGEN_T(IA,G,IS3,T))
                                 )
                 )
         )
         + VQPOLMINPROD(POLAREA,POLICY)
                   =G=
         IPOLREQ_Y(POLAREA,POLICY)
;


QPOLCAPTARGET  (POLAREA,POLICY)$(IPOLREQ_Y(POLAREA,POLICY) and POLTYP(POLICY,'CAPTARGET')) ..


         SUM(CCCRRRAAA$(POLAREAGEO(POLAREA,CCCRRRAAA)),
                 SUM(G$(POLTECH(POLICY,G)),
                         SUM(C$(sameas(C,CCCRRRAAA)),
                                 SUM((IA)$(IAGK_Y(IA,G) AND ICA(C,IA)),       IGKFX_Y(IA,G) + IGKVACCTOY(IA,G))
                                 + SUM((IA)$(IAGKN(IA,G) AND ICA(C,IA)),      VGKN(IA,G) )
                                 )
                         + SUM(IR$(sameas(IR,CCCRRRAAA)),
                                 SUM((IA)$(IAGK_Y(IA,G) AND RRRAAA(IR,IA)),   IGKFX_Y(IA,G) + IGKVACCTOY(IA,G))
                                 + SUM((IA)$(IAGKN(IA,G) AND RRRAAA(IR,IA)),  VGKN(IA,G) )
                                 )
                         + SUM(IA$(sameas(IA,CCCRRRAAA)),
                                                         (IGKFX_Y(IA,G) + IGKVACCTOY(IA,G))$(IAGK_Y(IA,G))
                                                         +VGKN(IA,G)$(IAGKN(IA,G))
                                 )
                 )
         )
         + VQPOLCAPTARGET(POLAREA,POLICY)
                   =G=
         IPOLREQ_Y(POLAREA,POLICY)
;

