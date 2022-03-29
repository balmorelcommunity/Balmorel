*INDIVUSERS add-on. Implemented by Juan Gea Bermudez 2019

$onmulti
$if     EXIST '../data/INDIVUSERS_COP.inc' $INCLUDE         '../data/INDIVUSERS_COP.inc';
$if not EXIST '../data/INDIVUSERS_COP.inc' $INCLUDE '../../base/data/INDIVUSERS_COP.inc';
$offmulti
