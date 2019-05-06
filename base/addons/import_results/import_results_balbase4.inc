* Equations for addon hyrsbb123 used in Balbase3 model definition
* Latest revision 20170419 (hr)

$ifi %HYRSBB123%==none    $goto label_no_hydro_results_import

$ifi %HYRSBB123%==contprice  QWATERVOLINI

$label label_no_hydro_results_import

$ifi %ADDELECSTORCONT%==yes  QESTOVOLTSIMPORT
$ifi %ADDHEATSTORCONT%==yes  QHSTOVOLTSIMPORT

