PARAMETER SUBSIDIES_F_EL(YYY,CCC,GGG) %semislash%
$if     EXIST '../data/SUBSIDIES_F_EL.inc' $INCLUDE         '../data/SUBSIDIES_F_EL.inc';
$if not EXIST '../data/SUBSIDIES_F_EL.inc' $INCLUDE '../../base/data/SUBSIDIES_F_EL.inc';
%semislash%

PARAMETER SUBSIDIES_F_HEAT(YYY,CCC,GGG) %semislash%
$if     EXIST '../data/SUBSIDIES_F_HEAT.inc' $INCLUDE         '../data/SUBSIDIES_F_HEAT.inc';
$if not EXIST '../data/SUBSIDIES_F_HEAT.inc' $INCLUDE '../../base/data/SUBSIDIES_F_HEAT.inc';
%semislash%

PARAMETER SUBSIDIES_F(YYY,CCC,GGG) %semislash%
$if     EXIST '../data/SUBSIDIES_F.inc' $INCLUDE         '../data/SUBSIDIES_F.inc';
$if not EXIST '../data/SUBSIDIES_F.inc' $INCLUDE '../../base/data/SUBSIDIES_F.inc';
%semislash%

PARAMETER SUBSIDIES_G_HEAT(YYY,CCC,GGG) %semislash%
$if     EXIST '../data/SUBSIDIES_G_HEAT.inc' $INCLUDE         '../data/SUBSIDIES_G_HEAT.inc';
$if not EXIST '../data/SUBSIDIES_G_HEAT.inc' $INCLUDE '../../base/data/SUBSIDIES_G_HEAT.inc';
%semislash%

PARAMETER SUBSIDIES_G_EL(YYY,CCC,GGG) %semislash%
$if     EXIST '../data/SUBSIDIES_G_EL.inc' $INCLUDE         '../data/SUBSIDIES_G_EL.inc';
$if not EXIST '../data/SUBSIDIES_G_EL.inc' $INCLUDE '../../base/data/SUBSIDIES_G_EL.inc';
%semislash%

PARAMETER SUBSIDIES_DE(CCC,DEUSER) %semislash%
$if     EXIST '../data/SUBSIDIES_DE.inc' $INCLUDE         '../data/SUBSIDIES_DE.inc';
$if not EXIST '../data/SUBSIDIES_DE.inc' $INCLUDE '../../base/data/SUBSIDIES_DE.inc';
%semislash%

PARAMETER SUBSIDIES_DH(CCC,DHUSER) %semislash%
$if     EXIST '../data/SUBSIDIES_DH.inc' $INCLUDE         '../data/SUBSIDIES_DH.inc';
$if not EXIST '../data/SUBSIDIES_DH.inc' $INCLUDE '../../base/data/SUBSIDIES_DH.inc';
%semislash%

