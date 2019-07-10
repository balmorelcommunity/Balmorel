$onmulti
$if     EXIST '../data/INDUSTRY_DH.inc' $INCLUDE         '../data/INDUSTRY_DH.inc';
$if not EXIST '../data/INDUSTRY_DH.inc' $INCLUDE '../../base/data/INDUSTRY_DH.inc';

$if     EXIST '../data/INDUSTRY_DH_VAR_T.inc' $INCLUDE         '../data/INDUSTRY_DH_VAR_T.inc';
$if not EXIST '../data/INDUSTRY_DH_VAR_T.inc' $INCLUDE '../../base/data/INDUSTRY_DH_VAR_T.inc';

$if     EXIST '../data/INDUSTRY_AGKN.inc' $INCLUDE         '../data/INDUSTRY_AGKN.inc';
$if not EXIST '../data/INDUSTRY_AGKN.inc' $INCLUDE '../../base/data/INDUSTRY_AGKN.inc';
$offmulti
