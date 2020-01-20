*INDIVUSERS add-on. Implemented by Juan Gea Bermudez 2019

$onmulti
$if     EXIST '../data/INDIVUSERS_GGG.inc' $INCLUDE         '../data/INDIVUSERS_GGG.inc';
$if not EXIST '../data/INDIVUSERS_GGG.inc' $INCLUDE '../../base/data/INDIVUSERS_GGG.inc';
$offmulti
