PARAMETER INDHEAT_DH_VAR_T(INDHEAT_AAA,INDHEAT_DHUSER,SSS,TTT) 'Variation in individual heat demand' %semislash%
$if     EXIST '../data/INDHEAT_DH_VAR_T.inc' $INCLUDE         '../data/INDHEAT_DH_VAR_T.inc';
$if not EXIST '../data/INDHEAT_DH_VAR_T.inc' $INCLUDE '../../base/data/INDHEAT_DH_VAR_T.inc';
%semislash%

PARAMETER INDHEAT_GINSTALL(YYY,INDHEAT_AAA,INDHEAT_GGG,INDHEAT_GROUP) 'Initial installed capacities percentage' %semislash%
*$if     EXIST '../data/INDHEAT_GINSTALL.inc' $INCLUDE         '../data/INDHEAT_GINSTALL.inc';
$if     EXIST '../data/INDHEAT_GINSTALL%TECHALT%.inc' $INCLUDE '../data/INDHEAT_GINSTALL%TECHALT%.inc';
$if not EXIST '../data/INDHEAT_GINSTALL%TECHALT%.inc' $INCLUDE '../data/INDHEAT_GINSTALL.inc';
$if not EXIST '../data/INDHEAT_GINSTALL.inc' $INCLUDE '../../base/data/INDHEAT_GINSTALL.inc';
%semislash%

PARAMETER INDHEAT_DH(YYY,INDHEAT_AAA,INDHEAT_DHUSER) 'BRUTTO nominal annual individual heat consumption' %semislash%
$if     EXIST '../data/INDHEAT_DH%TECHALT%.inc' $INCLUDE '../data/INDHEAT_DH%TECHALT%.inc';
$if not EXIST '../data/INDHEAT_DH%TECHALT%.inc' $INCLUDE         '../data/INDHEAT_DH.inc';
$if not EXIST '../data/INDHEAT_DH.inc' $INCLUDE '../../base/data/INDHEAT_DH.inc';
%semislash%

PARAMETER INDHEAT_GDATA(INDHEAT_GGG,GDATASET) 'Technology characteristics' %semislash%
$if     EXIST '../data/INDHEAT_GDATA%TECHALT%.inc' $INCLUDE         '../data/INDHEAT_GDATA%TECHALT%.inc';
$if not EXIST '../data/INDHEAT_GDATA%TECHALT%.inc' $INCLUDE         '../data/INDHEAT_GDATA.inc';
$if not EXIST '../data/INDHEAT_GDATA.inc' $INCLUDE '../../base/data/INDHEAT_GDATA.inc';
%semislash%

*Internal sets needed for data assignment:
Sets
INDHEAT_IGHSTO(INDHEAT_G)
INDHEAT_IGROUPSTO(INDHEAT_GROUP)
;
INDHEAT_IGHSTO(INDHEAT_G) = YES$(INDHEAT_GDATA(INDHEAT_G,'GDTYPE') EQ GHSTO);
INDHEAT_IGROUPSTO(INDHEAT_GROUP) = YES$(SUM(INDHEAT_IGHSTO,INDHEAT_GINGROUP(INDHEAT_IGHSTO,INDHEAT_GROUP)));

PARAMETER INDHEAT_STOFACTOR(INDHEAT_GROUP)        'Division factor for GKFX/VGKN on  size of storage'%semislash%
$if     EXIST '../data/INDHEAT_STOFACTOR.inc' $INCLUDE         '../data/INDHEAT_STOFACTOR.inc';
$if not EXIST '../data/INDHEAT_STOFACTOR.inc' $INCLUDE '../../base/data/INDHEAT_STOFACTOR.inc';

PARAMETER INDHEAT_GKFX(YYY,INDHEAT_AAA,INDHEAT_GGG,INDHEAT_GROUP) 'Installed capacities' %semislash%
*$if     EXIST '../data/INDHEAT_GKFX.inc' $INCLUDE         '../data/INDHEAT_GKFX.inc';
$if     EXIST '../data/INDHEAT_GKFX%TECHALT%.inc' $INCLUDE '../data/INDHEAT_GKFX%TECHALT%.inc';
$if not EXIST '../data/INDHEAT_GKFX%TECHALT%.inc' $INCLUDE '../data/INDHEAT_GKFX.inc';
$if not EXIST '../data/INDHEAT_GKFX.inc' $INCLUDE '../../base/data/INDHEAT_GKFX.inc';
%semislash%

PARAMETER INDHEAT_ANNUITYCG(CCC,INDHEAT_GGG) 'Transforms investment to annual payment (fraction)' %semislash%
$if     EXIST '../data/INDHEAT_ANNUITYCG.inc' $INCLUDE         '../data/INDHEAT_ANNUITYCG.inc';
$if not EXIST '../data/INDHEAT_ANNUITYCG.inc' $INCLUDE '../../base/data/INDHEAT_ANNUITYCG.inc';
%semislash%

PARAMETER INDHEAT_AGKN(INDHEAT_AAA,INDHEAT_GGG,INDHEAT_GROUP)  'Allowed investment in area' %semislash%
*$if     EXIST '../data/.inc' $INCLUDE         '../data/INDHEAT_AGKN.inc';
$if     EXIST '../data/INDHEAT_AGKN%TECHALT%.inc' $INCLUDE '../data/INDHEAT_AGKN%TECHALT%.inc';
$if not EXIST '../data/INDHEAT_AGKN%TECHALT%.inc' $INCLUDE '../data/INDHEAT_AGKN.inc';
$if not EXIST '../data/INDHEAT_AGKN.inc' $INCLUDE '../../base/data/INDHEAT_AGKN.inc';
%semislash%

PARAMETER INDHEAT_MINPERCENT(YYY,INDHEAT_AAA,INDHEAT_GROUP) 'Minimum percentage assumed to be fixed to a specific group' %semislash%
$if     EXIST '../data/INDHEAT_MINPERCENT%TECHALT%.inc' $INCLUDE         '../data/INDHEAT_MINPERCENT%TECHALT%.inc';
$if not EXIST '../data/INDHEAT_MINPERCENT%TECHALT%.inc' $INCLUDE '../data/INDHEAT_MINPERCENT.inc';
$if not EXIST '../data/INDHEAT_MINPERCENT.inc' $INCLUDE '../../base/data/INDHEAT_MINPERCENT.inc';
%semislash%

PARAMETER INDHEAT_MINPERCENTREL(YYY,INDHEAT_AAA,INDHEAT_SUMGROUP) 'Minimum percentage assumed to be fixed to a specific summed group' %semislash%
$if     EXIST '../data/INDHEAT_MINPERCENTREL.inc' $INCLUDE         '../data/INDHEAT_MINPERCENTREL.inc';
$if not EXIST '../data/INDHEAT_MINPERCENTREL.inc' $INCLUDE '../../base/data/INDHEAT_MINPERCENTREL.inc';
%semislash%

PARAMETER INDHEAT_MAXPERCENT(YYY,INDHEAT_AAA,INDHEAT_GROUP)       'Max percent that can be served by a group (%)' %semislash%
$if     EXIST '../data/INDHEAT_MAXPERCENT.inc' $INCLUDE         '../data/INDHEAT_MAXPERCENT.inc';
$if not EXIST '../data/INDHEAT_MAXPERCENT.inc' $INCLUDE '../../base/data/INDHEAT_MAXPERCENT.inc';

PARAMETER INDHEAT_MAXPERCENTREL(YYY,INDHEAT_AAA,INDHEAT_SUMGROUP) 'Maximum percentage assumed to be fixed to a specific summed group' %semislash%
$if     EXIST '../data/INDHEAT_MINPERCENTREL.inc' $INCLUDE         '../data/INDHEAT_MAXPERCENTREL.inc';
$if not EXIST '../data/INDHEAT_MINPERCENTREL.inc' $INCLUDE '../../base/data/INDHEAT_MAXPERCENTREL.inc';
%semislash%

PARAMETER INDHEAT_COP(INDHEAT_AAA,INDHEAT_GGG,INDHEAT_GROUP,SSS,TTT)  'COP of heat pump technologies' %semislash%
$if     EXIST '../data/INDHEAT_COP.inc' $INCLUDE         '../data/INDHEAT_COP.inc';
$if not EXIST '../data/INDHEAT_COP.inc' $INCLUDE '../../base/data/INDHEAT_COP.inc';
%semislash%

PARAMETER INDHEAT_SOLH_VAR_T(INDHEAT_AAA,SSS,TTT) 'Variation in solar heating profile' %semislash%
$if     EXIST '../data/INDHEAT_SOLH_VAR_T.inc' $INCLUDE         '../data/INDHEAT_SOLH_VAR_T.inc';
$if not EXIST '../data/INDHEAT_SOLH_VAR_T.inc' $INCLUDE '../../base/data/INDHEAT_SOLH_VAR_T.inc';
%semislash%

PARAMETER INDHEAT_SOLHFLH(INDHEAT_AAA) 'Solar heating FLH' %semislash%
$if     EXIST '../data/INDHEAT_SOLHFLH.inc' $INCLUDE         '../data/INDHEAT_SOLHFLH.inc';
$if not EXIST '../data/INDHEAT_SOLHFLH.inc' $INCLUDE '../../base/data/INDHEAT_SOLHFLH.inc';
%semislash%

PARAMETER INDHEAT_CARDGROUP(INDHEAT_GROUP) 'Cardinality of groups of technologies' %semislash%
$if     EXIST '../data/INDHEAT_CARDGROUP.inc' $INCLUDE         '../data/INDHEAT_CARDGROUP.inc';
$if not EXIST '../data/INDHEAT_CARDGROUP.inc' $INCLUDE '../../base/data/INDHEAT_CARDGROUP.inc';
%semislash%

PARAMETER INDHEAT_FACTORINVCOST(YYY,INDHEAT_GGG,INDHEAT_GROUP) 'Factor to multiply investment cost with for specific heating groups (default 1)' %semislash%
$if     EXIST '../data/INDHEAT_FACTORINVCOST.inc' $INCLUDE         '../data/INDHEAT_FACTORINVCOST.inc';
$if not EXIST '../data/INDHEAT_FACTORINVCOST.inc' $INCLUDE '../../base/data/INDHEAT_FACTORINVCOST.inc';
%semislash%

PARAMETER INDHEAT_FACTOROMFCOST(YYY,INDHEAT_GGG,INDHEAT_GROUP) 'Factor to multiply fixed O&M cost with for specific heating groups (default 1)' %semislash%
$if     EXIST '../data/INDHEAT_FACTOROMFCOST.inc' $INCLUDE         '../data/INDHEAT_FACTOROMFCOST.inc';
$if not EXIST '../data/INDHEAT_FACTOROMFCOST.inc' $INCLUDE '../../base/data/INDHEAT_FACTOROMFCOST.inc';
%semislash%

PARAMETER INDHEAT_RETROFITFACTOR(INDHEAT_GGG)        'Percentage of investment cost paid when retrofitting' %semislash%
$if     EXIST '../data/INDHEAT_RETROFITFACTOR.inc' $INCLUDE         '../data/INDHEAT_RETROFITFACTOR.inc';
$if not EXIST '../data/INDHEAT_RETROFITFACTOR.inc' $INCLUDE '../../base/data/INDHEAT_RETROFITFACTOR.inc';

