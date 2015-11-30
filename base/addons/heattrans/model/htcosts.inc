* Heat transmission cost:
+ SUM((IAE,IAI)$(IXHKINI_Y(IAE,IAI) OR IXHKN(IAE,IAI) OR IXHKN(IAI,IAE)),
        SUM((S,T), IHOURSINST(S,T) * (VXH_T(IAE,IAI,S,T) * XHCOST(IAE,IAI))))


* Investment costs, new heat transmission capacity
* (the average of the annuities for the (one or two) countires in question
* is used for transmission):                    /*varmetrans*/
+ SUM((IAE,IAI)$(IXHKN(IAE,IAI) OR IXHKN(IAE,IAI)), VXHKN(IAE,IAI)*XHINVCOST(IAE,IAI)*
        (0.5*(SUM(C$ICA(C,IAE),ANNUITYC(C))+SUM(C$ICA(C,IAI),ANNUITYC(C)))))



