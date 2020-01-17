*INDIVUSERS add-on. Implemented by Juan Gea Bermudez 2019

$onmulti
$if     EXIST '../data/INDIVUSERS_DH_VAR_T.inc' $INCLUDE         '../data/INDIVUSERS_DH_VAR_T.inc';
$if not EXIST '../data/INDIVUSERS_DH_VAR_T.inc' $INCLUDE '../../base/data/INDIVUSERS_DH_VAR_T.inc';
$offmulti
