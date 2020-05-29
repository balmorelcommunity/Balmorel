PARAMETER SOCIOTARIFF_ALL(YYY,CCC,FFF) 'Socio-economic grid tariffs for all sectors in base model' %semislash%
$if     EXIST '../data/SOCIOTARIFF_ALL.inc' $INCLUDE         '../data/SOCIOTARIFF_ALL.inc';
$if not EXIST '../data/SOCIOTARIFF_ALL.inc' $INCLUDE '../../base/data/SOCIOTARIFF_ALL.inc';
%semislash%

$ifi not %INDHEAT%==yes $goto endINDHEAT
PARAMETER SOCIOTARIFF_INDHEAT(YYY,CCC,FFF) 'Socio-economic grid tariffs for INDHEAT' %semislash%
$if     EXIST '../data/SOCIOTARIFF_INDHEAT.inc' $INCLUDE         '../data/SOCIOTARIFF_INDHEAT.inc';
$if not EXIST '../data/SOCIOTARIFF_INDHEAT.inc' $INCLUDE '../../base/data/SOCIOTARIFF_INDHEAT.inc';
%semislash%
$label endINDHEAT