$if     EXIST '../data/FIXEDDEMAND_DE.inc' $INCLUDE         '../data/FIXEDDEMAND_DE.inc';
$if not EXIST '../data/FIXEDDEMAND_DE.inc' $INCLUDE '../../base/data/FIXEDDEMAND_DE.inc';
