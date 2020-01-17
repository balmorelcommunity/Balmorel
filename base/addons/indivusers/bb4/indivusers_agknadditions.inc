*INDIVUSERS add-on. Implemented by Juan Gea Bermudez 2019

$onmulti
$if     EXIST '../data/INDIVUSERS_AGKN.inc' $INCLUDE         '../data/INDIVUSERS_AGKN.inc';
$if not EXIST '../data/INDIVUSERS_AGKN.inc' $INCLUDE '../../base/data/INDIVUSERS_AGKN.inc';
$offmulti
