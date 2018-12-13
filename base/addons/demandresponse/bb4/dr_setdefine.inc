SET DR_TECHNOLOGIES          'Demand response technology'  %semislash%
SET DR_TECH(DR_TECHNOLOGIES) 'Demand response technology in the simulation' %semislash%
SET DR_DATASET               'characteristics of demand response technologies' %semislash%

$if     EXIST '../data/DR_SETINPUT.inc' $INCLUDE         '../data/DR_SETINPUT.inc';
$if not EXIST '../data/DR_SETINPUT.inc' $INCLUDE '../../base/data/DR_SETINPUT.inc';
