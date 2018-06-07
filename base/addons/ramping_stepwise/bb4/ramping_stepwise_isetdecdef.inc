SET IRAMPING_G (G) 'Technologies with ramping constraints';
SET IRAMPING_G_RATE (G,RAMPING_RATE) 'Technologoies with ramping constraints and ramping rate';

* RAMPING TECHNOLOGIES TO BE USED
LOOP (RAMPING_TECH_TYPE,
         LOOP (RAMPING_TECH_GROUP,
                 LOOP (RAMPING_FUELS,
                         LOOP (G,
                                 if(((GDATA(G,'GDTYPE') = RAMPING_TECH_TYPE_VALUE (RAMPING_TECH_TYPE)) AND (GDATA(G,'GDTECHGROUP')=RAMPING_TECH_GROUP_VALUE(RAMPING_TECH_GROUP)) AND (GDATA(G,'GDFUEL') = RAMPING_FUELS_VALUE(RAMPING_FUELS))),
                                        IRAMPING_G(G)=YES;
                                        IRAMPING_G_RATE(G,RAMPING_RATE)=YES;
                                 );
                         );
                 );
         );
);

