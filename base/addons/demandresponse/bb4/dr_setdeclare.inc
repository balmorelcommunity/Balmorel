$if     EXIST '../data/DR_SETINPUT.inc' $INCLUDE         '../data/DR_SETINPUT.inc';
$if not EXIST '../data/DR_SETINPUT.inc' $INCLUDE '../../base/data/DR_SETINPUT.inc';
