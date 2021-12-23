EQUATIONS

*Plants with storage
QHYDROCAS_HYRSEEQ(YYY,AAA,GGG,SSS) 'Hydropower balance                    '                                                                     !! Balance of storage
QHYDROCAS_HYGEEQ(YYY,AAA,GGG,SSS) 'weekly generation balance'              !! Balance of production
QHYDROCAS_VGEDAYUP(YYY,AAA,GGG,SSS,DAY) 'daily generation balance'
QHYDROCAS_HYRSGMAX(YYY,AAA,GGG,SSS,TTT) 'Maximum hourly production level'                                                                         !! Endogenous lower limit to VGE_T     optional
QHYDROCAS_HYRSGMIN(YYY,AAA,GGG,SSS,TTT) 'Minimum hourly production level'                                                                         !! Endogenous upper limit to VGE_T     optional
QHYDROCAS_VGESUP(YYY,AAA,GGG,SSS) 'Maximum weekly generation level for endogenous invested hydropower'                                            !! Upper limit to VHYDROCAS_VGE_S     (also .up)
QHYDROCAS_VGESLO(YYY,AAA,GGG,SSS) 'Minimum weekly generation level for endogenous invested hydropower'                                            !! Upper limit to VHYDROCAS_VGE_S     (also .up)
QHYDROCAS_HYRSMINVOL(YYY,AAA,GGG,SSS) 'Minimum storage level of hydropower reservoirs, endogenous investments'                                    !! Lower limit to VHYDROCAS_RESLEVEL
QHYDROCAS_HYRSMAXVOL(YYY,AAA,GGG,SSS) 'Maximum storage level of hydropower reservoirs, endogenous investments'                                    !! Upper limit to VHYDROCAS_RESLEVEL

*Pumped storage
QHYDROCAS_HYRSMAXPUMP(YYY,AAA,GGG,SSS,TTT) 'Maximum level of pumping'                                                                             !! Upper limit to pumping   (also .up)

*HSEG
QHYDROCAS_HSEG(YYY,AAA,GGG,SSS,TTT) 'Hydropower production, relationship between VGE_T and HSEG'                                                  !! optional
QHYDROCAS_HSEGMAX(YYY,AAA,GGG,HSEG,SSS,TTT) 'Hydropower production must be assigned to segment'                                                   !! optional
;

** SET GKFX to maximum of production capacity per hour.
** Hydropower balance
QHYDROCAS_HYRSEEQ(IY411,IA,G,S)$(IAGK_HYDROPOWER(IA,G) AND IAGK_HASORPOT(IY411,IA,G) AND IS3(S))..
$ifi not %BBMODE%==BB3          (VHYDROCAS_RESLEVEL(IY411,IA,G,S++1) - VHYDROCAS_RESLEVEL(IY411,IA,G,S) )$HDATA(G,'HDRESERVOIR')                                                                                                                      !! reservoir change
$ifi %BBMODE%==BB3       P_RESCHANGE(IY411,IA,G,S)$HDATA(G,'HDRESERVOIR')
         + SUM(T,  IHYRST(S,T) * (VHYDROCAS_VGE_S(IY411,IA,G,S) + VHYDROCAS_SPILL_RES(IY411,IA,G,S)))                                                                                                                          !!Production  and Spill
         - SUM((T,IGALIAS)$(IAGK_HASORPOT(IY411,IA,IGALIAS) AND HYDROPOWER_TRANSFER(IA,IGALIAS,G)),
                 HYDROPOWER_TRANSFER(IA,IGALIAS,G) * IHYRST(S,T) * (VHYDROCAS_VGE_S(IY411,IA,IGALIAS,S) + VHYDROCAS_SPILL_RES(IY411,IA,IGALIAS,S)$IGPOWERPLANT(IGALIAS)))                                                    !!Inflow from upstream
         - SUM(T, IHYRST(S,T) * VHYDROCAS_PUMP_T(IY411,IA,G,S,T)* SUM(IGALIAS$HYDROPOWER_PUMPTRANSFER(IA,IGALIAS,G), HYDROPOWER_PUMPTRANSFER(IA,IGALIAS,G)+1))$IGPUMP(G)                                                       !!Pumped into reservoir,
         + SUM((T,IGALIAS)$(IAGK_HASORPOT(IY411,IA,IGALIAS) AND IGPUMP(IGALIAS) AND HYDROPOWER_PUMPTRANSFER(IA,G,IGALIAS)), HYDROPOWER_PUMPTRANSFER(IA,G,IGALIAS) * IHYRST(S,T) * VHYDROCAS_PUMP_T(IY411,IA,IGALIAS,S,T))      !!Pumped out of reservoir, efficiency handled in  qeeq.
         =E=
         (IHYINF_REG_S(IA,G,S)  + IHYINF_UNREG_S(IA,G,S)  )                                                                                                                                                                    !! inflow
         * ( GKFX(IY411,IA,G)$IAGKFX(IY411,IA,G)
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,G)$IGDECOMEXOPOT(IY411,IA,G)
         +VGKNACCUMNET(IY411,IA,G)$SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,G))
         )
         -  (0
$ifi %WY_RESCHANGE%==YES  + IRES_CHANGE(IY411,IA,G)
         *( GKFX(IY411,IA,G)$IAGKFX(IY411,IA,G)+VGKNACCUMNET(IY411,IA,G)$SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,G))                                                                  !! Reservoir change in weather year
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,G)$IGDECOMEXOPOT(IY411,IA,G)
         ))$(ORD(S) EQ CARD(S))

*+ VQHYDROCAS_HYRSEEQ(IY411,IA,G,S,'IMINUS')- VQHYDROCAS_HYRSEEQ(IY411,IA,G,S,'IPLUS')
;


** Limit to weekly generation
QHYDROCAS_HYGEEQ(IY411,IA,G,S)$(IAGK_HYDROPOWER(IA,G) AND IGPOWERPLANT(G) AND IAGK_HASORPOT(IY411,IA,G)  AND IS3(S))..
         SUM(T, VGE_T(IY411,IA,G,S,T) + VHYDROCAS_SPILL(IY411,IA,G,S,T)) / CARD(T)
         =E=
         VHYDROCAS_VGE_S(IY411,IA,G,S)
;


** Limit to daily generation
*  Maximum storage withdrawal from river storage power plants on daily basis
QHYDROCAS_VGEDAYUP(IY411,IA,G,S,IDAY)$(IAGK_HYDROPOWER(IA,G) AND IAGK_HASORPOT(IY411,IA,G) AND IGHYDISPATCH(G) AND IS3(S) AND IHD_RATES(IA,G,S))..    !!  AND IHD_RATES(IA,G,S) < GKRATE(IA,G,S))
         SUM(T$IDAYT(IDAY,T), VGE_T(IY411,IA,G,S,T) + VHYDROCAS_SPILL(IY411,IA,G,S,T)) / (CARD(T)/CARD(IDAY))
         =L=
         (IHD_RATES(IA,G,S) + IHYINF_UNREG_S(IA,G,S)/SUM(T, IHYRST(S,T))) * ( GKFX(IY411,IA,G)$IAGKFX(IY411,IA,G)+VGKNACCUMNET(IY411,IA,G)$SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,G))
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,G)$IGDECOMEXOPOT(IY411,IA,G)
                 )  ;


** Limits to hourly generation
* Minimum production level dependent on rate of fixed production     (Share of installed capacity or share of max reg + unreg?)
QHYDROCAS_HYRSGMIN(IY411,IA,G,S,T)$(IAGK_HYDROPOWER(IA,G) AND IGPOWERPLANT(G) AND IAGK_HASORPOT(IY411,IA,G) AND IS3(S))..
         VGE_T(IY411,IA,G,S,T)
         =G=
         HDATA(G,'HDFIXED') * VHYDROCAS_VGE_S(IY411,IA,G,S)
         - VHYDROCAS_SPILL(IY411,IA,G,S,T);

* Maximum production level dependent on rate of fixed production
QHYDROCAS_HYRSGMAX(IY411,IA,G,S,T)$(IAGK_HYDROPOWER(IA,G) AND IGPOWERPLANT(G) AND HDATA(G,'HDFIXED') AND IAGK_HASORPOT(IY411,IA,G) AND IS3(S))..
         VGE_T(IY411,IA,G,S,T)
         =L=
         HDATA(G,'HDFIXED') * VHYDROCAS_VGE_S(IY411,IA,G,S)                                                                          !! inflexible capacity
         + (1- HDATA(G,'HDFIXED')) *                                                                                                  !! flexible capacity
           ( GKFX(IY411,IA,G)$IAGKFX(IY411,IA,G)+VGKNACCUMNET(IY411,IA,G)$SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,G))
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,G)$IGDECOMEXOPOT(IY411,IA,G)
            )* (1$(NOT IGKRATE(IA,G,S,T)) + IGKRATE(IA,G,S,T))
;


** Limits to weekly generation for plants that can be invested in
* Maximum weekly production level less than hdrates + unreg inflow
QHYDROCAS_VGESUP(IY411,IA,G,S)$(IAGK_HYDROPOWER(IA,G) AND IGKFIND(G) AND IAGK_HASORPOT(IY411,IA,G) AND IS3(S))..
         VHYDROCAS_VGE_S(IY411,IA,G,S)
         =L=
         (IHD_RATES(IA,G,S) + IHYINF_UNREG_S(IA,G,S)/SUM(T, IHYRST(S,T))) * ( GKFX(IY411,IA,G)$IAGKFX(IY411,IA,G)+VGKNACCUMNET(IY411,IA,G)$SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,G))     !! Unreg has been put here.
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,G)$IGDECOMEXOPOT(IY411,IA,G)
         )  ;

* Maximum weekly production level must be higher than unregulated production
QHYDROCAS_VGESLO(IY411,IA,G,S)$(IAGK_HYDROPOWER(IA,G) AND IGKFIND(G) AND IAGK_HASORPOT(IY411,IA,G) AND IHYINF_UNREG_S(IA,G,S) AND IS3(S))..
         VHYDROCAS_VGE_S(IY411,IA,G,S)
         =G=
         IHYINF_UNREG_S(IA,G,S)/SUM(T, IHYRST(S,T))
         * ( GKFX(IY411,IA,G)$IAGKFX(IY411,IA,G)+VGKNACCUMNET(IY411,IA,G)$SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,G))  !! Unreg production
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,G)$IGDECOMEXOPOT(IY411,IA,G)
          )  ;



** Pumped storage
** Maximum level of pumping
QHYDROCAS_HYRSMAXPUMP(IY411,IA,G,S,T)$(IAGK_HYDROPOWER(IA,G) AND IGPUMP(G) AND IGKFIND(G) AND IAGK_HASORPOT(IY411,IA,G) AND IS3(S))..
         VHYDROCAS_PUMP_T(IY411,IA,G,S,T)
         =L=
         HDATA(G,'HDPUMPPOWER')
         *  ( GKFX(IY411,IA,G)$IAGKFX(IY411,IA,G)+VGKNACCUMNET(IY411,IA,G)$SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,G))
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,G)$IGDECOMEXOPOT(IY411,IA,G)
          )  ;


** Reservoir limits for plants that can be invested in
* Minimum storage level of hydropower reservoirs
QHYDROCAS_HYRSMINVOL(IY411,IA,G,S)$(IAGK_HYDROPOWER(IA,G) AND HDATA(G,'HDRESERVOIR') AND IGKFIND(G) AND IAGK_HASORPOT(IY411,IA,G) AND IS3(S))..
         VHYDROCAS_RESLEVEL(IY411,IA,G,S)
         =G=
         HMINLEVELS(G,S) * HDATA(G,'HDRESERVOIR')
         * ( GKFX(IY411,IA,G)$IAGKFX(IY411,IA,G)+VGKNACCUMNET(IY411,IA,G)$SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,G))
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,G)$IGDECOMEXOPOT(IY411,IA,G)
          )   ;

* Maximum storage level of hydropower reservoirs
QHYDROCAS_HYRSMAXVOL(IY411,IA,G,S)$(IAGK_HYDROPOWER(IA,G) AND HDATA(G,'HDRESERVOIR') AND IGKFIND(G) AND IAGK_HASORPOT(IY411,IA,G) AND IS3(S))..
         VHYDROCAS_RESLEVEL(IY411,IA,G,S)
         =L=
         HDATA(G,'HDRESERVOIR')
         * ( GKFX(IY411,IA,G)$IAGKFX(IY411,IA,G)+VGKNACCUMNET(IY411,IA,G)$SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,G))
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,G)$IGDECOMEXOPOT(IY411,IA,G)
          )  ;


** HSEG **    Stepwise marginal cost increase for high production rates. Reflects e.g. lower efficiencies at high utilization.
* Hydropower production, relationship between VGE_T and HSEG
QHYDROCAS_HSEG(IY411,IA,G,S,T)$(IAGK_HYDROPOWER(IA,G) AND IGHYDISPATCH(G) AND IAGK_HASORPOT(IY411,IA,G) AND IS3(S) AND NOT IHIGHUNREGSEASONS(IA,G,S))..
         VGE_T(IY411,IA,G,S,T)
         -  IHYINF_UNREG_S(IA,G,S) / IHYRST(S,T)/CARD(T)    * ( GKFX(IY411,IA,G)$IAGKFX(IY411,IA,G)+VGKNACCUMNET(IY411,IA,G)$SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,G))
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,G)$IGDECOMEXOPOT(IY411,IA,G)
                 )                                                                                                  !!
         =E=
         SUM(HSEG, VHYDROCAS_HSEG(IY411,IA,G,HSEG,S,T));

* Hydropower production must be assigned to segment         !! If unreg inflow is higher than installed capacity, therefore the equation is only ran in instances without flooding
QHYDROCAS_HSEGMAX(IY411,IA,G,HSEG,S,T)$(IAGK_HYDROPOWER(IA,G) AND IGHYDISPATCH(G) AND IGKFIND(G) AND IAGK_HASORPOT(IY411,IA,G) AND IS3(S) AND NOT IHIGHUNREGSEASONS(IA,G,S))..
         VHYDROCAS_HSEG(IY411,IA,G,HSEG,S,T)
         =L=
         (( GKFX(IY411,IA,G)$IAGKFX(IY411,IA,G)+VGKNACCUMNET(IY411,IA,G)$SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,G))
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,G)$IGDECOMEXOPOT(IY411,IA,G)
        )*(1$(NOT IGKRATE(IA,G,S,T)) + IGKRATE(IA,G,S,T))
         - IHYINF_UNREG_S(IA,G,S) /IHYRST(S,T)/CARD(T)    * ( GKFX(IY411,IA,G)$IAGKFX(IY411,IA,G)+VGKNACCUMNET(IY411,IA,G)$SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,G))
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,G)$IGDECOMEXOPOT(IY411,IA,G)
                 ))/ CARD(HSEG);







