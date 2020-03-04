*INDIVUSERS add-on. Implemented by Juan Gea Bermudez 2019

$onmulti
$if     EXIST '../data/INDIVUSERS_SOLHFLH.inc' $INCLUDE         '../data/INDIVUSERS_SOLHFLH.inc';
$if not EXIST '../data/INDIVUSERS_SOLHFLH.inc' $INCLUDE '../../base/data/INDIVUSERS_SOLHFLH.inc';
$offmulti
