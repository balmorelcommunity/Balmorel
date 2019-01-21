* Stepwise ramping Juan Gea Bermúdez 2018.

PARAMETER UC_TECH_TYPE_VALUE(UC_TECH_TYPE) 'UC technology types'   %semislash%
$if     EXIST '../data/UC_TECH_TYPE_VALUE.inc' $INCLUDE         '../data/UC_TECH_TYPE_VALUE.inc';
$if not EXIST '../data/UC_TECH_TYPE_VALUE.inc' $INCLUDE '../../base/data/UC_TECH_TYPE_VALUE.inc';
%semislash%;

PARAMETER UC_TECH_GROUP_VALUE(UC_TECH_GROUP)  'UC technology groups'   %semislash%
$if     EXIST '../data/UC_TECH_GROUP_VALUE.inc' $INCLUDE         '../data/UC_TECH_GROUP_VALUE.inc';
$if not EXIST '../data/UC_TECH_GROUP_VALUE.inc' $INCLUDE '../../base/data/UC_TECH_GROUP_VALUE.inc';
%semislash%;

PARAMETER UC_FUELS_VALUE(UC_FUELS) 'Ramping fuels'   %semislash%
$if     EXIST '../data/UC_FUELS_VALUE.inc' $INCLUDE         '../data/UC_FUELS_VALUE.inc';
$if not EXIST '../data/UC_FUELS_VALUE.inc' $INCLUDE '../../base/data/UC_FUELS_VALUE.inc';
%semislash%;

PARAMETER RAMPING_COSTS_UP(UC_TECH_TYPE,UC_TECH_GROUP,UC_FUELS,RAMPING_RATE) 'Ramping up costs for each technology group, tech gype, fuel and ramping rate (Money/MWh)'   %semislash%
$if     EXIST '../data/RAMPING_COSTS_UP.inc' $INCLUDE         '../data/RAMPING_COSTS_UP.inc';
$if not EXIST '../data/RAMPING_COSTS_UP.inc' $INCLUDE '../../base/data/RAMPING_COSTS_UP.inc';
%semislash%;

PARAMETER RAMPING_COSTS_DOWN(UC_TECH_TYPE,UC_TECH_GROUP,UC_FUELS,RAMPING_RATE) 'Ramping down costs for each technology group, tech gype, fuel and ramping rate (Money/MWh)'   %semislash%
$if     EXIST '../data/RAMPING_COSTS_DOWN.inc' $INCLUDE         '../data/RAMPING_COSTS_DOWN.inc';
$if not EXIST '../data/RAMPING_COSTS_DOWN.inc' $INCLUDE '../../base/data/RAMPING_COSTS_DOWN.inc';
%semislash%;

PARAMETER RAMPING_CAPABILITY_UP(UC_TECH_TYPE,UC_TECH_GROUP,UC_FUELS,RAMPING_RATE) 'Ramping up capability for each technology group, tech gype, fuel and ramping rate (% capacity)'   %semislash%
$if     EXIST '../data/RAMPING_CAPABILITY_UP.inc' $INCLUDE         '../data/RAMPING_CAPABILITY_UP.inc';
$if not EXIST '../data/RAMPING_CAPABILITY_UP.inc' $INCLUDE '../../base/data/RAMPING_CAPABILITY_UP.inc';
%semislash%;

PARAMETER RAMPING_CAPABILITY_DOWN(UC_TECH_TYPE,UC_TECH_GROUP,UC_FUELS,RAMPING_RATE) 'Ramping down capability for each technology group, tech gype, fuel and ramping rate (% capacity)'   %semislash%
$if     EXIST '../data/RAMPING_CAPABILITY_DOWN.inc' $INCLUDE         '../data/RAMPING_CAPABILITY_DOWN.inc';
$if not EXIST '../data/RAMPING_CAPABILITY_DOWN.inc' $INCLUDE '../../base/data/RAMPING_CAPABILITY_DOWN.inc';
%semislash%;


