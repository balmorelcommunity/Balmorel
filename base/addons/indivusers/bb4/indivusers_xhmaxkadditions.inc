*INDIVUSERS add-on. Implemented by Juan Gea Bermudez 2019

$onmulti
$if     EXIST '../data/INDIVUSERS_XHMAXK.inc' $INCLUDE         '../data/INDIVUSERS_XHMAXK.inc';
$if not EXIST '../data/INDIVUSERS_XHMAXK.inc' $INCLUDE '../../base/data/INDIVUSERS_XHMAXK.inc';
$offmulti
