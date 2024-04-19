* UC Translated to BB4 by Juan Gea Bermúdez 2018.

PARAMETER IHOURST(SSS,TTT) "Accumulated hours in S and T";
PARAMETER IACCUMHOURS "Accumulated hours count";

IACCUMHOURS=0;
LOOP(S,
   LOOP(T,
      IHOURST(S,T)=IACCUMHOURS;
      IACCUMHOURS=IACCUMHOURS+CHRONOHOUR(S,T);
   );
);

$ifi not %STEPWISE_RAMPING_UC%==ramp_const_cost $goto STEPWISERAMPING_END

** RAMPING CHARACTERISTICS OF THE TECHNOLOGIES TO BE USED
PARAMETER IRAMPING_G_COSTS_UP(G,RAMPING_RATE) 'Ramping up costs for each technology (money/MWh)';
PARAMETER IRAMPING_G_COSTS_DOWN(G,RAMPING_RATE) 'Ramping down costs for each technology (money/MWh)';
PARAMETER IRAMPING_G_CAPABILITY_UP(G,RAMPING_RATE) 'Ramping up capability for each technology for each ramping rate mode (% Capacity)';
PARAMETER IRAMPING_G_CAPABILITY_DOWN(G,RAMPING_RATE) 'Ramping down capability for each technology for each ramping rate mode (% Capacity)';

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
$label  STEPWISERAMPING_END

$ifi not %PLANNED_MAINTENANCE%==yes $goto NO_PLANNED_MAINTENANCE
PARAMETER IGPLANMAINT(GGG) "Internal parameter to correct the value of GDPLANMAINT based on current run SSIZE values";
IGPLANMAINT(IGUC)$GDATA(IGUC,'GDPLANMAINT')=SUM((ISALIAS,ISALIAS2)$(IGUCUTMAINT(IGUC,ISALIAS,ISALIAS2) AND ORD(ISALIAS) EQ 1),SSIZE(ISALIAS2)*WEIGHT_S(ISALIAS2));
$label NO_PLANNED_MAINTENANCE
