$onmulti
$if     EXIST '../data/DATACENTERS_XHINVCOST.inc' $INCLUDE         '../data/DATACENTERS_XHINVCOST.inc';
$if not EXIST '../data/DATACENTERS_XHINVCOST.inc' $INCLUDE '../../base/data/DATACENTERS_XHINVCOST.inc';
$offmulti
