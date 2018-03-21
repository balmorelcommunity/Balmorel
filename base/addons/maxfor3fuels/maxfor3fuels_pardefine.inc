PARAMETER MAXFOR3FUELS_GMAX3F(YYY,CCCRRRAAA,FFF,IFFFALIAS,IFFFALIAS2)             'Maximum fuel use per year combination of three fuels (default/0/, eps for 0) (GJ)' %semislash%
$if     EXIST '../data/MAXFOR3FUELS_GMAX3F.inc' $INCLUDE         '../data/MAXFOR3FUELS_GMAX3F.inc';
$if not EXIST '../data/MAXFOR3FUELS_GMAX3F.inc' $INCLUDE '../../base/data/MAXFOR3FUELS_GMAX3F.inc';
%semislash%;
