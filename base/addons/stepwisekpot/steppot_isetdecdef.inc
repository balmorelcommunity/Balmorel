SET IGKPOTSTEP(G) 'Technologies  that has KPOT_STEP)';
SET IKPOTSTEP(AAA,G) 'technology groups in areas that has KPOT_STEP)';

* if data entered for tech group and ...
IKPOTSTEP(IA,G) = YES$((SUM(Y, GKFX(Y,IA,G)) OR AGKN(IA,G))
                                 AND  SUM((TECH_GROUP,KPOTSTEP)$(GDATA(G,'GDTECHGROUP') EQ TECH_GROUP_VALUE(TECH_GROUP)),
                                         SUM(C$ICA(C,IA), TECHGROUPKPOT_STEP(IA,TECH_GROUP,KPOTSTEP))
                                         + SUM(IR$RRRAAA(IR,IA), TECHGROUPKPOT_STEP(IR,TECH_GROUP,KPOTSTEP))
                                         + TECHGROUPKPOT_STEP(IA,TECH_GROUP,KPOTSTEP)));



*IGKPOTSTEP(G) = YES$SUM((Y,IA,TECH_GROUP,KPOTSTEP)$(GDATA(G,'GDTECHGROUP') EQ TECH_GROUP_VALUE(TECH_GROUP)), IKPOTSTEP(Y,IA,TECH_GROUP,KPOTSTEP) );
