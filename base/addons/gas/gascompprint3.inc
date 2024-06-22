* File gascompprint2.inc.
* This file is an extension to the welfare calculation module for the Balmorel model.
* Created by Jens Hauch and Thomas E. Pedersen, COWI A/S (DK).
* Adapted for Balmorel version 2.10, 2.13 by Hans Ravn.
* Extended to for the gas add-on by Lars Bregnbæk, X-mas 2006.


*===============================================================================
*                Overview
*===============================================================================

* This file contains calculation of intermediate parameter values.

* There are 6 parts: gas producers, gasconsumers (except heat and power generators),
*                    TSOs, Distributors, Suppliers, Storageoperators, Exporers.

* Much of the code in this file may seem superfluous. The development phylosophy
* has been to prepare the code for any forseeable additions with regard to agent
* detail. For instance many agentgroups have associated costs or profits which are
* set to zero as there is at present no available data, nor an accurate repressentation
* of these factors in the model.

*===============================================================================
*                End: Overview
*===============================================================================

*===============================================================================
*                Gas Producers
*===============================================================================

* Only Danish natural gas production considered. Should be modified for new investments.
GasProducerRevenue(Y,'Denmark')= Sum((S,T),(IGEXT_COST('Nybro',S)*IOF3P6 + IOF1000000*(-1*VSUP.m('Nybro',S,T)/IHOURSINST(S,T)))*VSUP.l('Nybro',S,T)*IHOURSINST(S,T));

* Artificially set to zero
GasProducerCosts(Y,C) = 0;

GasProducerProfit(Y,C) = GasProducerRevenue(Y,C)-GasProducerCosts(Y,C);



*===============================================================================
*                Gas Consumers
*===============================================================================


* Gasconsumers (except heat and power generators)

* Costs to residual consumers (e.g. private homes and small businesses) (Input currency)
residualcosts(Y,C) = SUM((IA,S,T)$ICA(C,IA), IDGRES_Y(IA,S,T)*IOF1000000 *(QCONSUMPTION.m(IA,S,T)$ICA('Denmark',IA)
                                                                          +QGSVERIGE.m(S,T)$ICA('Sweden',IA)));

* Costs to other consumers (e.g. Industry) (Input currency)
othercosts(Y,C) = SUM((IA,S,T)$ICA(C,IA), IDGOTH_Y(IA,S,T)*IOF1000000 *(QCONSUMPTION.m(IA,S,T)$ICA('Denmark',IA)
                                                                       +QGSVERIGE.m(S,T)$ICA('Sweden',IA)));

*===============================================================================
*                Gas Distributors
*===============================================================================

* Distributioners revenue.
DSOrevenue(Y,C) = 1/7.43/1.389*SUM((DDD,IA,S,T)$(DDDNODE(DDD,IA) and ICA(C,IA)), TAU_DIST(DDD)*VGUD.l(IA,S,T)*IHOURSINST(S,T))$SAMEAS(C,'Denmark')
                 +1/7.43/1.389*SUM((TRANSIT,S,T), TAU_DIST('SE_S_DIST')*VTRANSIT.l(TRANSIT,S,T)*IHOURSINST(S,T))$SAMEAS(C,'Sweden');

* Distributor costs artificially set to zero.
DSOcosts(Y,C) = 0;

DSOprofit(Y,C) = DSOrevenue(Y,C)-DSOcosts(Y,C);

*===============================================================================
*                Gas TSOs
*===============================================================================

* TSO capacity revenue (Input currency)
TSOCAPrev(Y,'Denmark') = +1/7.43/1.389*(
$ifi %bb1%==yes + SUM(SYSENTRY,  TAU_EN_Y*VTC_EN_Y.l(SYSENTRY)     )
$ifi %bb1%==yes + SUM(SYSEXIT,   TAU_EX_Y*VTC_EX_Y.l(SYSEXIT)     )
$ifi %bb1%==yes + SUM(SYSENTRY,  SUM(IMONTH, TAU_EN_M(IMONTH)*VTC_EN_M.l(SYSENTRY,IMONTH)*MONTHSCALE(IMONTH))     )
$ifi %bb1%==yes + SUM(SYSEXIT,   SUM(IMONTH, TAU_EX_M(IMONTH)*VTC_EX_M.l(SYSEXIT,IMONTH)*MONTHSCALE(IMONTH))     )
$ifi %bb2%==yes + SUM(SYSENTRY,  TAU_EN_Y*VTC_EN_Y.l(SYSENTRY)     )
$ifi %bb2%==yes + SUM(SYSEXIT,   TAU_EX_Y*VTC_EX_Y.l(SYSEXIT)     )
$ifi %bb2%==yes + SUM(SYSENTRY,  SUM(IMONTH, TAU_EN_M(IMONTH)*VTC_EN_M.l(SYSENTRY,IMONTH)*MONTHSCALE(IMONTH))     )
$ifi %bb2%==yes + SUM(SYSEXIT,  SUM(IMONTH, TAU_EX_M(IMONTH)*VTC_EX_M.l(SYSEXIT,IMONTH)*MONTHSCALE(IMONTH))     )
+     SUM(SYSENTRY,  sum(IS3,IDAYSIN_S(IS3)/7*(TAU_EN_W(IS3)*VTC_EN_W.l(SYSENTRY,IS3)))     )
+     SUM(SYSEXIT,   sum(IS3,IDAYSIN_S(IS3)/7*(TAU_EX_W(IS3)*VTC_EX_W.l(SYSEXIT,IS3)))     )
$ifi %bb3%==yes + SUM(SYSENTRY,  TAU_EN_Y*ITC_EN_Y(SYSENTRY)     )
$ifi %bb3%==yes + SUM(SYSEXIT,   TAU_EX_Y*ITC_EX_Y(SYSEXIT)     )
$ifi %bb3%==yes + SUM(SYSENTRY,  SUM(IMONTH, TAU_EN_M(IMONTH)*ITC_EN_M(SYSENTRY,IMONTH)*MONTHSCALE(IMONTH))     )
$ifi %bb3%==yes + SUM(SYSEXIT,   SUM(IMONTH, TAU_EX_M(IMONTH)*ITC_EX_M(SYSEXIT,IMONTH)*MONTHSCALE(IMONTH))     )
$ifi %bb3%==yes + SUM(SYSENTRY,  sum((IS3,DAY), TAU_EN_D(IS3,DAY)*VTC_EN_D.l(SYSENTRY,IS3,DAY))     )
$ifi %bb3%==yes + SUM(SYSEXIT,   sum((IS3,DAY), TAU_EX_D(IS3,DAY)*VTC_EX_D.l(SYSEXIT,IS3,DAY))     )
);

* TSO volumetric revenue
TSOVOLrev(Y,'Denmark') = TAU_VOL/7.43/1.389*sum((S,T), Sum(SOURCE, VSUP.l(SOURCE,S,T)*IHOURSINST(S,T))-VEXP.l('Nybro',S)*IHOURSINST(S,T));

* TSO capacity rent (i.e. additional congestion charges that could be applied without changing production, transmission or consumption).
TSOCAPRent(Y,'Denmark') =
$ifi %BB1%==yes +SUM((SOURCE,S,T)$(not SAMEAS(SOURCE,'Nybro')),  VSUP.l(SOURCE,S,T)*(-1)*VSUP.m(SOURCE,S,T)*IOF1000000)
$ifi %BB2%==yes +SUM((SOURCE,S,T)$(not SAMEAS(SOURCE,'Nybro')),  VSUP.l(SOURCE,S,T)*QSUPPLYMAX.m(SOURCE,S,T)*IOF1000000)
$ifi %BB3%==yes +SUM((SOURCE,S,T)$(not SAMEAS(SOURCE,'Nybro')),  VSUP.l(SOURCE,S,T)*(-1)*VSUP.m(SOURCE,S,T)*IOF1000000)
$ifi %BB1%==yes +SUM((SOURCE,S)$(not SAMEAS(SOURCE,'Nybro')),    VEXP.l(SOURCE,S)*(-1)*VEXP.m(SOURCE,S)*IOF1000000)
$ifi %BB2%==yes +SUM((SOURCE,S)$(not SAMEAS(SOURCE,'Nybro')),    VEXP.l(SOURCE,S)*QEXPMAX.m(SOURCE,S)*IOF1000000)
$ifi %BB3%==yes +SUM((SOURCE,S)$(not SAMEAS(SOURCE,'Nybro')),    VEXP.l(SOURCE,S)*(-1)*VEXP.m(SOURCE,S)*IOF1000000)
$ifi %BB1%==yes +SUM((TRANSIT,S,T),  VTRANSIT.l(TRANSIT,S,T)*(-1)*VTRANSIT.m(TRANSIT,S,T)*IOF1000000)
$ifi %BB2%==yes +SUM((TRANSIT,S,T),  VTRANSIT.l(TRANSIT,S,T)*QGTRANSIT_MAX.m(TRANSIT,S,T)*IOF1000000)
$ifi %BB3%==yes +SUM((TRANSIT,S,T),  VTRANSIT.l(TRANSIT,S,T)*(-1)*VTRANSIT.m(TRANSIT,S,T)*IOF1000000)
;

* Artificially set to zero baring investments (investments pending).
TSOfixedcosts(Y,C)=0;

* Artificially set to zero.
TSOvariablecosts(Y,C)=0;

TSOprofit(Y,C) = TSOCAPrev(Y,C) + TSOVOLrev(Y,C) -TSOfixedcosts(Y,C) - TSOvariablecosts(Y,C);

*===============================================================================
*                Gas SSOs
*===============================================================================

* Storage costs
*NOTICE ERROR HERE. STORAGE CAPACITY MAY EXIST IN OTHER COURTRIES i.e. SWEDEN)
SSOCAPrev(Y,'Denmark')=
$ifi %bb1%==yes +1/7.43/1.389*sum(SCON, VSC.l(SCON)*SCONDATA(SCON,'TARRIF'))
$ifi %bb2%==yes +1/7.43/1.389*sum(SCON, VSC.l(SCON)*SCONDATA(SCON,'TARRIF'))
$ifi %bb3%==yes +1/7.43/1.389*sum(SCON, ISC_Y(SCON)*SCONDATA(SCON,'TARRIF'))
;

SSOVOLrev(Y,C) = SUM((STORE(IA),S,T)$ICA(C,IA),
                 +SUM((IR,STORETYPE)$RRRAAA(IR,STORE),VINJ.l(STORE,STORETYPE,S,T)*GSTOREDATA(STORETYPE,'ELECT')*QEEQ.m(IR,S,T))
                 +SUM(STORETYPE, VEXT.l(STORE,STORETYPE,S,T)*GSTOREDATA(STORETYPE,'GAS')*QGEQ.m(S,T))
                 )*IOF1000000;

SSOCAPrent(Y,C) = SUM((STORE(IA),S,T)$ICA(C,IA),
$ifi %bb1%==yes  SUM(STORETYPE, VEXT.l(STORE,STORETYPE,S,T)*VEXT.m(STORE,STORETYPE,S,T))
$ifi %bb2%==yes  SUM(STORETYPE, VEXT.l(STORE,STORETYPE,S,T)*QGEXT_MAX.m(STORE,STORETYPE,S,T))
$ifi %bb3%==yes  SUM(STORETYPE, VEXT.l(STORE,STORETYPE,S,T)*VEXT.m(STORE,STORETYPE,S,T))
$ifi %bb1%==yes  +SUM(STORETYPE, VINJ.l(STORE,STORETYPE,S,T)*(-1*VINJ.m(STORE,STORETYPE,S,T)))
$ifi %bb2%==yes  +SUM(STORETYPE, VINJ.l(STORE,STORETYPE,S,T)*QGINJ_MAX.m(STORE,STORETYPE,S,T)))
$ifi %bb3%==yes  +SUM(STORETYPE, VINJ.l(STORE,STORETYPE,S,T)*(-1*VINJ.m(STORE,STORETYPE,S,T))))
$ifi %bb1%==yes  +SUM(STORETYPE, VSTOCK.l(STORE,STORETYPE,S,T)*(-1*VSTOCK.m(STORE,STORETYPE,S,T)))
$ifi %bb2%==yes  +SUM(STORETYPE, VSTOCK.l(STORE,STORETYPE,S,T)*QGSTORE_MAX.m(STORE,STORETYPE,S,T))
$ifi %bb3%==yes  +SUM(STORETYPE, VSTOCK.l(STORE,STORETYPE,S,T)*(-1*VSTOCK.m(STORE,STORETYPE,S,T)))
                 )*IOF1000000;

* Artificially set to zero unless investments are made (pending)
SSOfixedcosts(Y,C)= 0;

* Set electricity costs = volumetric revenue
SSOvariablecosts(Y,C)=SSOVOLrev(Y,C);

SSOprofit(Y,C) = SSOCAPrev(Y,C)+SSOVOLrev(Y,C)-(SSOfixedcosts(Y,C)+SSOvariablecosts(Y,C));

*===============================================================================
*                Gas Shippers
*===============================================================================

GasShipperCosts(Y,C) =
* Køb fra producenter
                     GasProducerRevenue(Y,C)$SAMEAS(C,'Denmark')
* Import
                       +Sum((SOURCE,S,T)$(ICA(C,SOURCE) and not SAMEAS(SOURCE,'Nybro')),(IOF3P6*IGEX_PRICE(SOURCE,S))*VSUP.l(SOURCE,S,T)*IHOURSINST(S,T))$SAMEAS(C,'Denmark')
* Gas transport
                       +TSOCAPrev(Y,C) + TSOVOLrev(Y,C)
* Køb på det danske marked:
                       +IOF1000000*Sum((STORE,STORETYPE,S,T)$ICA(C,STORE), VEXT.l(STORE,STORETYPE,S,T)*QGEQ.m(S,T))
;

GasShipperRevenue(Y,C) =  IOF1000000*Sum((IA,S,T)$ICA('Denmark',IA),QCONSUMPTION.m(IA,S,T)*VGUD.l(IA,S,T))$SAMEAS(C,'Denmark')-DSOrevenue(Y,'Denmark')$SAMEAS(C,'Denmark')
                         +IOF1000000*Sum((STORE,STORETYPE,S,T)$ICA(C,STORE), VINJ.l(STORE,STORETYPE,S,T)*QGEQ.m(S,T))$SAMEAS(C,'Denmark')
                         +Sum((SOURCE,S,T),IHOURSINST(S,T)*(IGEX_PRICE(SOURCE,S)*IOF3P6)*VEXP.l(SOURCE,S))$SAMEAS(C,'Denmark')
                         +IOF1000000*Sum((TRANSIT,S,T)$ICA(C,TRANSIT),QGSVERIGE.m(S,T)*VTRANSIT.l(TRANSIT,S,T))$SAMEAS(C,'Denmark')-DSOrevenue(Y,'Sweden')$SAMEAS(C,'Denmark');

GasShipperProfit(Y,C) = GasShipperRevenue(Y,C) - GasShipperCosts(Y,C) ;

$ifi %BB1%==yes ShipperCapRent(Y,'Denmark') = +SUM(S,   VEXP.l('Nybro',S)*(-1)*VEXP.m('Nybro',S)*IOF1000000);
$ifi %BB2%==yes ShipperCapRent(Y,'Denmark') = +SUM(S,   VEXP.l('Nybro',S)*QEXPMAX.m('Nybro',S)*IOF1000000);
$ifi %BB3%==yes ShipperCapRent(Y,'Denmark') = +SUM(S,   VEXP.l('Nybro',S)*(-1)*VEXP.m('Nybro',S)*IOF1000000);

*===============================================================================
*                Gas Suppliers
*===============================================================================
* This agent's economics appear rather artificial. The supplier is considered to be
* an arbitrageur, purchasing gas from the shipper upon exit from the transmission
* system and upon entry to the distribution system, and reselling to the enduser
* thereby making a profit. However, the models fundamentals ensure that there are
* no excess profits and that the markets are arbitrag-free. Thereby, the supplier
* should never make a profit, and is only included here for the sake of generality.

* Suppliercosts are defined as retail less distribution costs. The distribution
* costs are then added to the costs.
GasSupplierCosts(Y,C)=  IOF1000000*Sum((IA,S,T)$ICA(C,IA),QCONSUMPTION.m(IA,S,T)*VGUD.l(IA,S,T))
                       +IOF1000000*Sum((TRANSIT,S,T)$ICA(C,TRANSIT),QGSVERIGE.m(S,T)*VTRANSIT.l(TRANSIT,S,T))$SAMEAS(C,'Sweden')
                       -DSOrevenue(Y,C)+DSOrevenue(Y,C);

* Supplier revenue is the retail value of gas.
GasSupplierRevenue(Y,C) = IOF1000000*Sum((IA,S,T)$ICA(C,IA),QCONSUMPTION.m(IA,S,T)*VGUD.l(IA,S,T))
                         +IOF1000000*Sum((TRANSIT,S,T)$ICA(C,TRANSIT),QGSVERIGE.m(S,T)*VTRANSIT.l(TRANSIT,S,T))$SAMEAS(C,'Sweden');


GasSupplierProfit(Y,C) = GasSupplierRevenue(Y,C) - GasSupplierCosts(Y,C);

*===============================================================================
*                Gas Storage User
*===============================================================================


GasStorageUserCost(Y,C) = SSOCAPrev(Y,C) + SSOVOLrev(Y,C)
                          +SUM((STORE,STORETYPE,S,T)$ICA(C,STORE),
                                 QGEQ.m(S,T)*VINJ.l(STORE,STORETYPE,S,T)
*                                +QGSTOREBAL.m(STORE,STORETYPE,S,T)*VEXT.l(STORE,STORETYPE,S,T)*IHOURSINST(S,T)
                           )*IOF1000000
;

GasStorageUserRevenue(Y,C) = +SUM((STORE,STORETYPE,S,T)$ICA(C,STORE),
                                 VEXT.l(STORE,STORETYPE,S,T)*QGEQ.m(S,T)
*                                +VINJ.l(STORE,STORETYPE,S,T)*QGSTOREBAL.m(STORE,STORETYPE,S,T)*IHOURSINST(S,T)
                             )*IOF1000000
;

GasStorageUserProfit(Y,C) = GasStorageUserRevenue(Y,C)-GasStorageUserCost(Y,C);