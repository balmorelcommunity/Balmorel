* File heattrans_balbase4.inc for the Balmorel model. For use with addon heattrans.
* Latest revision 20180922(hr)

* Include the following equations in model Balbase4



$ifi %HeatTransInvest%==yes QXHK_UP
$ifi %HeatTransInvest%==yes QXHKNACCUMNET
$ifi %HeatTransInvest%==yes QXHINVSYMMETRY
$ifi %HeatTransInvest%==yes QXHKMAX
*QXHKNACCUMGROSS

*$ontext
*to be checked
QXHGETOH
*$offtext
