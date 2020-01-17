*INDIVUSERS add-on. Implemented by Juan Gea Bermudez 2019

$onmulti
$if     EXIST '../data/INDIVUSERS_XHLOSS.inc' $INCLUDE         '../data/INDIVUSERS_XHLOSS.inc';
$if not EXIST '../data/INDIVUSERS_XHLOSS.inc' $INCLUDE '../../base/data/INDIVUSERS_XHLOSS.inc';
$offmulti
