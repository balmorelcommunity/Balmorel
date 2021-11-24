PARAMETER DC_GDHE(GGG)      'Heat consumption of chiller technologies (MWt-hot/MWt-cold)'
$if     EXIST '../data/DATACENTERS_GDHE.inc' $INCLUDE         '../data/DATACENTERS_GDHE.inc';
$if not EXIST '../data/DATACENTERS_GDHE.inc' $INCLUDE '../../base/data/DATACENTERS_GDHE.inc';
