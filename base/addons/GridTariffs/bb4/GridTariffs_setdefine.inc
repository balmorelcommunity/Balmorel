SET MMM 'Month' %semislash%
$if     EXIST '../data/MMM.INC' $INCLUDE         '../data/MMM.INC';
$if not EXIST '../data/MMM.INC' $INCLUDE '../../base/data/MMM.INC';

SET GRDATASET            'Grid rent data'   %semislash%
$if     EXIST '../data/GRDATASET.inc' $INCLUDE         '../data/GRDATASET.inc';
$if not EXIST '../data/GRDATASET.inc' $INCLUDE '../../base/data/GRDATASET.inc';
