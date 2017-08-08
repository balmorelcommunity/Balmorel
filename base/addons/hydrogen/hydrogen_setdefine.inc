SET HYDROGEN_GGG(GGG)  'All hydrogen technologies'   %semislash%
$if     EXIST '../data/HYDROGEN_GGG.inc' $INCLUDE         '../data/HYDROGEN_GGG.inc';
$if not EXIST '../data/HYDROGEN_GGG.inc' $INCLUDE '../../base/data/HYDROGEN_GGG.inc';
%semislash%;
