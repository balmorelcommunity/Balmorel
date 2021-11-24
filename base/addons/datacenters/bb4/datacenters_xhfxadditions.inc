$onmulti
$if     EXIST '../data/DATACENTERS_XHKFX.inc' $INCLUDE         '../data/DATACENTERS_XHKFX.inc';
$if not EXIST '../data/DATACENTERS_XHKFX.inc' $INCLUDE '../../base/data/DATACENTERS_XHKFX.inc';
$offmulti
