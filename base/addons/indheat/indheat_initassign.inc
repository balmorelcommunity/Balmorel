SET TESTSET(Y,INDHEAT_AAA,INDHEAT_GGG,INDHEAT_GROUP,S,T);

* ----------------- Assign IAGKFX, IAGKN, IAGKNY, IAGK_HASORPOT ----------------------------------

INDHEAT_IAGKFX(Y,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP)=NO;
INDHEAT_IAGK_HASORPOT(Y,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP)=NO;

INDHEAT_IAGKFX(Y,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP) = YES$INDHEAT_GKFX(Y,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP);
INDHEAT_IAGK_HASORPOT(Y,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP) = YES$INDHEAT_GKFX(Y,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP);

INDHEAT_IAGKN(INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP)=NO;
INDHEAT_IAGKNY(Y,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP)=NO;

$ifi not %TechInvest%==yes $goto Generation_investments_end

* IAGKN and IAGKNY indicates when and where technologies may be invested, based on various combinations of input data.
* Initially: identical to AGKN:
INDHEAT_IAGKN(INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP) = INDHEAT_AGKN(INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP);

* Note: by definition, there should be no GGG in AGKN(aaa,GGG) with GDATA(GGG,'GDKVARIABL')=1.
* This is to be checked in error2.inc: TODO. For now, overwrite to make sure:  No new capacity if capacity is not specified to be found endogeneously:
INDHEAT_IAGKN(INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP)$(INDHEAT_GINGROUP(INDHEAT_G,INDHEAT_GROUP) AND (NOT INDHEAT_GDATA(INDHEAT_G,'GDKVARIABL') EQ 1)) = NO;

INDHEAT_IAGKNY(Y,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP) = INDHEAT_IAGKN(INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP);
INDHEAT_IAGKNY(Y,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP)$(INDHEAT_GINGROUP(INDHEAT_G,INDHEAT_GROUP) AND YVALUE(Y) LT INDHEAT_GDATA(INDHEAT_G,'GDFROMYEAR') OR (YVALUE(Y) GT INDHEAT_GDATA(INDHEAT_G,'GDLASTYEAR')) AND (INDHEAT_GDATA(INDHEAT_G,'GDLASTYEAR') GT 0) OR (YVALUE(Y) LT INDHEAT_GINVESTSTART))=NO;

*Update of IAGK_HASORPOT based on potential production

INDHEAT_IAGK_HASORPOT(Y,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP)$INDHEAT_IAGKNY(Y,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP) = YES;

Parameter TestOutput;
Parameter TestYear;
***This loop makes sure that if you invest in a technology in the year Y, you can use it until it is decommissioned, even if you do not allow for investments on this technology in the future
LOOP(Y$(ORD(Y) NE CARD(Y)),
                   LOOP(INDHEAT_IA,
                               LOOP((INDHEAT_G,INDHEAT_GROUP)$(INDHEAT_IAGKNY(Y,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP) AND INDHEAT_GINGROUP(INDHEAT_G,INDHEAT_GROUP)),
                                        LOOP(IYALIAS2$((ORD(IYALIAS2) GT ORD(Y)) AND ((YVALUE(Y)+INDHEAT_GDATA(INDHEAT_G,'GDLIFETIME')) GT (YVALUE(IYALIAS2)))),
                                                                 TestOutput = (YVALUE(Y)+INDHEAT_GDATA(INDHEAT_G,'GDLIFETIME'));
                                                                 TestYear = YVALUE(IYALIAS2);
                                                                 INDHEAT_IAGK_HASORPOT(Y++1,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP)= INDHEAT_IAGK_HASORPOT(Y++1,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP)+INDHEAT_IAGKNY(Y,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP);
                                         );
                               );
                    );
);

$label  Generation_investments_end


* ----------------- End: Assign IAGKFX, IAGKN, IAGKNY, IAGK_HASORPOT -----------------------------

*------------ Calculation of IYHASANNUITYG to include/exclude the payment of the annuities---------------------
PARAMETERS
         INDHEAT_IYHASANNUITYG(Y,IYALIAS,INDHEAT_G)      "Binary parameter to establish whether the annuity of an investment of a technology made in Y (first index) should be paid in the time period Y (second index) (0,1)"
         INDHEAT_IINVYEARG_LEFT(Y,IYALIAS,INDHEAT_G)     "Remaining years of the lifetime of G of an investment made in Y (first index) at the beggining of Y (second index) (years)"
         INDHEAT_IN_INV_G(Y,INDHEAT_G)                   "Number of investments made OF G within Y (fraction)"
;

$ifi not %TechInvest%==yes  INDHEAT_IYHASANNUITYG(IYALIAS,Y,INDHEAT_G)= 0;
$ifi not %TechInvest%==yes $goto endtechinvest

LOOP(IYALIAS,
  LOOP(INDHEAT_G$SUM((INDHEAT_IA,INDHEAT_GROUP),INDHEAT_IAGKNY(IYALIAS,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP)),
    LOOP(Y$(ORD(Y) EQ ORD(IYALIAS)),
      INDHEAT_IINVYEARG_LEFT(IYALIAS,Y,INDHEAT_G)=INDHEAT_GDATA(INDHEAT_G,'GDLIFETIME');
    );
  );
);

LOOP(IYALIAS,
  LOOP(INDHEAT_G$SUM((INDHEAT_IA,INDHEAT_GROUP),INDHEAT_IAGKNY(IYALIAS,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP)),
         ILOOPBREAK=0;
         INDHEAT_IN_INV_G(IYALIAS,INDHEAT_G)$(YVALUE(IYALIAS) GE INDHEAT_GDATA(INDHEAT_G,'GDFROMYEAR') AND YVALUE(IYALIAS) LE INDHEAT_GDATA(INDHEAT_G,'GDLASTYEAR'))
                 = ROUND(IWEIGHTY(IYALIAS)/INDHEAT_GDATA(INDHEAT_G,'GDLIFETIME'));
         IF (INDHEAT_IN_INV_G(IYALIAS,INDHEAT_G) EQ 0,
                 INDHEAT_IN_INV_G(IYALIAS,INDHEAT_G)=1;
         );

         LOOP(Y$(ORD(Y) GE ORD(IYALIAS) AND (ILOOPBREAK EQ 0)),
*First year's annuity
         IF (ORD(Y) EQ ORD(IYALIAS),
         INDHEAT_IYHASANNUITYG(IYALIAS,Y,INDHEAT_G)= 1;
         IF(INDHEAT_IINVYEARG_LEFT(IYALIAS,Y,INDHEAT_G)*INDHEAT_IN_INV_G(IYALIAS,INDHEAT_G) LE IWEIGHTY(Y),
            ILOOPBREAK=1;
          );
          INDHEAT_IINVYEARG_LEFT(IYALIAS,Y+1,INDHEAT_G)$(ORD(Y) NE CARD(IYALIAS2))=INDHEAT_GDATA(INDHEAT_G,'GDLIFETIME')*INDHEAT_IN_INV_G(IYALIAS,INDHEAT_G)-IWEIGHTY(Y);
          INDHEAT_IINVYEARG_LEFT(IYALIAS,Y+1,INDHEAT_G)$((ORD(Y) NE CARD(IYALIAS2)) AND INDHEAT_IINVYEARG_LEFT(IYALIAS,Y+1,INDHEAT_G) LT 0)=0;
        );
*Remaining year's annuity
      IF (ORD(Y) GT ORD(IYALIAS),
        IF ( INDHEAT_IINVYEARG_LEFT(IYALIAS,Y,INDHEAT_G) GT IWEIGHTY(Y) ,
          INDHEAT_IYHASANNUITYG(IYALIAS,Y,INDHEAT_G)= 1;
            INDHEAT_IINVYEARG_LEFT(IYALIAS,Y+1,INDHEAT_G)$(ORD(Y) NE CARD(IYALIAS2))=INDHEAT_IINVYEARG_LEFT(IYALIAS,Y,INDHEAT_G)-IWEIGHTY(Y);
          );
          IF ((INDHEAT_IINVYEARG_LEFT(IYALIAS,Y,INDHEAT_G) GE IWEIGHTY(IYALIAS)/2) AND (INDHEAT_IINVYEARG_LEFT(IYALIAS,Y,INDHEAT_G) LE IWEIGHTY(Y)) ,  !!Assumption: if the reamining years are more ore equal than half of IWEIGHTY, then the technology is in in this snapshot
            INDHEAT_IYHASANNUITYG(IYALIAS,Y,INDHEAT_G)= 1;
            ILOOPBREAK=1;
          );
          IF ((INDHEAT_IINVYEARG_LEFT(IYALIAS,Y,INDHEAT_G) LT IWEIGHTY(IYALIAS)/2) AND (INDHEAT_IINVYEARG_LEFT(IYALIAS,Y,INDHEAT_G) LE IWEIGHTY(Y)) , !!Assumption: if the reamining years are less than half of IWEIGHTY, then the technology is out in this snapshot
            INDHEAT_IYHASANNUITYG(IYALIAS,Y,INDHEAT_G)= 0;
            ILOOPBREAK=1;
          );
        );
      );
  );
);

$label endtechinvest
