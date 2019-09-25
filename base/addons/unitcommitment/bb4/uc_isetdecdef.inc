* UC Translated to BB4 by Juan Gea Bermúdez 2018.

SET UC_FUELS(FFF) 'Fuels with ramping constraints';
SET IGUC(G) "Unit commitment: the set of units participating in unit commitment";

PARAMETER ICOUNT_LEFT "Internal parameter to calculate amount of timesteps left. Relevant for minimum start up time and shut down options";

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




$ifi not %MINSTARTUPTIME%==yes $goto MINSTARTUPTIME_END
SET IGUCUT(GGG,SSS,TTT,SSS,TTT) "Internal set to assign for each GGG, SSS(first) and TTT(first), the timesteps in SSS(second) and TTT(second) linked to the minimum start up time" ;

*IGUCUT CALCULATION
LOOP(SREV(ISALIAS2,ISALIAS3),
   LOOP(TREV(ITALIAS2,ITALIAS3),
      LOOP(IGUC$(GDATA(IGUC,'GDUCUTMIN') GT CHRONOHOUR(ISALIAS3,ITALIAS3)),
         ICOUNT_LEFT=GDATA(IGUC,'GDUCUTMIN');
         LOOP(SREV2(S,ISALIAS)$((ICOUNT_LEFT GT 0) AND (ORD(ISALIAS) LE ORD(ISALIAS3))),
            LOOP(TREV2(T,ITALIAS)$((ICOUNT_LEFT GT 0) AND (NOT (ORD(ISALIAS) EQ ORD(ISALIAS3) AND (ORD(ITALIAS3) LT ORD(ITALIAS))) ) ),
               IGUCUT(IGUC,ISALIAS3,ITALIAS3,ISALIAS,ITALIAS)=YES;
               IF(ORD(ITALIAS) EQ 1,
                  ICOUNT_LEFT=ICOUNT_LEFT-CHRONOHOUR(ISALIAS-1,ITALIAS--1);
               ELSE
                  ICOUNT_LEFT=ICOUNT_LEFT-CHRONOHOUR(ISALIAS,ITALIAS-1);
               );
            );
         );
      );
   );
);

$label  MINSTARTUPTIME_END


$ifi not %MINSHUTDOWNTIME%==yes $goto MINSHUTDOWNTIME_END

SET IGUCDT(GGG,SSS,TTT,SSS,TTT) "Internal set to assign for each GGG, SSS(first) and TTT(first), the timesteps in SSS(second) and TTT(second) linked to the minimum start up time" ;                                                                                                                                      ;

*IGUCDT CALCULATION
LOOP(SREV(ISALIAS2,ISALIAS3),
   LOOP(TREV(ITALIAS2,ITALIAS3),
      LOOP(IGUC$(GDATA(IGUC,'GDUCDTMIN') GT CHRONOHOUR(ISALIAS3,ITALIAS3)),
         ICOUNT_LEFT=GDATA(IGUC,'GDUCDTMIN');
         LOOP(SREV2(S,ISALIAS)$((ICOUNT_LEFT GT 0) AND (ORD(ISALIAS) LE ORD(ISALIAS3))),
            LOOP(TREV2(T,ITALIAS)$((ICOUNT_LEFT GT 0) AND (NOT (ORD(ISALIAS) EQ ORD(ISALIAS3) AND (ORD(ITALIAS3) LT ORD(ITALIAS))) ) ),
               IGUCDT(IGUC,ISALIAS3,ITALIAS3,ISALIAS,ITALIAS)=YES;
               IF(ORD(ITALIAS) EQ 1,
                  ICOUNT_LEFT=ICOUNT_LEFT-CHRONOHOUR(ISALIAS-1,ITALIAS--1);
               ELSE
                  ICOUNT_LEFT=ICOUNT_LEFT-CHRONOHOUR(ISALIAS,ITALIAS-1);
               );
            );
         );
      );
   );
);

$label  MINSHUTDOWNTIME_END