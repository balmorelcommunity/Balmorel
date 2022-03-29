* File apkndiscvarsequas.inc with addon apkndisc for the OptiWaste model.

INTEGER VARIABLE VPROCKAPDISCNEW(Y,AAA,PROC,APKNDISCSIZESET) "New PROC capacity in relation to discrete capacity size investments (addon APKNDISC) (integer)";


EQUATION QAPKNDISCEQUALCONT(Y,AAA,PROC)   'The continuous invested capacity must be the sum of a combination of the specified discrete sizes or zero (Addon APKNDISC) (U/hW)';

* Addon APKNDISC: 'The continuous invested capacity must be the sum of a combination of the specified discrete sizes or zero (Addon APKNDISC) (U/hW)'
QAPKNDISCEQUALCONT(IAPROCKAPDISCNEW(IY411,IA,PROC))..
VPROCKAPNEW(IY411,IA,PROC) =E= SUM(APKNDISCSIZESET$APKNDISCDATA(PROC,APKNDISCSIZESET,'APKNDISCSIZE'),
    VPROCKAPDISCNEW(IY411,IA,PROC,APKNDISCSIZESET)*APKNDISCDATA(PROC,APKNDISCSIZESET,'APKNDISCSIZE'));
