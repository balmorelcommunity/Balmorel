*INDIVUSERS add-on. Implemented by Juan Gea Bermudez 2019

$onmulti
$if     EXIST '../data/INDIVUSERS_DH.inc' $INCLUDE         '../data/INDIVUSERS_DH.inc';
$if not EXIST '../data/INDIVUSERS_DH.inc' $INCLUDE '../../base/data/INDIVUSERS_DH.inc';
$offmulti
