* File agkndiscinternal.inc.
* To be used with addon AGKNDISC to the Balmorel model.


SET IAGKNDISCAG(AAA,G)  'Area, technology for discrete size investment, where technology may be invested based on AGKN and implicit constraints (Addon AGKNDISC)';

PARAMETER IAGKNDISCDIFFCOST(AAA,G,AGKNDISCGSIZESET,AGKNDISCGDATASET) 'Investment costs in relation to discrete capacity size investments, as difference for aech size (Money) (Addon AGKNDISC)';

  IAGKNDISCDIFFCOST(IA,G,AGKNDISCGSIZESET,AGKNDISCGDATASET)$AGKNDISCAG(IA,G) =
         AGKNDISCGDATA(G,AGKNDISCGSIZESET,'AGKNDISCINVCOST')
      -  AGKNDISCGDATA(G,AGKNDISCGSIZESET,'AGKNDISCSIZE')*GOMFCOST(IA,G)
      -  AGKNDISCGDATA(G,AGKNDISCGSIZESET,'AGKNDISCSIZE')*GINVCOST(IA,G);



