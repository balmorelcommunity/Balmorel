*INDIVUSERS add-on. Implemented by Juan Gea Bermudez 2019

$onmulti
$if     EXIST '../data/INDIVUSERS_XHINVCOST.inc' $INCLUDE         '../data/INDIVUSERS_XHINVCOST.inc';
$if not EXIST '../data/INDIVUSERS_XHINVCOST.inc' $INCLUDE '../../base/data/INDIVUSERS_XHINVCOST.inc';
$offmulti
