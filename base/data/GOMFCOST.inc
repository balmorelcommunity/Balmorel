* PARAMETER GOMFCOST(AAA,GGG) holds the annual fixed operating
* and maintenance costs.
* Unit: kEUR90/MW.


TABLE GOMFCOST(AAA,GGG)  'Annual fixed operating costs (kMoney/MW)'
             DK_E_Rural_WI
DK_E_Rural   0
;

* Default values given by GDATA(TG,'GOMFCOST0')
* are used unless non-zero values have been otherwise specified :

GOMFCOST(AAA,GGG)$(GOMFCOST(AAA,GGG) EQ 0)= GDATA(GGG,'GDOMFCOST0');
* Format modified 23-10-01