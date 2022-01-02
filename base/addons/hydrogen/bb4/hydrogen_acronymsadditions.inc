$onmulti
$if     EXIST '../data/HYDROGEN_ACRONYMS.inc' $INCLUDE         '../data/HYDROGEN_ACRONYMS.inc';
$if not EXIST '../data/HYDROGEN_ACRONYMS.inc' $INCLUDE '../../base/data/HYDROGEN_ACRONYMS.inc';
$offmulti
