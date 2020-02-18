* Transport add-on. Added by Juan Gea Bermudez

PARAMETER TRANSDEMAND_Y(YYY,CCC) 'Transport demand per country and year (MWh)'  %semislash%
$if     EXIST '../data/TRANSPORT_TRANSDEMAND_Y.inc' $INCLUDE         '../data/TRANSPORT_TRANSDEMAND_Y.inc';
$if not EXIST '../data/TRANSPORT_TRANSDEMAND_Y.inc' $INCLUDE '../../base/data/TRANSPORT_TRANSDEMAND_Y.inc';
%semislash%;

SCALAR TRANS_PEAKAVG_RATIO     'Peak to average ratio for demand related to other transport'  %semislash%
$if     EXIST '../data/TRANSPORT_TRANS_PEAKAVG_RATIO.inc' $INCLUDE         '../data/TRANSPORT_TRANS_PEAKAVG_RATIO.inc';
$if not EXIST '../data/TRANSPORT_TRANS_PEAKAVG_RATIO.inc' $INCLUDE '../../base/data/TRANSPORT_TRANS_PEAKAVG_RATIO.inc';
%semislash%;


