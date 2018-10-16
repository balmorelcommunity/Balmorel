EQUATIONS
QGETOH_CAP1(YYY,AAA,SSS,TTT) 'endogenous limit to electricity consumption under demand charge winter, summer and "2"'
QGETOH_CAP2(YYY,AAA,SSS,TTT) 'endogenous limit to electricity consumption under demand charge TOU'
QGETOH_CAPY(YYY,AAA,SSS,TTT) 'endogenous limit to electricity consumption under demand charge yearly'
QGETOH_CAPBB3(YYY,AAA,SSS,TTT) 'demand charge for BB3'
;

QGETOH_CAP1(IY411,IA,IS3,T)$(SUM(IGETOH, IAGK_HASORPOT(IY411,IA,IGETOH)) AND SUM(IR$RRRAAA(IR,IA), IGR_PRICE_TECH(IY411,IR,'GRDDCW')))..
                         SUM(IGETOH$IAGK_HASORPOT(IY411,IA,IGETOH), VGF_T(IY411,IA,IGETOH,IS3,T))
                         =L=
                         SUM(MMM, VGETOH_CAP1(IY411,IA,MMM)* ISSSTTTMMM(IS3,T,MMM));


QGETOH_CAP2(IY411,IA,IS3,T)$(SUM(IGETOH,IAGK_HASORPOT(IY411,IA,IGETOH)) AND SUM(IR$RRRAAA(IR,IA), IGR_PRICE_TECH(IY411,IR,'GRDDCTOU')))..
                         SUM(IGETOH$IAGK_HASORPOT(IY411,IA,IGETOH), VGF_T(IY411,IA,IGETOH,IS3,T)$SUM(IR$RRRAAA(IR,IA), IGR_TIME('GRDDCTOU',IR,IS3,T)))
                         =L=
                         SUM(MMM, VGETOH_CAP2(IY411,IA,MMM)* ISSSTTTMMM(IS3,T,MMM));

QGETOH_CAPY(IY411,IA,IS3,T)$(SUM(IGETOH,IAGK_HASORPOT(IY411,IA,IGETOH)) AND SUM(IR$RRRAAA(IR,IA), IGR_PRICE_TECH(IY411,IR,'GRDDCY')))..
                         SUM(IGETOH$IAGK_HASORPOT(IY411,IA,IGETOH), VGF_T(IY411,IA,IGETOH,IS3,T))
                         =L=
                         VGETOH_CAPY(IY411,IA);

QGETOH_CAPBB3(Y,IA,IS3,T)$SUM(IGETOH,IAGK_HASORPOT(Y,IA,IGETOH))..
                         SUM(IGETOH, VGF_T(Y,IA,IGETOH,IS3,T)) =L= IGRGETOHLEVEL(IA,IS3,T);
