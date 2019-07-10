SET LIMITSFORFUELS_NUMCONMAX  'Sets in which a combination of maxima are set' %semislash%
$if     EXIST '../data/LIMITSFORFUELS_NUMCONMAX.inc' $INCLUDE         '../data/LIMITSFORFUELS_NUMCONMAX.inc';
$if not EXIST '../data/LIMITSFORFUELS_NUMCONMAX.inc' $INCLUDE '../../base/data/LIMITSFORFUELS_NUMCONMAX.inc';
%semislash%;

SET LIMITSFORFUELS_GMAXFSET(LIMITSFORFUELS_NUMCONMAX,CCCRRRAAA,FFF) 'Sets of which a combination of maxima are set' %semislash%
$if     EXIST '../data/LIMITSFORFUELS_GMAXFSET.inc' $INCLUDE         '../data/LIMITSFORFUELS_GMAXFSET.inc';
$if not EXIST '../data/LIMITSFORFUELS_GMAXFSET.inc' $INCLUDE '../../base/data/LIMITSFORFUELS_GMAXFSET.inc';
%semislash%;

SET LIMITSFORFUELS_VGFMAXSET(LIMITSFORFUELS_NUMCONMAX,CCCRRRAAA,FFF) 'Sets of which a combination of maxima are set' %semislash%
$if     EXIST '../data/LIMITSFORFUELS_VGFMAXSET.inc' $INCLUDE         '../data/LIMITSFORFUELS_VGFMAXSET.inc';
$if not EXIST '../data/LIMITSFORFUELS_VGFMAXSET.inc' $INCLUDE '../../base/data/LIMITSFORFUELS_VGFMAXSET.inc';
%semislash%;

SET LIMITSFORFUELS_NUMCONMIN  'Sets in which a combination of minima are set' %semislash%
$if     EXIST '../data/LIMITSFORFUELS_NUMCONMIN.inc' $INCLUDE         '../data/LIMITSFORFUELS_NUMCONMIN.inc';
$if not EXIST '../data/LIMITSFORFUELS_NUMCONMAX.inc' $INCLUDE '../../base/data/LIMITSFORFUELS_NUMCONMIN.inc';
%semislash%;

SET LIMITSFORFUELS_GMINFSET(LIMITSFORFUELS_NUMCONMIN,CCCRRRAAA,FFF) 'Sets of which a combination of minima are set' %semislash%
$if     EXIST '../data/LIMITSFORFUELS_GMINFSET.inc' $INCLUDE         '../data/LIMITSFORFUELS_GMINFSET.inc';
$if not EXIST '../data/LIMITSFORFUELS_GMAXFSET.inc' $INCLUDE '../../base/data/LIMITSFORFUELS_GMINFSET.inc';
%semislash%;

SET LIMITSFORFUELS_VGFMINSET(LIMITSFORFUELS_NUMCONMIN,CCCRRRAAA,FFF) 'Sets of which a combination of minima are set' %semislash%
$if     EXIST '../data/LIMITSFORFUELS_VGFMINSET.inc' $INCLUDE         '../data/LIMITSFORFUELS_VGFMINSET.inc';
$if not EXIST '../data/LIMITSFORFUELS_VGFMINSET.inc' $INCLUDE '../../base/data/LIMITSFORFUELS_VGFMINSET.inc';
%semislash%;