* Ancilliary services by Juan Gea Bermúdez 2019.

PARAMETER SECONDARY_RESERVES(YYY,RRR) 'Secondary reserve requirement in each hour (MW)';
PARAMETER TERTIARY_RESERVES(YYY,RRR) 'Tertiary reserve requirement in each hour (MW)';
SCALAR AS_MIN_RAMPING 'Minimum ramping requirement. Values are unitless. E.g.: 1 means that it is requested to have the speed to go from 0 to full power in 1 hour, 2 means it is requested to go from 0 to full power in 1/2 hour, etc.';
PARAMETER ASSECRES_T(YYY,AAA,GGG,SSS,TTT)   'Allocated Secondary reserve for each technology (MW). To be transferred to future runs.';
PARAMETER ASTERRES_T(YYY,AAA,GGG,SSS,TTT)   'Allocated Tertiary reserve for each technology (MW). To be transferred to future runs.';
