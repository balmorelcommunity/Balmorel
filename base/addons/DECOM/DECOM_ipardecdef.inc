* Decommissioning introduced by Juan Gea Bermúdez 2018.


$ifi not %LIFETIME_DECOM_EXO_G%==yes $ifi not %ECONOMIC_DECOM_EXO_G%==yes  $ifi not %NO_DECOM_EXO_G%==yes  $goto DEFAULT_DECOMMISSIONING_EXOGENOUS_GENERATION

*Calculation of the exogenous decommissioning of exogenous technologies based on lifetime

PARAMETER IDECOM_EXO(YYY,AAA,G) "Internal parameter that representes the exogenous decommissioning of exogenous technologies based on lifetime";
IDECOM_EXO(Y,IA,G)=0;

PARAMETER IDECOM_CHANGE(YYY,AAA,G) "Change in GKFX with respect to previous year in YYY";
IDECOM_CHANGE(YYY,IA,G)=0;

ILOOPBREAK=0;

LOOP(YYY$(NOT(ORD(YYY) EQ 1) AND (YYY.VAL GT GDECOMEXOSTART)),
  LOOP(IA,
    LOOP(G,
      ILOOPBREAK=0;
      IDECOM_CHANGE(YYY,IA,G)=GKFX(YYY,IA,G)-GKFX(YYY-1,IA,G);
      IF((GKFX(YYY,IA,G) LT GKFX(YYY-1,IA,G)),
        LOOP(Y$(ILOOPBREAK EQ 0),
          IF((YYY.VAL LE Y.VAL),
            IDECOM_EXO(Y,IA,G) = GKFX(YYY-1,IA,G) - GKFX(YYY,IA,G) + IDECOM_EXO(Y,IA,G);
            ILOOPBREAK=1;
          );
        );
      );
    );
  );
);


*Modification of GKFX to allow to keep track of decommissioning variables
LOOP(YYY$(NOT(ORD(YYY) EQ 1) AND (YYY.VAL GT GDECOMEXOSTART)),
  LOOP(IA,
    LOOP(G,
      IF((IDECOM_CHANGE(YYY,IA,G) LT 0),
        GKFX(YYY,IA,G)=GKFX(YYY-1,IA,G);
      );
      IF((IDECOM_CHANGE(YYY,IA,G) GE 0),
        GKFX(YYY,IA,G)=GKFX(YYY-1,IA,G)+IDECOM_CHANGE(YYY,IA,G);
      );
    );
  );
);
$label  DEFAULT_DECOMMISSIONING_EXOGENOUS_GENERATION
