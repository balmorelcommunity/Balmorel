* Import results Juan Gea Bermúdez 2019.

$ifi not %ADDTECHDECOM%==yes $goto DEFAULT_DECOMMISSIONING_EXOGENOUS_GENERATION

*Calculation of the exogenous decommissioning of exogenous technologies based on lifetime

PARAMETER IDECOM_CHANGE(YYY,AAA,G) "Change in GKFX with respect to previous year in YYY";
IDECOM_CHANGE(YYY,IA,G)=0;

LOOP(YYY$(NOT(ORD(YYY) EQ 1) AND (YYY.VAL GT GDECOMEXOPOTSTART)),
  LOOP(IA,
    LOOP(G,
      IDECOM_CHANGE(YYY,IA,G)=GKFX(YYY,IA,G)-GKFX(YYY-1,IA,G);
    );
  );
);

*Modification of GKFX to allow to apply tkeep track of decommissioning variables
LOOP(YYY$(NOT(ORD(YYY) EQ 1) AND (YYY.VAL GT GDECOMEXOPOTSTART)),
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

*Modification of GKFX with exogenous decommissioning
GKFX(Y,IA,G)=GKFX(Y,IA,G)-GVDECOM_EXO_ACCUM(Y,IA,G);

$label  DEFAULT_DECOMMISSIONING_EXOGENOUS_GENERATION


*Adding Investment addition as exogenous capacities
$ifi %ADDTECHINVEST%==yes  GKFX(Y,IA,G)$GVGKNACCUMNET(Y,IA,G)=GKFX(Y,IA,G)+GVGKNACCUMNET(Y,IA,G);
$ifi %ADDTRANSINVEST%==yes XKFX(Y,IRE,IRI)$XVXKNACCUMNET(Y,IRE,IRI)=XKFX(Y,IRE,IRI)+XVXKNACCUMNET(Y,IRE,IRI);

*Modification of GKFX values in case they are negative (sometimes there can be issues with the decimals)
GKFX(Y,IA,G)$(GKFX(Y,IA,G) LT eps)=0;