$onmulti
$if     EXIST '../data/HYDROCAS_GDATA_FLH.inc' $INCLUDE         '../data/HYDROCAS_GDATA_FLH.inc';
$if not EXIST '../data/HYDROCAS_GDATA_FLH.inc' $INCLUDE '../../base/data/HYDROCAS_GDATA_FLH.inc';
$offmulti
