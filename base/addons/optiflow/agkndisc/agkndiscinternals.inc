* File agkndiscinternal.inc.
* To be used with addon AGKNDISC to the Balmorel model.

SET IAGKNDISC_YAG(YYY,AAA,GGG)  'Area, technology for discrete size investment, where technology may be invested based on AGKN and implicit constraints (Addon AGKNDISC)';

* The investment amount (MW) in endogenous capacity will, also with discrete size investments, be expressed by variable VGKN.
* The associated capacity and cost will be used in the same way as with continuous size investments.
* To account for economies of scale the difference between the continuous and the discrete size situation
* will be expressed in IAGKNDISCDIFFCOST.
* This value (which may be negative, zero or positive) will be added in QOBJ.


PARAMETER IAGKNDISCDIFFCOST(AAA,G,AGKNDISCSIZESET) 'DEBUG ONLY: Investment costs in relation to discrete capacity size investments, as difference for each size (Money) (Addon AGKNDISC)';

* For continuous size investment the following costs are included in QOBJ:
* investment cost, annual operation and management fixed costs, and operation and management variable costs.
* For the discrete size investments, these costs may differ.
* IAGKNDISCDIFFCOST holds the difference with respect to investment cost, annual operation and management fixed costs,
* but not operation and management variable costs.
* A positive value means that then discrete size investment is more expensive, a negative value that it is less.

* IAGKNDISCDIFFCOST is added in QOBJ.
* Note that the factor to GINVCOST in QOBJ is IOF1000000 (unit is MMoney/MW), while it is IOF1000 to GOMFCOST (unit is kMoney/MW).
* The unit for AGKNDISCINVCOST is MMoney/MW, for AGKNDISCOMFCOST it is kMoney/MW.
* The factor to IAGKNDISCDIFFCOST in QOBJ is. This explains the factor IOF1000 below.

* The expression below is used in agkndiscaddobj.inc.

 
  IAGKNDISCDIFFCOST(IA,G,AGKNDISCSIZESET)$AGKNDISC_AG(IA,G) =
    IOF1000000*(AGKNDISCDATA(G,AGKNDISCSIZESET,'AGKNDISCINVCOST') - AGKNDISCDATA(G,AGKNDISCSIZESET,'AGKNDISCSIZE')*GINVCOST(IA,G))
  + IOF1000   *(AGKNDISCDATA(G,AGKNDISCSIZESET,'AGKNDISCOMFCOST') - AGKNDISCDATA(G,AGKNDISCSIZESET,'AGKNDISCSIZE')*GOMFCOST(IA,G))

;

