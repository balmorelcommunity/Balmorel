* Equations for addon import results used in seasonal rolling horizon model definition
* Latest revision 20200720 (jgb)


$ifi %HYRSBB123%==cont  QWATERVOLINI
$ifi %HYRSBB123%==price  QHYRSSEQCURT
$ifi %ADDESTOVOLTS%==cont  QESTOVOLTSIMPORT
$ifi %ADDHSTOVOLTS%==cont  QHSTOVOLTSIMPORT
$ifi %ADDESTOVOLT%==cont  QESTOVOLTIMPORT
$ifi %ADDHSTOVOLT%==cont  QHSTOVOLTIMPORT

$ifi %HYDROGEN%==yes $ifi %ADDH2STOVOLTS%==cont QH2STOVOLTSIMPORT
$ifi %HYDROGEN%==yes $ifi %ADDBIOMETHSTOVOLTS%==cont QBIOMETHSTOVOLTSIMPORT


