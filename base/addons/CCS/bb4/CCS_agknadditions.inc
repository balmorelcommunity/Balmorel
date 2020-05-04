* CCS add-on. Added by Juan Gea Bermudez

$onmulti
$if     EXIST '../data/CCS_AGKN.inc' $INCLUDE         '../data/CCS_AGKN.inc';
$if not EXIST '../data/CCS_AGKN.inc' $INCLUDE '../../base/data/CCS_AGKN.inc';
$offmulti
