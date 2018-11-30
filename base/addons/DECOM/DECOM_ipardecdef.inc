* Decommissioning introduced by Juan Gea Bermúdez 2018.


$ifi not %LIIFETIME_DECOM_EXO_G%==yes $goto LIFETIME_DECOMMISSIONING_EXOGENOUS_GENERATION
*This loops modifies the 
LOOP (YYY$(NOT(ORD(YYY) EQ CARD(YYY)))),
         LOOP (AAA,
                 LOOP (G,
                                 IF((GKFX(YYY+1,AAA,G) LT GKFX(YYY,AAA,G)),
                                           GKFX(YYY+1,AAA,G)=GKFX(YYY,AAA,G);
                                 );
                 );
         );
);
$label  LIFETIME_DECOMMISSIONING_EXOGENOUS_GENERATION
