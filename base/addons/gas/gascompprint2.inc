* File gascompprint2.inc.
* This file is an extension to the welfare calculation module for the Balmorel model.
* Created by Jens Hauch and Thomas E. Pedersen, COWI A/S (DK).
* Adapted for Balmorel version 2.10, 2.13 by Hans Ravn.
* Extended to for the gas add-on by Lars Bregnbæk, X-mas 2006.



*===============================================================================
*                Overview
*===============================================================================

* This file contains
* data
* declarations of internal parameters.

* Data:
*    scalar irt Interest rate;
*    parameter tlifetime Life time for transmission capacity - years;


* Comments on terminology:
* p: prices
* e: electricity (pe: electricity price)
* h: heat
* psur: producers surplus
* earnings: producers surplus (at national level - so the terminology seems slightly inconsistent)
* cw: consumers welfare (cwe: electricity, cwh: heat)
* dc: discounted
* dlt, delta: difference

* Note that internal parameters do not obey to the conventions that their name should start with 'I'.



*===============================================================================
*                Overview end
*===============================================================================

PARAMETERS
         residualcosts(Y,C)      'Gas costs for residual consumers (Input currency)'
         residualcosts00(Y,C)    'Gas costs for residual consumers (Input currency)'
         dresidualbenifit(C)     'Discounted welfare change for residual consumers (Input currency)'

         othercosts(Y,C)         'Gas costs for other consumers (Input currency)'
         othercosts00(Y,C)       'Gas costs for other consumers (Input currency)'
         dotherbenifit(C)        'Discounted welfare change for residual consumers (Input currency)'

         DSOrevenue(Y,C)         'Revenue for distribution companies'
         DSOcosts(Y,C)
         DSOprofit(Y,C)          'Profits for distribution companies (Input currency)'
         DSOprofit00(Y,C)        'Profits for distribution companies (Input currency)'
         dcdltDSOprofit(C)       'Discounted welfare change for distribution companies (Input currency)'

         TSOCAPrev(Y,C)          'TSO Revenue from capacity products'
         TSOCAPrev00(Y,C)        'TSO Revenue from capacity products'
         dcdltTSOCAPrevbenefit(C)     'Discounted welfare change in TSO from Capacity products (Input currency)'

         TSOVOLrev(Y,C)          'TSO volumetric revenue'
         TSOVOLrev00(Y,C)        'TSO volumetric revenue'
         dcdltTSOVOLrevbenefit(C)    'Discounted welfare change in TSO from Volumetic tariffs (Input currency)'

         TSOCAPRent(Y,C)         'TSO Capacity rent'
         TSOCAPRent00(Y,C)       'TSO Capacity rent'
         dcdltTSOCAPRentbenefit(C)   'Discounted welfare change in TSO Capacity rent (Input currency)'

         TSOfixedcosts(Y,C)
         TSOfixedcosts00(Y,C)
         TSOvariablecosts(Y,C)
         TSOvariablecosts00(Y,C)
         TSOprofit(Y,C)
         TSOprofit00(Y,C)

         dcdltTSOProfit(C)       'Discounted welfare change in TSO profit (Input currency)'

         SSOCAPrev(Y,C)          'SSO Capacity revenue'
         SSOCAPrev00(Y,C)        'SSO Capacity revenue'
         dcdltSSOCAPrevbenefit(C)    'Discounted welfare change in SSO Capacity revenue (Input currency)'

         SSOVOLrev(Y,C)          'SSO volumetric revenue'
         SSOVOLrev00(Y,C)        'SSO volumetric revenue'
         dcdltSSOVOLrevbenefit(C)    'Discounted welfare change in SSO volumetric revenue (Input currency)'

         SSOCAPrent(Y,C)         'SSO Capacity rent'
         SSOCAPrent00(Y,C)       'SSO Capacity rent'
         dcdltSSOCAPrentbenefit(C)   'Discountred welfare change in SSO Capacity rent (Input currency)'

         SSOfixedcosts(Y,C)
         SSOvariablecosts(Y,C)

         SSOprofit(Y,C)
         SSOprofit00(Y,C)
         dcdltSSOProfit(C)       'Discounted welfare change in SSO profits (Input currency)'

         GasSupplierCosts(Y,C)
         GasSupplierRevenue(Y,C)
         GasSupplierProfit(Y,C)
         GasSupplierProfit00(Y,C)
         dcdltGasSupplierProfit(C) 'Discounted welfare change for gas suppliers (Input currency)'

         GasShipperCosts(Y,C)
         GasShipperRevenue(Y,C)
         GasShipperProfit(Y,C)
         GasShipperProfit00(Y,C)
         dcdltGasShipperProfit(C)  'Discounted welfare change for gas shippers (Input currency)'

         GasProducerCosts(Y,C)
         GasProducerRevenue(Y,C)
         GasProducerProfit(Y,C)
         GasProducerProfit00(Y,C)
         dcdltGasProducerProfit(C) 'Discounted welfare change for gas shippers (Input currency)'

         GasStorageUserCost(Y,C)
         GasStorageUserRevenue(Y,C)
         GasStorageUserProfit(Y,C)
         GasStorageUserProfit00(Y,C)
         dcdltGasStorageUserProfit(C)

         ShipperCapRent(Y,C)
         ShipperCapRent00(Y,C)
         dcdltShipperCapRent(C)
;