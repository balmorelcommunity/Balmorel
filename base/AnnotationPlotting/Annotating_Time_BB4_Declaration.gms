* Subset of year and Season
$oninline
$oneolcom

SET IYS(YYY,SSS) "Mapping (IY411,SSS)"
$include ../../base/AnnotationPlotting/YSMapping.inc


SET IYS_sub(YYY,SSS) "Mapping (IY411,SSS)";

* Blocks and block helper
$SET blocksize 1
$eval totalBlocks ceil((card(YYY)*card(S))/%blocksize%)

SET blocks /bl1*bl%totalBlocks%/
SET BlockSelected(blocks)

SET timeHelper /tH1*tH%blocksize%/


Parameter blockAssignment(blocks,S,YYY);

SET blockAssignmentHelper(S,blocks,timeHelper,YYY);

SET blockAssignmentTime(blocks,S,YYY);

SCALAR annot_blockLast;
PARAMETER annot_blockStage(S,YYY);
