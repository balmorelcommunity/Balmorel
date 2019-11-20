* Ancilliary services by Juan Gea Bermúdez 2019.

PARAMETER SECONDARY_RESERVES(YYY,RRR) 'Secondary reserve requirement in each hour (MW)'  %semislash%
$if     EXIST '../data/ANCILLIARY_SERVICES_SECONDARY_RESERVES.inc' $INCLUDE         '../data/ANCILLIARY_SERVICES_SECONDARY_RESERVES.inc';
$if not EXIST '../data/ANCILLIARY_SERVICES_SECONDARY_RESERVES.inc' $INCLUDE '../../base/data/ANCILLIARY_SERVICES_SECONDARY_RESERVES.inc';
%semislash%;

PARAMETER TERTIARY_RESERVES(YYY,RRR) 'Tertiary reserve requirement in each hour (MW)'  %semislash%
$if     EXIST '../data/ANCILLIARY_SERVICES_TERTIARY_RESERVES.inc' $INCLUDE         '../data/ANCILLIARY_SERVICES_TERTIARY_RESERVES.inc';
$if not EXIST '../data/ANCILLIARY_SERVICES_TERTIARY_RESERVES.inc' $INCLUDE '../../base/data/ANCILLIARY_SERVICES_TERTIARY_RESERVES.inc';
%semislash%;

SCALAR AS_MIN_RAMPING 'Minimum ramping requirement. Values are unitless. E.g.: 1 means that it is requested to have the speed to go from 0 to full power in 1 hour, 2 means it is requested to go from 0 to full power in 1/2 hour, etc.'  %semislash%
$if     EXIST '../data/ANCILLIARY_SERVICES_AS_MIN_RAMPING.inc' $INCLUDE         '../data/ANCILLIARY_SERVICES_AS_MIN_RAMPING.inc';
$if not EXIST '../data/ANCILLIARY_SERVICES_AS_MIN_RAMPING.inc' $INCLUDE '../../base/data/ANCILLIARY_SERVICES_AS_MIN_RAMPING.inc';
%semislash%;


