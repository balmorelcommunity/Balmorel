PARAMETER AGKNDISCDATA(G,AGKNDISCSIZESET,AGKNDISCDATASET) "Technology investment data for discrete capacity size investments"   %semislash%
$if     EXIST '../data/AGKNDISC_AGKNDISCDATA.inc' $INCLUDE      '../data/AGKNDISC_AGKNDISCDATA.inc';
$if not EXIST '../data/AGKNDISC_AGKNDISCDATA.inc' $INCLUDE '../../base/addons/AGKNdisc/AGKNDISC_AGKNDISCDATA.inc';
