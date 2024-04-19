* -------- GAS COSTS -------- *
* Gas expenses in kr. exchange rate 7.43 used
$ontext
$ifi %bb1%==yes     +                          CTC_EN_Y            *VTC_EN_Y
$ifi %bb1%==yes     +                          CTC_EX_Y            *VTC_EX_Y
$ifi %bb1%==yes     + SUM(IMONTH,              CTC_EN_M(IMONTH)   *VTC_EN_M(IMONTH))
$ifi %bb1%==yes     + SUM(IMONTH,              CTC_EX_M(IMONTH)   *VTC_EX_M(IMONTH))
$ifi %bb2%==yes     +                          CTC_EN_Y            *VTC_EN_Y
$ifi %bb2%==yes     +                          CTC_EX_Y            *VTC_EX_Y
$ifi %bb2%==yes     + SUM(IMONTH,              CTC_EN_M(IMONTH)   *VTC_EN_M(IMONTH))
$ifi %bb2%==yes     + SUM(IMONTH,              CTC_EX_M(IMONTH)   *VTC_EX_M(IMONTH))
                    + SUM(IS3,                 CTC_EN_W(IS3)       *VTC_EN_W(IS3))
                    + SUM(IS3,                 CTC_EX_W(IS3)       *VTC_EX_W(IS3))
$ifi %bb3%==yes     + SUM((IS3,DAY),           CTC_EN_D(IS3,DAY)    *VTC_EN_D(IS3,DAY))
$ifi %bb3%==yes     + SUM((IS3,DAY),           CTC_EX_D(IS3,DAY)    *VTC_EX_D(IS3,DAY))
                    + SUM((SOURCE,IS3,T),      CSUP(SOURCE,IS3,T)     *VSUP(SOURCE,IS3,T))
$ifi %bb1%==yes     + SUM(SCON,                CSC(SCON)              *VSC(SCON))
$ifi %bb2%==yes     + SUM(SCON,                CSC(SCON)              *VSC(SCON))
                    + SUM((STORE,IS3,T),       CINJ(STORE, IS3,T)     *VINJ(STORE, IS3,T))
                    + SUM((SOURCE,IS3,T),      CEXP(SOURCE,IS3,T)     *VEXP(SOURCE,IS3,T))
$offtext

+1/7.43/1.389*(
* Transmission costs
$ifi %bb1%==yes + SUM(SYSENTRY,  TAU_EN_Y*VTC_EN_Y(SYSENTRY)     )
$ifi %bb1%==yes + SUM(SYSEXIT,   TAU_EX_Y*VTC_EX_Y(SYSEXIT)     )
$ifi %bb1%==yes + SUM(SYSENTRY,  SUM(IMONTH, TAU_EN_M(IMONTH)*VTC_EN_M(SYSENTRY,IMONTH)*MONTHSCALE(IMONTH))     )
$ifi %bb1%==yes + SUM(SYSEXIT,   SUM(IMONTH, TAU_EX_M(IMONTH)*VTC_EX_M(SYSEXIT,IMONTH)*MONTHSCALE(IMONTH))     )
$ifi %bb2%==yes + SUM(SYSENTRY,  TAU_EN_Y*VTC_EN_Y(SYSENTRY)     )
$ifi %bb2%==yes + SUM(SYSEXIT,   TAU_EX_Y*VTC_EX_Y(SYSEXIT)     )
$ifi %bb2%==yes + SUM(SYSENTRY,  SUM(IMONTH, TAU_EN_M(IMONTH)*VTC_EN_M(SYSENTRY,IMONTH)*MONTHSCALE(IMONTH))     )
$ifi %bb2%==yes + SUM(SYSEXIT,  SUM(IMONTH, TAU_EX_M(IMONTH)*VTC_EX_M(SYSEXIT,IMONTH)*MONTHSCALE(IMONTH))     )
+     SUM(SYSENTRY,  sum(IS3,IDAYSIN_S(IS3)/7*(TAU_EN_W(IS3)*VTC_EN_W(SYSENTRY,IS3)))     )
+     SUM(SYSEXIT,   sum(IS3,IDAYSIN_S(IS3)/7*(TAU_EX_W(IS3)*VTC_EX_W(SYSEXIT,IS3)))     )
+     SUM((SYSENTRY,IS3,T), VTC_EN_FLEX(SYSENTRY,IS3,T)*IHOURSINST(IS3,T)*TAU_EN_FLEX(SYSENTRY)     )
+     SUM((SYSEXIT,IS3,T),  VTC_EX_FLEX(SYSEXIT,IS3,T) *IHOURSINST(IS3,T)*TAU_EX_FLEX(SYSEXIT)    )
$ifi %bb3%==yes + SUM(SYSENTRY,  sum((IS3,DAY), TAU_EN_D(IS3,DAY)*VTC_EN_D(SYSENTRY,IS3,DAY))     )
$ifi %bb3%==yes + SUM(SYSEXIT,  sum((IS3,DAY), TAU_EX_D(IS3,DAY)*VTC_EX_D(SYSEXIT,IS3,DAY))     )
+     SUM((IA,IS3,T)$ICA('Denmark',IA), TAU_VOL*VGUD(IA,IS3,T))
+     SUM((SOURCE,IS3,T)$(not sameas(SOURCE,'Nybro')), IHOURSINST(IS3,T)*VEXP(SOURCE,IS3))
+     SUM((TRANSIT,IS3,T),IHOURSINST(IS3,T)*VTRANSIT(TRANSIT,IS3,T))
* Storage costs
$ifi %bb1%==yes +sum(SCON, VSC(SCON)*SCONDATA(SCON,'TARRIF'))
$ifi %bb2%==yes +sum(SCON, VSC(SCON)*SCONDATA(SCON,'TARRIF'))
* Udkommenteret fordi variable omkostninger kobles til el og gas priser
*      +TAU_INJ*sum((STORE,IS3,T), IHOURSINST(IS3,T)*VINJ(STORE, IS3,T))

* Distribution costs
+     sum((DDD,AAA,IS3,T)$(DDDNODE(DDD,AAA) and IA(AAA)) , IHOURSINST(IS3,T)*TAU_DIST(DDD)*VGUD(AAA,IS3,T))
+     sum((DDD,TRANSIT,IS3,T)$DDDNODE(DDD,TRANSIT), IHOURSINST(IS3,T)*TAU_DIST(DDD)*VTRANSIT(TRANSIT,IS3,T))
)
* Consumer utility

* Value of exports
- sum((SOURCE,IS3,T),IHOURSINST(IS3,T)*(IGEX_PRICE(SOURCE,IS3)*IOF3P6)*VEXP(SOURCE,IS3))

* Cost of imports
+ sum((SOURCE,IS3,T)$(not sameas(SOURCE,'Nybro')),IHOURSINST(IS3,T)*(IGEX_PRICE(SOURCE,IS3)*IOF3P6)*VSUP(SOURCE,IS3,T))

* Cost of extraction
+ sum((SOURCE,IS3,T),IHOURSINST(IS3,T)*IGEXT_COST(SOURCE,IS3)*IOF3P6*VSUP(SOURCE,IS3,T))

* Investment costs
$ifi %bb2%==yes + sum(NGINV,COST_NGINV(NGINV)*VGINFINV(NGINV))*GASANNUITY

$ifi %bb2%==yes + sum((C,GNETSTEPS), GNET_COST(C,GNETSTEPS)*VGNETINV(C,GNETSTEPS))*GASANNUITY

$ifi %bb2%==yes + sum((STORE,STORETYPE),GSTOREDATA(STORETYPE,'INVCOST')*VGINVSTORE(STORE,STORETYPE))
$ifi %bb2%==yes + sum((STORE,STORETYPE),GSTOREDATA(STORETYPE,'FOMK')*VGINVSTORE(STORE,STORETYPE))
$ifi %bb2%==yes + sum((STORE,STORETYPE),GSTOREDATA(STORETYPE,'MargExtInvCost')*VGINVEXT(STORE,STORETYPE))
$ifi %bb2%==yes + sum((STORE,STORETYPE),GSTOREDATA(STORETYPE,'MargInjInvCost')*VGINVINJ(STORE,STORETYPE))
