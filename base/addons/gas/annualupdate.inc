* Transfer investments from previous year by raising the lower bound on investment
* quantity.
$ifi %bb2%==yes VGINVSTORE.lo(STORE,STORETYPE) = VGINVSTORE.l(STORE,STORETYPE);
$ifi %bb2%==yes VGINVINJ.lo(STORE,STORETYPE)   = VGINVINJ.l(STORE,STORETYPE);
$ifi %bb2%==yes VGINVEXT.lo(STORE,STORETYPE)   = VGINVEXT.l(STORE,STORETYPE);
$ifi %bb2%==yes VGINFINV.lo(NGINV) = VGINFINV.l(NGINV);
$ifi %bb2%==yes VGNETINV.lo(C,GNETSTEPS)       = VGNETINV.l(C,GNETSTEPS);

* Load capacity reservations (BB3 only) reservations are generated in BB1 or BB2
$ifi %bb3%==yes  ITC_EX_Y(SYSEXIT)           = TC_EX_Y(SYSEXIT,Y);
$ifi %bb3%==yes  ITC_EX_M(SYSEXIT,S,T)       = TC_EX_M(SYSEXIT,Y,S,T);
$ifi %bb3%==yes  ITC_EN_Y(SYSENTRY)          = TC_EN_Y(SYSENTRY,Y);
$ifi %bb3%==yes  ITC_EN_M(SYSENTRY,S,T)      = TC_EN_M(SYSENTRY,Y,S,T);

$ifi %bb3%==yes  IGSFXW(STORE,STORETYPE,S)              = GSFXW(Y,STORE,STORETYPE,S);
$ifi %bb3%==yes  ISC(SCON)              = SC_Y(Y,SCON);
$ifi %bb3%==yes  IHYFXRW(S,IR)          = HYFXRW_GAS(Y,S,IR);
$ifi %bb3%==yes  IWATERVAL(IA,S)        = WATERVAL(Y,S,IA);

* Gas consumption not instigated by generation of electricity and/or district
* heating:
IDGRES_Y(IA,S,T)= DGRES(Y,IA) * (DGRES_VAR(IA,S,T)  / IDGRES_SUMVAR(IA))$(IDGRES_SUMVAR(IA) >0);
IDGOTH_Y(IA,S,T)= DGOTH(Y,IA) * (DGOTH_VAR(IA,S,T)  / IDGOTH_SUMVAR(IA))$(IDGOTH_SUMVAR(IA) >0);

* Use simple bounds for capacity of supply, export, and storage operations when
* not simulating with endogenous investments.
$ifi not %bb2%==yes VSTOCK.UP(STORE,STORETYPE,S,T)= STORAGE_MAX(Y,STORE,STORETYPE)-TSOSTORAGE(Y,STORE,STORETYPE);
$ifi not %bb2%==yes VINJ.UP(STORE,STORETYPE,S,T)  = INJ_MAX(Y,STORE,STORETYPE)    ;
$ifi not %bb2%==yes VEXT.UP(STORE,STORETYPE,S,T)  = EXT_MAX(Y,STORE,STORETYPE)    ;
$ifi not %bb2%==yes VEXP.UP(SOURCE,S)             = EXP_MAX(Y,SOURCE)   ;
$ifi not %BB2%==yes VTRANSIT.up(TRANSIT(AAA),S,T) = SUM(SOURCE(AAA), EXP_MAX(Y,SOURCE));
$ifi not %bb2%==yes VSUP.UP(SOURCE,S,T)           = SUPPLY_MAX(Y,SOURCE);

* Delivery maximum is never a simple bound.
IDEV_MAX(SYSEXIT)                                 = DEV_MAX(Y,SYSEXIT);

* Add investments in gas infrastructure to bb1 or bb3 simulation
$ifi %ADDINVEST%==yes VSTOCK.UP(STORE,STORETYPE,S,T)= STOREACC(Y,STORE,STORETYPE)+ VSTOCK.UP(STORE,STORETYPE,S,T)  ;
$ifi %ADDINVEST%==yes VINJ.UP(STORE,STORETYPE,S,T)  = INJACC(Y,STORE,STORETYPE)+   VINJ.UP(STORE,STORETYPE,S,T)    ;
$ifi %ADDINVEST%==yes VEXT.UP(STORE,STORETYPE,S,T)  = EXTACC(Y,STORE,STORETYPE)+   VEXT.UP(STORE,STORETYPE,S,T)    ;
$ifi %ADDINVEST%==yes VEXP.UP(SOURCE,S)             = EXPACC(Y,SOURCE)+            VEXP.UP(SOURCE,S)             ;
$ifi %ADDINVEST%==yes VTRANSIT.UP(TRANSIT(AAA),S,T) = SUM(SOURCE(AAA), EXPACC(Y,SOURCE))+ VTRANSIT.UP(TRANSIT,S,T);
$ifi %ADDINVEST%==yes VSUP.UP(SOURCE,S,T)           = SUPACC(Y,SOURCE)+            VSUP.UP(SOURCE,S,T)             ;
$ifi %ADDINVEST%==yes IDEV_MAX(SYSEXIT)             = DEV_MAX(Y,SYSEXIT)+DEVACC(Y,SYSEXIT);

* Parameters used for define capacity bounds of existing infrastructure. Total
* capacity also includes capacity effects of investments.
$ifi %bb2%==yes ISUPPLY_MAX(SOURCE)         = SUPPLY_MAX(Y,SOURCE);
$ifi %bb2%==yes IEXP_MAX(SOURCE)            = EXP_MAX(Y,SOURCE)   ;
$ifi %bb2%==yes IINJ_MAX(STORE,STORETYPE)   = INJ_MAX(Y,STORE,STORETYPE)   ;
$ifi %bb2%==yes IEXT_MAX(STORE,STORETYPE)   = EXT_MAX(Y,STORE,STORETYPE)    ;
$ifi %bb2%==yes ISTORE_MAX(STORE,STORETYPE) = STORAGE_MAX(Y,STORE,STORETYPE)-TSOSTORAGE(Y,STORE,STORETYPE) ;

* Define border price at adjacent systems.
IGEX_PRICE(SOURCE,S) = GEX_PRICE(Y,SOURCE,S);

* Assign wellhead price.
IGEXT_COST(SOURCE,S) = GEXT_COST(Y,SOURCE,S);