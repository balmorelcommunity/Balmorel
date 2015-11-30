PARAMETER DH2(YYY,RRR)  'Yearly demand for hydrogen from the transport sector'   %semislash%
$if     EXIST '../addons/Hydrogen/DH2.inc' $INCLUDE         '../addons/Hydrogen/DH2.inc';
$if not EXIST '../addons/Hydrogen/DH2.inc' $INCLUDE '../../base/addons/Hydrogen/DH2.inc';
%semislash%;


PARAMETER DH2_VAR_T(RRR,SSS,TTT) 'Variation profile of H2 demand per region'  %semislash%
$if     EXIST '../addons/Hydrogen/DH2_VAR_T.inc' $INCLUDE         '../addons/Hydrogen/DH2_VAR_T.inc';
$if not EXIST '../addons/Hydrogen/DH2_VAR_T.inc' $INCLUDE '../../base/addons/Hydrogen/DH2_VAR_T.inc';
%semislash%;


PARAMETER IDH2_SUMST(RRR) 'Variation profile of H2 demand per region' ;


PARAMETER IDH2_T_Y(RRR,SSS,TTT)  'Variation of H2 demand in each region along the year';


PARAMETER H2STOVOL_START(Y,AAA,G,SSS)    'Start level of hydrogen storage';
* Include start filling level of hydrogen storage obtained from yearly simulation
$ifi %bb3%==yes execute_load '../../base/addons/Hydrogen/H2STOVOL_START.gdx', H2STOVOL_START;

