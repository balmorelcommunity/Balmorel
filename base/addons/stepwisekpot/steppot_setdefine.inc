
SET KPOTSTEP 'step in techgroupkpot'          %semislash%
$if     EXIST '../data/KPOTSTEP.inc' $INCLUDE      '../data/KPOTSTEP.inc';
$if not EXIST '../data/KPOTSTEP.inc' $INCLUDE '../../base/data/KPOTSTEP.inc';
%semislash%;
