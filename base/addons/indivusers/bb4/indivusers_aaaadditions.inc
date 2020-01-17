*INDIVUSERS add-on. Implemented by Juan Gea Bermudez 2019

$onmulti
$if     EXIST '../data/INDIVUSERS_AAA.inc' $INCLUDE         '../data/INDIVUSERS_AAA.inc';
$if not EXIST '../data/INDIVUSERS_AAA.inc' $INCLUDE '../../base/data/INDIVUSERS_AAA.inc';
$offmulti
