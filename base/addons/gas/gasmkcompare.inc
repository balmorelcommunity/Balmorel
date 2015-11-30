* File gasmkcompare.inc.
* This file is an extension to the welfare calculation module for the Balmorel model.
* Created by Jens Hauch and Thomas E. Pedersen, COWI A/S (DK).
* Adapted for Balmorel version 2.10, 2.13 by Hans Ravn.
* Extended to for the gas add-on by Lars Bregnbæk, X-mas 2006.


*===============================================================================
*                Overview
*===============================================================================

* Intermediate parameter values are printed to files for later use.
* The parameter values were calculated in gascompprint3.inc, as ..,..,.., etc.
* They are here saved under names ...00, ...00, ...00, etc.

*===============================================================================
*                Overview end
*===============================================================================

*===============================================================================
*                Consumers
*===============================================================================

$libinclude gams2prm residualcosts residualcosts00
$libinclude gams2prm othercosts othercosts00

*===============================================================================
*                Distribution companies
*===============================================================================

$libinclude gams2prm DSOprofit DSOprofit00

*===============================================================================
*                TSO
*===============================================================================

$libinclude gams2prm TSOCAPrev TSOCAPrev00
$libinclude gams2prm TSOVOLrev TSOVOLrev00
$libinclude gams2prm TSOCAPRent TSOCAPRent00
$libinclude gams2prm TSOprofit TSOprofit00


*===============================================================================
*                SSO
*===============================================================================

$libinclude gams2prm SSOCAPrev SSOCAPrev00
$libinclude gams2prm SSOVOLrev SSOVOLrev00
$libinclude gams2prm SSOCAPrent SSOCAPrent00
$libinclude gams2prm SSOProfit SSOProfit00

*===============================================================================
*                Producers
*===============================================================================

$libinclude gams2prm GasProducerProfit GasProducerProfit00

*===============================================================================
*                Suppliers
*===============================================================================

$libinclude gams2prm GasSupplierProfit GasSupplierProfit00

*===============================================================================
*                Shippers
*===============================================================================

$libinclude gams2prm GasShipperProfit GasShipperProfit00
$libinclude gams2prm ShipperCapRent ShipperCapRent00


*===============================================================================
*                Gas Storage Customers
*===============================================================================

$libinclude gams2prm GasStorageUserProfit GasStorageUserProfit00