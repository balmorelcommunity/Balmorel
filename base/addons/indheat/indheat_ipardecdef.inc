*Check if relevant here:
*PARAMETER INDHEAT_GKFX(YYY,INDHEAT_AAA,INDHEAT_GGG,INDHEAT_GROUP) 'Installed capacities' %semislash%
*$if     EXIST '../data/INDHEAT_GKFX.inc' $INCLUDE         '../data/INDHEAT_GKFX.inc';
*$if not EXIST '../data/INDHEAT_GKFX.inc' $INCLUDE '../../base/data/INDHEAT_GKFX.inc';
*%semislash%

PARAMETERS
         INDHEAT_IDH_SUMST(INDHEAT_AAA,INDHEAT_DHUSER) 'Annual amount of nominal heat demand (MWh)'
         INDHEAT_ISOLHSUMST(INDHEAT_AAA) 'Annual amount of solar generated heat relative to ISOLHSUMST and (S,T) (MWh)'
         INDHEAT_IYHASANNUITYG(Y,IYALIAS,INDHEAT_G)      "Binary parameter to establish whether the annuity of an investment of a technology made in Y (first index) should be paid in the time period Y (second index) (0,1)"
         INDHEAT_IINVYEARG_LEFT(Y,IYALIAS,INDHEAT_G)     "Remaining years of the lifetime of G of an investment made in Y (first index) at the beggining of Y (second index) (years)"
         INDHEAT_IN_INV_G(Y,INDHEAT_G)                   "Number of investments made OF G within Y (fraction)"
;

$ifi not %timeseries_scaling%==usedtimesteps_timseries_scaling $goto usedtimesteps_timseries_scaling_end
*Timeseries values are scaled linearly by the following factor: scaling factor = annual energy content / sum of the energy in the used part of the timeseries
INDHEAT_IDH_SUMST(INDHEAT_IA,INDHEAT_DHUSER) = SUM((S,T), IHOURSINST(S,T)*INDHEAT_DH_VAR_T(INDHEAT_IA,INDHEAT_DHUSER,S,T));
INDHEAT_ISOLHSUMST(INDHEAT_IA) = SUM((S,T), IHOURSINST(S,T)*INDHEAT_SOLH_VAR_T(INDHEAT_IA,S,T));
$label  usedtimesteps_timseries_scaling_end

$ifi not %timeseries_scaling%==full_timeseries_scaling $goto full_timeseries_scaling_end
*Timeseries values are scaled linearly by the following factor: scaling factor = annual energy content / sum of the energy in the full timeseries
INDHEAT_IDH_SUMST(INDHEAT_IA,INDHEAT_DHUSER) = SUM((SSS,TTT), IHOURSINST(SSS,TTT)*INDHEAT_DH_VAR_T(INDHEAT_IA,INDHEAT_DHUSER,SSS,TTT));
INDHEAT_ISOLHSUMST(INDHEAT_IA) = SUM((SSS,TTT), IHOURSINST(SSS,TTT)*INDHEAT_SOLH_VAR_T(INDHEAT_IA,SSS,TTT));
$label  full_timeseries_scaling_end