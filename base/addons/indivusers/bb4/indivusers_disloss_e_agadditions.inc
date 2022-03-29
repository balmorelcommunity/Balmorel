*INDIVUSERS add-on. Implemented by Juan Gea Bermudez 2019

$onmulti
$if     EXIST '../data/INDIVUSERS_DISLOSS_E_AG.inc' $INCLUDE         '../data/INDIVUSERS_DISLOSS_E_AG.inc';
$if not EXIST '../data/INDIVUSERS_DISLOSS_E_AG.inc' $INCLUDE '../../base/data/INDIVUSERS_DISLOSS_E_AG.inc';
$offmulti
