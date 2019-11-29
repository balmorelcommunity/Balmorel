PARAMETERS
         INDHEAT_IDH_SUMST(INDHEAT_AAA,INDHEAT_DHUSER) 'Annual amount of nominal heat demand (MWh)'
         INDHEAT_ISOLHSUMST(INDHEAT_AAA) 'Annual amount of solar generated heat relative to ISOLHSUMST and (S,T) (MWh)'
         INDHEAT_IM_CO2(INDHEAT_GGG)
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

LOOP(FFF,
  INDHEAT_IM_CO2(INDHEAT_G)$INDHEAT_IGF(INDHEAT_G,FFF)   = FDATA(FFF,'FDCO2');
);

