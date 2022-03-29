*INDIVUSERS add-on. Implemented by Juan Gea Bermudez 2019

$onmulti
$if     EXIST '../data/INDIVUSERS_GKFX.inc' $INCLUDE         '../data/INDIVUSERS_GKFX.inc';
$if not EXIST '../data/INDIVUSERS_GKFX.inc' $INCLUDE '../../base/data/INDIVUSERS_GKFX.inc';
$offmulti
