SET DR_TECHNOLOGIES          'Demand response technology'  %semislash%
SET DR_TECH(DR_TECHNOLOGIES) 'Demand response technology in the simulation' %semislash%
SET DR_DATASET               'characteristics of demand response technologies' %semislash%

$if     EXIST '../data/DR_SETINPUT.INC' $INCLUDE         '../data/DR_SETINPUT.INC';
$if not EXIST '../data/DR_SETINPUT.INC' $INCLUDE '../../base/data/DR_SETINPUT.INC';
