* Stepwise ramping Juan Gea Bermúdez 2018.


** RAMPING CHARACTERISTICS OF THE TECHNOLOGIES TO BE USED
PARAMETER IRAMPING_G_COSTS_UP(G,RAMPING_RATE) 'Ramping up costs for each technology (money/MWh)';
PARAMETER IRAMPING_G_COSTS_DOWN(G,RAMPING_RATE) 'Ramping down costs for each technology (money/MWh)';
PARAMETER IRAMPING_G_CAPABILITY_UP(G,RAMPING_RATE) 'Ramping up capability for each technology for each ramping rate mode (% Capacity)';
PARAMETER IRAMPING_G_CAPABILITY_DOWN(G,RAMPING_RATE) 'Ramping down capability for each technology for each ramping rate mode (% Capacity)';


*This loops automatically calculates the ramping capabitilities and costs of the set G, depending on the input files. This avoids manually changing all the input parameters.

LOOP (UC_TECH_TYPE,
         LOOP (UC_TECH_GROUP,
                 LOOP (UC_FUELS,
                         LOOP ((G,RAMPING_RATE),
                                 if(((GDATA(G,'GDTYPE') = UC_TECH_TYPE_VALUE (UC_TECH_TYPE)) AND (GDATA(G,'GDTECHGROUP')=UC_TECH_GROUP_VALUE(UC_TECH_GROUP)) AND (GDATA(G,'GDFUEL') = UC_FUELS_VALUE(UC_FUELS))),
                                           IRAMPING_G_COSTS_UP(G,RAMPING_RATE)=RAMPING_COSTS_UP(UC_TECH_TYPE,UC_TECH_GROUP,UC_FUELS,RAMPING_RATE);
                                           IRAMPING_G_COSTS_DOWN(G,RAMPING_RATE)=RAMPING_COSTS_DOWN(UC_TECH_TYPE,UC_TECH_GROUP,UC_FUELS,RAMPING_RATE);
                                           IRAMPING_G_CAPABILITY_UP(G,RAMPING_RATE)=RAMPING_CAPABILITY_UP(UC_TECH_TYPE,UC_TECH_GROUP,UC_FUELS,RAMPING_RATE);
                                           IRAMPING_G_CAPABILITY_DOWN(G,RAMPING_RATE)=RAMPING_CAPABILITY_DOWN(UC_TECH_TYPE,UC_TECH_GROUP,UC_FUELS,RAMPING_RATE);
                                 );
                         );
                 );
         );
);

