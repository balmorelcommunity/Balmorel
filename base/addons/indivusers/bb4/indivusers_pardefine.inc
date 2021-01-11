*Individual users addon

PARAMETER INDIVUSERS_MINSHARE_DH(YYY,RRR,DHUSER,INDIVUSERS_GROUP) 'Minimum share of heat demand per heat user in an individual user group (-)' %semislash%
$if     EXIST '../data/INDIVUSERS_MINSHARE_DH.inc' $INCLUDE         '../data/INDIVUSERS_MINSHARE_DH.inc';
$if not EXIST '../data/INDIVUSERS_MINSHARE_DH.inc' $INCLUDE '../../base/data/INDIVUSERS_MINSHARE_DH.inc';
%semislash%;

PARAMETER INDIVUSERS_MAXSHARE_DH(YYY,RRR,DHUSER,INDIVUSERS_GROUP) 'Maximum share of heat demand per heat user in an individual user group (-)' %semislash%
$if     EXIST '../data/INDIVUSERS_MAXSHARE_DH.inc' $INCLUDE         '../data/INDIVUSERS_MAXSHARE_DH.inc';
$if not EXIST '../data/INDIVUSERS_MAXSHARE_DH.inc' $INCLUDE '../../base/data/INDIVUSERS_MAXSHARE_DH.inc';
%semislash%;

