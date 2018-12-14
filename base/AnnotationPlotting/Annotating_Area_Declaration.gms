set AAA "years "/2012*2050/;
set IA(AAA) "assigned subet of y";

IA('2035')=yes;
IA('2025')=yes;

* Blocks and block helper
$SET blocksize 1

$eval totalBlocks ceil(card(AAA)/%blocksize%)

SET blocks /bl1*bl%totalBlocks%/
SET BlockSelected(blocks)
SET areaHelper /aH1*aH%blocksize%/
display blocks;

BlockSelected(blocks) = no;
Parameter blockAssignment(blocks,AAA);
blockAssignment(blocks,AAA) =no;
blockAssignment(blocks,IA) = yes;
display blockAssignment;



SET blockAssignmentHelper(blocks,areaHelper, AAA) /(#blocks . #areaHelper ) : #AAA /
SET blockAssignmentAreas(blocks,AAA);
display blockAssignmentHelper;
Option blockAssignmentAreas < blockAssignmentHelper     ;
display blockAssignmentAreas;


*SET blockAssignmentRegions(blocks,RRR);

*blockAssignmentRegions(blocks,IR) = sum(IA$(RRRAAA(IR,IA)), blockAssignmentAreas(blocks,IA));
*display blockAssignmentRegions;

$offorder
BlockSelected(blocks) = sum(AAA$(ord(blocks)=ord(AAA)),blockAssignment(blocks,AAA));
display BlockSelected;