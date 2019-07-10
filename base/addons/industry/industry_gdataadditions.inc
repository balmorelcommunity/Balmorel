$onmulti
$if     EXIST '../data/INDUSTRY_GDATA.inc' $INCLUDE         '../data/INDUSTRY_GDATA.inc';
$if not EXIST '../data/INDUSTRY_GDATA.inc' $INCLUDE '../../base/data/INDUSTRY_GDATA.inc';
$offmulti
