SET LIMITSFORFUELS_NUMCONMAX  'Sets in which a combination of maxima are set' %semislash%
$if     EXIST '../data/LIMITSFORFUELS_NUMCONMAX.inc' $INCLUDE         '../data/LIMITSFORFUELS_NUMCONMAX.inc';
$if not EXIST '../data/LIMITSFORFUELS_NUMCONMAX.inc' $INCLUDE '../../base/data/LIMITSFORFUELS_NUMCONMAX.inc';
%semislash%;

SET LIMITSFORFUELS_GMAXFSET(LIMITSFORFUELS_NUMCONMAX,CCCRRRAAA,FFF) 'Sets of which a combination of maxima are set' %semislash%
$if     EXIST '../data/LIMITSFORFUELS_GMAXFSET.inc' $INCLUDE         '../data/LIMITSFORFUELS_GMAXFSET.inc';
$if not EXIST '../data/LIMITSFORFUELS_GMAXFSET.inc' $INCLUDE '../../base/data/LIMITSFORFUELS_GMAXFSET.inc';
%semislash%;

SET LIMITSFORFUELS_VGFSET(LIMITSFORFUELS_NUMCONMAX,CCCRRRAAA,FFF) 'Sets of which a combination of maxima are set' %semislash%
$if     EXIST '../data/LIMITSFORFUELS_VGFSET.inc' $INCLUDE         '../data/LIMITSFORFUELS_VGFSET.inc';
$if not EXIST '../data/LIMITSFORFUELS_VGFSET.inc' $INCLUDE '../../base/data/LIMITSFORFUELS_VGFSET.inc';
%semislash%;