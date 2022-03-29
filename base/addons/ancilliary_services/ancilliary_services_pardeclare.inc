* Ancillary services by Juan Gea Bermúdez 2019.

PARAMETER FCRDOWN(YYY,CCCRRRAAA) 'FCR down regulation requirement in each hour (MW)';
PARAMETER FCRUP(YYY,CCCRRRAAA) 'FCR up regulation requirement in each hour (MW)';
PARAMETER AFRRDOWN(YYY,CCCRRRAAA) 'AFRR down regulation requirement in each hour (MW)';
PARAMETER AFRRUP(YYY,CCCRRRAAA) 'AFRR up regulation requirement in each hour (MW)';
PARAMETER MFRRDOWN(YYY,CCCRRRAAA) 'MFRR down regulation requirement in each hour (MW)';
PARAMETER MFRRUP(YYY,CCCRRRAAA) 'MFRR up regulation requirement in each hour (MW)';
PARAMETER MRRDOWN(YYY,CCCRRRAAA) 'MRR down regulation requirement in each hour (MW)';
PARAMETER MRRUP(YYY,CCCRRRAAA) 'MRR up regulation requirement in each hour (MW)';

SCALAR MIN_RAMPING_FCR 'Minimum ramping requirement for FCR. Values are unitless. E.g.: 1 means that it is requested to have the speed to go from 0 to full power in 1 hour, 2 means it is requested to go from 0 to full power in 1/2 hour, etc.';
SCALAR MIN_RAMPING_MFRR 'Minimum ramping requirement for MFRR. Values are unitless. E.g.: 1 means that it is requested to have the speed to go from 0 to full power in 1 hour, 2 means it is requested to go from 0 to full power in 1/2 hour, etc.';
SCALAR MIN_RAMPING_AFRR 'Minimum ramping requirement for AFRR. Values are unitless. E.g.: 1 means that it is requested to have the speed to go from 0 to full power in 1 hour, 2 means it is requested to go from 0 to full power in 1/2 hour, etc.';
SCALAR MAX_STARTTIME_MFRR 'Maximum start time requirement for MFRR (hours)' ;
SCALAR MAX_STARTTIME_MRR 'Maximum start time requirement for MRR (hours)' ;
SCALAR MIN_TIMEON_FCR  'Minimum time that a unit needs to be online to deliver FCR (hours)';
SCALAR MIN_TIMEON_AFRR  'Minimum time that a unit needs to be online to deliver AFRR (hours)';


$ifi %ANC_SERV_VRE%==yes PARAMETER VRE_CERT_AS(YYY,GGG) 'Certainty/probability associated to the provision of ancilary services from VRE (0-1, 0 means no certainty, 1 means full certainty)';

