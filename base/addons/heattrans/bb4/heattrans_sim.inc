* File heattrans_sim.inc for addon heattrans
* Latest revision 20181014(hr)

* Complement to equation QXHK_UP for the case with no endogenous transmission investments.
VXH_T.UP(IY411,IAE,IAI,S,T)$(IXHK_HASORPOT(IY411,IAE,IAI) AND (NOT SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IXHKN(IY411,IAE,IAI)))) = XHKFX(IY411,IAE,IAI);




