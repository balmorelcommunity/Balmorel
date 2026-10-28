$if     EXIST '../data/DR_DATAINPUT.inc' $INCLUDE         '../data/DR_DATAINPUT.inc';
$if not EXIST '../data/DR_DATAINPUT.inc' $INCLUDE '../../base/data/DR_DATAINPUT.inc';
%semislash%;

* Exported by the investment run (Balmorelbb4.inc); with import_results it is declared in import_results_pardeclare.inc
$ifi not %import_results%==yes PARAMETER DRKN_ACCUMNET(YYY,AAA,DR_TECHNOLOGIES) 'Accumulated demand response capacity to be used in future runs (MW)';
