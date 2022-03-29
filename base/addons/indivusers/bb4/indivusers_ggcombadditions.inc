*INDIVUSERS add-on. Implemented by Juan Gea Bermudez 2019

$onmulti
$if     EXIST '../data/INDIVUSERS_GGCOMB.inc' $INCLUDE         '../data/INDIVUSERS_GGCOMB.inc';
$if not EXIST '../data/INDIVUSERS_GGCOMB.inc' $INCLUDE '../../base/data/INDIVUSERS_GGCOMB.inc';
$offmulti
