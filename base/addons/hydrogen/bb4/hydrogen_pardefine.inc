PARAMETER HYDROGEN_DH2(YYY,CCCRRRAAA)  'Yearly demand for hydrogen from the transport sector'   %semislash%
$if     EXIST '../data/HYDROGEN_DH2.inc' $INCLUDE         '../data/HYDROGEN_DH2.inc';
$if not EXIST '../data/HYDROGEN_DH2.inc' $INCLUDE '../../base/data/HYDROGEN_DH2.inc';
%semislash%;

PARAMETER HYDROGEN_DH2_VAR_T(CCCRRRAAA,SSS,TTT) 'Variation profile of H2 demand per region'  %semislash%
$if     EXIST '../data/HYDROGEN_DH2_VAR_T.inc' $INCLUDE         '../data/HYDROGEN_DH2_VAR_T.inc';
$if not EXIST '../data/HYDROGEN_DH2_VAR_T.inc' $INCLUDE '../../base/data/HYDROGEN_DH2_VAR_T.inc';
%semislash%;

PARAMETER HYDROGEN_STOVOL_START(Y,AAA,G,SSS)    'Start level of hydrogen storage';
* Include start filling level of hydrogen storage obtained from yearly simulation
$ifi %bb3%==yes execute_load '../../simex/HYDROGEN_STOVOL_START.gdx', HYDROGEN_STOVOL_START;

PARAMETER HYDROGEN_H2TOF(GGG) 'Hydrogen to fuel factor'  %semislash%
$if     EXIST '../data/HYDROGEN_H2TOF.inc' $INCLUDE         '../data/HYDROGEN_H2TOF.inc';
$if not EXIST '../data/HYDROGEN_H2TOF.inc' $INCLUDE '../../base/data/HYDROGEN_H2TOF.inc';
%semislash%

$onmulti
$if     EXIST '../data/HYDROGEN_AGKN.inc' $INCLUDE         '../data/HYDROGEN_AGKN.inc';
$if not EXIST '../data/HYDROGEN_AGKN.inc' $INCLUDE '../../base/data/HYDROGEN_AGKN.inc';

$if     EXIST '../data/HYDROGEN_FDATA.inc' $INCLUDE         '../data/HYDROGEN_FDATA.inc';
$if not EXIST '../data/HYDROGEN_FDATA.inc' $INCLUDE '../../base/data/HYDROGEN_FDATA.inc';

$if     EXIST '../data/HYDROGEN_FUELPRICE.inc' $INCLUDE         '../data/HYDROGEN_FUELPRICE.inc';
$if not EXIST '../data/HYDROGEN_FUELPRICE.inc' $INCLUDE '../../base/data/HYDROGEN_FUELPRICE.inc';

$if     EXIST '../data/HYDROGEN_FUELPRICE.inc' $INCLUDE         '../data/HYDROGEN_GKFX.inc';
$if not EXIST '../data/HYDROGEN_FUELPRICE.inc' $INCLUDE '../../base/data/HYDROGEN_GKFX.inc';
$offmulti
