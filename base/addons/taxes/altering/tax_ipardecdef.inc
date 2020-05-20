PARAMETER TAX_F_EL(YYY,CCC,GGG) %semislash%
$if     EXIST '../data/TAX_F_EL.inc' $INCLUDE         '../data/TAX_F_EL.inc';
$if not EXIST '../data/TAX_F_EL.inc' $INCLUDE '../../base/data/TAX_F_EL.inc';

PARAMETER TAX_F_HEAT(YYY,CCC,GGG) %semislash%
$if     EXIST '../data/TAX_F_HEAT.inc' $INCLUDE         '../data/TAX_F_HEAT.inc';
$if not EXIST '../data/TAX_F_HEAT.inc' $INCLUDE '../../base/data/TAX_F_HEAT.inc';

PARAMETER TAX_F(YYY,CCC,GGG) %semislash%
$if     EXIST '../data/TAX_F.inc' $INCLUDE         '../data/TAX_F.inc';
$if not EXIST '../data/TAX_F.inc' $INCLUDE '../../base/data/TAX_F.inc';

PARAMETER TAX_G_HEAT(YYY,CCC,GGG) %semislash%
$if     EXIST '../data/TAX_G_HEAT.inc' $INCLUDE         '../data/TAX_G_HEAT.inc';
$if not EXIST '../data/TAX_G_HEAT.inc' $INCLUDE '../../base/data/TAX_G_HEAT.inc';

PARAMETER TAX_G_EL(YYY,CCC,GGG) %semislash%
$if     EXIST '../data/TAX_G_EL.inc' $INCLUDE         '../data/TAX_G_EL.inc';
$if not EXIST '../data/TAX_G_EL.inc' $INCLUDE '../../base/data/TAX_G_EL.inc';

PARAMETER TAX_DE(CCC,DEUSER) %semislash%
$if     EXIST '../data/TAX_DE.inc' $INCLUDE         '../data/TAX_DE.inc';
$if not EXIST '../data/TAX_DE.inc' $INCLUDE '../../base/data/TAX_DE.inc';

PARAMETER TAX_DH(CCC,DHUSER) %semislash%
$if     EXIST '../data/TAX_DH.inc' $INCLUDE         '../data/TAX_DH.inc';
$if not EXIST '../data/TAX_DH.inc' $INCLUDE '../../base/data/TAX_DH.inc';

