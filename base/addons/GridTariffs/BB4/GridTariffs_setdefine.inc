SET MMM 'Month' %semislash%
$if     EXIST '../data/MMM.INC' $INCLUDE         '../data/MMM.inc';
$if not EXIST '../data/MMM.INC' $INCLUDE '../../base/data/MMM.inc';

SET GRDATASET            'Grid rent data'   %semislash%
$if     EXIST '../data/GRDATASET.inc' $INCLUDE         '../data/GRDATASET.inc';
$if not EXIST '../data/GRDATASET.inc' $INCLUDE '../../base/data/GRDATASET.inc';
