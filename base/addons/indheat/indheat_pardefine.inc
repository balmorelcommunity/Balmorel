PARAMETER INDHEAT_DH_VAR_T(INDHEAT_AAA,SSS,TTT) 'Variation in individual heat demand' %semislash%
$if     EXIST '../data/INDHEAT_DH_VAR_T.inc' $INCLUDE         '../data/INDHEAT_DH_VAR_T.inc';
$if not EXIST '../data/INDHEAT_DH_VAR_T.inc' $INCLUDE '../../base/data/INDHEAT_DH_VAR_T.inc';

PARAMETER INDHEAT_DH(YYY,INDHEAT_AAA) 'BRUTTO nominal annual individual heat consumption' %semislash%
$if     EXIST '../data/INDHEAT_DH.inc' $INCLUDE         '../data/INDHEAT_DH.inc';
$if not EXIST '../data/INDHEAT_DH.inc' $INCLUDE '../../base/data/INDHEAT_DH.inc';

PARAMETER INDHEAT_GKFX(YYY,INDHEAT_AAA,INDHEAT_GGG,INDHEAT_GROUP) 'Installed capacities' %semislash%
$if     EXIST '../data/INDHEAT_GKFX.inc' $INCLUDE         '../data/INDHEAT_GKFX.inc';
$if not EXIST '../data/INDHEAT_GKFX.inc' $INCLUDE '../../base/data/INDHEAT_GKFX.inc';

PARAMETER INDHEAT_GDATA(INDHEAT_GGG,GDATASET) 'Technology characteristics' %semislash%
$if     EXIST '../data/INDHEAT_GDATA.inc' $INCLUDE         '../data/INDHEAT_GDATA.inc';
$if not EXIST '../data/INDHEAT_GDATA.inc' $INCLUDE '../../base/data/INDHEAT_GDATA.inc';

PARAMETER INDHEAT_MINPERCENT(YYY,INDHEAT_AAA,INDHEAT_GROUP) 'Minimum percentage assumed to be fixed to a specific group' %semislash%
$if     EXIST '../data/INDHEAT_MINPERCENT.inc' $INCLUDE         '../data/INDHEAT_MINPERCENT.inc';
$if not EXIST '../data/INDHEAT_MINPERCENT.inc' $INCLUDE '../../base/data/INDHEAT_MINPERCENT.inc';

PARAMETER INDHEAT_ANNUITYCG(CCC,INDHEAT_GGG) 'Transforms investment to annual payment (fraction)'
$if     EXIST '../data/INDHEAT_ANNUITYCG.inc' $INCLUDE         '../data/INDHEAT_ANNUITYCG.inc';
$if not EXIST '../data/INDHEAT_ANNUITYCG.inc' $INCLUDE '../../base/data/INDHEAT_ANNUITYCG.inc';

PARAMETER INDHEAT_AGKN(INDHEAT_AAA,INDHEAT_GGG,INDHEAT_GROUP)  'Allowed investment in area'
$if     EXIST '../data/INDHEAT_AGKN.inc' $INCLUDE         '../data/INDHEAT_AGKN.inc';
$if not EXIST '../data/INDHEAT_AGKN.inc' $INCLUDE '../../base/data/INDHEAT_AGKN.inc';

PARAMETER TEST(YYY,INDHEAT_AAA,INDHEAT_GGG,INDHEAT_GROUP)