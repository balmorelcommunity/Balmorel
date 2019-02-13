* Subset of year and Season
$oninline
$oneolcom

SET IYS(YYY,SSS) "Mapping (YYY,SSS)"     !! Hans text revised
$include ../../base/AnnotationPlotting/YSMapping.inc


*SET IYS_sub(YYY,SSS) "Mapping (IY411,SSS)";    Hans replaced by next
SET IYS_sub(Y,S) "Mapping (Y,S)";

* Blocks and block helper
$SET blocksize 1
*$eval totalBlocks ceil((card(YYY)*card(S))/%blocksize%)   Hans replaced by next
$eval totalBlocks ceil((card(Y)*card(S))/%blocksize%)

SET blocks /bl1*bl%totalBlocks%/
SET BlockSelected(blocks)

SET timeHelper /tH1*tH%blocksize%/


*Parameter blockAssignment(blocks,S,YYY);    Hans replaced by next
Parameter blockAssignment(blocks,S,Y);

*SET blockAssignmentHelper(S,blocks,timeHelper,YYY); Hans replaced by next
SET blockAssignmentHelper(S,blocks,timeHelper,Y);

*SET blockAssignmentTime(blocks,S,YYY);   Hans replaced by next
SET blockAssignmentTime(blocks,S,Y);

SCALAR annot_blockLast;
*PARAMETER annot_blockStage(S,YYY);   Hans replaced by next
PARAMETER annot_blockStage(S,Y);
