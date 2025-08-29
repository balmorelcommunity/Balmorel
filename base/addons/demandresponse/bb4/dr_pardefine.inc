$if     EXIST '../data/DR_DATAINPUT.inc' $INCLUDE         '../data/DR_DATAINPUT.inc';
$if not EXIST '../data/DR_DATAINPUT.inc' $INCLUDE '../../base/data/DR_DATAINPUT.inc';
%semislash%;
