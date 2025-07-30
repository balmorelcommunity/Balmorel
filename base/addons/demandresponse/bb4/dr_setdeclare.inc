$if     EXIST '../data_GREAT/DR_SETINPUT.inc' $INCLUDE         '../data_GREAT/DR_SETINPUT.inc';
$if not EXIST '../data/DR_SETINPUT.inc' $INCLUDE '../../base/data/DR_SETINPUT.inc';