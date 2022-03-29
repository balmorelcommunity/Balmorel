*INDIVUSERS add-on. Implemented by Juan Gea Bermudez 2019

$onmulti
$if     EXIST '../data/INDIVUSERS_RRRAAA.inc' $INCLUDE         '../data/INDIVUSERS_RRRAAA.inc';
$if not EXIST '../data/INDIVUSERS_RRRAAA.inc' $INCLUDE '../../base/data/INDIVUSERS_RRRAAA.inc';
$offmulti
