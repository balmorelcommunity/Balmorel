SET gasanvendelser "FROM MDB2GMS" /
'Centralt kraftværk'
'Andre timeaflæste'
'Decentral kraftvarme'
'Decentral ren varmeproduktion'
Fjernvarmekedeler
'Industriel andet formål'
'Industriel kraftvarme'
residual
/;

PARAMETER DG_HNG_VAR(gasanvendelser,SSS,TTT),
          DG_MidtNord_VAR(gasanvendelser,SSS,TTT),
          DG_DongOest_VAR(gasanvendelser,SSS,TTT),
          DG_DongVest_VAR(gasanvendelser,SSS,TTT),
          DG_NGF_VAR(gasanvendelser,SSS,TTT);

execute_load '../../base/addons/gas/gasforbrug.gdx', DG_HNG_VAR,DG_MidtNord_VAR, DG_DongOest_VAR, DG_DongVest_VAR,  DG_NGF_VAR;


PARAMETER DG_VAR(gasanvendelser,AAA,SSS,TTT)
/
$ondelim
$include '../../base/addons/gas/gasforbrug.csv';
$offdelim
/;