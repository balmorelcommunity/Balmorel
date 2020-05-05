* CCS add-on. Added by Juan Gea Bermudez

$onmulti
$if     EXIST '../data/CCS_CCS_G.inc' $INCLUDE         '../data/CCS_CCS_G.inc';
$if not EXIST '../data/CCS_CCS_G.inc' $INCLUDE '../../base/data/CCS_CCS_G.inc';
$offmulti
