* Stepwise ramping Juan Gea Bermúdez 2018.

SET UC_FUELS(FFF) 'Fuels with ramping constraints';
SET IGUC(G) "Unit commitment: the set of units participating in unit commitment";

* Exogenously given UC technologies
IGUC(G)$(GDATA(G,'GDUC') EQ 1)=YES;


* Automatic UC technology definition
LOOP (UC_TECH_TYPE,
         LOOP (UC_TECH_GROUP,
                 LOOP (UC_FUELS,
                         LOOP (G,
                                 if(((GDATA(G,'GDTYPE') = UC_TECH_TYPE_VALUE (UC_TECH_TYPE)) AND (GDATA(G,'GDTECHGROUP')=UC_TECH_GROUP_VALUE(UC_TECH_GROUP)) AND (GDATA(G,'GDFUEL') = UC_FUELS_VALUE(UC_FUELS))),
                                        IGUC(G)=YES;
                                 );
                         );
                 );
         );
);



