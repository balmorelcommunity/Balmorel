* File agkndiscinternal.inc with addon apkndisc for the OptiWaste model.

SET IAPROCKAPDISCNEW(Y,AAA,PROC)  'Area, PROC for discrete size investment, where PROC may be invested based on APKN and implicit constraints (addon apkndisc)';
*  Quick (and slightly dirtey) way:
IAPROCKAPDISCNEW(Y,IA,PROC) = APKNDISC_AP(IA,PROC);

PARAMETER IAPKNDISCDIFFCOST(AAA,PROC,APKNDISCSIZESET) 'DEBUG ONLY: Investment costs in relation to discrete capacity size investments, as difference for each size (Money) (addon apkndisc)';
IAPKNDISCDIFFCOST(IA,PROC,APKNDISCSIZESET)$APKNDISC_AP(IA,PROC) =
       -(APKNDISCDATA(PROC,APKNDISCSIZESET,'APKNDISCINVCOST') - APKNDISCDATA(PROC,APKNDISCSIZESET,'APKNDISCSIZE')*PROCDATA(PROC,'PROCINVCOST'));  !! Investment cost difference
