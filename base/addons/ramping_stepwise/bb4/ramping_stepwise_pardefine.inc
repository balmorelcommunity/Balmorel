
PARAMETER RAMPING_TECH_TYPE_VALUE(RAMPING_TECH_TYPE) 'Ramping technology types'   %semislash%
$if     EXIST '../data/RAMPING_TECH_TYPE_VALUE.inc' $INCLUDE         '../data/RAMPING_TECH_TYPE_VALUE.inc';
$if not EXIST '../data/RAMPING_TECH_TYPE_VALUE.inc' $INCLUDE '../../base/data/RAMPING_TECH_TYPE_VALUE.inc';
%semislash%;

PARAMETER RAMPING_TECH_GROUP_VALUE(RAMPING_TECH_GROUP)  'Ramping technology groups'   %semislash%
$if     EXIST '../data/RAMPING_TECH_GROUP_VALUE.inc' $INCLUDE         '../data/RAMPING_TECH_GROUP_VALUE.inc';
$if not EXIST '../data/RAMPING_TECH_GROUP_VALUE.inc' $INCLUDE '../../base/data/RAMPING_TECH_GROUP_VALUE.inc';
%semislash%;

PARAMETER RAMPING_FUELS_VALUE(RAMPING_FUELS) 'Ramping fuels'   %semislash%
$if     EXIST '../data/RAMPING_FUELS_VALUE.inc' $INCLUDE         '../data/RAMPING_FUELS_VALUE.inc';
$if not EXIST '../data/RAMPING_FUELS_VALUE.inc' $INCLUDE '../../base/data/RAMPING_FUELS_VALUE.inc';
%semislash%;

PARAMETER RAMPING_COSTS_UP(RAMPING_TECH_TYPE,RAMPING_TECH_GROUP,RAMPING_FUELS,RAMPING_RATE) 'Ramping up costs for each technology group, tech gype, fuel and ramping rate (Money/MWh)'   %semislash%
$if     EXIST '../data/RAMPING_COSTS_UP.inc' $INCLUDE         '../data/RAMPING_COSTS_UP.inc';
$if not EXIST '../data/RAMPING_COSTS_UP.inc' $INCLUDE '../../base/data/RAMPING_COSTS_UP.inc';
%semislash%;

PARAMETER RAMPING_COSTS_DOWN(RAMPING_TECH_TYPE,RAMPING_TECH_GROUP,RAMPING_FUELS,RAMPING_RATE) 'Ramping down costs for each technology group, tech gype, fuel and ramping rate (Money/MWh)'   %semislash%
$if     EXIST '../data/RAMPING_COSTS_DOWN.inc' $INCLUDE         '../data/RAMPING_COSTS_DOWN.inc';
$if not EXIST '../data/RAMPING_COSTS_DOWN.inc' $INCLUDE '../../base/data/RAMPING_COSTS_DOWN.inc';
%semislash%;

PARAMETER RAMPING_CAPABILITY_UP(RAMPING_TECH_TYPE,RAMPING_TECH_GROUP,RAMPING_FUELS,RAMPING_RATE) 'Ramping up capability for each technology group, tech gype, fuel and ramping rate (% capacity)'   %semislash%
$if     EXIST '../data/RAMPING_CAPABILITY_UP.inc' $INCLUDE         '../data/RAMPING_CAPABILITY_UP.inc';
$if not EXIST '../data/RAMPING_CAPABILITY_UP.inc' $INCLUDE '../../base/data/RAMPING_CAPABILITY_UP.inc';
%semislash%;

PARAMETER RAMPING_CAPABILITY_DOWN(RAMPING_TECH_TYPE,RAMPING_TECH_GROUP,RAMPING_FUELS,RAMPING_RATE) 'Ramping down capability for each technology group, tech gype, fuel and ramping rate (% capacity)'   %semislash%
$if     EXIST '../data/RAMPING_CAPABILITY_DOWN.inc' $INCLUDE         '../data/RAMPING_CAPABILITY_DOWN.inc';
$if not EXIST '../data/RAMPING_CAPABILITY_DOWN.inc' $INCLUDE '../../base/data/RAMPING_CAPABILITY_DOWN.inc';
%semislash%;


