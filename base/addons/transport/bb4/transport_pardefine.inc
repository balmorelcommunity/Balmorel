* Transport add-on. Added by Juan Gea Bermudez

PARAMETER TRANSDEMAND_Y(YYY,CCC) 'Transport demand per country and year (MWh)'  %semislash%
$if     EXIST '../data/TRANSPORT_TRANSDEMAND_Y.inc' $INCLUDE         '../data/TRANSPORT_TRANSDEMAND_Y.inc';
$if not EXIST '../data/TRANSPORT_TRANSDEMAND_Y.inc' $INCLUDE '../../base/data/TRANSPORT_TRANSDEMAND_Y.inc';
%semislash%;


