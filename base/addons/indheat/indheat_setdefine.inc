SET
INDHEAT_GROUP 'Group of technologies' %semislash%
$if     EXIST '../data/INDHEAT_GROUP.inc' $INCLUDE         '../data/INDHEAT_GROUP.inc';
$if not EXIST '../data/INDHEAT_GROUP.inc' $INCLUDE '../../base/data/INDHEAT_GROUP.inc';

INDHEAT_AAA(AAA) 'Areas with individual heating' %semislash%
$if     EXIST '../data/INDHEAT_AAA.inc' $INCLUDE         '../data/INDHEAT_AAA.inc';
$if not EXIST '../data/INDHEAT_AAA.inc' $INCLUDE '../../base/data/INDHEAT_AAA.inc';

INDHEAT_G 'Individual heating technologies' %semislash%
$if     EXIST '../data/INDHEAT_G.inc' $INCLUDE         '../data/INDHEAT_G.inc';
$if not EXIST '../data/INDHEAT_G.inc' $INCLUDE '../../base/data/INDHEAT_G.inc';

INDHEAT_GINGROUP(INDHEAT_G,INDHEAT_GROUP) 'Technologies belonging to each group' %semislash%
$if     EXIST '../data/INDHEAT_GINGROUP.inc' $INCLUDE         '../data/INDHEAT_GINGROUP.inc';
$if not EXIST '../data/INDHEAT_GINGROUP.inc' $INCLUDE '../../base/data/INDHEAT_GINGROUP.inc';

ALIAS(INDHEAT_GROUP, INDHEAT_GROUPFROM);
ALIAS(INDHEAT_GROUP, INDHEAT_GROUPTO);

INDHEAT_GMOVE(INDHEAT_G,INDHEAT_GROUPFROM,INDHEAT_GROUPTO) 'Technologies that can be moved from group GROUPFROM to GROUPTO' %semislash%
$if     EXIST '../data/INDHEAT_GMOVE.inc' $INCLUDE         '../data/INDHEAT_GMOVE.inc';
$if not EXIST '../data/INDHEAT_GMOVE.inc' $INCLUDE '../../base/data/INDHEAT_GMOVE.inc';
