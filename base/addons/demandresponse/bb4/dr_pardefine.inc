$if     EXIST '../data_GREAT/DR_DATAINPUT.inc' $INCLUDE         '../data_GREAT/DR_DATAINPUT.inc';
$if not EXIST '../data/DR_DATAINPUT.inc' $INCLUDE '../../base/data/DR_DATAINPUT.inc';
%semislash%;
