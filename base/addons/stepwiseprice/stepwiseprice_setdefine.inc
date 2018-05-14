SET STEPWISEPRICE_L 'The line segments of which the stepwise fuel prices are defined'
$if     EXIST '../data/STEPWISEPRICE_L.inc' $INCLUDE         '../data/STEPWISEPRICE_L.inc';
$if not EXIST '../data/STEPWISEPRICE_L.inc' $INCLUDE '../../base/data/STEPWISEPRICE_L.inc';

SET STEPWISEPRICE_FFF(FFF) 'Fuels of which there is a stepwise fuel price'
$if     EXIST '../data/STEPWISEPRICE_L.inc' $INCLUDE         '../data/STEPWISEPRICE_FFF.inc';
$if not EXIST '../data/STEPWISEPRICE_L.inc' $INCLUDE '../../base/data/STEPWISEPRICE_FFF.inc';