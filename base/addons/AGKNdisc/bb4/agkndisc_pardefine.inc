PARAMETER AGKNDISCDATA(G,AGKNDISCSIZESET,AGKNDISCDATASET) "Technology investment data for discrete capacity size investments"   %semislash%
$if     EXIST '../data/X3VPIM.inc' $INCLUDE      '../data/agkndisc_agkndiscdata.inc';
$if not EXIST '../data/X3VPIM.inc' $INCLUDE '../../base/addons/x3v/demodata/agkndisc_agkndiscdata.inc';
