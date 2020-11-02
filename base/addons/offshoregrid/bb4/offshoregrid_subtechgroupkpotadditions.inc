*Offshore grid add-on. Implemented by Juan Gea Bermudez 2019


$onmulti
$if     EXIST '../data/OFFSHOREGRID_SUBTECHGROUPKPOT.inc' $INCLUDE         '../data/OFFSHOREGRID_SUBTECHGROUPKPOT.inc';
$if not EXIST '../data/OFFSHOREGRID_SUBTECHGROUPKPOT.inc' $INCLUDE '../../base/data/OFFSHOREGRID_SUBTECHGROUPKPOT.inc';
$offmulti