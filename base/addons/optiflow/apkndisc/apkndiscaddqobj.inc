* File apkndiscaddqobj.inc.
* To be used with addon APKNDISC to the Balmorel model.
* Contains addon APKNDISC contribution to QOBJ.

* For continuous size investment the following costs are included in QOBJ:
* investment cost, annual operation and management fixed costs, and operation and management variable costs.  [Note: not all these elements presently implemented]
* For the discrete size investments, these costs may differ.
* The expression below holds the difference with respect to investment cost, fixed annual operation and management costs,
* but NOT variable operation and management costs.
* A positive value of the factor to VPROCKAPDISCNEW means that the discrete size investment is more expensive, a negative value that it is less.

* The expression below is added in QOBJ.

     - SUM((IY411,IA,PROC)$IAPROCKAPDISCNEW(IY411,IA,PROC),
         SUM(APKNDISCSIZESET$APKNDISCDATA(PROC,APKNDISCSIZESET,'APKNDISCSIZE'),
           VPROCKAPDISCNEW(IY411,IA,PROC,APKNDISCSIZESET)
            *(
              (APKNDISCDATA(PROC,APKNDISCSIZESET,'APKNDISCINVCOST') - APKNDISCDATA(PROC,APKNDISCSIZESET,'APKNDISCSIZE')*PROCDATA(PROC,'PROCINVCOST'))  !! Investment cost difference
*            +(APKNDISCDATA(PROCAPKNDISCSIZESET,'APKNDISCOMFCOST') - APKNDISCDATA(PROC,APKNDISCSIZESET,'APKNDISCSIZE')*PROCDATA(PROC,??)) !! Fixed annual operation and management costs. Presently not implemented, see APKNDISCDATASET.inc and APKNDISCDATA.inc
             )
       ))    !! TODO: annuity and stuff

