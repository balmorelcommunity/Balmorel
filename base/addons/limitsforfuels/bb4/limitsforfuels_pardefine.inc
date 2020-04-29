PARAMETER LIMITSFORFUELS_CONVFACTOR(FFF)           'Conversion factor for fuels if setting a maximum for several fuels' %semislash%
$if     EXIST '../data/LIMITSFORFUELS_CONVFACTORMAX.inc' $INCLUDE         '../data/LIMITSFORFUELS_CONVFACTORMAX.inc';
$if not EXIST '../data/LIMITSFORFUELS_CONVFACTORMAX.inc' $INCLUDE '../../base/data/LIMITSFORFUELS_CONVFACTORMAX.inc';
%semislash%;

PARAMETER LIMITSFORFUELS_CONVFACTORMIN(FFF)        'Conversion factor for fuels if setting a minimum for several fuels' %semislash%
$if     EXIST '../data/LIMITSFORFUELS_CONVFACTORMIN.inc' $INCLUDE         '../data/LIMITSFORFUELS_CONVFACTORMIN.inc';
$if not EXIST '../data/LIMITSFORFUELS_CONVFACTORMIN.inc' $INCLUDE '../../base/data/LIMITSFORFUELS_CONVFACTORMIN.inc';
%semislash%;

PARAMETER LIMITSFORFUELS_GMAXF(YYY,CCCRRRAAA,FFF)  'Maximum fuel use (GJ) per year for several fuels' %semislash%
$if     EXIST '../data/LIMITSFORFUELS_GMAXF.inc' $INCLUDE         '../data/LIMITSFORFUELS_GMAXF.inc';
$if not EXIST '../data/LIMITSFORFUELS_GMAXF.inc' $INCLUDE '../../base/data/LIMITSFORFUELS_GMAXF.inc';
%semislash%;

PARAMETER LIMITSFORFUELS_GMINF(YYY,CCCRRRAAA,FFF)  'Minimum fuel use (GJ) per year for several fuels' %semislash%
$if     EXIST '../data/LIMITSFORFUELS_GMINF.inc' $INCLUDE         '../data/LIMITSFORFUELS_GMINF.inc';
$if not EXIST '../data/LIMITSFORFUELS_GMINF.inc' $INCLUDE '../../base/data/LIMITSFORFUELS_GMINF.inc';
%semislash%;
