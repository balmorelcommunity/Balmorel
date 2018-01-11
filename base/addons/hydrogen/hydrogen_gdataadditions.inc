PARAMETER HYDROGEN_GDATA(HYDROGEN_GGG,GDATASET)  'Hydrogen technologies characteristics'   %semislash%
$if     EXIST '../data/HYDROGEN_GDATA.inc' $INCLUDE         '../data/HYDROGEN_GDATA.inc';
$if not EXIST '../data/HYDROGEN_GDATA.inc' $INCLUDE '../../base/data/HYDROGEN_GDATA.inc';
%semislash%;

* Make HYDROGEN_GDATA part of GDATA:
GDATA(HYDROGEN_GGG,GDATASET)= HYDROGEN_GDATA(HYDROGEN_GGG,GDATASET);
