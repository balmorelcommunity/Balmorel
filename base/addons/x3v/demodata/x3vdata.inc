* LARS: Flyttet fra balmorel.gms
$INCLUDE '../../base/addons/x3v/data/x3vpim.inc';
* This file contains:
* PARAMETER X3VPIM "Price (Money/MWh) of price dependent imported electricity";
$INCLUDE '../../base/addons/x3v/data/x3vpex.inc';
* This file contains:
* PARAMETER X3VPEX "Price (Money/MWh) of price dependent exported electricity"

* LARS: Nyt
$ifi %X3VfxQ%==yes PARAMETER X3VBAL(YYY,X3VPLACE0) 'Annual net-exports to third countries w. price profile MWh/year';

* Net exports assumed to be zero based on the assumption that competetative investments ensure
* long run equilibrium prices.
* LARS: Nogen skulle måske fylde de historiske exportmænger til verifikations formål?
$ifi %X3VfxQ%==yes X3VBAL(YYY,X3VPLACE0)=20000;

* Shadow price of balancing imports and exports according to annual values.
PARAMETER X3VBALSP(YYY,X3VPLACE0);
* Get shadow price of the annual balance constriant.
$ifi %X3VfxP%==yes execute_load '../../base/addons/x3v/data/X3V_%X3VPRICECASE%_BALSP.gdx',X3VBALSP;