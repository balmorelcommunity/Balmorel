PARAMETER LIMITSFORFUELS_CONVFACTOR(FFF)           'Conversion factor from wood, woodwaste, straw to thermgas (FFF=thermgas, thermgas_up, thermgas_h2)' %semislash%
$if     EXIST '../data/LIMITSFORFUELS_CONVFACTOR.inc' $INCLUDE         '../data/LIMITSFORFUELS_CONVFACTOR.inc';
$if not EXIST '../data/LIMITSFORFUELS_CONVFACTOR.inc' $INCLUDE '../../base/data/LIMITSFORFUELS_CONVFACTOR.inc';
%semislash%;
