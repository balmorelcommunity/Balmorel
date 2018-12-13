PARAMETER SSSTTTMMM(SSS,TTT) 'S&T vs Month' %semislash%
$if     EXIST '../data/SSSTTTMMM.inc' $INCLUDE         '../data/SSSTTTMMM.inc';
$if not EXIST '../data/SSSTTTMMM.inc' $INCLUDE '../../base/data/SSSTTTMMM.inc';

PARAMETER GRTIME_M(CCC,GRDATASET,MMM)       "Months where tariff component applies" %semislash%
$if     EXIST '../data/GRTIME_M.inc' $INCLUDE         '../data/GRTIME_M.inc';
$if not EXIST '../data/GRTIME_M.inc' $INCLUDE '../../base/data/GRTIME_M.inc';

PARAMETER GRTIME_T(CCC,GRDATASET,TTT)       "Hours of week where tariff component applies" %semislash%
$if     EXIST '../data/GRTIME_T.inc' $INCLUDE         '../data/GRTIME_T.inc';
$if not EXIST '../data/GRTIME_T.inc' $INCLUDE '../../base/data/GRTIME_T.inc';

PARAMETER GR_PRICE_USER(CCC,DEUSER,GRDATASET)       "Data on grid tariff rates for demand user groups" %semislash%
$if     EXIST '../data/GR_PRICE_USER.inc' $INCLUDE         '../data/GR_PRICE_USER.inc';
$if not EXIST '../data/GR_PRICE_USER.inc' $INCLUDE '../../base/data/GR_PRICE_USER.inc';

PARAMETER GR_PRICE_TECH(CCC,GRDATASET)               "Data on grid tariff rates for power to X technologies" %semislash%
$if     EXIST '../data/GR_PRICE_TECH.inc' $INCLUDE         '../data/GR_PRICE_TECH.inc';
$if not EXIST '../data/GR_PRICE_TECH.inc' $INCLUDE '../../base/data/GR_PRICE_TECH.inc';



