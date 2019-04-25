* 20190425 Hans
* Subset of year and Season
$oninline
$oneolcom

$LOG "##### Entering Annotating_Time_BB4_Declaration.inc #####"
SET IYS(YYY,SSS) "Mapping (YYY,SSS)"

$include ../../base/AnnotationPlotting/YSMapping.inc

SET IYS_sub(Y,S) "Mapping (Y,S)";

* Blocks and block helper
$SET blocksize 1
$eval totalBlocks ceil((card(Y)*card(S))/%blocksize%)

SET blocks /bl1*bl%totalBlocks%/
SET BlockSelected(blocks)

SET timeHelper /tH1*tH%blocksize%/

Parameter blockAssignment(Y, blocks,S);

SET blockAssignmentHelper(Y,S,blocks,timeHelper);

SET blockAssignmentTime(Y,blocks,S);

SCALAR annot_blockFirst /1/;
SCALAR annot_blockLast;
* For testing something:


PARAMETER annot_blockStage(S,Y);

* The next are for unloading to gdx file, see Annotating_Time_BB4
acronym SeeTheText;
SCALAR   Annotating_Time_BB4_BASIC "Basic sets and assigments for the BB4 time annotation " /SeeTheText/;

display "Basic from the Annotation_Time_BB4_Declaration.gms file, in order of Definitions:", IYS,  blocks, timeHelper;

option blockAssignment:0,  annot_blockFirst:0,  annot_blockLast:0,  annot_blockStage:0 ;

$LOG "##### Leaving Annotating_Time_BB4_Declaration.inc #####"


