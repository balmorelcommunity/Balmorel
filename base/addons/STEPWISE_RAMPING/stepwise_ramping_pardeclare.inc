* Stepwise ramping Juan Gea Bermúdez 2018.

PARAMETER UC_TECH_TYPE_VALUE(UC_TECH_TYPE) 'UC technology types';
PARAMETER UC_TECH_GROUP_VALUE(UC_TECH_GROUP)  'UC technology groups';
PARAMETER UC_FUELS_VALUE(UC_FUELS) 'UC fuels';


PARAMETER RAMPING_COSTS_UP(UC_TECH_TYPE,UC_TECH_GROUP,UC_FUELS,RAMPING_RATE) 'Ramping up costs for each technology group, tech gype, fuel and ramping rate (Money/MWh)';
PARAMETER RAMPING_COSTS_DOWN(UC_TECH_TYPE,UC_TECH_GROUP,UC_FUELS,RAMPING_RATE) 'Ramping down costs for each technology group, tech gype, fuel and ramping rate (Money/MWh)';
PARAMETER RAMPING_CAPABILITY_UP(UC_TECH_TYPE,UC_TECH_GROUP,UC_FUELS,RAMPING_RATE) 'Ramping up capability for each technology group, tech gype, fuel and ramping rate (% capacity)';
PARAMETER RAMPING_CAPABILITY_DOWN(UC_TECH_TYPE,UC_TECH_GROUP,UC_FUELS,RAMPING_RATE) 'Ramping down capability for each technology group, tech gype, fuel and ramping rate (% capacity)';


