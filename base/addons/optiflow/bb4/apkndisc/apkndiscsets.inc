* File apkndiscset.inc with addon apkndisc for the OptiWaste model.

SET APKNDISCAP(AAA,PROC) "Areas for possible location of discrete capacity investments in Processes (addon apkndisc)";
SET APKNDISCPSIZESET     "Set of possible sizes for discrete capacity investments in Processes (addon apkndisc)";
SET APKNDISCPDATASET     "Processes investment data types for discrete capacity size investments (addon apkndisc)";
PARAMETER APKNDISCPDATA(PROC,APKNDISCPSIZESET,APKNDISCPDATASET) "Investment data for discrete Process capacity size investments (addon apkndisc)";
