* File compprint3.INC.
* This file is part of the new welfare calculation module for the Balmorel model.
* Created by Lars Bregnbæk


* This file contains routines for handling of intermediate information that may
* be usefull output.


*===============================================================================
*                Overview
*===============================================================================



*===============================================================================
*                Overview end
*===============================================================================

         e_rev(Y,C)          =eps+   OMONEY*SUM((IR,S,T)$CCCRRR(C,IR),
                                                     IOF1000000*QEEQ.m(IR,S,T)*(
                                                         SUM(IAGK_Y(IA,IGE)$((RRRAAA(IR,IA)) AND IGNOTETOH(IGE)), VGE_T.l(IA,IGE,S,T))
                                                       + SUM(IAGKN(IA,IGE)$((RRRAAA(IR,IA)) AND IGNOTETOH(IGE)), VGEN_T.l(IA,IGE,S,T))
                                                       - SUM(IA$(RRRAAA(IR,IA) AND sum(IGESTO,IAGK_Y(IA,IGESTO)+IAGKN(IA,IGESTO))),VESTOLOADT.l(IA,S,T))
                                                         )
                                                         )/IOF1000000;

         h_rev(Y,C)          =eps+   OMONEY*Sum((IA,S,T)$(IDH_SUMST(IA) NE 0 and ICA(C,IA)),
                                         IOF1000000*QHEQ.m(IA,S,T)*(
                                             SUM(IGBPR$IAGK_Y(IA,IGBPR),VGH_T.l(IA,IGBPR,S,T))
                                           + SUM(IGBPR$IAGKN(IA,IGBPR),VGHN_T.l(IA,IGBPR,S,T))
                                           + SUM(IGEXT$IAGK_Y(IA,IGEXT),VGH_T.l(IA,IGEXT,S,T))
                                           + SUM(IGEXT$IAGKN(IA,IGEXT),VGHN_T.l(IA,IGEXT,S,T))
                                           + SUM(IGHH$IAGK_Y(IA,IGHH),VGH_T.l(IA,IGHH,S,T))
                                           + SUM(IGHH$IAGKN(IA,IGHH),VGHN_T.l(IA,IGHH,S,T))
                                           + SUM(IGETOH$IAGK_Y(IA,IGETOH),VGH_T.l(IA,IGETOH,S,T))
                                           + SUM(IGETOH$IAGKN(IA,IGETOH),VGHN_T.l(IA,IGETOH,S,T))
                                           + SUM(IGESTO$(IAGK_Y(IA,IGESTO) and GDATA(IGESTO,'GDCB')),VGE_T.l(IA,IGESTO,S,T)/GDATA(IGESTO,'GDCB'))
                                           - SUM(IGHSTO$(IAGK_Y(IA,IGHSTO) or IAGKN(IA,IGHSTO)),VHSTOLOADT.l(IA,S,T))
                                                                      )
                                         )/IOF1000000;

         fxcost(Y,C)         =eps+  OMONEY*IOF1000*(SUM(IAGK_Y(IA,G)$ICA(C,IA),(IGKVACCTOY(IA,G) + IGKFX_Y(IA,G)
$ifi %DECOMPEFF%==yes                                                                   -VDECOM.l(IA,G)
                                                                                         )*GOMFCOST(IA,G))
                                + SUM(IAGKN(IA,G)$ICA(C,IA),VGKN.l(IA,G)*GOMFCOST(IA,G)))/IOF1000000          ;

         fuelcost(Y,C)       =eps+ OMONEY*(

                                         SUM((IAGK_Y(IA,G),FFF)$(GDATA(G,'GDFUEL') EQ FDATA(FFF,'FDNB') and ICA(C,IA) and IGNOTETOH(G)),
                                           IFUELP_Y(IA,FFF) * IOF3P6 * SUM((S,T), IHOURSINST(S,T)*VGF_T.l(IA,G,S,T)) )
                                        +SUM((IAGKN(IA,G),FFF)$(GDATA(G,'GDFUEL') EQ FDATA(FFF,'FDNB') and ICA(C,IA) and IGNOTETOH(G)),
                                           IFUELP_Y(IA,FFF) * IOF3P6 * SUM((S,T), IHOURSINST(S,T)*VGFN_T.l(IA,G,S,T)) )

                                +SUM((IR,S,T)$CCCRRR(C,IR),
                                   IOF1000000*QEEQ.m(IR,S,T)*(
                                                        SUM(IAGK_Y(IA,IGE)$((RRRAAA(IR,IA)) AND IGETOH(IGE) and ICA(C,IA)), VGE_T.l(IA,IGE,S,T))
                                                      + SUM(IAGKN(IA,IGE)$((RRRAAA(IR,IA)) AND IGETOH(IGE) and ICA(C,IA)), VGEN_T.l(IA,IGE,S,T))
                                                         )
                                                         )
                                 )/IOF1000000;



         vcost(Y,C)          =eps+ OMONEY*(
                                    SUM(IAGK_Y(IA,IGE)$ICA(C,IA), GOMVCOST(IA,IGE) * SUM((S,T), IHOURSINST(S,T)*VGE_T.l(IA,IGE,S,T)))
                                  + SUM(IAGK_Y(IA,IGNOTETOH(IGH))$ICA(C,IA), GOMVCOST(IA,IGNOTETOH) * SUM((S,T), IHOURSINST(S,T)*GDATA(IGNOTETOH,'GDCV')*(VGH_T.l(IA,IGNOTETOH,S,T))))
                                  + SUM(IAGKN(IA,IGE)$ICA(C,IA), GOMVCOST(IA,IGE) * SUM((S,T), IHOURSINST(S,T)*VGEN_T.l(IA,IGE,S,T)))
                                  + SUM(IAGKN(IA,IGNOTETOH(IGH))$ICA(C,IA), GOMVCOST(IA,IGNOTETOH) * SUM((S,T), IHOURSINST(S,T)*GDATA(IGNOTETOH,'GDCV')*(VGHN_T.l(IA,IGNOTETOH,S,T))))
                                       )/IOF1000000;

*Erkki UC welfare

         UCstartcost(Y,C)        =eps
$ifi %UnitComm%==yes             + OMONEY*(
$ifi %UnitComm%==yes               SUM(IAGK_Y(IA,IGUC)$ICA(C,IA),GDATA(IGUC,'GDUCUCOST')*GDATA(IGUC,'GDUCUNITSIZE')*SUM((S,T),VUCU.L(IA,IGUC,S,T)
$ifi %UnitComm%==yes             + VUCUN.L(IA,IGUC,S,T))))
$ifi %UnitComm%==yes                  /IOF1000000
                                 ;

         UCshutcost(Y,C)         =eps
$ifi %UnitComm%==yes             + OMONEY*(
$ifi %UnitComm%==yes              SUM(IAGK_Y(IA,IGUC)$ICA(C,IA),GDATA(IGUC,'GDUCDCOST')*GDATA(IGUC,'GDUCUNITSIZE')*SUM((S,T),VUCD.L(IA,IGUC,S,T)
$ifi %UnitComm%==yes             + VUCDN.L(IA,IGUC,S,T))))
$ifi %UnitComm%==yes                /IOF1000000
                                  ;


         UCfixedcost(Y,C)         =eps
$ifi %UnitComm%==yes              + OMONEY*(
$ifi %UnitComm%==yes               SUM(IAGK_Y(IA,IGUC)$ICA(C,IA),GDATA(IGUC,'GDUCCOST0')*GDATA(IGUC,'GDUCUNITSIZE')*SUM((S,T),VUCON.L(IA,IGUC,S,T)
$ifi %UnitComm%==yes              + VUCONN.L(IA,IGUC,S,T))))
$ifi %UnitComm%==yes                 /IOF1000000
                                   ;
*Erkki


         capcost_ex(Y,C)     =eps+ OMONEY*IOF1000000*(SUM(IAGK_Y(IA,G)$ICA(C,IA),(IGKFX_Y(IA,G))*GINVCOST(IA,G)))/IOF1000000;
         capcost_en(Y,C)     =eps+ ( OMONEY*IOF1000000*(SUM(IAGKN(IA,G)$ICA(C,IA), VGKN.l(IA,G)*GINVCOST(IA,G)))
                                    +OMONEY*IOF1000000*(SUM(IAGK_Y(IA,G)$ICA(C,IA),(IGKVACCTOY(IA,G))*GINVCOST(IA,G)))
                                    )/IOF1000000;
* LARS20070829: Still no capital costs on exogenous transmission capacity.
         capcost_trans_ex(Y,C) =eps+ OMONEY*(  0 )/IOF1000000;
         capcost_trans_en(Y,C) =eps+ OMONEY*(  SUM(IRE$CCCRRR(C,IRE), SUM(IRI$(IXKN(IRI,IRE) OR IXKN(IRE,IRI)), VXKN.l(IRE,IRI)*XINVCOST(IRE,IRI)*IOF05))
                                              +SUM(IRI$CCCRRR(C,IRI), SUM(IRE$(IXKN(IRI,IRE) OR IXKN(IRE,IRI)), VXKN.l(IRE,IRI)*XINVCOST(IRE,IRI)*IOF05))
                                                 )/IOF1000000;

         co2cost(Y,C)        =eps+ OMONEY*ITAX_CO2_Y(C)*SUM((IA,G,S,T)$(ICA(C,IA) and (IAGKN(IA,G) or IAGK_Y(IA,G))), IHOURSINST(S,T) * (IM_CO2(G)/1000) * IOF3P6 *
                                 (VGF_T.l(IA,G,S,T)$IAGK_Y(IA,G)+VGFN_T.l(IA,G,S,T)$IAGKN(IA,G)))/IOF1000000                     ;

         so2cost(Y,C)        =eps+ OMONEY*ITAX_SO2_Y(C)*SUM((IA,G,S,T)$(ICA(C,IA) and (IAGKN(IA,G) or IAGK_Y(IA,G))), IHOURSINST(S,T) * (IM_SO2(G)/1000) * IOF3P6 *
                                 (VGF_T.l(IA,G,S,T)$IAGK_Y(IA,G)+VGFN_T.l(IA,G,S,T)$IAGKN(IA,G)))/IOF1000000                     ;

         noxcost(Y,C)        =eps+ OMONEY*ITAX_NOX_Y(C)*SUM((IA,G,S,T)$(ICA(C,IA) and (IAGKN(IA,G) or IAGK_Y(IA,G))), IHOURSINST(S,T) * (GDATA(G,'GDNOX')/1000000)*IOF3P6*
                                 (VGF_T.l(IA,G,S,T)$IAGK_Y(IA,G)+VGFN_T.l(IA,G,S,T)$IAGKN(IA,G)))/IOF1000000                ;

         fueltax(Y,C)        =eps+     OMONEY*(
                                     SUM((FFF,S,T), SUM(IAGK_Y(IA,G)$((GDATA(G,'GDFUEL') EQ FDATA(FFF,'FDNB'))  AND ICA(C,IA)),
                                       IHOURSINST(S,T) * (TAX_F(FFF,C)+ITAX_GF(IA,G)) * IOF3P6 *VGF_T.l(IA,G,S,T)))
                                   + SUM((FFF,S,T), SUM(IAGKN(IA,G)$((GDATA(G,'GDFUEL') EQ FDATA(FFF,'FDNB')) AND ICA(C,IA)),
                                       IHOURSINST(S,T) * (TAX_F(FFF,C)+ITAX_GF(IA,G)) * IOF3P6 *VGFN_T.l(IA,G,S,T)))
                                         )/IOF1000000;

         heattax_GH(Y,C) =eps+ OMONEY*(   + SUM((IA,IGH,S,T)$(IAGK_Y(IA,IGH) and ITAX_GH(IA,IGH) AND ICA(C,IA)),
                                                 ITAX_GH(IA,IGH)*IOF3P6*VGH_T.l(IA,IGH,S,T)*IHOURSINST(S,T))
                                            + SUM((IA,IGH,S,T)$(IAGKN(IA,IGH) and ITAX_GH(IA,IGH) AND ICA(C,IA)),
                                                 ITAX_GH(IA,IGH)*IOF3P6*VGHN_T.l(IA,IGH,S,T)*IHOURSINST(S,T))
                                )/IOF1000000;


         vindSubsidy(Y,C) =eps
$ifi %WINDTARGET%==yes         + OMONEY*QWNDTARGET.m(C)*IOF1000000*SUM((IA,IGWND,S,T)$ICA(C,IA),
$ifi %WINDTARGET%==yes                                                                 ( VGE_T.l(IA,IGWND,S,T)$IAGK_Y(IA,IGWND)
$ifi %WINDTARGET%==yes                                                                  +VGEN_T.l(IA,IGWND,S,T)$IAGKN(IA,IGWND))*IHOURSINST(S,T)
$ifi %WINDTARGET%==yes                                                                 )/IOF1000000
                                 ;

         e_cost(Y,C)         =eps+ OMONEY*SUM((IR,S,T)$CCCRRR(C,IR),   IOF1000000*QEEQ.m(IR,S,T)*(   (IDE_T_Y(IR,S,T)
                                                  + SUM(DEF_U1,VDEF_T.l(IR,S,T,DEF_U1) )
                                                  - SUM(DEF_D1,VDEF_T.l(IR,S,T,DEF_D1) )
                                                  + SUM(DEF_U2,VDEF_T.l(IR,S,T,DEF_U2) )
                                                  - SUM(DEF_D2,VDEF_T.l(IR,S,T,DEF_D2) )
                                                  + SUM(DEF_U3,VDEF_T.l(IR,S,T,DEF_U3) )
                                                  - SUM(DEF_D3,VDEF_T.l(IR,S,T,DEF_D3) )
                                                                                       )/(1-DISLOSS_E(IR)))
                                                                                  )/IOF1000000;

         h_cost(Y,C)         =eps+ OMONEY*Sum((IA,S,T)$(IDH_SUMST(IA) NE 0 and ICA(C,IA)),
                                         IOF1000000*QHEQ.m(IA,S,T)*(
                                                  (IDH_T_Y(IA,S,T)
                                                        + SUM(DHF_U1,VDHF_T.l(IA,S,T,DHF_U1) )
                                                        - SUM(DHF_D1,VDHF_T.l(IA,S,T,DHF_D1) )
                                                        + SUM(DHF_U2,VDHF_T.l(IA,S,T,DHF_U2) )
                                                        - SUM(DHF_D2,VDHF_T.l(IA,S,T,DHF_D2) )
                                                        + SUM(DHF_U3,VDHF_T.l(IA,S,T,DHF_U3) )
                                                        - SUM(DHF_D3,VDHF_T.l(IA,S,T,DHF_D3) )
                                                  )/(1-DISLOSS_H(IA))
                                                                      )
                                         )/IOF1000000;


         e_util(Y,C)         =eps+OMONEY*(
                                      - SUM(IR$CCCRRR(C,IR),
                                             SUM((S,T), IHOURSINST(S,T)*
                                               (SUM(DEF_D1, VDEF_T.l(IR,S,T,DEF_D1)* (IDEFP_T(IR,S,T,DEF_D1)+TAX_DE(C)+DISCOST_E(IR))  )
                                              +  SUM(DEF_D2, VDEF_T.l(IR,S,T,DEF_D2)* (IDEFP_T(IR,S,T,DEF_D2)+TAX_DE(C)+DISCOST_E(IR))  )
                                              +  SUM(DEF_D3, VDEF_T.l(IR,S,T,DEF_D3)* (IDEFP_T(IR,S,T,DEF_D3)+TAX_DE(C)+DISCOST_E(IR))  )
                                                )
                                                )

                                            +SUM((S,T), IHOURSINST(S,T)*
                                               (SUM(DEF_U1, VDEF_T.l(IR,S,T,DEF_U1)* (IDEFP_T(IR,S,T,DEF_U1)+TAX_DE(C)+DISCOST_E(IR))  )
                                               + SUM(DEF_U2, VDEF_T.l(IR,S,T,DEF_U2)* (IDEFP_T(IR,S,T,DEF_U2)+TAX_DE(C)+DISCOST_E(IR))  )
                                               + SUM(DEF_U3, VDEF_T.l(IR,S,T,DEF_U3)* (IDEFP_T(IR,S,T,DEF_U3)+TAX_DE(C)+DISCOST_E(IR)) )
                                                )
                                                )
                                        ))/IOF1000000;

         h_util(Y,C)         =eps+OMONEY*(
                                    - SUM(IA$ICA(C,IA),
                                      SUM((S,T), IHOURSINST(S,T)
                                      * SUM(DHF_D1, VDHF_T.l(IA,S,T,DHF_D1)* (IDHFP_T(IA,S,T,DHF_D1)+TAX_DH(C) ) )))

                                    + SUM(IA$ICA(C,IA),
                                      SUM((S,T), IHOURSINST(S,T)
                                      * SUM(DHF_U1, VDHF_T.l(IA,S,T,DHF_U1)* (IDHFP_T(IA,S,T,DHF_U1)+TAX_DH(C) ) )))
                                        )/IOF1000000;


         bottleneck(Y,C)     =eps+  OMONEY*(
                                         Sum((S,T),
*                                Udgående strøm
                                          Sum(irrre$(CCCRRR(C,IRRRe) and ire(irrre)),
                                                   Sum(irrri$(iri(irrri) and  (not sameas(irrre,irrri)) and ((VXKN.l(IRRRE,IRRRI) > 0) or (IXKINI_Y(IRRRE,IRRRI) > 0 ))),
                                                          IOF1000000*(qeeq.m(IRRRi,S,T)*vx_t.l(irRRe,irRRi,S,t)*(1-XLOSS(IRRRE,IRRRI)) - qeeq.m(IRRRe,S,T)*vx_t.l(irRRe,irRRi,S,t))))/2
*                                Indgående strøm
                                         +Sum(irrri$(CCCRRR(C,IRRRi) and iri(irrri)),
                                                   Sum(irrre$(ire(irrre) and  (not sameas(irrre,irrri)) and ((VXKN.l(IRRRE,IRRRI) > 0) or (IXKINI_Y(IRRRE,IRRRI) > 0 ))),
                                                          IOF1000000*(qeeq.m(IRRRi,S,T)*vx_t.l(irRRe,irRRi,S,t)*(1-XLOSS(IRRRE,IRRRI)) - qeeq.m(IRRRe,S,T)*vx_t.l(irRRe,irRRi,S,t))))/2
                                                 )
                                         )/IOF1000000;

         tradesurp(Y,C)      =eps+  OMONEY*SUM((IR,S,T)$CCCRRR(C,IR), IOF1000000*QEEQ.m(IR,S,T)*(-IX3FX_T_Y(IR,S,T)))/IOF1000000;

         transcost(Y,C)      =eps+  OMONEY*(  SUM((IRE,IRI)$((IXKINI_Y(IRE,IRI) OR IXKN(IRE,IRI) OR IXKN(IRI,IRE)) and (CCCRRR(C,IRI) or CCCRRR(C,IRE))),
                                                 SUM((S,T), IHOURSINST(S,T) * (VX_T.l(IRE,IRI,S,T) * XCOST(IRE,IRI)))))/2/IOF1000000;



         watervaluevar(Y,C)  =eps+ OMONEY*(
                                            SUM(IAGK_Y(IA,IGHYRS)$ICA(C,IA), SUM((S,T), HYPPROFILS(IA,S)* IHOURSINST(S,T)*VGE_T.l(IA,IGHYRS,S,T)))
                                          + SUM(IAGKN(IA,IGHYRS)$ICA(C,IA), SUM((S,T), HYPPROFILS(IA,S)* IHOURSINST(S,T)*VGEN_T.l(IA,IGHYRS,S,T)))
                                        )/IOF1000000;

         watervalue(Y,C)     =eps
$ifi not %bb3%==yes $goto not_waterval_CP
$ifi not %WATERVAL%==yes $goto not_waterval_CP
                               +OMONEY*(
                                  SUM(IAGK_Y(IA,IGHYRS)$ICA(C,IA),SUM((S,T), IWATERVAL(IA,S)* IHOURSINST(S,T)*VGE_T.l(IA,IGHYRS,S,T)))
                                + SUM(IAGKN(IA,IGHYRS)$ICA(C,IA), SUM((S,T), IWATERVAL(IA,S)* IHOURSINST(S,T)*VGEN_T.l(IA,IGHYRS,S,T)))
                                )/IOF1000000
$label not_waterval_CP
                                ;

         NOxemission(Y,C)    =eps+ SUM((IA,G,S,T)$(ICA(C,IA) and (IAGKN(IA,G) or IAGK_Y(IA,G))), IHOURSINST(S,T) * (GDATA(G,'GDNOX')/1000000)*IOF3P6*
                                 (VGF_T.l(IA,G,S,T)$IAGK_Y(IA,G)+VGFN_T.l(IA,G,S,T)$IAGKN(IA,G)))/IOF1000000  ;
         SO2emission(Y,C)    =eps+ SUM((IA,G,S,T)$(ICA(C,IA) and (IAGKN(IA,G) or IAGK_Y(IA,G))), IHOURSINST(S,T) * (IM_SO2(G)/1000) * IOF3P6 *
                                 (VGF_T.l(IA,G,S,T)$IAGK_Y(IA,G)+VGFN_T.l(IA,G,S,T)$IAGKN(IA,G)))/IOF1000000  ;

$ifi %BB3%==yes CO2shadowval(Y,C)   =eps
$ifi not %BB3%==yes CO2shadowval(Y,C)$QLIMCO2.M(C)   =eps
$ifi not %BB3%==yes              + OMONEY*IOF1000000*
$ifi not %BB3%==yes                       (-QLIMCO2.M(C))*
$ifi not %BB3%==yes                        SUM((G,S,T), IHOURSINST(S,T) * (IM_CO2(G)/1000) * IOF3P6 *
$ifi not %BB3%==yes                          SUM(IA$ICA(C,IA),(VGE_T.L(IA,G,S,T) + VGEN_T.L(IA,G,S,T)
$ifi not %BB3%==yes                      + GDATA(G,'GDCV')*(VGH_T.L(IA,G,S,T) + VGHN_T.L(IA,G,S,T))) /
$ifi not %BB3%==yes                        (GDATA(G,'GDFE')* GEFFDERATE(IA,G))))/IOF1000000
                                 ;

         Fosshadowval(Y,C)=eps
$ifi %FOSSILTARGET%==yes    +OMONEY*IOF1000000*SUM(CCCFOSSIL$CCCFOSSILEC(CCCFOSSIL,C),
$ifi %FOSSILTARGET%==yes         QFOSSILTARGET.m(CCCFOSSIL)
$ifi %FOSSILTARGET%==yes         )*
$ifi %FOSSILTARGET%==yes    (
$ifi %FOSSILTARGET%==yes    + SUM((S,T), SUM(IAGK_Y(IA,IGE)$(IGFOSSIL(IGE) AND ICA(C,IA)),
$ifi %FOSSILTARGET%==yes      IHOURSINST(S,T) * IOF3P6 *
$ifi %FOSSILTARGET%==yes      (VGE_T.l(IA,IGE,S,T) / (GDATA(IGE,'GDFE') * GEFFDERATE(IA,IGE)))))
$ifi %FOSSILTARGET%==yes   + SUM((S,T), SUM(IAGK_Y(IA,IGH)$(IGFOSSIL(IGH) AND ICA(C,IA)),
$ifi %FOSSILTARGET%==yes      IHOURSINST(S,T) * IOF3P6 *
$ifi %FOSSILTARGET%==yes      GDATA(IGH,'GDCV')* VGH_T.l(IA,IGH,S,T)/(GDATA(IGH,'GDFE') * GEFFDERATE(IA,IGH))))
$ifi %FOSSILTARGET%==yes    + SUM((S,T), SUM(IAGKN(IA,IGE)$(IGFOSSIL(IGE) AND ICA(C,IA)),
$ifi %FOSSILTARGET%==yes      IHOURSINST(S,T) * IOF3P6 *
$ifi %FOSSILTARGET%==yes      (VGEN_T.l(IA,IGE,S,T) / (GDATA(IGE,'GDFE') * GEFFDERATE(IA,IGE)))))
$ifi %FOSSILTARGET%==yes   + SUM((S,T), SUM(IAGKN(IA,IGH)$(IGFOSSIL(IGH) AND ICA(C,IA)),
$ifi %FOSSILTARGET%==yes      IHOURSINST(S,T) * IOF3P6 *
$ifi %FOSSILTARGET%==yes      GDATA(IGH,'GDCV')*VGHN_T.l(IA,IGH,S,T)/(GDATA(IGH,'GDFE')*GEFFDERATE(IA,IGH))))
$ifi %FOSSILTARGET%==yes   )/IOF1000000
                 ;

         VEShadowval(Y,C)    =eps
$ifi %RENEWTARGET%==yes     +OMONEY*IOF1000000*SUM(CCCRESHAREE$CCCRESHAREEC(CCCRESHAREE,C),
$ifi %RENEWTARGET%==yes        QRENEW.m(CCCRESHAREE)
$ifi %RENEWTARGET%==yes        )*SUM((S,T), IHOURSINST(S,T) *
$ifi %RENEWTARGET%==yes        (SUM(IAGK_Y(IA,IGRENEW(IGE))$ICA(C,IA),
$ifi %RENEWTARGET%==yes                      VGE_T.l(IA,IGE,S,T)
$ifi %RENEWTARGET%==yes              )
$ifi %RENEWTARGET%==yes             +SUM(IAGKN(IA,IGRENEW(IGE))$ICA(C,IA),
$ifi %RENEWTARGET%==yes                      VGEN_T.l(IA,IGE,S,T)
$ifi %RENEWTARGET%==yes                      ))
$ifi %RENEWTARGET%==yes       )/IOF1000000
                         ;


*         e_tax(Y,C)          =eps+ OMONEY*TAX_DE(C)*SUM((IR,S,T)$CCCRRR(C,IR),  IHOURSINST(S,T)*
         e_tax(Y,C)          =eps+ OMONEY*SUM((IR,S,T)$CCCRRR(C,IR), TAX_DE(C) * IHOURSINST(S,T)*
                                         (IDE_T_Y(IR,S,T)
                                           + SUM(DEF_U1,VDEF_T.l(IR,S,T,DEF_U1) )
                                           - SUM(DEF_D1,VDEF_T.l(IR,S,T,DEF_D1) )
                                           + SUM(DEF_U2,VDEF_T.l(IR,S,T,DEF_U2) )
                                           - SUM(DEF_D2,VDEF_T.l(IR,S,T,DEF_D2) )
                                           + SUM(DEF_U3,VDEF_T.l(IR,S,T,DEF_U3) )
                                           - SUM(DEF_D3,VDEF_T.l(IR,S,T,DEF_D3) )
                                         )
                                 )/IOF1000000;

         h_tax(Y,C)          =eps+ OMONEY*TAX_DH(C)*SUM((IA,S,T)$ICA(C,IA),  IHOURSINST(S,T)*
                                         (IDH_T_Y(IA,S,T)
                                           + SUM(DHF_U1,VDHF_T.l(IA,S,T,DHF_U1) )
                                           - SUM(DHF_D1,VDHF_T.l(IA,S,T,DHF_D1) )
                                         )
                                 )/IOF1000000;


         dist_e(Y,C)         =eps+OMONEY*(
                                      - SUM(IR$CCCRRR(C,IR), DISCOST_E(IR)*
                                             SUM((S,T), IHOURSINST(S,T)
                                              * (SUM(DEF_D1, VDEF_T.l(IR,S,T,DEF_D1)  )
                                              +  SUM(DEF_D2, VDEF_T.l(IR,S,T,DEF_D2)  )
                                              +  SUM(DEF_D3, VDEF_T.l(IR,S,T,DEF_D3)  )
                                                )
                                                )
                                            )
                                      + SUM(IR$CCCRRR(C,IR),DISCOST_E(IR)*
                                             SUM((S,T), IHOURSINST(S,T)*
                                               ( IDE_T_Y(IR,S,T)
                                               + SUM(DEF_U1, VDEF_T.l(IR,S,T,DEF_U1)  )
                                               + SUM(DEF_U2, VDEF_T.l(IR,S,T,DEF_U2)  )
                                               + SUM(DEF_U3, VDEF_T.l(IR,S,T,DEF_U3)  )
                                                )
                                                )
                                            )
                                        )/IOF1000000;

         dist_h(Y,C)         =eps+OMONEY*(
                                    - SUM(IA$ICA(C,IA), DISCOST_H(IA)*
                                      SUM((S,T), IHOURSINST(S,T)
                                      * SUM(DHF_D1, VDHF_T.l(IA,S,T,DHF_D1)  ))))

                                    + SUM(IA$ICA(C,IA), DISCOST_H(IA)*
                                      SUM((S,T), IHOURSINST(S,T)
                                      * (IDH_T_Y(IA,S,T)+SUM(DHF_U1, VDHF_T.l(IA,S,T,DHF_U1)  )))
                                        )/IOF1000000;
$ontext
         reacEf(Y,C)$BASELOADSERVICE(C) =eps
                         +OMONEY*IOF1000000*Sum((S,T), QBASELOAD.m(C,S,T)*IHOURSINST(S,T)*(
                               SUM(IAGK_Y(IA,IGE)$(ICA(C,IA) AND IGEBASE(IGE)), VGE_T.l(IA,IGE,S,T))
                             + SUM(IAGKN(IA,IGE)$(ICA(C,IA) AND IGEBASE(IGE)), VGEN_T.l(IA,IGE,S,T)))
                          )/IOF1000000
         ;
$offtext
*-------------------------------------------------------------------------------
* Add output for addon modules. It is best if addon code is in include files.
*-------------------------------------------------------------------------------

$ifi %H2%==yes $include '../../base/addons/Hydrogen/compare/hycompprint3.inc';
$ifi %transport%==yes $include '../../base/addons/transport/compare/trcompprint3.inc';

*Erkki- Calculation of welfare results in hourly resolution. Allows for analysis of when exactly the bulk of welfare is won/lost
$ifi not %hourlywelfare%==yes  $goto nothourlywelfare

hourlygenerationcost(Y,C,S,T)       =eps+ OMONEY*(

                                         SUM((IAGK_Y(IA,G),FFF)$(GDATA(G,'GDFUEL') EQ FDATA(FFF,'FDNB') and ICA(C,IA) and IGNOTETOH(G)),
                                           IFUELP_Y(IA,FFF) * IOF3P6 * IHOURSINST(S,T)*VGF_T.l(IA,G,S,T) )
                                        +SUM((IAGKN(IA,G),FFF)$(GDATA(G,'GDFUEL') EQ FDATA(FFF,'FDNB') and ICA(C,IA) and IGNOTETOH(G)),
                                           IFUELP_Y(IA,FFF) * IOF3P6 * IHOURSINST(S,T)*VGFN_T.l(IA,G,S,T) )

                                +SUM((IR)$CCCRRR(C,IR),
                                   IOF1000000*QEEQ.m(IR,S,T)*(
                                                        SUM(IAGK_Y(IA,IGE)$((RRRAAA(IR,IA)) AND IGETOH(IGE) and ICA(C,IA)), VGE_T.l(IA,IGE,S,T))
                                                      + SUM(IAGKN(IA,IGE)$((RRRAAA(IR,IA)) AND IGETOH(IGE) and ICA(C,IA)), VGEN_T.l(IA,IGE,S,T))
                                                         )
                                                         )
                                 )/IOF1000000

                             + OMONEY*(
                                    SUM(IAGK_Y(IA,IGE)$ICA(C,IA), GOMVCOST(IA,IGE) * IHOURSINST(S,T)*VGE_T.l(IA,IGE,S,T))
                                  + SUM(IAGK_Y(IA,IGNOTETOH(IGH))$ICA(C,IA), GOMVCOST(IA,IGNOTETOH) * IHOURSINST(S,T)*GDATA(IGNOTETOH,'GDCV')*(VGH_T.l(IA,IGNOTETOH,S,T)))
                                  + SUM(IAGKN(IA,IGE)$ICA(C,IA), GOMVCOST(IA,IGE) * IHOURSINST(S,T)*VGEN_T.l(IA,IGE,S,T))
                                  + SUM(IAGKN(IA,IGNOTETOH(IGH))$ICA(C,IA), GOMVCOST(IA,IGNOTETOH) * IHOURSINST(S,T)*GDATA(IGNOTETOH,'GDCV')*(VGHN_T.l(IA,IGNOTETOH,S,T)))
                                       )/IOF1000000

                             + OMONEY*ITAX_CO2_Y(C)*SUM((IA,G)$(ICA(C,IA) and (IAGKN(IA,G) or IAGK_Y(IA,G))), IHOURSINST(S,T) * (IM_CO2(G)/1000) * IOF3P6 *
                                 (VGF_T.l(IA,G,S,T)$IAGK_Y(IA,G)+VGFN_T.l(IA,G,S,T)$IAGKN(IA,G)))/IOF1000000

                             +     OMONEY*(
                                     SUM((FFF), SUM(IAGK_Y(IA,G)$((GDATA(G,'GDFUEL') EQ FDATA(FFF,'FDNB'))  AND ICA(C,IA)),
                                       IHOURSINST(S,T) * (TAX_F(FFF,C)+ITAX_GF(IA,G)) * IOF3P6 *VGF_T.l(IA,G,S,T)))
                                   + SUM((FFF), SUM(IAGKN(IA,G)$((GDATA(G,'GDFUEL') EQ FDATA(FFF,'FDNB')) AND ICA(C,IA)),
                                       IHOURSINST(S,T) * (TAX_F(FFF,C)+ITAX_GF(IA,G)) * IOF3P6 *VGFN_T.l(IA,G,S,T)))
                                         )/IOF1000000;

hourlye_rev(Y,C,S,T)       =eps+   OMONEY*SUM((IR)$CCCRRR(C,IR),
                                                     IOF1000000*QEEQ.m(IR,S,T)*(
                                                         SUM(IAGK_Y(IA,IGE)$((RRRAAA(IR,IA)) AND IGNOTETOH(IGE)), VGE_T.l(IA,IGE,S,T))
                                                       + SUM(IAGKN(IA,IGE)$((RRRAAA(IR,IA)) AND IGNOTETOH(IGE)), VGEN_T.l(IA,IGE,S,T))
                                                       - SUM(IA$(RRRAAA(IR,IA) AND sum(IGESTO,IAGK_Y(IA,IGESTO)+IAGKN(IA,IGESTO))),VESTOLOADT.l(IA,S,T))
                                                         )
                                                         )/IOF1000000;

hourlye_cost(Y,C,S,T)         =eps+ OMONEY*SUM((IR)$CCCRRR(C,IR),   IOF1000000*QEEQ.m(IR,S,T)*(   (IDE_T_Y(IR,S,T)
                                                  + SUM(DEF_U1,VDEF_T.l(IR,S,T,DEF_U1) )
                                                  - SUM(DEF_D1,VDEF_T.l(IR,S,T,DEF_D1) )
                                                  + SUM(DEF_U2,VDEF_T.l(IR,S,T,DEF_U2) )
                                                  - SUM(DEF_D2,VDEF_T.l(IR,S,T,DEF_D2) )
                                                  + SUM(DEF_U3,VDEF_T.l(IR,S,T,DEF_U3) )
                                                  - SUM(DEF_D3,VDEF_T.l(IR,S,T,DEF_D3) )
                                                                                       )/(1-DISLOSS_E(IR)))
                                                                                  )/IOF1000000;

hourlybottleneck(Y,C,S,T)     =eps+  OMONEY*(

*                                Udgående strøm
                                          Sum(irrre$(CCCRRR(C,IRRRe) and ire(irrre)),
                                                   Sum(irrri$(iri(irrri) and  (not sameas(irrre,irrri)) and ((VXKN.l(IRRRE,IRRRI) > 0) or (IXKINI_Y(IRRRE,IRRRI) > 0 ))),
                                                          IOF1000000*(qeeq.m(IRRRi,S,T)*vx_t.l(irRRe,irRRi,S,t)*(1-XLOSS(IRRRE,IRRRI)) - qeeq.m(IRRRe,S,T)*vx_t.l(irRRe,irRRi,S,t))))/2
*                                Indgående strøm
                                         +Sum(irrri$(CCCRRR(C,IRRRi) and iri(irrri)),
                                                   Sum(irrre$(ire(irrre) and  (not sameas(irrre,irrri)) and ((VXKN.l(IRRRE,IRRRI) > 0) or (IXKINI_Y(IRRRE,IRRRI) > 0 ))),
                                                          IOF1000000*(qeeq.m(IRRRi,S,T)*vx_t.l(irRRe,irRRi,S,t)*(1-XLOSS(IRRRE,IRRRI)) - qeeq.m(IRRRe,S,T)*vx_t.l(irRRe,irRRi,S,t))))/2

                                         )/IOF1000000;


$ifi %x3v%==yes hourlyX3V(Y,C,S,T)           =eps + OMONEY*sum((IR)$CCCRRR(C,IR),sum((X3VPLACE0,X3VSTEP0), IOF1000000*QEEQ.m(IR,S,T)*VX3VIM_T.l(IR,X3VPLACE0,X3VSTEP0,S,T)))

$ifi %x3v%==yes                                                                                /IOF1000000;


$label nothourlywelfare
*Erkki