* Ancilliary services by Juan Gea Bermúdez 2019.

PARAMETER FCRDOWN(YYY,CCCRRRAAA) 'FCR down regulation requirement in each hour (MW)'  %semislash%
$if     EXIST '../data/ANCILLIARY_SERVICES_FCRDOWN.inc' $INCLUDE         '../data/ANCILLIARY_SERVICES_FCRDOWN.inc';
$if not EXIST '../data/ANCILLIARY_SERVICES_FCRDOWN.inc' $INCLUDE '../../base/data/ANCILLIARY_SERVICES_FCRDOWN.inc';
%semislash%;

PARAMETER FCRUP(YYY,CCCRRRAAA) 'FCR up regulation requirement in each hour (MW)'   %semislash%
$if     EXIST '../data/ANCILLIARY_SERVICES_FCRUP.inc' $INCLUDE         '../data/ANCILLIARY_SERVICES_FCRUP.inc';
$if not EXIST '../data/ANCILLIARY_SERVICES_FCRUP.inc' $INCLUDE '../../base/data/ANCILLIARY_SERVICES_FCRUP.inc';
%semislash%;

PARAMETER AFRRDOWN(YYY,CCCRRRAAA) 'AFRR down regulation requirement in each hour (MW)'  %semislash%
$if     EXIST '../data/ANCILLIARY_SERVICES_AFRRDOWN.inc' $INCLUDE         '../data/ANCILLIARY_SERVICES_AFRRDOWN.inc';
$if not EXIST '../data/ANCILLIARY_SERVICES_AFRRDOWN.inc' $INCLUDE '../../base/data/ANCILLIARY_SERVICES_AFRRDOWN.inc';
%semislash%;

PARAMETER AFRRUP(YYY,CCCRRRAAA) 'AFRR up regulation requirement in each hour (MW)'  %semislash%
$if     EXIST '../data/ANCILLIARY_SERVICES_AFRRUP.inc' $INCLUDE         '../data/ANCILLIARY_SERVICES_AFRRUP.inc';
$if not EXIST '../data/ANCILLIARY_SERVICES_AFRRUP.inc' $INCLUDE '../../base/data/ANCILLIARY_SERVICES_AFRRUP.inc';
%semislash%;

PARAMETER MFRRDOWN(YYY,CCCRRRAAA) 'MFRR down regulation requirement in each hour (MW)'    %semislash%
$if     EXIST '../data/ANCILLIARY_SERVICES_MFRRDOWN.inc' $INCLUDE         '../data/ANCILLIARY_SERVICES_MFRRDOWN.inc';
$if not EXIST '../data/ANCILLIARY_SERVICES_MFRRDOWN.inc' $INCLUDE '../../base/data/ANCILLIARY_SERVICES_MFRRDOWN.inc';
%semislash%;

PARAMETER MFRRUP(YYY,CCCRRRAAA) 'MFRR up regulation requirement in each hour (MW)'     %semislash%
$if     EXIST '../data/ANCILLIARY_SERVICES_MFRRUP.inc' $INCLUDE         '../data/ANCILLIARY_SERVICES_MFRRUP.inc';
$if not EXIST '../data/ANCILLIARY_SERVICES_MFRRUP.inc' $INCLUDE '../../base/data/ANCILLIARY_SERVICES_MFRRUP.inc';
%semislash%;

PARAMETER MRRDOWN(YYY,CCCRRRAAA) 'MRR down regulation requirement in each hour (MW)'    %semislash%
$if     EXIST '../data/ANCILLIARY_SERVICES_MRRDOWN.inc' $INCLUDE         '../data/ANCILLIARY_SERVICES_MRRDOWN.inc';
$if not EXIST '../data/ANCILLIARY_SERVICES_MRRDOWN.inc' $INCLUDE '../../base/data/ANCILLIARY_SERVICES_MRRDOWN.inc';
%semislash%;

PARAMETER MRRUP(YYY,CCCRRRAAA) 'MRR up regulation requirement in each hour (MW)'  %semislash%
$if     EXIST '../data/ANCILLIARY_SERVICES_MRRUP.inc' $INCLUDE         '../data/ANCILLIARY_SERVICES_MRRUP.inc';
$if not EXIST '../data/ANCILLIARY_SERVICES_MRRUP.inc' $INCLUDE '../../base/data/ANCILLIARY_SERVICES_MRRUP.inc';
%semislash%;

SCALAR MIN_RAMPING_FCR 'Minimum ramping requirement for FCR. Values are unitless. E.g.: 1 means that it is requested to have the speed to go from 0 to full power in 1 hour, 2 means it is requested to go from 0 to full power in 1/2 hour, etc.'   %semislash%
$if     EXIST '../data/ANCILLIARY_SERVICES_MIN_RAMPING_FCR.inc' $INCLUDE         '../data/ANCILLIARY_SERVICES_MIN_RAMPING_FCR.inc';
$if not EXIST '../data/ANCILLIARY_SERVICES_MIN_RAMPING_FCR.inc' $INCLUDE '../../base/data/ANCILLIARY_SERVICES_MIN_RAMPING_FCR.inc';
%semislash%;

SCALAR MIN_RAMPING_MFRR 'Minimum ramping requirement for MFRR. Values are unitless. E.g.: 1 means that it is requested to have the speed to go from 0 to full power in 1 hour, 2 means it is requested to go from 0 to full power in 1/2 hour, etc.'  %semislash%
$if     EXIST '../data/ANCILLIARY_SERVICES_MIN_RAMPING_MFRR.inc' $INCLUDE         '../data/ANCILLIARY_SERVICES_MIN_RAMPING_MFRR.inc';
$if not EXIST '../data/ANCILLIARY_SERVICES_MIN_RAMPING_MFRR.inc' $INCLUDE '../../base/data/ANCILLIARY_SERVICES_MIN_RAMPING_MFRR.inc';
%semislash%;

SCALAR MIN_RAMPING_AFRR 'Minimum ramping requirement for AFRR. Values are unitless. E.g.: 1 means that it is requested to have the speed to go from 0 to full power in 1 hour, 2 means it is requested to go from 0 to full power in 1/2 hour, etc.'  %semislash%
$if     EXIST '../data/ANCILLIARY_SERVICES_MIN_RAMPING_AFRR.inc' $INCLUDE         '../data/ANCILLIARY_SERVICES_MIN_RAMPING_AFRR.inc';
$if not EXIST '../data/ANCILLIARY_SERVICES_MIN_RAMPING_AFRR.inc' $INCLUDE '../../base/data/ANCILLIARY_SERVICES_MIN_RAMPING_AFRR.inc';
%semislash%;

SCALAR MAX_STARTTIME_MFRR 'Maximum start time requirement for MFRR (hours)'  %semislash%
$if     EXIST '../data/ANCILLIARY_SERVICES_MAX_STARTTIME_MFRR.inc' $INCLUDE         '../data/ANCILLIARY_SERVICES_MAX_STARTTIME_MFRR.inc';
$if not EXIST '../data/ANCILLIARY_SERVICES_MAX_STARTTIME_MFRR.inc' $INCLUDE '../../base/data/ANCILLIARY_SERVICES_MAX_STARTTIME_MFRR.inc';
%semislash%;

SCALAR MAX_STARTTIME_MRR 'Maximum start time requirement for MRR (hours)'  %semislash%
$if     EXIST '../data/ANCILLIARY_SERVICES_MAX_STARTTIME_MRR.inc' $INCLUDE         '../data/ANCILLIARY_SERVICES_MAX_STARTTIME_MRR.inc';
$if not EXIST '../data/ANCILLIARY_SERVICES_MAX_STARTTIME_MRR.inc' $INCLUDE '../../base/data/ANCILLIARY_SERVICES_MAX_STARTTIME_MRR.inc';
%semislash%;

