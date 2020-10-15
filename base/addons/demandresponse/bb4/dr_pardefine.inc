$if     EXIST '../data/DR_DATAINPUT.inc' $INCLUDE         '../data/DR_DATAINPUT.inc';
$if not EXIST '../data/DR_DATAINPUT.inc' $INCLUDE '../../base/data/DR_DATAINPUT.inc';
%semislash%;

PARAMETER DR_ACCUMNET(YYY,AAA,DR_TECH) 'Resulting capacity of Demand response technologies';
$ifi %import_results%==YES $ifi %ADDTECHDEV%==yes  execute_load  '../../simex/DR_ACCUMNET.gdx', DR_ACCUMNET;    