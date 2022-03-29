* File heattrans_ipardecdef.inc for addon heattrans

* Transmision investments is subject to control by the option HeatTransInvest,
* therefore set a default and update if investments are intended.
* Even though IXHK_HASORPOT and IXHKN are sets, it is convenient to define them here

PARAMETER IYHASANNUITYXH(Y,Y)           "Binary parameter to establish whether the annuity of an investment of a heat transmission line investment made in Y (first index) should be paid in the time period Y (second index) (0,1)";
SET IXHK_HASORPOT(Y,IAAAE,IAAAI)  "Heat transmission lines with existing or potentially invested capacity current year";
SET IXHKN(Y,IAAAE,IAAAI) 'Pair of areas that may get new heat transmission capacity, yearly dependent';
PARAMETER IXHKRATE(IAAAE,IAAAI,S,T)     "Heat Transmission capacity rating (share; non-negative, typically close to 1; default/1/, use eps for 0)";

IXHKRATE(IAE,IAI,S,T) = XHKRATE(IAE,IAI,S,T);
IXHK_HASORPOT(Y,IAE,IAI) = YES$XHKFX(Y,IAE,IAI);
IXHKN(Y,IAE,IAI)=NO;

$ifi not %HeatTransInvest%==yes IYHASANNUITYXH(IYALIAS,Y)= 0;

$ifi not %HeatTransInvest%==yes $goto Heat_Transmission_investments_end

*IYHASANNUITYX CALCULATION
LOOP(IYALIAS,
  LOOP(Y$(ORD(Y) EQ ORD(IYALIAS)),
    IINVYEARX_LEFT(IYALIAS,Y)=LIFETIME_XH;
  );
);

LOOP(IYALIAS,
  ILOOPBREAK=0;
  IN_INV_X(IYALIAS)=ROUND(IWEIGHTY(IYALIAS)/LIFETIME_XH);
*Correction of inv
  IF ( IN_INV_X(IYALIAS) EQ 0,
    IN_INV_X(IYALIAS)=1;
  );
  LOOP(Y$(ORD(Y) GE ORD(IYALIAS) AND (ILOOPBREAK EQ 0)),

*First year's annuity
    IF ( ORD(Y) EQ ORD(IYALIAS),
      IYHASANNUITYXH(IYALIAS,Y)= 1;
      IF(IINVYEARX_LEFT(IYALIAS,Y)*IN_INV_X(IYALIAS) LE IWEIGHTY(Y),
      ILOOPBREAK=1;
      );
      IINVYEARX_LEFT(IYALIAS,Y+1)$(ORD(Y) NE CARD(IYALIAS2))=LIFETIME_XH*IN_INV_X(IYALIAS)-IWEIGHTY(Y);
    );
*Remaining year's annuity
    IF ( ORD(Y) GT ORD(IYALIAS),
      IF ( IINVYEARX_LEFT(IYALIAS,Y) GT IWEIGHTY(Y) ,
        IYHASANNUITYXH(IYALIAS,Y)= 1;
        IINVYEARX_LEFT(IYALIAS,Y+1)$(ORD(Y) NE CARD(IYALIAS2))=IINVYEARX_LEFT(IYALIAS,Y)-IWEIGHTY(Y);
      );
      IF ( (IINVYEARX_LEFT(IYALIAS,Y) GE IWEIGHTY(Y)/2) AND (IINVYEARX_LEFT(IYALIAS,Y) LE IWEIGHTY(Y)) ,
        IYHASANNUITYXH(IYALIAS,Y)= 1;
        ILOOPBREAK=1;
      );
      IF ( (IINVYEARX_LEFT(IYALIAS,Y) LT IWEIGHTY(Y)/2) AND (IINVYEARX_LEFT(IYALIAS,Y) LE IWEIGHTY(Y)) ,
        IYHASANNUITYXH(IYALIAS,Y)= 0;
        ILOOPBREAK=1;
      );
    );
  );
);


IXHKN(Y,IAE,IAI)$(XHINVCOST(Y,IAE,IAI) AND XHINVCOST(Y,IAE,IAI) LT INF AND (XHINVESTSTART LE YVALUE(Y))) = YES;
IXHK_HASORPOT(Y,IAE,IAI)$(XHINVCOST(Y,IAE,IAI) AND XHINVCOST(Y,IAE,IAI) LT INF AND (XHINVESTSTART LE YVALUE(Y))) = YES;

*This loop makes sure that if you invest in one line in the year Y, you can use this line in the future, even if you do not allow for investments on this line in the future
LOOP(Y$(ORD(Y) GT 1),
  LOOP(IAE,
    LOOP(IAI,
      IF ((XHINVCOST(Y-1,IAE,IAI) AND XHINVCOST(Y-1,IAE,IAI) LT INF AND (XHINVESTSTART LE YVALUE(Y))),
        IXHK_HASORPOT(Y,IAE,IAI)=IXHKN(Y,IAE,IAI)+YES$XHKFX(Y,IAE,IAI);
      );
      LOOP(IYALIAS2$((ORD(IYALIAS2) GE ORD(Y)) AND (ORD(IYALIAS2) NE CARD(IYALIAS2))),
      IXHK_HASORPOT(Y+1,IAE,IAI)= IXHK_HASORPOT(Y+1,IAE,IAI)+IXHKN(Y,IAE,IAI);
      );
    );
  );
);


$label  Heat_Transmission_investments_end


