* File agkndiscaddobj.inc.
* To be used with addon AGKNDISC to the Balmorel model.
* Contains addon AGKNDISC contribution to QOBJ.

* For continuous size investment the following costs are included in QOBJ:
* investment cost, annual operation and management fixed costs, and operation and management variable costs.
* For the discrete size investments, these costs may differ.
* The expression below holds the difference with respect to investment cost, annual operation and management fixed costs,
* but NOT operation and management variable costs.
* A positive value means that then discrete size investment is more expensive, a negative value that it is less.

* Note that the factor (continuous size) to GINVCOST in QOBJ is IOF1000000 (unit is MMoney/MW), while it is IOF1000 to GOMFCOST (unit is kMoney/MW).
* The unit for AGKNDISCINVCOST is MMoney/MW, for AGKNDISCOMFCOST it is kMoney/MW, cf. AGKNDISCDATASET and AGKNDISCDATA.

* The expression below is added in QOBJ.

   + (SUM(IAGKNDISC_YAG(Y,IA,G)$IY411(Y),  SUM(AGKNDISCSIZESET$AGKNDISCDATA(G,AGKNDISCSIZESET,'AGKNDISCSIZE'),
     VGKNDISC(Y,IA,G,AGKNDISCSIZESET)*

     ( IOF1000000*(AGKNDISCDATA(G,AGKNDISCSIZESET,'AGKNDISCINVCOST') - AGKNDISCDATA(G,AGKNDISCSIZESET,'AGKNDISCSIZE')*GINVCOST(IA,G))  !! Investment cost difference
      +IOF1000   *(AGKNDISCDATA(G,AGKNDISCSIZESET,'AGKNDISCOMFCOST') - AGKNDISCDATA(G,AGKNDISCSIZESET,'AGKNDISCSIZE')*GOMFCOST(IA,G))) !! Fixed annual operation and management costs

     *(SUM(C$ICA(C,IA),ANNUITYC(C)))*IY4GINVCOSTWEIGHT(Y,G))))

