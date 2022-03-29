* Transport add-on. Added by Juan Gea Bermudez

PARAMETER TRANSDEMAND_Y(YYY,RRR) 'Transport demand per region and year (MWh)';
PARAMETER TRANSDEMAND_S(YYY,RRR,SSS) 'Transport demand per region, year, and season (MWh)  to be used in future runs';
PARAMETER TRANSDEMAND_T(YYY,RRR,SSS,TTT) 'Transport demand per region, year, and season, and term (MWh) to be used in future runs';
SCALAR TRANS_PEAKAVG_RATIO     'Peak to average ratio for demand related to other transport';
PARAMETER TRANSDEMAND_T_MAX(Y,RRR)   'Maximum power demand (MW) to be used in future runs';


