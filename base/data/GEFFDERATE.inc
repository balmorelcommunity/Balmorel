* PARAMETER GEFFDERATE represents a reduction in efficiency,
* relative to the one entered in the table GINFO as FE.
* Unit: (none).

* This reduction may represent the effects of depreciation
* and deviation between bestpoint and average efficiences.

TABLE GEFFDERATE(AAA,GGG)  'Reduction in fuel efficiency (fraction)'
               DK_E_Rural_WI
DK_E_Rural     1
;

* Unless other values are assigned in the TABLE above,
* a default value are used and assigned below:

GEFFDERATE(AAA,G)$(GEFFDERATE(AAA,G) EQ 0)=             1;