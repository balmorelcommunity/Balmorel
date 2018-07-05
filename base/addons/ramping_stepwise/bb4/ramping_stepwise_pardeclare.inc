PARAMETER RAMPING_TECH_TYPE_VALUE(RAMPING_TECH_TYPE) 'Ramping technology types';
PARAMETER RAMPING_TECH_GROUP_VALUE(RAMPING_TECH_GROUP)  'Ramping technology groups';
PARAMETER RAMPING_FUELS_VALUE(RAMPING_FUELS) 'Ramping fuels';
PARAMETER RAMPING_COSTS_UP(RAMPING_TECH_TYPE,RAMPING_TECH_GROUP,RAMPING_FUELS,RAMPING_RATE) 'Ramping up costs for each technology group, tech gype, fuel and ramping rate (Money/MWh)';
PARAMETER RAMPING_COSTS_DOWN(RAMPING_TECH_TYPE,RAMPING_TECH_GROUP,RAMPING_FUELS,RAMPING_RATE) 'Ramping down costs for each technology group, tech gype, fuel and ramping rate (Money/MWh)';
PARAMETER RAMPING_CAPABILITY_UP(RAMPING_TECH_TYPE,RAMPING_TECH_GROUP,RAMPING_FUELS,RAMPING_RATE) 'Ramping up capability for each technology group, tech gype, fuel and ramping rate (% capacity)';
PARAMETER RAMPING_CAPABILITY_DOWN(RAMPING_TECH_TYPE,RAMPING_TECH_GROUP,RAMPING_FUELS,RAMPING_RATE) 'Ramping down capability for each technology group, tech gype, fuel and ramping rate (% capacity)';
