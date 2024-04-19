PARAMETER HYDROGEN_DH2(YYY,CCCRRRAAA)  'Yearly demand for hydrogen'   %semislash%
$if     EXIST '../data/HYDROGEN_DH2.inc' $INCLUDE         '../data/HYDROGEN_DH2.inc';
$if not EXIST '../data/HYDROGEN_DH2.inc' $INCLUDE '../../base/data/HYDROGEN_DH2.inc';
%semislash%;

*IK add
PARAMETER HYDROGEN_DH2_SYN(YYY,CCCRRRAAA)  'Yearly demand for hydrogen'   %semislash%
$if     EXIST '../data/HYDROGEN_DH2_SYN.inc' $INCLUDE         '../data/HYDROGEN_DH2_SYN.inc';
$if not EXIST '../data/HYDROGEN_DH2_SYN.inc' $INCLUDE '../../base/data/HYDROGEN_DH2_SYN.inc';
%semislash%;

PARAMETER HYDROGEN_DH2_VAR_T(CCCRRRAAA,SSS,TTT) 'Variation profile of H2 demand per region'  %semislash%
$if     EXIST '../data/HYDROGEN_DH2_VAR_T.inc' $INCLUDE         '../data/HYDROGEN_DH2_VAR_T.inc';
$if not EXIST '../data/HYDROGEN_DH2_VAR_T.inc' $INCLUDE '../../base/data/HYDROGEN_DH2_VAR_T.inc';
%semislash%;

PARAMETER DISLOSS_H2(CCCRRRAAA) 'Distribution loss H2'  %semislash%
$if     EXIST '../data/HYDROGEN_DISLOSS_H2.inc' $INCLUDE         '../data/HYDROGEN_DISLOSS_H2.inc';
$if not EXIST '../data/HYDROGEN_DISLOSS_H2.inc' $INCLUDE '../../base/data/HYDROGEN_DISLOSS_H2.inc';
%semislash%;

PARAMETER HYDROGEN_STOVOL_START(Y,AAA,G,SSS)    'Start level of hydrogen storage';
* Include start filling level of hydrogen storage obtained from yearly simulation
$ifi %bb3%==yes execute_load '../../simex/HYDROGEN_STOVOL_START.gdx', HYDROGEN_STOVOL_START;

PARAMETER HYDROGEN_H2TOF(GGG) 'Hydrogen to fuel factor'  %semislash%
$if     EXIST '../data/HYDROGEN_H2TOF.inc' $INCLUDE         '../data/HYDROGEN_H2TOF.inc';
$if not EXIST '../data/HYDROGEN_H2TOF.inc' $INCLUDE '../../base/data/HYDROGEN_H2TOF.inc';
%semislash%

$onmulti
$if     EXIST '../data/HYDROGEN_DAC_DE.inc' $INCLUDE         '../data/HYDROGEN_DAC_DE.inc';
$if not EXIST '../data/HYDROGEN_DAC_DE.inc' $INCLUDE '../../base/data/HYDROGEN_DAC_DE.inc';

$if     EXIST '../data/HYDROGEN_DAC_DH.inc' $INCLUDE         '../data/HYDROGEN_DAC_DH.inc';
$if not EXIST '../data/HYDROGEN_DAC_DH.inc' $INCLUDE '../../base/data/HYDROGEN_DAC_DH.inc';

$if     EXIST '../data/HYDROGEN_XH2KFX.inc' $INCLUDE         '../data/HYDROGEN_XH2KFX.inc';
$if not EXIST '../data/HYDROGEN_XH2KFX.inc' $INCLUDE '../../base/data/HYDROGEN_XH2KFX.inc';

$if     EXIST '../data/HYDROGEN_XH2INVCOST.inc' $INCLUDE         '../data/HYDROGEN_XH2INVCOST.inc';
$if not EXIST '../data/HYDROGEN_XH2INVCOST.inc' $INCLUDE '../../base/data/HYDROGEN_XH2INVCOST.inc';

$if     EXIST '../data/HYDROGEN_XH2INVCOST_NGTOH2.inc' $INCLUDE         '../data/HYDROGEN_XH2INVCOST_NGTOH2.inc';
$if not EXIST '../data/HYDROGEN_XH2INVCOST_NGTOH2.inc' $INCLUDE '../../base/data/HYDROGEN_XH2INVCOST_NGTOH2.inc';

$if     EXIST '../data/HYDROGEN_XH2COST.inc' $INCLUDE         '../data/HYDROGEN_XH2COST.inc';
$if not EXIST '../data/HYDROGEN_XH2COST.inc' $INCLUDE '../../base/data/HYDROGEN_XH2COST.inc';

$if     EXIST '../data/HYDROGEN_XH2LOSS.inc' $INCLUDE         '../data/HYDROGEN_XH2LOSS.inc';
$if not EXIST '../data/HYDROGEN_XH2LOSS.inc' $INCLUDE '../../base/data/HYDROGEN_XH2LOSS.inc';

$if     EXIST '../data/HYDROGEN_XH2KRATE.inc' $INCLUDE         '../data/HYDROGEN_XH2KRATE.inc';
$if not EXIST '../data/HYDROGEN_XH2KRATE.inc' $INCLUDE '../../base/data/HYDROGEN_XH2KRATE.inc';

$if     EXIST '../data/HYDROGEN_ANNUITYCXH2.inc' $INCLUDE         '../data/HYDROGEN_ANNUITYCXH2.inc';
$if not EXIST '../data/HYDROGEN_ANNUITYCXH2.inc' $INCLUDE '../../base/data/HYDROGEN_ANNUITYCXH2.inc';

$if     EXIST '../data/HYDROGEN_XH2MAXK_NGTOH2.inc' $INCLUDE         '../data/HYDROGEN_XH2MAXK_NGTOH2.inc';
$if not EXIST '../data/HYDROGEN_XH2MAXK_NGTOH2.inc' $INCLUDE '../../base/data/HYDROGEN_XH2MAXK_NGTOH2.inc';

$if     EXIST '../data/HYDROGEN_LIFETIME_XH2.inc' $INCLUDE         '../data/HYDROGEN_LIFETIME_XH2.inc';
$if not EXIST '../data/HYDROGEN_LIFETIME_XH2.inc' $INCLUDE '../../base/data/HYDROGEN_LIFETIME_XH2.inc';
$offmulti

$if     EXIST '../data/HYDROGEN_XH2INVCOST_ES.inc' $INCLUDE         '../data/HYDROGEN_XH2INVCOST_ES.inc';
$if not EXIST '../data/HYDROGEN_XH2INVCOST_ES.inc' $INCLUDE '../../base/data/HYDROGEN_XH2INVCOST_ES.inc';

$if     EXIST '../data/HYDROGEN_XH2KN_ES.inc' $INCLUDE         '../data/HYDROGEN_XH2KN_ES.inc';
$if not EXIST '../data/HYDROGEN_XH2KN_ES.inc' $INCLUDE '../../base/data/HYDROGEN_XH2KN_ES.inc';


