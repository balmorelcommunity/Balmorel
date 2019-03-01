SET
INDHEAT_GROUP 'Group of technologies' %semislash%
$if     EXIST '../data/INDHEAT_GROUP.inc' $INCLUDE         '../data/INDHEAT_GROUP.inc';
$if not EXIST '../data/INDHEAT_GROUP.inc' $INCLUDE '../../base/data/INDHEAT_GROUP.inc';

SET
INDHEAT_AAA(AAA) 'Areas with individual heating' %semislash%
$if     EXIST '../data/INDHEAT_AAA.inc' $INCLUDE         '../data/INDHEAT_AAA.inc';
$if not EXIST '../data/INDHEAT_AAA.inc' $INCLUDE '../../base/data/INDHEAT_AAA.inc';

SET
INDHEAT_GGG 'Individual heating technologies' %semislash%
$if     EXIST '../data/INDHEAT_GGG.inc' $INCLUDE         '../data/INDHEAT_GGG.inc';
$if not EXIST '../data/INDHEAT_GGG.inc' $INCLUDE '../../base/data/INDHEAT_GGG.inc';

SET
INDHEAT_G(INDHEAT_GGG) 'Individual heating technologies in simulation' %semislash%
$if     EXIST '../data/INDHEAT_G.inc' $INCLUDE         '../data/INDHEAT_G.inc';
$if not EXIST '../data/INDHEAT_G.inc' $INCLUDE '../../base/data/INDHEAT_G.inc';

SET
INDHEAT_GINGROUP(INDHEAT_GGG,INDHEAT_GROUP) 'Technologies belonging to each group' %semislash%
$if     EXIST '../data/INDHEAT_GINGROUP.inc' $INCLUDE         '../data/INDHEAT_GINGROUP.inc';
$if not EXIST '../data/INDHEAT_GINGROUP.inc' $INCLUDE '../../base/data/INDHEAT_GINGROUP.inc';

ALIAS(INDHEAT_GROUP, INDHEAT_GROUPFROM);
ALIAS(INDHEAT_GROUP, INDHEAT_GROUPTO);
ALIAS(INDHEAT_G,INDHEAT_GALIAS);

SET
INDHEAT_GMOVE(INDHEAT_GGG,INDHEAT_GROUPFROM,INDHEAT_GROUPTO) 'Technologies that can be moved from group GROUPFROM to GROUPTO' %semislash%
$if     EXIST '../data/INDHEAT_GMOVE.inc' $INCLUDE         '../data/INDHEAT_GMOVE.inc';
$if not EXIST '../data/INDHEAT_GMOVE.inc' $INCLUDE '../../base/data/INDHEAT_GMOVE.inc';
