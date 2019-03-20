* Decommissioning introduced by Juan Gea Bermúdez 2018.


$ifi not %LIFETIME_DECOM_EXO_G%==yes $ifi not %ECONOMIC_DECOM_EXO_G%==yes  $ifi not %NO_DECOM_EXO_G%==yes  $goto DEFAULT_DECOMMISSIONING_EXOGENOUS_GENERATION

*Calculation of the exogenous decommissioning of exogenous technologies based on lifetime
PARAMETER IDECOM_EXO(YYY,AAA,G) "Internal parameter that representes the exogenous decommissioning of exogenous technologies based on lifetime";
IDECOM_EXO(Y,IA,G)=0;

PARAMETER IDECOM_CHANGE(YYY,AAA,G) "Change in GKFX with respect to previous year in YYY";
IDECOM_CHANGE(YYY,IA,G)=0;

ILOOPBREAK=0;

LOOP(YYY$(NOT(ORD(YYY) EQ 1) AND (YYY.VAL GT GDECOMEXOPOTSTART)),
  LOOP(IA,
    LOOP(G$IGDECOM(G),
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
LOOP(YYY$(NOT(ORD(YYY) EQ 1) AND (YYY.VAL GT GDECOMEXOPOTSTART)),
  LOOP(IA,
    LOOP(G$IGDECOM(G),
      IF((IDECOM_CHANGE(YYY,IA,G) LT 0),
        GKFX(YYY,IA,G)=GKFX(YYY-1,IA,G);
      );
      IF((IDECOM_CHANGE(YYY,IA,G) GE 0),
        GKFX(YYY,IA,G)=GKFX(YYY-1,IA,G)+IDECOM_CHANGE(YYY,IA,G);
      );
    );
  );
);

IGDECOMEXOPOT(Y,IA,G)$(GKFX(Y,IA,G) AND Y.VAL GE GDECOMEXOSTART AND IGDECOM(G))=1;


*Calculation of the year-to-be decommissioned of endogenous technologies based on lifetime
PARAMETER IGDECOMY(YYY,YYY,GGG)  'DECOMMISIONING YEAR OF ENDOGENOUS GENERATION INVESTMENTS DEPENDING ON INVESTMENT YEAR';

LOOP(G$(GDATA(G,'GDKVARIABL') EQ 1),
  LOOP(IYALIAS,
    LOOP(Y$(ORD(Y) EQ ORD(IYALIAS)),
      IINVYEARG_LEFT(IYALIAS,Y,G)=GDATA(G,'GDLIFETIME');
    );
  );
);

IGDECOMY(Y,Y,IGKFIND)=0;

LOOP(IGKFIND,
  LOOP(IYALIAS,
    IN_INV_G(IYALIAS,IGKFIND)=ROUND(IWEIGHTY(IYALIAS)/GDATA(IGKFIND,'GDLIFETIME'));
*Correction of IN_INV_G
    IF ( IN_INV_G(IYALIAS,IGKFIND) EQ 0,
      IN_INV_G(IYALIAS,IGKFIND)=1;
    );
    LOOP(Y$(ORD(Y) GE ORD(IYALIAS) AND (SUM(IYALIAS2$(ORD(IYALIAS2) LT ORD(Y)),IGDECOMY(IYALIAS,IYALIAS2,IGKFIND)) EQ 0)),
*First year
      IF (ORD(Y) EQ ORD(IYALIAS),
        IF(IINVYEARG_LEFT(IYALIAS,Y,IGKFIND)*IN_INV_G(IYALIAS,IGKFIND) LE IWEIGHTY(Y),
          IGDECOMY(IYALIAS,Y+1,IGKFIND)$(ORD(Y) NE CARD(IYALIAS2))=1;
          );
          IINVYEARG_LEFT(IYALIAS,Y+1,IGKFIND)$(ORD(Y) NE CARD(IYALIAS2))=GDATA(IGKFIND,'GDLIFETIME')*IN_INV_G(IYALIAS,IGKFIND)-IWEIGHTY(Y);
        );
*Remaining year
      IF (ORD(Y) GT ORD(IYALIAS),
        IF ( IINVYEARG_LEFT(IYALIAS,Y,IGKFIND) GT IWEIGHTY(Y),
          IINVYEARG_LEFT(IYALIAS,Y+1,IGKFIND)$(ORD(Y) NE CARD(IYALIAS2))=IINVYEARG_LEFT(IYALIAS,Y,IGKFIND)-IWEIGHTY(Y);
        );
        IF ((IINVYEARG_LEFT(IYALIAS,Y,IGKFIND) GE IWEIGHTY(IYALIAS)/2) AND (IINVYEARG_LEFT(IYALIAS,Y,IGKFIND) LE IWEIGHTY(Y)) ,  !!Assumption: if the reamining years are more ore equal than half of IWEIGHTY, then the technology is in in this snapshot
          IGDECOMY(IYALIAS,Y+1,IGKFIND)=1;
        );
        IF ((IINVYEARG_LEFT(IYALIAS,Y,IGKFIND) LT IWEIGHTY(IYALIAS)/2) AND (IINVYEARG_LEFT(IYALIAS,Y,IGKFIND) LE IWEIGHTY(Y)) , !!Assumption: if the reamining years are less than half of IWEIGHTY, then the technology is out in this snapshot
          IGDECOMY(IYALIAS,Y,IGKFIND)=1;
        );
      );
    );
  );
);
$label  DEFAULT_DECOMMISSIONING_EXOGENOUS_GENERATION
