*INDIVUSERS add-on. Implemented by Juan Gea Bermudez 2019

$onmulti
$if     EXIST '../data/INDIVUSERS_DE.inc' $INCLUDE         '../data/INDIVUSERS_DE.inc';
$if not EXIST '../data/INDIVUSERS_DE.inc' $INCLUDE '../../base/data/INDIVUSERS_DE.inc';
$offmulti
