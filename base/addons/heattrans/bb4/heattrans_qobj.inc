* File heattrans_qobj.inc for addon heattrans
* Latest revision 20181014(hr)

* Heat transmission cost:
+ SUM((IAE,IAI)$IXHK_HASORPOT(Y,IAE,IAI),
        SUM((IS3,T), IHOURSINST(IS3,T) * (VXH_T(Y,IAE,IAI,IS3,T) * XHCOST(IAE,IAI))))

* Investment costs, new heat transmission capacity
* (the average of the annuities for the two countries in question is used for international transmission):
    + SUM((IAE,IAI)$(IXHKN(Y,IAI,IAE) OR IXHKN(Y,IAE,IAI)),IOF05*VXHKN(Y,IAE,IAI)*XHINVCOST(Y,IAE,IAI)*
      (IOF05* (SUM(C$ICA(C,IAE),ANNUITYCXH(C))+SUM(C$ICA(C,IAI),ANNUITYCXH(C))))*SUM(IYALIAS2$(ORD(IYALIAS2) EQ ORD(Y)),IYHASANNUITYXH(IYALIAS2,Y)))

*Investment costs, heat transmission capacity invested in previous years
    + SUM((IYALIAS2,IAE,IAI)$((IXHKN(IYALIAS2,IAI,IAE) OR IXHKN(IYALIAS2,IAE,IAI))  AND (ORD(IYALIAS2) LT ORD(Y))),IOF05*VXHKN(IYALIAS2,IAE,IAI)*XHINVCOST(IYALIAS2,IAE,IAI)*
      (IOF05* (SUM(C$ICA(C,IAE),ANNUITYCXH(C))+SUM(C$ICA(C,IAI),ANNUITYCXH(C))))*IYHASANNUITYXH(IYALIAS2,Y))


