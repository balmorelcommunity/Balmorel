PARAMETER DC_GDHE(GGG)      'Heat consumption of chiller technologies (MWt-hot/MWt-cold)'
$if     EXIST '../data/DATACENTERS_GDHE.inc' $INCLUDE         '../data/DATACENTERS_GDHE.inc';
$if not EXIST '../data/DATACENTERS_GDHE.inc' $INCLUDE '../../base/data/DATACENTERS_GDHE.inc';

PARAMETER DC_FREECOOLING_POTENTIAL(SSS,TTT,AAA,DHUSER)      'When free cooling is available, this value multiplies cooling demand by 0'
$if     EXIST '../data/DATACENTERS_GDHE.inc' $INCLUDE         '../data/DATACENTERS_FREECOOLING_POTENTIAL.inc';
$if not EXIST '../data/DATACENTERS_GDHE.inc' $INCLUDE '../../base/data/DATACENTERS_FREECOOLING_POTENTIAL.inc';
