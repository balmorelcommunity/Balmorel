* File heattrans_setdeclare.inc for addon heattrans
* Latest revision 20181014(hr)

$if not declared IAAAE  ALIAS (AAA,IAAAE);
$if not declared IAAAI  ALIAS (AAA,IAAAI);

$if not declared IAE    ALIAS(IA,IAE);
$if not declared IAI    ALIAS(IA,IAI);

$ontext
*to be checked
* In case of temperature lift by heat pump:

SET XHGETOH(GGG) "Heat pumps used for lifting temperature for heat transmitted between two Areas";

SET XHTEMPLIFT(IAAAE,IAAAI) "Pair of areas for which temperature lift necessary";
$offtext