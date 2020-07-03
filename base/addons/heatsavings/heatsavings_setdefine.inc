SET HEATSV_STEPS   'Steps' %semislash%
$if     EXIST '../data/HEATSAVINGS_STEPS.inc' $INCLUDE         '../data/HEATSAVINGS_STEPS.inc'
$if not EXIST '../data/HEATSAVINGS_STEPS.inc' $INCLUDE '../../base/data/HEATSAVINGS_STEPS.inc';
%semislash%
