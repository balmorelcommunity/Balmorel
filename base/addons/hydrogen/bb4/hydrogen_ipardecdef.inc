PARAMETERS
   IHYDROGEN_DH2_SUMST(RRR)               'Variation profile of H2 demand per region'
   IHYDROGEN_STOVOL_START(AAA,G,SSS)    'Start level of hydrogen storage'
   IHYDROGEN_STOVOL_END(AAA,G,SSS)      'End level of hydrogen storage'
;

PARAMETER IHYDROGEN_DH2_REGION_T_Y(YYY,RRR,SSS,TTT)  'Variation of H2 demand in each region along the year';
PARAMETER IHYDROGEN_DH2_AREA_T_Y(YYY,AAA,SSS,TTT)    'Variation of H2 demand in each region along the year';
IHYDROGEN_DH2_REGION_T_Y(Y,IR,S,T) = (HYDROGEN_DH2(Y,IR)*HYDROGEN_DH2_VAR_T(IR,S,T)/IHYDROGEN_DH2_REGION_SUMST(IR))$(IHYDROGEN_DH2_REGION_SUMST(IR) GT 0);
IHYDROGEN_DH2_AREA_T_Y(Y,IA,S,T)  = (HYDROGEN_DH2(Y,IA)*HYDROGEN_DH2_VAR_T(IA,S,T)/IHYDROGEN_DH2_AREA_SUMST(IA))$(IHYDROGEN_DH2_AREA_SUMST(IA) GT 0);

* Transmision investments is subject to control by the option H2TransInvest,
* therefore set a default and update if investments are intended.
* Even though IXH2K_HASORPOT and IXH2KN are sets, it is convenient to define them here

PARAMETER IYHASANNUITYXH2(Y,Y)           "Binary parameter to establish whether the annuity of an investment of a H2 transmission line investment made in Y (first index) should be paid in the time period Y (second index) (0,1)";
SET IXH2K_HASORPOT(Y,IRRRE,IRRRI)        "H2 transmission lines with existing or potentially invested capacity current year";
SET IXH2KN(Y,IRRRE,IRRRI)                "Pair of regions that may get new H2 transmission capacity, yearly dependent";
SET IXH2KN_NGTOH2(Y,IRRRE,IRRRI)         "Pair of regions that may get new Conversion of existing natural gas pipe to H2 transmission capacity, yearly dependent";
PARAMETER IXH2KRATE(IRRRE,IRRRI,S,T)     "H2 Transmission capacity rating (share; non-negative, typically close to 1; default/1/, use eps for 0)";

IXH2KRATE(IRE,IRI,S,T) = XH2KRATE(IRE,IRI,S,T);
IXH2K_HASORPOT(Y,IRE,IRI) = YES$XH2KFX(Y,IRE,IRI);
IXH2KN(Y,IRE,IRI)=NO;
IXH2KN_NGTOH2(Y,IRE,IRI)=NO;

$ifi not %H2TransInvest%==yes IYHASANNUITYXH2(IYALIAS,Y)= 0;

$ifi not %H2TransInvest%==yes $goto H2_Transmission_investments_end

*IYHASANNUITYXH2 CALCULATION
LOOP(IYALIAS,
  LOOP(Y$(ORD(Y) EQ ORD(IYALIAS)),
    IINVYEARX_LEFT(IYALIAS,Y)=LIFETIME_XH2;
  );
);

LOOP(IYALIAS,
  ILOOPBREAK=0;
  IN_INV_X(IYALIAS)=ROUND(IWEIGHTY(IYALIAS)/LIFETIME_XH2);
*Correction of inv
  IF ( IN_INV_X(IYALIAS) EQ 0,
    IN_INV_X(IYALIAS)=1;
  );
  LOOP(Y$(ORD(Y) GE ORD(IYALIAS) AND (ILOOPBREAK EQ 0)),

*First year's annuity
    IF ( ORD(Y) EQ ORD(IYALIAS),
      IYHASANNUITYXH2(IYALIAS,Y)= 1;
      IF(IINVYEARX_LEFT(IYALIAS,Y)*IN_INV_X(IYALIAS) LE IWEIGHTY(Y),
      ILOOPBREAK=1;
      );
      IINVYEARX_LEFT(IYALIAS,Y+1)$(ORD(Y) NE CARD(IYALIAS2))=LIFETIME_XH2*IN_INV_X(IYALIAS)-IWEIGHTY(Y);
    );
*Remaining year's annuity
    IF ( ORD(Y) GT ORD(IYALIAS),
      IF ( IINVYEARX_LEFT(IYALIAS,Y) GT IWEIGHTY(Y) ,
        IYHASANNUITYXH2(IYALIAS,Y)= 1;
        IINVYEARX_LEFT(IYALIAS,Y+1)$(ORD(Y) NE CARD(IYALIAS2))=IINVYEARX_LEFT(IYALIAS,Y)-IWEIGHTY(Y);
      );
      IF ( (IINVYEARX_LEFT(IYALIAS,Y) GE IWEIGHTY(Y)/2) AND (IINVYEARX_LEFT(IYALIAS,Y) LE IWEIGHTY(Y)) ,
        IYHASANNUITYXH2(IYALIAS,Y)= 1;
        ILOOPBREAK=1;
      );
      IF ( (IINVYEARX_LEFT(IYALIAS,Y) LT IWEIGHTY(Y)/2) AND (IINVYEARX_LEFT(IYALIAS,Y) LE IWEIGHTY(Y)) ,
        IYHASANNUITYXH2(IYALIAS,Y)= 0;
        ILOOPBREAK=1;
      );
    );
  );
);


IXH2KN(Y,IRE,IRI)$(XH2INVCOST(Y,IRE,IRI) AND XH2INVCOST(Y,IRE,IRI) LT INF AND (XH2INVESTSTART LE YVALUE(Y))) = YES;
IXH2KN_NGTOH2(Y,IRE,IRI)$(XH2INVCOST_NGTOH2(Y,IRE,IRI) AND XH2INVCOST_NGTOH2(Y,IRE,IRI) LT INF AND (XH2INVESTSTART LE YVALUE(Y))) = YES;
IXH2K_HASORPOT(Y,IRE,IRI)$(XH2INVCOST(Y,IRE,IRI) AND XH2INVCOST(Y,IRE,IRI) LT INF AND (XH2INVESTSTART LE YVALUE(Y))) = YES;
IXH2K_HASORPOT(Y,IRE,IRI)$(XH2INVCOST_NGTOH2(Y,IRE,IRI) AND XH2INVCOST_NGTOH2(Y,IRE,IRI) LT INF AND (XH2INVESTSTART LE YVALUE(Y))) = YES;

*These loops makes sure that if you invest in one line in the year Y, you can use this line in the future, even if you do not allow for investments on this line in the future
LOOP(Y$(ORD(Y) GT 1),
  LOOP(IRE,
    LOOP(IRI,
      IF ((XH2INVCOST(Y-1,IRE,IRI) AND XH2INVCOST(Y-1,IRE,IRI) LT INF AND (XH2INVESTSTART LE YVALUE(Y))),
        IXH2K_HASORPOT(Y,IRE,IRI)=IXH2KN(Y,IRE,IRI)+YES$XH2KFX(Y,IRE,IRI);
      );
      LOOP(IYALIAS2$((ORD(IYALIAS2) GE ORD(Y)) AND (ORD(IYALIAS2) NE CARD(IYALIAS2))),
      IXH2K_HASORPOT(Y+1,IRE,IRI)= IXH2K_HASORPOT(Y+1,IRE,IRI)+IXH2KN(Y,IRE,IRI);
      );
    );
  );
);

LOOP(Y$(ORD(Y) GT 1),
  LOOP(IRE,
    LOOP(IRI,
      IF ((XH2INVCOST_NGTOH2(Y-1,IRE,IRI) AND XH2INVCOST_NGTOH2(Y-1,IRE,IRI) LT INF AND (XH2INVESTSTART LE YVALUE(Y))),
        IXH2K_HASORPOT(Y,IRE,IRI)=IXH2KN_NGTOH2(Y,IRE,IRI)+YES$XH2KFX(Y,IRE,IRI);
      );
      LOOP(IYALIAS2$((ORD(IYALIAS2) GE ORD(Y)) AND (ORD(IYALIAS2) NE CARD(IYALIAS2))),
      IXH2K_HASORPOT(Y+1,IRE,IRI)= IXH2K_HASORPOT(Y+1,IRE,IRI)+IXH2KN_NGTOH2(Y,IRE,IRI);
      );
    );
  );
);

$label  H2_Transmission_investments_end
