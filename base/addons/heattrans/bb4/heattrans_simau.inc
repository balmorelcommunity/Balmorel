* File heattrans_simau.inc for addon heattrans
* Latest revision 20181014(hr)

* Presently assuming NO endogenous investments! Code ot be revised if introduced

IXHK_HASORPOT(IY411,IAE,IAI) = YES$XHKFX(IY411,IAE,IAI);
IXHK_HASORPOT(IY411,IAE,IAI)$XHKN(IAE,IAI) = YES;

* Update bounds:
* Complement to equation ???QXK_UP???  for the case with no endogenous heat transmission investments.
VXH_T.UP(IY411,IAE,IAI,S,T)$(NOT XHKN(IAE,IAI)) = XHKFX(IY411,IAE,IAI);
VXHKNACCUMNET.FX(IY411,IAE,IAI)$(NOT XHKN(IAE,IAI)) = 0;  !! COMMENT FROM BB4.SIM FOR VXKNACCUMNET  !! Should not be necessary if condition on IAGKN(IA,G) is properly used in .gms code.


$LOG "TODO for addon heattrans in %system.incname%";

