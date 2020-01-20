*INDIVUSERS add-on. Implemented by Juan Gea Bermudez 2019

$onmulti
$if     EXIST '../data/INDIVUSERS_G.inc' $INCLUDE         '../data/INDIVUSERS_G.inc';
$if not EXIST '../data/INDIVUSERS_G.inc' $INCLUDE '../../base/data/INDIVUSERS_G.inc';
$offmulti
