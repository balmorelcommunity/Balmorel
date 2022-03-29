* File agkndiscequations.inc.
* To be used with addon AGKNDISC to the Balmorel model.


* 'The continuous invested capacity must be one of the specified discrete sizes or zero (Addon AGKNDISC) (MW)'
QAGKNDISCEQUALCONT(IAGKNDISC_YAG(IY411,IA,G))..

VGKN(IY411,IA,G) =E= SUM(AGKNDISCSIZESET$AGKNDISCDATA(G,AGKNDISCSIZESET,'AGKNDISCSIZE'),  VGKNDISC(IY411,IA,G,AGKNDISCSIZESET)*AGKNDISCDATA(G,AGKNDISCSIZESET,'AGKNDISCSIZE'));


* 'At most one of the specified discrete capacity size investments is chosen (Addon AGKNDISC) ()'
QAGKNDISC01(IAGKNDISC_YAG(IY411,IA,G))..
 SUM(AGKNDISCSIZESET$AGKNDISCDATA(G,AGKNDISCSIZESET,'AGKNDISCSIZE'), VGKNDISC(IY411,IA,G,AGKNDISCSIZESET)) =L= 1;
