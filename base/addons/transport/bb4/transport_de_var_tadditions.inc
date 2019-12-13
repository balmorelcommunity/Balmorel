* Transport add-on. Added by Juan Gea Bermudez


$onmulti
$if     EXIST '../data/TRANSPORT_DE_VAR_T.inc' $INCLUDE         '../data/TRANSPORT_DE_VAR_T.inc';
$if not EXIST '../data/TRANSPORT_DE_VAR_T.inc' $INCLUDE '../../base/data/TRANSPORT_DE_VAR_T.inc';
$offmulti