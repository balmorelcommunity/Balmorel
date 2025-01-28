$ifi not %HYDROGEN%==YES $ifi not %h2_transmission_definition%==area $goto AREA_TRANSMISSION
$if not declared IAAAE  ALIAS (AAA,IAAAE);
$if not declared IAAAI  ALIAS (AAA,IAAAI);

$if not declared IAE    ALIAS(IA,IAE);
$if not declared IAI    ALIAS(IA,IAI);
$label AREA_TRANSMISSION
