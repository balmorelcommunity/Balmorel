*Intraseasonal EVs need none of these pins: QEV_BEV_BEBALANCE wraps T--1 inside each week, so every
*rolling week is already cyclic. Pinning T001 and T168 on top made the T001 hour bridge two levels
*taken from the previous week's availability, which ended on the EV_infeas slack.
*Interseasonal EVs keep them to link one rolling week to the next.
$ifi not %EV_INTERSEASONAL%==yes $goto NO_EV_INTERSEASONAL_PINS

*Fixing values relevant for next iteration
VEV_BE_BEV.FX(IY411,IR,IS3LOOPSET+1,T)$(IHASBEV(IR)  AND ORD(T) EQ CARD(T) )=IEV_BEV_available(IY411, IS3LOOPSET,T, IR)*(EV_BEV_batsize(IY411)- 0.01)/1.1;
VEV_BE_BEV.FX(IY411,IR,IS3LOOPSET+1,T)$(IHASBEV(IR)  AND ORD(T) EQ 1 )=IEV_BEV_available(IY411, IS3LOOPSET,T, IR)*(EV_BEV_batsize(IY411)- 0.01)/1.1;

*Boundary SOC for the first and last season, so EVs cannot start the year full or end it drained.
*Pinned to the same availability-derived level as above, NOT to EV_BE_BEV: import_results zeroes
*that parameter when ADDEVSTOS=none (import_results_ipardecdef.inc), which pinned these points to
*an empty fleet and pushed QEV_BEV_BEBALANCE onto the EV_infeas slack.
*S01/T001 and S01/T168 use the S01,T168 level rather than S01,T001, since availability in the very
*first hour of the year is the whole fleet and is not representative.
*SAMEAS keeps each pin to runs that simulate the seasons and hours it refers to.
VEV_BE_BEV.FX(IY411,IR,S,T)$(IHASBEV(IR) AND SAMEAS(S,'S01') AND (SAMEAS(T,'T001') OR SAMEAS(T,'T168')) AND SUM(ITALIAS$SAMEAS(ITALIAS,'T168'),1))
    = SUM(ITALIAS$SAMEAS(ITALIAS,'T168'), IEV_BEV_available(IY411,S,ITALIAS,IR))*(EV_BEV_batsize(IY411)- 0.01)/1.1;
VEV_BE_BEV.FX(IY411,IR,S,T)$(IHASBEV(IR) AND SAMEAS(S,'S02') AND SAMEAS(T,'T001') AND SUM((ISALIAS,ITALIAS)$(SAMEAS(ISALIAS,'S01') AND SAMEAS(ITALIAS,'T168')),1))
    = SUM((ISALIAS,ITALIAS)$(SAMEAS(ISALIAS,'S01') AND SAMEAS(ITALIAS,'T168')), IEV_BEV_available(IY411,ISALIAS,ITALIAS,IR))*(EV_BEV_batsize(IY411)- 0.01)/1.1;
*S52/T168 uses its OWN availability, not S51's: EV_BEV_return_profile spikes in the final hour of
*the year (the Monte Carlo year ends with every EV on the charger), so almost the whole fleet plugs in and
*returns its trip energy there. Pinning that hour to the previous week's level leaves that return
*energy with nowhere to go and makes QEV_BEV_BEBALANCE(S52,T168) infeasible.
VEV_BE_BEV.FX(IY411,IR,S,T)$(IHASBEV(IR) AND SAMEAS(S,'S52') AND SAMEAS(T,'T168')) = IEV_BEV_available(IY411,S,T,IR)*(EV_BEV_batsize(IY411)- 0.01)/1.1;

$label NO_EV_INTERSEASONAL_PINS

