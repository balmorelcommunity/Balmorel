EQUATIONS

*Plants with storage
QHYDROCAS_HYRSEEQ(YYY,AAA,GGG,SSS) 'Storage balance of hydropower reservoirs'                                                                     !! Balance of storage
QHYDROCAS_HYGEEQ(YYY,AAA,GGG,SSS) 'Relationship between hourly production levels, unregulated inflow and production from reservoirs'              !! Balance of production
QHYDROCAS_HYRREEQ(YYY,AAA,GGG,SSS,TTT) ' Balance of run of river power plants'
QHYDROCAS_HYRSMINVOL(YYY,AAA,GGG,SSS) 'Minimum storage level of hydropower reservoirs'                                                            !! Lower limit to VHYDROCAS_RESLEVEL
QHYDROCAS_HYRSMAXVOL(YYY,AAA,GGG,SSS) 'Maximum storage level of hydropower reservoirs'                                                            !! Upper limit to VHYDROCAS_RESLEVEL
QHYDROCAS_HYRSGMAX(YYY,AAA,GGG,SSS,TTT) 'Maximum production level of river storage plants'                                                        !! Endogenous lower limit to VGE_T     optional
QHYDROCAS_HYRSGMIN(YYY,AAA,GGG,SSS,TTT) 'Minimum production level of river storage plants'                                                        !! Endogenous upper limit to VGE_T     optional
QHYDROCAS_VGESUP(YYY,AAA,GGG,SSS) 'Maximum storage withdrawal from river storage power plants'                                                !! Upper limit to VHYDROCAS_VGE_S     (also .up)
QHYDROCAS_VGESLO(YYY,AAA,GGG,SSS) 'Maximum storage withdrawal from river storage power plants'                                                !! Upper limit to VHYDROCAS_VGE_S     (also .up)

*Pumped storage
QHYDROCAS_HYRSMAXPUMP(YYY,AAA,GGG,SSS,TTT) 'Maximum level of pumping'                                                                             !! Upper limit to pumping   (also .up)

*HSEG
QHYDROCAS_HSEG(YYY,AAA,GGG,SSS,TTT) 'Hydropower production, relationship between VGE_T and HSEG'                                                  !! optional
QHYDROCAS_HSEGMAX(YYY,AAA,GGG,HSEG,SSS,TTT) 'Hydropower production must be assigned to segment'                                                   !! optional
;

** SET GKFX to maximum of production capacity per hour.
** Storage balance of hydropower reservoirs'
QHYDROCAS_HYRSEEQ(IY411,IA,G,S)$(IAGK_HYDRCAS(IA,G) AND IGHYRS(G) AND IAGK_HASORPOT(IY411,IA,G) AND IS3(S))..
      (VHYDROCAS_RESLEVEL(IY411,IA,G,S++1) - VHYDROCAS_RESLEVEL(IY411,IA,G,S) )$HDATA(G,'HDRESERVOIR')
       + SUM(T,  IHYRST(S,T) * (VHYDROCAS_VGE_S(IY411,IA,G,S) + VHYDROCAS_SPILL_RES(IY411,IA,G,S)))                                                                                                            !!Production  and Spill
       - SUM((T,IGALIAS)$(IAGK_HASORPOT(IY411,IA,IGALIAS) AND HYDROCAS_TRANSFER(IA,IGALIAS,G)),
                 HYDROCAS_TRANSFER(IA,IGALIAS,G) * IHYRST(S,T) * (VHYDROCAS_VGE_S(IY411,IA,IGALIAS,S) + VHYDROCAS_SPILL_RES(IY411,IA,IGALIAS,S)$IGPOWERPLANT(IGALIAS)))                                         !!Inflow from upstream
       - SUM(T, IHYRST(S,T) * VHYDROCAS_PUMP_T(IY411,IA,G,S,T)* SUM(IGALIAS$HYDROCAS_PUMPTRANSFER(IA,IGALIAS,G), HYDROCAS_PUMPTRANSFER(IA,IGALIAS,G)+1))$IGPUMP(G)                                               !!Pumped into reservoir
       + SUM((T,IGALIAS)$(IAGK_HASORPOT(IY411,IA,IGALIAS) AND IGPUMP(IGALIAS) AND HYDROCAS_PUMPTRANSFER(IA,G,IGALIAS)), HYDROCAS_PUMPTRANSFER(IA,G,IGALIAS) * IHYRST(S,T) * VHYDROCAS_PUMP_T(IY411,IA,IGALIAS,S,T))      !!Pumped out of reservoir
      =E=
       (IHYINFNAT_S(IA,G,S) + IHYINFUPSTREAM_S(IA,G,S) + IHYINFUNREG_S(IA,G,S))                                                                                                                                  !! All forms of inflow really
       * ( GKFX(IY411,IA,G)$IAGKFX(IY411,IA,G)
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,G)$IGDECOMEXOPOT(IY411,IA,G)
       +VGKNACCUMNET(IY411,IA,G)$SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,G))
        )
*+ VQHYDROCAS_HYRSEEQ(IY411,IA,G,S,'IMINUS')- VQHYDROCAS_HYRSEEQ(IY411,IA,G,S,'IPLUS')
;


** Relationship between hourly production levels, unregulated inflow and production from reservoirs
QHYDROCAS_HYGEEQ(IY411,IA,G,S)$(IAGK_HYDRCAS(IA,G) AND IGHYRS(G) AND IAGK_HASORPOT(IY411,IA,G) AND IGPOWERPLANT(G) AND IS3(S))..
         SUM(T, VGE_T(IY411,IA,G,S,T) + VHYDROCAS_SPILL(IY411,IA,G,S,T)) / CARD(T)
         =E=
         VHYDROCAS_VGE_S(IY411,IA,G,S)
;
QHYDROCAS_HYRREEQ(IY411,IA,G,S,T)$(IAGK_HYDRCAS(IA,G) AND IGKFIND(G) AND IGHYRR(G) AND IAGK_HASORPOT(IY411,IA,G) AND IGPOWERPLANT(G) AND IS3(S))..
         VGE_T(IY411,IA,G,S,T) + VHYDROCAS_SPILL(IY411,IA,G,S,T)
         =E=
         (IHYINFNAT_S(IA,G,S) + IHYINFUPSTREAM_S(IA,G,S) + IHYINFUNREG_S(IA,G,S))                                                                                                                                  !! All forms of inflow really
       * ( GKFX(IY411,IA,G)$IAGKFX(IY411,IA,G)
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,G)$IGDECOMEXOPOT(IY411,IA,G)
       +VGKNACCUMNET(IY411,IA,G)$SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,G))
        )
;

** Minimum storage level of hydropower reservoirs
QHYDROCAS_HYRSMINVOL(IY411,IA,G,S)$(IAGK_HYDRCAS(IA,G) AND IGHYRS(G) AND IGKFIND(G) AND IAGK_HASORPOT(IY411,IA,G) AND IS3(S))..
           VHYDROCAS_RESLEVEL(IY411,IA,G,S) =G=
         ( GKFX(IY411,IA,G)$IAGKFX(IY411,IA,G)+VGKNACCUMNET(IY411,IA,G)$SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,G))
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,G)$IGDECOMEXOPOT(IY411,IA,G)
          ) * HDATA(G,'HDRESERVOIR') * HMINLEVELS(G,S);

** Maximum storage level of hydropower reservoirs
QHYDROCAS_HYRSMAXVOL(IY411,IA,G,S)$(IAGK_HYDRCAS(IA,G) AND IGHYRS(G) AND IGKFIND(G) AND IAGK_HASORPOT(IY411,IA,G) AND IS3(S))..
           VHYDROCAS_RESLEVEL(IY411,IA,G,S) =L=
         ( GKFX(IY411,IA,G)$IAGKFX(IY411,IA,G)+VGKNACCUMNET(IY411,IA,G)$SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,G))
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,G)$IGDECOMEXOPOT(IY411,IA,G)
          ) * HDATA(G,'HDRESERVOIR') ;



* Minimum production level dependent on rate of fixed production     (Share of installed capacity or share of max reg + unreg?)
QHYDROCAS_HYRSGMIN(IY411,IA,G,S,T)$(IAGK_HYDRCAS(IA,G) AND IGPOWERPLANT(G) AND IAGK_HASORPOT(IY411,IA,G) AND IS3(S))..
         VGE_T(IY411,IA,G,S,T)
         =G=
         HDATA(G,'HDFIXED') * VHYDROCAS_VGE_S(IY411,IA,G,S)
         - VHYDROCAS_SPILL(IY411,IA,G,S,T);

* Maximum production level dependent on rate of fixed production
QHYDROCAS_HYRSGMAX(IY411,IA,G,S,T)$(IAGK_HYDRCAS(IA,G) AND IGPOWERPLANT(G) AND HDATA(G,'HDFIXED') AND IAGK_HASORPOT(IY411,IA,G) AND IS3(S))..
         VGE_T(IY411,IA,G,S,T)
         =L=
         HDATA(G,'HDFIXED') * VHYDROCAS_VGE_S(IY411,IA,G,S)                                                                          !! inflexible capacity
         + (1- HDATA(G,'HDFIXED')) *                                                                                                  !! flexible capacity
           ( GKFX(IY411,IA,G)$IAGKFX(IY411,IA,G)+VGKNACCUMNET(IY411,IA,G)$SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,G))
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,G)$IGDECOMEXOPOT(IY411,IA,G)
            )* (1$(NOT IGKRATE(IA,G,S,T)) + IGKRATE(IA,G,S,T))
;


** Maximum storage withdrawal from storage power plants less than loss free capacity * rates
QHYDROCAS_VGESUP(IY411,IA,G,S)$(IAGK_HYDRCAS(IA,G) AND IGKFIND(G) AND IAGK_HASORPOT(IY411,IA,G) AND HYDROCAS_RATES(IA,G,S) AND IS3(S))..
         VHYDROCAS_VGE_S(IY411,IA,G,S)
         =L=
         (1$(NOT HYDROCAS_RATES(IA,G,S)) + HYDROCAS_RATES(IA,G,S)) * ( GKFX(IY411,IA,G)$IAGKFX(IY411,IA,G)+VGKNACCUMNET(IY411,IA,G)$SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,G))
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,G)$IGDECOMEXOPOT(IY411,IA,G)
         )  ;

** Maximum storage withdrawal from storage power plants must be higher than unregulated production
QHYDROCAS_VGESLO(IY411,IA,G,S)$(IAGK_HYDRCAS(IA,G) AND IGKFIND(G) AND IAGK_HASORPOT(IY411,IA,G) AND IHYINFUNREG_S(IA,G,S) AND IS3(S))..
         VHYDROCAS_VGE_S(IY411,IA,G,S)
         =G=
         IHYINFUNREG_S(IA,G,S)   * ( GKFX(IY411,IA,G)$IAGKFX(IY411,IA,G)+VGKNACCUMNET(IY411,IA,G)$SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,G))  !! Unreg production
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,G)$IGDECOMEXOPOT(IY411,IA,G)
          )/SUM(T, IHYRST(S,T))  ;


** Pumped storage
** Maximum level of pumping
QHYDROCAS_HYRSMAXPUMP(IY411,IA,G,S,T)$(IAGK_HYDRCAS(IA,G) AND IGPUMP(G) AND IGKFIND(G) AND IAGK_HASORPOT(IY411,IA,G) AND IS3(S))..
         VHYDROCAS_PUMP_T(IY411,IA,G,S,T)
         =L=
         ( GKFX(IY411,IA,G)$IAGKFX(IY411,IA,G)+VGKNACCUMNET(IY411,IA,G)$SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,G))
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,G)$IGDECOMEXOPOT(IY411,IA,G)
          ) * HDATA(G,'HDPUMPPOWER')  ;


** HSEG **    Stepwise marginal cost increase for high production rates. Reflects e.g. lower efficiencies at high utilization.                                                                                              !!    AND VHYDROCAS_VGE_S.UP(IY411,IA,G,S)*(CARD(HSEG)-1)/CARD(HSEG) > VHYDROCAS_VGE_S.LO(IY411,IA,G,S)
* Hydropower production, relationship between VGE_T and HSEG                                                                                                                                                                !! AND IHYINFUNREG_S(IA,G,S) < IHYRST(S,T)*CARD(T)*(CARD(HSEG)-1)/CARD(HSEG)
QHYDROCAS_HSEG(IY411,IA,G,S,T)$(IAGK_HYDRCAS(IA,G) AND IGPOWERPLANT(G) AND IGHYRS(G) AND IAGK_HASORPOT(IY411,IA,G) AND IS3(S) AND NOT IHIGHUNREGSEASONS(IA,G,S))..
         VGE_T(IY411,IA,G,S,T)
         -  IHYINFUNREG_S(IA,G,S)   * ( GKFX(IY411,IA,G)$IAGKFX(IY411,IA,G)+VGKNACCUMNET(IY411,IA,G)$SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,G))
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,G)$IGDECOMEXOPOT(IY411,IA,G)
                 )/IHYRST(S,T)/CARD(T)
         =E=
         SUM(HSEG, VHYDROCAS_HSEG(IY411,IA,G,HSEG,S,T));

* Hydropower production must be assigned to segment         !! If unreg inflow is higher than installed capacity, therefore the equation is only ran in instances without flooding
QHYDROCAS_HSEGMAX(IY411,IA,G,HSEG,S,T)$(IAGK_HYDRCAS(IA,G) AND IGPOWERPLANT(G) AND IGHYRS(G) AND IGKFIND(G) AND IAGK_HASORPOT(IY411,IA,G) AND IS3(S) AND NOT IHIGHUNREGSEASONS(IA,G,S) )..
         VHYDROCAS_HSEG(IY411,IA,G,HSEG,S,T)
         =L=
         (( GKFX(IY411,IA,G)$IAGKFX(IY411,IA,G)+VGKNACCUMNET(IY411,IA,G)$SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,G))
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,G)$IGDECOMEXOPOT(IY411,IA,G)
        )*(1$(NOT IGKRATE(IA,G,S,T)) + IGKRATE(IA,G,S,T))
         - IHYINFUNREG_S(IA,G,S)   * ( GKFX(IY411,IA,G)$IAGKFX(IY411,IA,G)+VGKNACCUMNET(IY411,IA,G)$SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,G))
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,G)$IGDECOMEXOPOT(IY411,IA,G)
                 )/IHYRST(S,T)/CARD(T))/ CARD(HSEG);








$ontext
*old stuff

QHYDROCAS_HYRSPRODUCTION(YYY,AAA,GGG,SSS,TTT) 'Relationship between weekly and hourly production levels of river storage plants'
QHYDROCAS_HYRSPRODUCTION_DOWN(YYY,AAA,GGG,SSS,TTT) 'Relationship between weekly and hourly production levels of river storage plants'


** Relationship between weekly and hourly production levels for plants with outlet to rivers. Upper level
QHYDROCAS_HYRSPRODUCTION(IY411,IA,G,S,T)$(IAGK_HYDRCAS(IA,G) AND IAGK_HASORPOT(IY411,IA,G) AND HDATA(G,'HDRIVEROUT') AND IS3(S))..
         VGE_T(IY411,IA,G,S,T)
         =L=
         VHYDROCAS_RESS(IY411,IA,G,S)
         + ((1-HDATA(G,'HDRIVEROUT'))+HDATA(G,'HDRIVEROUT')*(1-HDATA(G,'HDFIXED')))*(1$(NOT IGKRATE(IA,G,S,T)) + IGKRATE(IA,G,S,T))
         * (        (GKFX(IY411,IA,G)$IAGKFX(IY411,IA,G) + VGKNACCUMNET(IY411,IA,G)$SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,G))
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,G)$IGDECOMEXOPOT(IY411,IA,G)
                    )$(NOT HDATA(G,'HDLOSSFREE'))
                    + ((HDATA(G,'HDLOSSFREE')  +  IHYINFUNREG_S(IA,G,S))   * ( GKFX(IY411,IA,G)$IAGKFX(IY411,IA,G)+VGKNACCUMNET(IY411,IA,G)$SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,G))
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,G)$IGDECOMEXOPOT(IY411,IA,G)
                        ))$HDATA(G,'HDLOSSFREE')
         )  ;

** Relationship between weekly and hourly production levels of river storage plant, Lower level
QHYDROCAS_HYRSPRODUCTION_DOWN(IY411,IA,G,S,T)$(IAGK_HYDRCAS(IA,G) AND IAGK_HASORPOT(IY411,IA,G) AND HDATA(G,'HDRIVEROUT') AND IS3(S))..
         VGE_T(IY411,IA,G,S,T)
         =G=
         VHYDROCAS_RESS(IY411,IA,G,S);

* Flex plants
QHYDROCAS_FLEXINFLOW(YYY,AAA,GGG) 'inflow is restricted by full-load-hours for FLEX plants'


** Flex plants               !! It saves calculation time to not model the storage dynamics in power plants with plenty storage... to be removed
* Inflow is restricted by full load hours only for Flex plants
QHYDROCAS_FLEXINFLOW(IY411,IA,G)$(IAGK_HYDRCAS(IA,G) AND IAGK_HASORPOT(IY411,IA,G) AND IGHYRS(G) AND (HDATA(G,'HDTYPE') EQ FLEX))..
         SUM((S,T), IHOURSINST(S,T)* VGE_T(IY411,IA,G,S,T))
         =L=
         (HDATA(G,'HDINFLOW')+HDATA(G,'HDINFLOWUREG')) * (1$(NOT INLFOWADJUST(IA)) + INLFOWADJUST(IA))  * ( GKFX(IY411,IA,G)$IAGKFX(IY411,IA,G)+VGKNACCUMNET(IY411,IA,G)$SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,G))
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,G)$IGDECOMEXOPOT(IY411,IA,G)
          )    ;


** Pumped storage water balance for lower unit
*QHYDROCAS_PUMPEQ(IY411,IA,G,S)$(IAGK_HYDRCAS(IA,G) AND IGPUMP(G) AND IAGK_HASORPOT(IY411,IA,G) AND IS3(S))..
*         SUM((T, VHYDROCAS_PUMP_T(IY411,IA,G,S,T) + VGE_T(IY411,IA,G,S,T))
*         =L=
*         IHYINF_PUMP(IY411,IA,G,S) * ( GKFX(IY411,IA,G)$IAGKFX(IY411,IA,G)
*$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,G)$IGDECOMEXOPOT(IY411,IA,G)
*         +VGKNACCUMNET(IY411,IA,G)$SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,G))
*         );

*QHYDROCAS_HYRSUNREG(YYY,AAA,SSS) 'Unreg production in non river storage plants'                                                                   !! Balance of unregulated production

** Unreg production in non river storage plants
*QHYDROCAS_HYRSUNREG(IY411,IA,S)$(IA_HYDROCASA(IA) AND SUM(G$IGHYRS(G), IAGK_HYDRCAS(IA,G) AND IAGK_HASORPOT(IY411,IA,G)) AND IS3(S))..       !!$(### Has unreg inflow)
*         SUM((T,G)$(IGHYRS(G) AND IAGK_HYDRCAS(IA,G) AND IAGK_HASORPOT(IY411,IA,G)), VGE_T(IY411,IA,G,S,T)) / CARD(T)
*         =G=
*         WTR_UNREG_VARS(IA,S)*1000  / CARD(TTT)
*         + SUM(G$(IGHYRS(G) AND IAGK_HYDRCAS(IA,G) AND IAGK_HASORPOT(IY411,IA,G)), IHYINFUNREG_S(IA,G,S)   * ( GKFX(IY411,IA,G)$IAGKFX(IY411,IA,G)+VGKNACCUMNET(IY411,IA,G)$SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,G))  !! Unreg production
*$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,G)$IGDECOMEXOPOT(IY411,IA,G)
*                 ));

** ROR plants                                                                            !! Seems like either this or the equation above is unnecessary     or both???
** Production in river plants is a sum of natural inflow and inflow from upstream plants
*QHYDROCAS_HYRRMAXG(IY411,IA,G,S,T)$(IAGK_HYDRCAS(IA,G) AND IAGK_HASORPOT(IY411,IA,G) AND IGHYRR(G) AND IS3(S))..
*         VGE_T(IY411,IA,G,S,T)
*         =L=
*         IHYINFUNREG_S(IA,G,S) * ( GKFX(IY411,IA,G)$IAGKFX(IY411,IA,G)+VGKNACCUMNET(IY411,IA,G)$SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,G))
*$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,G)$IGDECOMEXOPOT(IY411,IA,G)
*        )
*       +  SUM((IGALIAS,ITALIAS)$(IAGK_HYDRCAS(IA,IGALIAS) AND IGHYRS(IGALIAS) AND HYDROCAS_TRANSFER(IA,G,IGALIAS)), HYDROCAS_TRANSFER(IA,G,IGALIAS) * VGE_T(IY411,IA,IGALIAS,S,ITALIAS))/CARD(ITALIAS);


         + VHYDROCAS_SPILL_RES(IY411,IA,G,S) * 0.5                                                                                                    !! Flooding in reservoir

QHYDROCAS_HYRSMINPROD(YYY,AAA,GGG,SSS) 'Minimum production level of river storage plants'                                                         !! Lower limit to VHYDROCAS_VGE_S

** Minimum production level
QHYDROCAS_HYRSMINPROD(IY411,IA,G,S)$(IAGK_HYDRCAS(IA,G) AND IAGK_HASORPOT(IY411,IA,G) AND HDATA(G,'HDMIN') AND IS3(S))..
         SUM(T, VGE_T(IY411,IA,G,S,T)) / CARD(T)
         =G=
         HDATA(G,'HDMIN') * ( GKFX(IY411,IA,G)$IAGKFX(IY411,IA,G)+VGKNACCUMNET(IY411,IA,G)$SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,G))
$ifi %DECOM%==yes   -VDECOM_EXO_ACCUM(IY411,IA,G)$IGDECOMEXOPOT(IY411,IA,G)
          )    ;

*QHYDROCAS_HYRRMAXG(YYY,AAA,GGG,SSS,TTT) 'Production in river plants is a sum of natural inflow and inflow from upstream plants'                   !! Balance of unregulated production (necessary)

$offtext
