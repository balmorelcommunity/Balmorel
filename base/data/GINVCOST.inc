* PARAMETER GINVCOST holds the investment cost for new technology.
* Unit: MEUR90/MW.


TABLE GINVCOST(AAA,GGG)  'Investment cost for new technology (MMoney/MW)'
             DK_E_Rural_WI
DK_E_Rural   0
;

* Default values given by GDATA(GGG,'GDINVCOST0')
* are used unless non-zero values have been otherwise specified:

GINVCOST(AAA,GGG)$(GINVCOST(AAA,GGG) EQ 0)= GDATA(GGG,'GDINVCOST0');

