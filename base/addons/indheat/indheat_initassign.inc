* ----------------- Assign IAGKFX, IAGKN, IAGKNY, IAGK_HASORPOT ----------------------------------


INDHEAT_IAGKFX(Y,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP) = YES$INDHEAT_GKFX(Y,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP);
INDHEAT_IAGK_HASORPOT(Y,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP) = YES$INDHEAT_GKFX(Y,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP);

INDHEAT_IAGKN(INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP)=NO;
INDHEAT_IAGKNY(Y,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP)=NO;

$ifi not %GenInvest%==yes $goto Generation_investments_end

* IAGKN and IAGKNY indicates when and where technologies may be invested, based on various combinations of input data.
* Initially: identical to AGKN:
INDHEAT_IAGKN(INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP) = INDHEAT_AGKN(INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP);

* Note: by definition, there should be no GGG in AGKN(aaa,GGG) with GDATA(GGG,'GDKVARIABL')=1.
* This is to be checked in error2.inc: TODO. For now, overwrite to make sure:  No new capacity if capacity is not specified to be found endogeneously:
INDHEAT_IAGKN(INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP)$(INDHEAT_GINGROUP(INDHEAT_G,INDHEAT_GROUP) AND (NOT INDHEAT_GDATA(INDHEAT_G,'GDKVARIABL') EQ 1)) = NO;

INDHEAT_IAGKNY(Y,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP) = INDHEAT_IAGKN(INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP);
INDHEAT_IAGKNY(Y,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP)$(INDHEAT_GINGROUP(INDHEAT_G,INDHEAT_GROUP) AND YVALUE(Y) LT INDHEAT_GDATA(INDHEAT_G,'GDFROMYEAR') OR (YVALUE(Y) GT INDHEAT_GDATA(INDHEAT_G,'GDLASTYEAR')) AND (INDHEAT_GDATA(INDHEAT_G,'GDLASTYEAR') GT 0) OR (YVALUE(Y) LT GINVESTSTART))=NO;

*Update of IAGK_HASORPOT based on potential production

INDHEAT_IAGK_HASORPOT(Y,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP)$INDHEAT_IAGKNY(Y,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP) = YES;

***This loop makes sure that if you invest in a technology in the year Y, you can use it until it is decommissioned, even if you do not allow for investments on this technology in the future
LOOP(Y$(ORD(Y) NE CARD(Y)),
                   LOOP(INDHEAT_IA,
                         LOOP(INDHEAT_GROUP,
                               LOOP(INDHEAT_G$(INDHEAT_IAGKNY(Y,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP) AND INDHEAT_GINGROUP(INDHEAT_G,INDHEAT_GROUP)),
                                        LOOP(IYALIAS2$((ORD(IYALIAS2) GT ORD(Y)) AND ((YVALUE(Y)+INDHEAT_GDATA(INDHEAT_G,'GDLIFETIME')) GT (YVALUE(IYALIAS2)))),
                                                                    INDHEAT_IAGK_HASORPOT(Y++1,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP)= INDHEAT_IAGK_HASORPOT(Y++1,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP)+INDHEAT_IAGKNY(Y,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP);
                                        );
                               );
                         );
                    );
);

$label  Generation_investments_end

Display INDHEAT_IAGK_HASORPOT, INDHEAT_IAGKNY;


* ----------------- End: Assign IAGKFX, IAGKN, IAGKNY, IAGK_HASORPOT -----------------------------