* File heattrans_setdeclare.inc for addon heattrans
* Latest revision 20181014(hr)

$if not declared IAAAE  ALIAS (AAA,IAAAE);
$if not declared IAAAI  ALIAS (AAA,IAAAI);

$if not declared IAE    ALIAS(IA,IAE);
$if not declared IAI    ALIAS(IA,IAI);



SET XHKN(IAAAE,IAAAI) 'Pair of areas that may get new heat transmission capacity';

* Transmission capacity (MW) between areas IAE (exporting) and  IAI (importing)
* at the beginning of current simulation year:
PARAMETER XHKFX(YYY,IAAAE,IAAAI) 'Heat transmission capacity between regions at beginning of year (MW)';


SET IXHK_HASORPOT(Y,IAAAE,IAAAI)  "Heat transmission lines with existing or potentially invested capacity current year";

SET XHTEMPLIFT(IAAAE,IAAAI) "Pair of areas for which temperature lift necessary";


* In case of temperature lift by heat pump:

SET XHGETOH(GGG) "Heat pumps used for lifting temperature for heat transmitted between two Areas";
