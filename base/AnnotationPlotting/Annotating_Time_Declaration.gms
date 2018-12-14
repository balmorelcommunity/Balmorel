****************************************************************************************************
* Blocks and block helper
$SET blocksize 1

$eval totalBlocks ceil(card(IS3)/%blocksize%)

SET blocks /bl1*bl%totalBlocks%/
SET seasonHelper /sH1*sH%blocksize%/

SET blockAssignmentHelper(blocks,seasonHelper, IS3) /(#blocks . #seasonHelper ) : #S /

SET blockAssignmentSeasons(blocks,IS3);
Option blockAssignmentSeasons < blockAssignmentHelper     ;

$offorder
SCALAR annot_blockLast;
annot_blockLast = card(blocks) + 2;

PARAMETER annot_blockStage(S);
annot_blockStage(S) = sum(blockAssignmentSeasons(blocks,IS3), ord(blocks)) + 1;
$onorder


