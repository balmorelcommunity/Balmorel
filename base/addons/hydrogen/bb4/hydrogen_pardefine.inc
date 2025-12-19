PARAMETER HYDROGEN_DH2(YYY,CCCRRRAAA)  'Yearly demand for hydrogen'   %semislash%
$if     EXIST '../data/HYDROGEN_DH2.inc' $INCLUDE         '../data/HYDROGEN_DH2.inc';
$if not EXIST '../data/HYDROGEN_DH2.inc' $INCLUDE '../../base/data/HYDROGEN_DH2.inc';
%semislash%;


PARAMETER HYDROGEN_FLEXDH2(YYY,CCCRRRAAA)  'Yearly demand for hydrogen'   %semislash%
$if     EXIST '../data/HYDROGEN_FLEXDH2.inc' $INCLUDE         '../data/HYDROGEN_FLEXDH2.inc';
$if not EXIST '../data/HYDROGEN_FLEXDH2.inc' $INCLUDE '../../base/data/HYDROGEN_FLEXDH2.inc';
%semislash%;

PARAMETER HYDROGEN_DH2_VAR_T(CCCRRRAAA,SSS,TTT) 'Variation profile of H2 demand per region'  %semislash%
$if     EXIST '../data/HYDROGEN_DH2_VAR_T.inc' $INCLUDE         '../data/HYDROGEN_DH2_VAR_T.inc';
$if not EXIST '../data/HYDROGEN_DH2_VAR_T.inc' $INCLUDE '../../base/data/HYDROGEN_DH2_VAR_T.inc';
%semislash%;

PARAMETER DISLOSS_H2(CCCRRRAAA) 'Distribution loss H2'  %semislash%
$if     EXIST '../data/HYDROGEN_DISLOSS_H2.inc' $INCLUDE         '../data/HYDROGEN_DISLOSS_H2.inc';
$if not EXIST '../data/HYDROGEN_DISLOSS_H2.inc' $INCLUDE '../../base/data/HYDROGEN_DISLOSS_H2.inc';
%semislash%;

PARAMETER HYDROGEN_STOVOL_START(Y,AAA,G,SSS)    'Start level of hydrogen storage';
* Include start filling level of hydrogen storage obtained from yearly simulation
$ifi %bb3%==yes execute_load '../../simex/HYDROGEN_STOVOL_START.gdx', HYDROGEN_STOVOL_START;

$onmulti
$if     EXIST '../data/HYDROGEN_DAC_DE.inc' $INCLUDE         '../data/HYDROGEN_DAC_DE.inc';
$if not EXIST '../data/HYDROGEN_DAC_DE.inc' $INCLUDE '../../base/data/HYDROGEN_DAC_DE.inc';

$if     EXIST '../data/HYDROGEN_DAC_DH.inc' $INCLUDE         '../data/HYDROGEN_DAC_DH.inc';
$if not EXIST '../data/HYDROGEN_DAC_DH.inc' $INCLUDE '../../base/data/HYDROGEN_DAC_DH.inc';

$if     EXIST '../data/HYDROGEN_METHANATION_DE.inc' $INCLUDE         '../data/HYDROGEN_METHANATION_DE.inc';
$if not EXIST '../data/HYDROGEN_METHANATION_DE.inc' $INCLUDE '../../base/data/HYDROGEN_METHANATION_DE.inc';

$if     EXIST '../data/HYDROGEN_METHANATION_DH2.inc' $INCLUDE         '../data/HYDROGEN_METHANATION_DH2.inc';
$if not EXIST '../data/HYDROGEN_METHANATION_DH2.inc' $INCLUDE '../../base/data/HYDROGEN_METHANATION_DH2.inc';

$if     EXIST '../data/HYDROGEN_BIOGASUPGRADING_DE.inc' $INCLUDE         '../data/HYDROGEN_BIOGASUPGRADING_DE.inc';
$if not EXIST '../data/HYDROGEN_BIOGASUPGRADING_DE.inc' $INCLUDE '../../base/data/HYDROGEN_BIOGASUPGRADING_DE.inc';

$if     EXIST '../data/HYDROGEN_XH2KFX.inc' $INCLUDE         '../data/HYDROGEN_XH2KFX.inc';
$if not EXIST '../data/HYDROGEN_XH2KFX.inc' $INCLUDE '../../base/data/HYDROGEN_XH2KFX.inc';

$if     EXIST '../data/HYDROGEN_XH2INVCOST.inc' $INCLUDE         '../data/HYDROGEN_XH2INVCOST.inc';
$if not EXIST '../data/HYDROGEN_XH2INVCOST.inc' $INCLUDE '../../base/data/HYDROGEN_XH2INVCOST.inc';

$if     EXIST '../data/HYDROGEN_XH2INVCOST_NGTOH2.inc' $INCLUDE         '../data/HYDROGEN_XH2INVCOST_NGTOH2.inc';
$if not EXIST '../data/HYDROGEN_XH2INVCOST_NGTOH2.inc' $INCLUDE '../../base/data/HYDROGEN_XH2INVCOST_NGTOH2.inc';

$if     EXIST '../data/HYDROGEN_XH2COST.inc' $INCLUDE         '../data/HYDROGEN_XH2COST.inc';
$if not EXIST '../data/HYDROGEN_XH2COST.inc' $INCLUDE '../../base/data/HYDROGEN_XH2COST.inc';

$if     EXIST '../data/HYDROGEN_XH2LOSS.inc' $INCLUDE         '../data/HYDROGEN_XH2LOSS.inc';
$if not EXIST '../data/HYDROGEN_XH2LOSS.inc' $INCLUDE '../../base/data/HYDROGEN_XH2LOSS.inc';

$if     EXIST '../data/HYDROGEN_XH2KRATE.inc' $INCLUDE         '../data/HYDROGEN_XH2KRATE.inc';
$if not EXIST '../data/HYDROGEN_XH2KRATE.inc' $INCLUDE '../../base/data/HYDROGEN_XH2KRATE.inc';

$if     EXIST '../data/HYDROGEN_ANNUITYCXH2.inc' $INCLUDE         '../data/HYDROGEN_ANNUITYCXH2.inc';
$if not EXIST '../data/HYDROGEN_ANNUITYCXH2.inc' $INCLUDE '../../base/data/HYDROGEN_ANNUITYCXH2.inc';

$if     EXIST '../data/HYDROGEN_XH2MAXK_NGTOH2.inc' $INCLUDE         '../data/HYDROGEN_XH2MAXK_NGTOH2.inc';
$if not EXIST '../data/HYDROGEN_XH2MAXK_NGTOH2.inc' $INCLUDE '../../base/data/HYDROGEN_XH2MAXK_NGTOH2.inc';

$if     EXIST '../data/HYDROGEN_LIFETIME_XH2.inc' $INCLUDE         '../data/HYDROGEN_LIFETIME_XH2.inc';
$if not EXIST '../data/HYDROGEN_LIFETIME_XH2.inc' $INCLUDE '../../base/data/HYDROGEN_LIFETIME_XH2.inc';
$offmulti

$if     EXIST '../data/HYDROGEN_XH2INVCOST_ES.inc' $INCLUDE         '../data/HYDROGEN_XH2INVCOST_ES.inc';
$if not EXIST '../data/HYDROGEN_XH2INVCOST_ES.inc' $INCLUDE '../../base/data/HYDROGEN_XH2INVCOST_ES.inc';

$if     EXIST '../data/HYDROGEN_XH2KN_ES.inc' $INCLUDE         '../data/HYDROGEN_XH2KN_ES.inc';
$if not EXIST '../data/HYDROGEN_XH2KN_ES.inc' $INCLUDE '../../base/data/HYDROGEN_XH2KN_ES.inc';


*OBS FF
*Parameters for relative cost increase from underwater share (H2 corridors)
PARAMETER TRANSSHARE_H2(IRRRE,IRRRI)  'Fraction of H2 corridor length between IRE and IRI that is underwater'
$if     EXIST '../data/TRANSSHARE_H2.inc' $INCLUDE         '../data/TRANSSHARE_H2.inc';
$if not EXIST '../data/TRANSSHARE_H2.inc' $INCLUDE '../../base/data/TRANSSHARE_H2.inc';
%semislash%;

*Parameters for relative cost increase from mountainous share (H2 corridors)
PARAMETER TRANSSHARE_MOUNTAIN_H2(IRRRE,IRRRI)  'Fraction of H2 corridor length between IRE and IRI in mountainous regions'
$if     EXIST '../data/TRANSSHARE_MOUNTAIN_H2.inc' $INCLUDE         '../data/TRANSSHARE_MOUNTAIN_H2.inc';
$if not EXIST '../data/TRANSSHARE_MOUNTAIN_H2.inc' $INCLUDE '../../base/data/TRANSSHARE_MOUNTAIN_H2.inc';
%semislash%;

SCALAR UNDERWATER_REL_INCR 'Increase in PROCINVCOST and PROCFIXEDCOST for the subsea share of a transport pipeline (relative increase from base)'
$if     EXIST '../data/OPTIFLOW_UNDERWATER_REL_INCR.inc' $INCLUDE         '../data/OPTIFLOW_UNDERWATER_REL_INCR.inc';
$if not EXIST '../data/OPTIFLOW_UNDERWATER_REL_INCR.inc' $INCLUDE '../../base/data/OPTIFLOW_UNDERWATER_REL_INCR.inc';
%semislash%;

SCALAR MOUNTAIN_REL_INCR 'Increase in PROCINVCOST and PROCFIXEDCOST for the mountainous share of a transport pipeline (relative increase from base)'
$if     EXIST '../data/OPTIFLOW_MOUNTAIN_REL_INCR.inc' $INCLUDE         '../data/OPTIFLOW_MOUNTAIN_REL_INCR.inc';
$if not EXIST '../data/OPTIFLOW_MOUNTAIN_REL_INCR.inc' $INCLUDE '../../base/data/OPTIFLOW_MOUNTAIN_REL_INCR.inc';
%semislash%;

*Geography multiplier for H2 transmission corridors
PARAMETER XH2_GEOMULT(IRRRE,IRRRI) 'Relative cost multiplier for H2 pipelines accounting for underwater and mountainous shares';

XH2_GEOMULT(IRE,IRI) =
    1
  + TRANSSHARE_H2(IRE,IRI)          * (UNDERWATER_REL_INCR - 1)
  + TRANSSHARE_MOUNTAIN_H2(IRE,IRI) * (MOUNTAIN_REL_INCR  - 1)
;
