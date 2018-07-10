
SET IAGKNDISCAG(AAA,G)  'Area, technology for discrete size investment, where technology may be invested based on AGKN and implicit constraints (Addon AGKNDISC)';

IAGKNDISCAG(AAA,G) = AGKNDISC(AAA,G);
*IAGKNDISCAG(IY411,IA,G) = AGKNDISC(IA,G);  !! Input data, independent of Year
*IAGKNDISCAG(IY411,IA,IGKKNOWN) = NO;          !! No new capacity if notIGKFIND (but should not be allowed in input data)
*IAGKNDISCAG(IY411,IA,G)$(YVALUE(IY411) LT GDATA(G,'GDFROMYEAR')) = NO; !! Add year dependency

PARAMETER IAGKNDISCDIFFCOST(AAA,G,AGKNDISCSIZESET,AGKNDISCDATASET) 'Investment costs in relation to discrete capacity size investments, as difference for each size (Money) (Addon AGKNDISC)';

  IAGKNDISCDIFFCOST(IA,G,AGKNDISCSIZESET,AGKNDISCDATASET)$IAGKNDISCAG(IA,G) =
         AGKNDISCDATA(G,AGKNDISCSIZESET,'AGKNDISCINVCOST')
      -  AGKNDISCDATA(G,AGKNDISCSIZESET,'AGKNDISCSIZE')*GOMFCOST(IA,G)
      -  AGKNDISCDATA(G,AGKNDISCSIZESET,'AGKNDISCSIZE')*GINVCOST(IA,G);



