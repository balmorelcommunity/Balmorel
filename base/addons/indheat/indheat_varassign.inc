*Fixing the VGKN investments in previous optimizations to apply correctly the decommissioning (missing: this formula is not enough if the years are analysed in a discontinuous way)
$ifi %GenInvest%==yes         LOOP(Y$(YVALUE(Y) LE YVALUE(IYALIAS)),INDHEAT_VGKN.FX(Y,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP) = INDHEAT_VGKN.L(Y,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP););

*Fixing the accumulated investments from previous optimization for the next optimization
$ifi %GenInvest%==yes         INDHEAT_VGKNACCUMNET.FX(IY411FIRST,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP)$SUM(Y$(YVALUE(Y) LE YVALUE(IY411FIRST)),INDHEAT_AGKN(INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP)) = INDHEAT_VGKNACCUMNET.L(IY411FIRST,INDHEAT_IA,INDHEAT_G,INDHEAT_GROUP);
