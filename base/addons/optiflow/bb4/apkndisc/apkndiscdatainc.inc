

SET APKNDISCSIZESET    "Set of possible sizes for discrete capacity investments in Processes (addon apkndisc)" %semislash%
$if     EXIST '../addons/OptiFlow/data/AGKNDISCGSIZESET.inc' $INCLUDE         '../addons/OptiFlow/data/APKNDISCSIZESET.inc';
$if not EXIST '../addons/OptiFlow/data/AGKNDISCGSIZESET.inc' $INCLUDE '../../base/addons/OptiFlow/data/APKNDISCSIZESET.inc';
%semislash%

SET APKNDISCDATASET    "Processes investment data types for discrete capacity size investments (addon apkndisc)" %semislash%
$if     EXIST '../addons/OptiFlow/data/AGKNDISCGDATASET.inc' $INCLUDE         '../addons/OptiFlow/data/APKNDISCDATASET.inc';
$if not EXIST '../addons/OptiFlow/data/AGKNDISCGDATASET.inc' $INCLUDE '../../base/addons/OptiFlow/data/APKNDISCDATASET.inc';
%semislash%

PARAMETER APKNDISCDATA(PROC,APKNDISCSIZESET,APKNDISCDATASET) "Investment data for discrete Process capacity size investments (addon apkndisc)" %semislash%
$if     EXIST '../addons/OptiFlow/data/APKNDISCDATA.inc' $INCLUDE         '../addons/OptiFlow/data/APKNDISCDATA.inc';
$if not EXIST '../addons/OptiFlow/data/APKNDISCDATA.inc' $INCLUDE '../../base/addons/OptiFlow/data/APKNDISCDATA.inc';
%semislash%

SET APKNDISC_AP(AAA,PROC) "Areas for possible location of discrete capacity investments in Processes (addon apkndisc)" %semislash%
$if     EXIST '../addons/OptiFlow/data/APKNDISC_AP.inc' $INCLUDE         '../addons/OptiFlow/data/APKNDISC_AP.inc';
$if not EXIST '../addons/OptiFlow/data/APKNDISC_AP.inc' $INCLUDE '../../base/addons/OptiFlow/data/APKNDISC_AP.inc';
%semislash%
