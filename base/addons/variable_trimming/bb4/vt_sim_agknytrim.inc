
* To make sure all relevant technologies are taken into consideration IAGKNY is reassigned.
IAGKNY(IY411,IA,G)$(ITV_G(G) AND IAGKN(IA,G) AND (IY411.VAL LE GDATA(G,'GDLASTYEAR'))$GDATA(G,'GDLASTYEAR') AND (IY411.VAL GE GDATA(G,'GDFROMYEAR')) AND (IY411.VAL GE GINVESTSTART)) = YES;

* Possibility to unload variables for testing and comparison
*execute_unload "../output/temp/ITV_TEST_PRE.gdx", IAGKNY,  IAGK_HASORPOT, SYSTEMDATETIME ;

*------------------------------------------------------------------------------------
* Loop trough all the years in the balbase4 model (goes through most of the file)
*-------------------------------------------------------------------------------------
LOOP(IY411,

* TV_IY411 is the remaining years of the balbase4 model within the IY411-loop.
ITV_IY411(Y) = NO;
ITV_IY411(IY411ALIAS) = YES$((IY411.val LE IY411ALIAS.val) );

* Technologies considered: investment opportunities for the current year in IY411 loop that is also in the TV_G subset.
IAGKNY_IY411(Y,IA,G) = NO;
IAGKNY_IY411(ITV_IY411,IA,G) = YES$(IAGKNY(IY411,IA,G) AND ITV_G(G));                    !! AND SUM(C$ICA(C,IA), IINVYEARG_LEFT(C,IY411,ITV_IY411,G)) Check if latest. it might be relevant for loong investment horizons

* For testing and debugging only, ITVCOMPARED shows which technologies are compared in each year
ITVCOMPARED(IY411,ITV_IY411,IA,G) =  IAGKNY_IY411(ITV_IY411,IA,G);

* Unassign technologies affected by zero-emission limits
IAGKNY_IY411(ITV_IY411,IA,G)$(ITV_ZERO(ITV_IY411,IA,G) OR ITV_ZEROEL(ITV_IY411,IA,G)) = NO;


*-------------------------------------------------
* Calculating and using the screening curves
*-------------------------------------------------

** Calculating annual costs of serving Heat (H) or Electricity (E) under different assumptions for full load hours, full load hours for heat generation and value of "by-product" (heat when considering el-production and visa versa)
* Extraction plants
ITV_ANNUALCOST_H(Y,IA,G,TV_FLH,TV_FLHHEAT,TV_PR)$(IGEXT(G) AND ITV_HEATA(Y,IA) AND IAGKNY_IY411(Y,IA,G) AND ITV_FILTER(Y,IA,TV_FLH,TV_FLHHEAT,TV_PR)) =
         ITV_FIXED(Y,IA,G) * GDATA(G,'GDCB') + ITV_VARHEAT(Y,IA,G) * TV_FLHHEAT.VAL + ITV_VAREL(Y,IA,G) * TV_FLH.VAL*GDATA(G,'GDCB')                !! costs per MW installed heat capacity
         - TV_PR.VAL/100 * SUM(IR$RRRAAA(IR,IA), ITV_CHEAPESTCNDR(Y,IR,TV_FLH)) * GDATA(G,'GDCB') ;                                                 !! value of byproduct: electricity

ITV_ANNUALCOST_E(Y,IA,G,TV_FLH,TV_FLHHEAT,TV_PR)$(IGEXT(G) AND IAGKNY_IY411(Y,IA,G) AND ITV_FILTER(Y,IA,TV_FLH,TV_FLHHEAT,TV_PR)) =
         ITV_FIXED(Y,IA,G) + ITV_VAREL(Y,IA,G) * TV_FLH.VAL + ITV_VARHEAT(Y,IA,G) * TV_FLHHEAT.VAL / GDATA(G,'GDCB')                                !! costs per MW installed electricity capacity
         - TV_PR.VAL/100 * MIN(1000000, ITV_CHEAPESTHOB(Y,IA,TV_FLHHEAT)) / GDATA(G,'GDCB')  ;                                                     !! value of byproduct: heat


* Back pressure plants
ITV_ANNUALCOST_H(Y,IA,G,TV_FLH,TV_FLHHEAT,TV_PR)$(IGBPR(G) AND ITV_HEATA(Y,IA) AND IAGKNY_IY411(Y,IA,G) AND ITV_FILTER(Y,IA,TV_FLH,TV_FLHHEAT,TV_PR))  =
         ITV_FIXED(Y,IA,G) * GDATA(G,'GDCB') + ITV_VARHEAT(Y,IA,G) * TV_FLH.VAL + ITV_VAREL(Y,IA,G) * TV_FLH.VAL*GDATA(G,'GDCB')
         - TV_PR.VAL/100 * SUM(IR$RRRAAA(IR,IA),ITV_CHEAPESTCNDR(Y,IR,TV_FLH)) * GDATA(G,'GDCB') ;                                       !! for BPR Costs are dependent on TV_FLH only as heat and electricity FLH must be the same
*                                                   MIN(1000000,               )
ITV_ANNUALCOST_E(Y,IA,G,TV_FLH,TV_FLHHEAT,TV_PR)$(IGBPR(G) AND IAGKNY_IY411(Y,IA,G) AND ITV_FILTER(Y,IA,TV_FLH,TV_FLHHEAT,TV_PR))  =
         ITV_FIXED(Y,IA,G) + ITV_VAREL(Y,IA,G) * TV_FLH.VAL + ITV_VARHEAT(Y,IA,G) * TV_FLH.VAL / GDATA(G,'GDCB')
         - TV_PR.VAL/100 * MIN(1000000, ITV_CHEAPESTHOB(Y,IA,TV_FLHHEAT)) / GDATA(G,'GDCB')  ;                                                             !! MIN(1000000 if no limitless CND or HOB option in area.


* Bypass elecitricy plants                                                                       !! this overwrites whats calculated for back pressure plants, but only when FLHHEAT GE than FLH
ITV_ANNUALCOST_H(Y,IA,G,TV_FLH,TV_FLHHEAT,TV_PR)$(IGBYPASS(G) AND ITV_HEATA(Y,IA) AND IAGKNY_IY411(Y,IA,G) AND ITV_FILTER(Y,IA,TV_FLH,TV_FLHHEAT,TV_PR) AND (TV_FLH.VAL LE TV_FLHHEAT.VAL))  =
         ITV_FIXED(Y,IA,G) * GDATA(G,'GDCB') + ITV_VARHEAT(Y,IA,G) * TV_FLHHEAT.VAL + ITV_VAREL(Y,IA,G) * TV_FLH.VAL*GDATA(G,'GDCB')
         - TV_PR.VAL/100 * SUM(IR$RRRAAA(IR,IA), ITV_CHEAPESTCNDR(Y,IR,TV_FLH)) * GDATA(G,'GDCB') ;

ITV_ANNUALCOST_E(Y,IA,G,TV_FLH,TV_FLHHEAT,TV_PR)$(IGBPR(G) AND IAGKNY_IY411(Y,IA,G) AND ITV_FILTER(Y,IA,TV_FLH,TV_FLHHEAT,TV_PR) AND (TV_FLH.VAL LE TV_FLHHEAT.VAL))  =
         ITV_FIXED(Y,IA,G) + ITV_VAREL(Y,IA,G) * TV_FLH.VAL + ITV_VARHEAT(Y,IA,G) * TV_FLHHEAT.VAL / GDATA(G,'GDCB')
         - TV_PR.VAL/100 * MIN(1000000, ITV_CHEAPESTHOB(Y,IA,TV_FLHHEAT)) / GDATA(G,'GDCB')  ;


* Condencing / HOB plants
ITV_ANNUALCOST_H(Y,IA,G,TV_FLH,TV_FLHHEAT,TV_PR)$(IGHOB(G) AND ITV_HEATA(Y,IA) AND IAGKNY_IY411(Y,IA,G) AND ITV_FILTER(Y,IA,TV_FLH,TV_FLHHEAT,TV_PR))  =
         ITV_FIXED(Y,IA,G) + ITV_VARHEAT(Y,IA,G) * TV_FLHHEAT.VAL ;

ITV_ANNUALCOST_E(Y,IA,G,TV_FLH,TV_FLHHEAT,TV_PR)$(IGCND(G) AND IAGKNY_IY411(Y,IA,G) AND ITV_FILTER(Y,IA,TV_FLH,TV_FLHHEAT,TV_PR))  =
         ITV_FIXED(Y,IA,G) + ITV_VAREL(Y,IA,G) * TV_FLH.VAL;

* Power to heat plants (bring in when having control over grid tariffs)
*ITV_ANNUALCOST_H(Y,IA,G,TV_FLH,TV_FLHHEAT,TV_PR)$(IGETOH(G) AND IAGKNY_IY411(Y,IA,G) ) = ITV_FIXED(Y,IA,G) + ITV_VARHEAT(Y,IA,G) * TV_FLHHEAT.VAL + TV_PR.VAL/100 * SUM(IR$RRRAAA(IR,IA), ITV_CHEAPESTCNDR(Y,IR,TV_FLHHEAT))/GDATA(G,'GDFE');



** Calulating the cost of the cheapest plants
* when not considering plants affected by max and eq fuel restrictions
ITV_CHEAPEST_E(Y,IA,TV_FLH,TV_FLHHEAT,TV_PR)$(SUM(G, IAGKNY_IY411(Y,IA,G)) AND ITV_FILTER(Y,IA,TV_FLH,TV_FLHHEAT,TV_PR)) =
                 SMIN(G$(IGE(G) AND IAGKNY_IY411(Y,IA,G) AND NOT ITV_REQEMAX(Y,IA,G) AND NOT ITV_REQMAX(Y,IA,G) AND NOT ITV_REQFX(Y,IA,G)),
                         ITV_ANNUALCOST_E(Y,IA,G,TV_FLH,TV_FLHHEAT,TV_PR));
ITV_CHEAPEST_H(Y,IA,TV_FLH,TV_FLHHEAT,TV_PR)$(ITV_HEATA(Y,IA) AND SUM(G, IAGKNY_IY411(Y,IA,G)) AND ITV_FILTER(Y,IA,TV_FLH,TV_FLHHEAT,TV_PR)) =
                 SMIN(G$(IGH(G) AND IAGKNY_IY411(Y,IA,G) AND NOT ITV_REQEMAX(Y,IA,G) AND NOT ITV_REQMAX(Y,IA,G) AND NOT ITV_REQFX(Y,IA,G)),
                         ITV_ANNUALCOST_H(Y,IA,G,TV_FLH,TV_FLHHEAT,TV_PR));

* when considering plants affected by max and eq fuel restrictions
ITV_CHEAPEST_EF(Y,IA,TV_FLH,TV_FLHHEAT,TV_PR)$(SUM(G, IAGKNY_IY411(Y,IA,G)) AND ITV_FILTER(Y,IA,TV_FLH,TV_FLHHEAT,TV_PR))=
                 SMIN(G$(IGE(G) AND IAGKNY_IY411(Y,IA,G)), ITV_ANNUALCOST_E(Y,IA,G,TV_FLH,TV_FLHHEAT,TV_PR));
ITV_CHEAPEST_HF(Y,IA,TV_FLH,TV_FLHHEAT,TV_PR)$(ITV_HEATA(Y,IA) AND SUM(G, IAGKNY_IY411(Y,IA,G)) AND ITV_FILTER(Y,IA,TV_FLH,TV_FLHHEAT,TV_PR)) =
                 SMIN(G$(IGH(G) AND IAGKNY_IY411(Y,IA,G)), ITV_ANNUALCOST_H(Y,IA,G,TV_FLH,TV_FLHHEAT,TV_PR));


** Identifying the cheapest plant
* when not considering plants affected by max and eq fuel restrictions
ITV_CHEAPEST(Y,IA,G,TV_FLH,TV_FLHHEAT,TV_PR)$(IGE(G) AND IAGKNY_IY411(Y,IA,G) AND ITV_FILTER(Y,IA,TV_FLH,TV_FLHHEAT,TV_PR)
                 AND (ITV_ANNUALCOST_E(Y,IA,G,TV_FLH,TV_FLHHEAT,TV_PR) = ITV_CHEAPEST_E(Y,IA,TV_FLH,TV_FLHHEAT,TV_PR)) ) = YES;
ITV_CHEAPEST(Y,IA,G,TV_FLH,TV_FLHHEAT,TV_PR)$(IGH(G) AND ITV_HEATA(Y,IA) AND IAGKNY_IY411(Y,IA,G) AND ITV_FILTER(Y,IA,TV_FLH,TV_FLHHEAT,TV_PR)
                 AND (ITV_ANNUALCOST_H(Y,IA,G,TV_FLH,TV_FLHHEAT,TV_PR) = ITV_CHEAPEST_H(Y,IA,TV_FLH,TV_FLHHEAT,TV_PR)) ) = YES;

* when considering plants affected by max and eq fuel restrictions
ITV_CHEAPEST(Y,IA,G,TV_FLH,TV_FLHHEAT,TV_PR)$(IGE(G) AND IAGKNY_IY411(Y,IA,G) AND ITV_FILTER(Y,IA,TV_FLH,TV_FLHHEAT,TV_PR)
                 AND (ITV_ANNUALCOST_E(Y,IA,G,TV_FLH,TV_FLHHEAT,TV_PR) = ITV_CHEAPEST_EF(Y,IA,TV_FLH,TV_FLHHEAT,TV_PR)) ) = YES;
ITV_CHEAPEST(Y,IA,G,TV_FLH,TV_FLHHEAT,TV_PR)$(IGH(G) AND ITV_HEATA(Y,IA) AND IAGKNY_IY411(Y,IA,G) AND ITV_FILTER(Y,IA,TV_FLH,TV_FLHHEAT,TV_PR)
                 AND (ITV_ANNUALCOST_H(Y,IA,G,TV_FLH,TV_FLHHEAT,TV_PR) = ITV_CHEAPEST_HF(Y,IA,TV_FLH,TV_FLHHEAT,TV_PR)) ) = YES;


** identifying the plants that are not the cheapest option in any of the cases considered
ITV_NEVERCHEAP(IY411,IA,G)$(IAGKNY_IY411(IY411,IA,G) AND NOT SUM((Y,TV_FLH,TV_FLHHEAT,TV_PR)$IAGKNY_IY411(Y,IA,G), ITV_CHEAPEST(Y,IA,G,TV_FLH,TV_FLHHEAT,TV_PR))) = YES;


); !! END LOOP IY411

*-------------------------------------------------
* Changes to IAGKNY and IAGK_HASORPOT
*-------------------------------------------------

ITV_NEVERCHEAP2(IY411,IA,G) = ITV_NEVERCHEAP(IY411,IA,G);

* Technologies with fx or minimum fuel use requirments are NOT removed from IAGKNY:
ITV_NEVERCHEAP2(IY411,IA,G)$(ITV_REQEMIN(IY411,IA,G) OR ITV_REQMIN(IY411,IA,G) OR ITV_REQFX(IY411,IA,G)) = NO;

* Technologies with zero emission constraints are removed from IAGKNY:
ITV_NEVERCHEAP2(IY411,IA,G)$(IAGKNY(IY411,IA,G) AND (ITV_ZERO(IY411,IA,G) OR ITV_ZEROEL(IY411,IA,G))) = YES;


* Remove technologies from IAGKNY
IAGKNY(IY411,IA,G)$ITV_NEVERCHEAP2(IY411,IA,G) = NO;

*Reinitialize IAGK_HASORPOT
IAGK_HASORPOT(Y,IA,G) = YES$(GKFX(Y,IA,G) or IAGKNY(Y,IA,G));

*
IAGK_NOINVEST(IY411,IA,G)$IYFIRST(IY411) = 0;

** same loop as in balmorelbb4.sim to make sure that if you invest in a technology in the year Y, you can use it until it is decommissioned, even if you do not allow for investments on this technology in the future  :
LOOP(Y$(ORD(Y) NE CARD(Y)),  LOOP(IA,  LOOP(G$(IAGKNY(Y,IA,G) AND NOT IAGK_NOINVEST(Y,IA,G)),
                                        LOOP(IYALIAS2$((ORD(IYALIAS2) GT ORD(Y)) AND ((YVALUE(Y)+GDATA(G,'GDLIFETIME')) GT (YVALUE(IYALIAS2)))),
                                                                    IAGK_HASORPOT(IYALIAS2,IA,G)= IAGK_HASORPOT(IYALIAS2,IA,G)+IAGKNY(Y,IA,G);
                                        ););););





* Possibility to print some of the values for testing and debugging
*execute_unload "../output/temp/ITV_TEST_POST.gdx", ITV_IY411, ITV_fixed, ITV_varel, ITV_varheat, ITV_REQMIN, ITV_REQEMIN, ITV_REQMAX, ITV_REQEMAX, ITV_REQFX, ITV_ZERO, ITV_CHEAPESTHOB, ITV_CHEAPESTCND, ITV_CHEAPESTCNDR,   ITV_NEVERCHEAP2,IAGKNY,
* IY411, ITVCOMPARED, ITV_NEVERCHEAP,IAGKNY_IY411, ITV_CHEAPEST, IAGK_HASORPOT, ITV_CHEAPEST_H, ITV_CHEAPEST_E, ITV_ANNUALCOST_E, ITV_ANNUALCOST_H, ITV_CHEAPEST_EF, ITV_CHEAPEST_HF, ITV_FILTER, SYSTEMDATETIME;

* Compare IAGK_HASORPOT and IAGKNY before and after
*execute        "gdxdiff  ../output/temp/ITV_TEST_PRE.gdx  ../output/temp/ITV_TEST_POST.gdx   ../output/temp/ITV_TEST_DIFF.gdx";
