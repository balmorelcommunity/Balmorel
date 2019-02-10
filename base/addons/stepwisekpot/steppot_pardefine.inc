PARAMETER TECHGROUPKPOT_STEP(CCCRRRAAA,TECH_GROUP,KPOTSTEP) 'share of TECHGROUPKPOT belonging to each step (fraction)' %semislash%
$if     EXIST '../data/TECHGROUPKPOT_STEP.inc' $INCLUDE      '../data/TECHGROUPKPOT_STEP.inc';
$if not EXIST '../data/TECHGROUPKPOT_STEP.inc' $INCLUDE '../../base/data/TECHGROUPKPOT_STEP.inc';
%semislash%;


PARAMETER KPOTSTEP_FLH(CCCRRRAAA,TECH_GROUP,KPOTSTEP) 'multiplier to FLH (1 equals no change)' %semislash%
$if     EXIST '../data/KPOTSTEP_FLH.inc' $INCLUDE      '../data/KPOTSTEP_FLH.inc';
$if not EXIST '../data/KPOTSTEP_FLH.inc' $INCLUDE '../../base/data/KPOTSTEP_FLH.inc';
%semislash%;
