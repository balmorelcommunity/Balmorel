*INDIVUSERS add-on. Implemented by Juan Gea Bermudez 2019

$onmulti
$if     EXIST '../data/INDIVUSERS_XHKFX.inc' $INCLUDE         '../data/INDIVUSERS_XHKFX.inc';
$if not EXIST '../data/INDIVUSERS_XHKFX.inc' $INCLUDE '../../base/data/INDIVUSERS_XHKFX.inc';
$offmulti
