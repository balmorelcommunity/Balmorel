* File XH_demodata1.inc

* This file is part of the Balmorel model extended for heat transmission.

* The data given here will probably not be valid for your model due to inconsistencies with other data,
* however, this file demonstrates the idea.

* The data file with real data is supposed to be located in the data folder, like any other input data file.
* The name of the date file must be XH.inc.


*------------------------------------------------------------------------------

* This file contains all input data concerning heat transmission capacities and costs

*------------------------------------------------------------------------------

* PARAMETER XHKINI contains the initital heat transmission capacities
* between pairs of areas.
* Units: MW.

* The heat transmission capacity is the capacity
* disregarding an eventual loss (see the table XHLOSS).
* Thus, if there is a loss, a maximum of XHCAPINIT MW may be sent into
* the transmission line, but at most (XHCAPINIT*XHLOSS) MW may be extracted.


* Data source:


* IAAAE is exporting area (i.e., 'from') and IAAAI is importing area (i.e., 'to').

TABLE XHKINI(IAAAE,IAAAI)  'Initial heat transmission capacity between areas (MW)'
            DK_W_LARGE  DK_W_SMALL
DK_W_LARGE      0          100
DK_W_SMALL     100          0
;


* PARAMETER XHINVCOST contains information about the investment cost
* in new heat transmission capacity between pairs of areas.
* Units: EUR90/MW.

* Observe: if INF is entered in the table, this means that no tranmission
* capacity can be established between the two associated areas.
* The matriXH should only have values in the lower half, as only those
* values are used in the model.

* Data source:

TABLE XHINVCOST(IAAAE,IAAAI)  'Investment cost in new heat transmission capacity (Money/MW)'
            DK_W_LARGE  DK_W_SMALL
DK_W_LARGE      0          210
DK_W_SMALL     210          0
;


* PARAMETER XHCOST contains information about the heat transmission
* cost between pairs of areas.
* Units: EUR90/MWh.

* The heat transmission cost is applied to the heat
* entering the heat transmission line.

* Observe: Unreasonable results may be found if there are neither
* cost nor loss associated with heat transmission.
* Therefore for all (non-diagonal) entries there should be a positive number
* in either TABLE XHCOST or in TABLE XHLOSS.

* Data source:


PARAMETER XHCOST(IAAAE,IAAAI)  'Heat transmission cost between areas (Money/MWh)' ;
XHCOST(IAAAE,IAAAI) = 0.0001;


* PARAMETER XHLOSS contains the loss in heat transmission is expressed as a fraction
* of the heat entering the transmission line.
* Units: (none)

* Observe: Unreasonable results may be found if there are neither
* cost nor loss associated with heat transmission.
* Therefore for all (non-diagonal) entries there should be a positive number
* in either TABLE XHCOST or in TABLE XHLOSS.

* Data source:

* The data entered assumes for simplicity that all heat transmission losses
* between areas IAAAE and IAAAI are the same in both directions.
* Therefore the loss data is given only once.
* It is therefore by convention assumed that loss data between areas IAAAE and IAAAI
* is given only for ORD(IAE) LT ORD(IAI), i.e. data is entered
* only in the upper right half of the table; the remaining data
* is filled in by the LOOP statement immediately after the table.

* (If this assumption is not found reasonable upon revision of the data,
* then fill in the whole table,
* and delete the fill-in LOOP statement immediately after the table.)


TABLE XHLOSS(IAAAE,IAAAI)  'Heat transmission loss between areas'
            DK_W_LARGE  DK_W_SMALL
DK_W_LARGE      0          0.1
DK_W_SMALL     0.1          0
;
* Then fill in the values not entered in the table assuming symmetry:
* LOOP( (IAAAE,IAAAI)$(ORD(IAAAE) GT ORD(IAAAI)),  XHLOSS(IAAAE,IAAAI)=XHLOSS(IAAAI,IAAAE););
