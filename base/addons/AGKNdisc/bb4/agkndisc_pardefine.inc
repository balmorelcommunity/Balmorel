PARAMETER AGKNDISCDATA(G,AGKNDISCSIZESET,AGKNDISCDATASET) "Technology investment data for discrete capacity size investments"   %semislash%
$if     EXIST '../data/agkndisc_agkndiscdata.inc' $INCLUDE      '../data/agkndisc_agkndiscdata.inc';
$if not EXIST '../data/agkndisc_agkndiscdata.inc' $INCLUDE '../../base/addons/agkndisc/agkndisc_agkndiscdata.inc';
