****************************************************************************************************
* Making mapping between time series indexs.
* The present code assumes card(SSS) is 52 and cart(TTT) is 168.
* The application of the mappings, e.g. in the form of generating time series on other time indexes is not presnetly included, it should be straightforwards.

$oneolcom
$oninline

*SET SSS /S01*S52/;
*SET TTT /T001*T168/;
SET DDD7 "Days in week, first is Monday" /D1*D7/;
SET DDD364 "Days in year  (short year, 364 days)" /D001*D364/;
set HHH24 "Hour of the day" /H01*H24/;
display ddd7,hhh24;

SET HHH24TTT(TTT,HHH24) "Mapping between (SSS,TTT) and (TTT,HHH24)";
HHH24TTT(TTT,HHH24)$(MOD(ORD(TTT),24) EQ ORD(HHH24)) = YES;  !!  mod(x,y)  returns the remainder of x divided by y
* The above misses the situation where (MOD(ORD(TTT),24) EQ 1), therefore:
HHH24TTT(TTT,HHH24)$((MOD(ORD(TTT),24) EQ 0) and (ORD(HHH24) eq 24)) = YES;
DISPLAY  HHH24TTT;

SET DDD7HHH24(DDD7,HHH24) "Mapping between (SSS,TTT) and ";
DDD7HHH24(DDD7,HHH24)  = YES;
DISPLAY  DDD7HHH24;

SET DDD7TTT(DDD7,TTT) "Mapping between (SSS,TTT) and (DDD7,TTT)";
DDD7TTT(DDD7,TTT)$(( (ORD(DDD7)-1)*24 LT (ORD(TTT) ))  AND (ORD(TTT) LE (ORD(DDD7)*24) ) ) = YES;
DISPLAY DDD7TTT;

SET DDD364TTT(DDD364,TTT) "Mapping between (SSS,TTT) and (DDD364,TTT)";
DDD364TTT(DDD364,TTT)$(( (MOD(ORD(DDD364),7)-1)*24 LT (ORD(TTT) ))  AND (ORD(TTT) LE (MOD(ORD(DDD364),7)*24) ) ) = YES;
* The above misses the situation where (MOD(ORD(TTT),24) EQ 1), therefore:
DDD364TTT(DDD364,TTT)$((ORD(DDD364) EQ 364) AND (144 LT ORD(TTT) )) = YES;
DISPLAY DDD364TTT ;

SET DDD364SSS(DDD364,SSS) "Mapping between (SSS,TTT) and (DDD364,SSS)";
DDD364SSS(DDD364,SSS)$(((ORD(SSS)-1)*7 LT ORD(DDD364)) AND (ORD(DDD364) LE (ORD(SSS)*7))) = YES;
DISPLAY DDD364SSS ;


SET DDD364SSTTT(DDD364,SSS,TTT) "Mapping between (SSS,TTT) and (DDD364,SSS,TTT)";
DDD364SSTTT(DDD364,SSS,TTT)$(DDD364SSS(DDD364,SSS) AND DDD364TTT(DDD364,TTT)) = YES;
DISPLAY  DDD364SSTTT;

* Blocks and block helper
$SET blocksize 1

$eval totalBlocks ceil(card(DDD364)/%blocksize%)

SET blocks /bl1*bl%totalBlocks%/
SET dayHelper /sH1*sH%blocksize%/

display blocks;
SET blockAssignmentHelper(blocks,dayHelper, DDD364) /(#blocks . #dayHelper ) : #DDD364 /

SET blockAssignmentDay(blocks,DDD364);
Option blockAssignmentDay < blockAssignmentHelper     ;

SET blockAssignmentSeason(blocks,SSS);
blockAssignmentSeason(blocks,S) = sum(DDD364$DDD364SSS(DDD364,S), blockAssignmentDay(blocks,DDD364));

SET blockAssignmentSeasonDay(blocks,SSS,TTT);

blockAssignmentSeasonDay(blocks,S,T) = sum(DDD364$DDD364SSTTT(DDD364,S,T), blockAssignmentDay(blocks,DDD364));
display blockAssignmentSeasonDay;