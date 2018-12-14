* File heattrans_qobj.inc for addon heattrans
* Latest revision 20181014(hr)

* Heat transmission cost:
+ SUM((IAE,IAI)$IXHK_HASORPOT(Y,IAE,IAI),
        SUM((S,T), IHOURSINST(S,T) * (VXH_T(Y,IAE,IAI,S,T) * XHCOST(IAE,IAI))))

                                                   /*  Not implemented yet 
* Investment costs, new heat transmission capacity (the average of the annuities for the (one or two) countires in question
* is used for transmission):
+ SUM((IAE,IAI)$(IXHKN(IAE,IAI) OR IXHKN(IAE,IAI)), VXHKN(Y,IAE,IAI)*XHINVCOST(IAE,IAI)*
        (0.5*(SUM(C$ICA(C,IAE),ANNUITYCHX(C))+SUM(C$ICA(C,IAI),ANNUITYCHX(C)))))


                                               */
$log "#### todo in %system.incname% ####;
