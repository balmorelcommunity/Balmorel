* Equations for addon hyrsbb123 used in Balbase3 model definition
* Latest revision 20170419 (hr)

$ifi %HYRSBB123%==none    $goto label_no_hydro_results_import

$ifi not %HYRSBB123%==price  QWATERVOLINI

$ontext
$ifi %HYRSBB123%==quant        QHYRSG
$ifi %HYRSBB123%==quantprice   QHYRSG
$ifi %HYRSBB123%==quantprice   QWATERVOLINI
$offtext


$label label_no_hydro_results_import

$ifi %ADDELECSTORCONT%==yes  QVESTOVOLTS
$ifi %ADDHEATSTORCONT%==yes  QVHSTOVOLTS