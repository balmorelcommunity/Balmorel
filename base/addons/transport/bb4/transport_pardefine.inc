* Transport add-on. Added by Juan Gea Bermudez

PARAMETER TRANSDEMAND_Y(YYY,RRR) 'Transport demand per country and year (MWh)'  %semislash%
$if     EXIST '../data/TRANSPORT_TRANSDEMAND_Y.inc' $INCLUDE         '../data/TRANSPORT_TRANSDEMAND_Y.inc';
$if not EXIST '../data/TRANSPORT_TRANSDEMAND_Y.inc' $INCLUDE '../../base/data/TRANSPORT_TRANSDEMAND_Y.inc';
%semislash%;

* Weekly targets loaded by import_results must add up to this year's annual demand, else weeks missing
* from the file (e.g. written by INV) are forced to zero demand. Checked here, after TRANSDEMAND_Y is defined
$ifi %import_results%==yes $ifi %ADDSEASONALTRANSPORTDEMAND%==yes abort$SUM((Y,IR)$TRANSDEMAND_Y(Y,IR), 1$(ABS(8760/SUM(S,WEIGHT_S(S))*SUM(S,TRANSDEMAND_S(Y,IR,S)) - TRANSDEMAND_Y(Y,IR)) GT 0.01*TRANSDEMAND_Y(Y,IR))) 'simex/TRANSDEMAND_S.gdx does not add up to TRANSDEMAND_Y, run fullyear for this year first';

SCALAR TRANS_PEAKAVG_RATIO     'Peak to average ratio for demand related to other transport'  %semislash%
$if     EXIST '../data/TRANSPORT_TRANS_PEAKAVG_RATIO.inc' $INCLUDE         '../data/TRANSPORT_TRANS_PEAKAVG_RATIO.inc';
$if not EXIST '../data/TRANSPORT_TRANS_PEAKAVG_RATIO.inc' $INCLUDE '../../base/data/TRANSPORT_TRANS_PEAKAVG_RATIO.inc';
%semislash%;


