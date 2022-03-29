*INDIVUSERS grid add-on. Implemented by Juan Gea Bermudez 2019

$onmulti
$if     EXIST '../data/INDIVUSERS_CCCRRRAAA.inc' $INCLUDE         '../data/INDIVUSERS_CCCRRRAAA.inc';
$if not EXIST '../data/INDIVUSERS_CCCRRRAAA.inc' $INCLUDE '../../base/data/INDIVUSERS_CCCRRRAAA.inc';
$offmulti
