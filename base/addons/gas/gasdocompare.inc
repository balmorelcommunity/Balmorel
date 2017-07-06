* File gasdocompare.INC.
* This file is part of the welfare calculation module for the Balmorel model.
* Created by Jens Hauch and Thomas E. Pedersen, COWI A/S (DK).
* Adapted for Balmorel version 2.10, 2.13 by Hans Ravn.
* Extended to for the gas add-on by Lars Bregnbæk, X-mas 2006.

* mangler: Base er næsten hårdkodet (men som det ses, er der mulighed for at vælge et andet base !)
* i welfare.inc ses, at der ikke er  mellemvariabler for trans - ...

*===============================================================================
*                Overview
*===============================================================================

* This file contains:

* calculation of differences between cases
* discounting of welfare changes for groups



*===============================================================================
*                Overview end
*===============================================================================

*===============================================================================
*                Gas Consumers
*===============================================================================

* Residual consumers (discounted welfare gains for consumers)
dresidualbenifit(C) = Sum(Y, -(residualcosts(Y,C)-residualcosts00(Y,C))/(1+diskrate)**(ord(y)-1))/IOF1000000;

* Other consumers (discounted welfare gains for consumers)
dotherbenifit(C) = Sum(Y, -(othercosts(Y,C)-othercosts00(Y,C))/(1+diskrate)**(ord(y)-1))/IOF1000000;


*===============================================================================
*                Distribution Companies
*===============================================================================


dcdltDSOprofit(C) = Sum(Y, (DSOprofit(Y,C)-DSOprofit00(Y,C))/(1+diskrate)**(ord(y)-1))/IOF1000000;


*===============================================================================
*                TSO
*===============================================================================

dcdltTSOVOLrevbenefit(C) = Sum(Y, (TSOVOLrev(Y,C)-TSOVOLrev00(Y,C))/(1+diskrate)**(ord(y)-1))/IOF1000000;

dcdltTSOCAPrevbenefit(C) = Sum(Y, (TSOCAPrev(Y,C)-TSOCAPrev00(Y,C))/(1+diskrate)**(ord(y)-1))/IOF1000000;

dcdltTSOCAPRentbenefit(C) = Sum(Y, (TSOCAPRent(Y,C)-TSOCAPRent00(Y,C))/(1+diskrate)**(ord(y)-1))/IOF1000000;

dcdltTSOProfit(C) = Sum(Y, (TSOProfit(Y,C) - TSOProfit00(Y,C))/(1+diskrate)**(ord(y)-1))/IOF1000000;

*===============================================================================
*                SSO
*===============================================================================

dcdltSSOCAPrevbenefit(C) = Sum(Y, (SSOCAPrev(Y,C)-SSOCAPrev00(Y,C))/(1+diskrate)**(ord(y)-1))/IOF1000000;


dcdltSSOVOLrevbenefit(C) = Sum(Y, (SSOVOLrev(Y,C)-SSOVOLrev00(Y,C))/(1+diskrate)**(ord(y)-1))/IOF1000000;


dcdltSSOCAPrentbenefit(C) = Sum(Y, (SSOCAPrent(Y,C)-SSOCAPrent00(Y,C))/(1+diskrate)**(ord(y)-1))/IOF1000000;


dcdltSSOProfit(C) = Sum(Y, (SSOProfit(Y,C) - SSOProfit00(Y,C))/(1+diskrate)**(ord(y)-1))/IOF1000000;


*===============================================================================
*                Producers
*===============================================================================

dcdltGasProducerProfit(C) = Sum(Y,(GasProducerProfit(Y,C) - GasProducerProfit00(Y,C))/(1+diskrate)**(ord(y)-1))/IOF1000000;

*===============================================================================
*                Suppliers
*===============================================================================

dcdltGasSupplierProfit(C) = Sum(Y, (GasSupplierProfit(Y,C)-GasSupplierProfit00(Y,C))/(1+diskrate)**(ord(y)-1))/IOF1000000;

*===============================================================================
*                Shippers
*===============================================================================

dcdltGasShipperProfit(C) = Sum(Y, (GasShipperProfit(Y,C) - GasShipperProfit00(Y,C))/(1+diskrate)**(ord(y)-1))/IOF1000000;

dcdltShipperCapRent(C) = Sum(Y, (ShipperCapRent(Y,C) - ShipperCapRent00(Y,C))/(1+diskrate)**(ord(y)-1))/IOF1000000;    

*===============================================================================
*                Gas Storage User
*===============================================================================

dcdltGasStorageUserProfit(C) = Sum(Y, (GasStorageUserProfit(Y,C) - GasStorageUserProfit00(Y,C))/(1+diskrate)**(ord(y)-1))/IOF1000000;
