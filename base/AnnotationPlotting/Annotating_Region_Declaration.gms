****************************************************************************************************
* Blocks and block helper
$SET blocksize 1

$eval totalBlocks ceil(card(RRR)/%blocksize%)

SET blocks /bl1*bl%totalBlocks%/
SET regionHelper /rH1*rH%blocksize%/

display blocks;

SET blockAssignmentHelper(blocks,regionHelper, RRR) /(#blocks . #regionHelper ) : #RRR /

SET blockAssignmentRegions(blocks,RRR);
Option blockAssignmentRegions < blockAssignmentHelper     ;
display blockAssignmentRegions;

SET blockAssignmentAreas(blocks,AAA);

blockAssignmentAreas(blocks,IA) = sum(IR$(RRRAAA(IR,IA)), blockAssignmentRegions(blocks,IR));
display blockAssignmentAreas;