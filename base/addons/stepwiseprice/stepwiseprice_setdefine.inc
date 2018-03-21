SET STEPWISEPRICE_L 'The line segments of which the stepwise fuel prices are defined'
$if     EXIST '../data/STEPWISEPRICE_L.inc' $INCLUDE         '../data/STEPWISEPRICE_L.inc';
$if not EXIST '../data/STEPWISEPRICE_L.inc' $INCLUDE '../../base/data/STEPWISEPRICE_L.inc';