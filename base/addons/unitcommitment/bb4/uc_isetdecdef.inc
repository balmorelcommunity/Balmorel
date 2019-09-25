* UC Translated to BB4 by Juan Gea Bermúdez 2018.

SET UC_FUELS(FFF) 'Fuels with ramping constraints';
SET IGUC(G) "Unit commitment: the set of units participating in unit commitment";

PARAMETER ICOUNT_LEFT "Internal parameter to calculate amount of timesteps left. Relevant for minimum start up time and shut down options";
SCALAR ISCOUNT;
SCALAR ITPOS;
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
SET IGUCUT(GGG,SSS,TTT,SSS,TTT) "Internal set to assign for each GGG, SSS(first) and TTT(first), the timesteps in SSS(second) and TTT(second) linked to the minimum on time" ;

*IGUCUT CALCULATION
LOOP(ISALIAS,
   LOOP(ITALIAS,
      LOOP(IGUC$GDATA(IGUC,'GDUCUTMIN'),
         ICOUNT_LEFT=GDATA(IGUC,'GDUCUTMIN');
         ISCOUNT=0;
         ITPOS=ORD(ITALIAS);
         WHILE((ICOUNT_LEFT GT 0) AND ((ORD(ISALIAS)-ISCOUNT) GT 0) AND (ICOUNT_LEFT/SUM(ITALIAS2$(ORD(ITALIAS2) EQ ITPOS),CHRONOHOUR(ISALIAS--ISCOUNT,ITALIAS2)) GT 0.5),
            IGUCUT(IGUC,ISALIAS,ITALIAS,ISALIAS-ISCOUNT,ITALIAS2)$(ORD(ITALIAS2) EQ ITPOS)=YES;
            ICOUNT_LEFT=ICOUNT_LEFT-SUM(ITALIAS2$(ORD(ITALIAS2) EQ ITPOS),CHRONOHOUR(ISALIAS-ISCOUNT,ITALIAS2));
            IF((ITPOS EQ 1),
               ITPOS=CARD(T);
               ISCOUNT=ISCOUNT+1;
            ELSE
               ITPOS=ITPOS-1;
            );
         );
      );
   );
);

$label  MINSTARTUPTIME_END


$ifi not %MINSHUTDOWNTIME%==yes $goto MINSHUTDOWNTIME_END

SET IGUCDT(GGG,SSS,TTT,SSS,TTT) "Internal set to assign for each GGG, SSS(first) and TTT(first), the timesteps in SSS(second) and TTT(second) linked to the minimum off time" ;                                                                                                                                      ;

*IGUCDT CALCULATION
LOOP(ISALIAS,
   LOOP(ITALIAS,
      LOOP(IGUC$GDATA(IGUC,'GDUCDTMIN'),
         ICOUNT_LEFT=GDATA(IGUC,'GDUCDTMIN');
         ISCOUNT=0;
         ITPOS=ORD(ITALIAS);
         WHILE((ICOUNT_LEFT GT 0) AND ((ORD(ISALIAS)-ISCOUNT) GT 0) AND (ICOUNT_LEFT/SUM(ITALIAS2$(ORD(ITALIAS2) EQ ITPOS),CHRONOHOUR(ISALIAS--ISCOUNT,ITALIAS2)) GT 0.5),
            IGUCDT(IGUC,ISALIAS,ITALIAS,ISALIAS-ISCOUNT,ITALIAS2)$(ORD(ITALIAS2) EQ ITPOS)=YES;
            ICOUNT_LEFT=ICOUNT_LEFT-SUM(ITALIAS2$(ORD(ITALIAS2) EQ ITPOS),CHRONOHOUR(ISALIAS-ISCOUNT,ITALIAS2));
            IF((ITPOS EQ 1),
               ITPOS=CARD(T);
               ISCOUNT=ISCOUNT+1;
            ELSE
               ITPOS=ITPOS-1;
            );
         );
      );
   );
);

$label  MINSHUTDOWNTIME_END


$ifi not %PLANNED_MAINTENANCE%==yes $goto NO_PLANNED_MAINTENANCE
SET IGUCUTMAINT(GGG,SSS,SSS) "Internal set to assign for each GGG, SSS(first), the timesteps in SSS(second) linked to the minimum time off due to mainteinance" ;                                                                                                                                      ;

*IGUCUTMAINT CALCULATION
LOOP(IGUC$GDATA(IGUC,'GDPLANMAINT'),
LOOP(ISALIAS,
      ICOUNT_LEFT=GDATA(IGUC,'GDPLANMAINT');
      ISCOUNT=0;
      WHILE((ICOUNT_LEFT GT 0) AND (ICOUNT_LEFT/(SSIZE(ISALIAS)*WEIGHT_S(ISALIAS)) GE 0.5),
         IGUCUTMAINT(IGUC,ISALIAS,ISALIAS--ISCOUNT)=YES;
         ISCOUNT=ISCOUNT+1;
         ICOUNT_LEFT= ICOUNT_LEFT - SSIZE(ISALIAS)*WEIGHT_S(ISALIAS);
      );
   );
);
$label NO_PLANNED_MAINTENANCE


