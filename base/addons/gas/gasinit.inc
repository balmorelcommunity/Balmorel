$ifi %bb2%==yes VGINFINV.l(NGINV)              = 0;
$ifi %bb2%==yes VGINVSTORE.l(STORE,STORETYPE)  = 0;
$ifi %bb2%==yes VGINVINJ.l(STORE,STORETYPE)    = 0;
$ifi %bb2%==yes VGINVEXT.l(STORE,STORETYPE)    = 0;
$ifi %bb2%==yes VGINVSTORE.up(STORE,STORETYPE) = MAXINVEST(STORE,STORETYPE);
$ifi %bb2%==yes STOREINV(STORE, STORETYPE)     = YES$MAXINVEST(STORE,STORETYPE);
$ifi %bb2%==yes VGNETINV.up(C,GNETSTEPS)       = 0;
$ifi %bb2%==yes VGNETINV.up(C,GNETSTEPS)       = GNET_MAX(C,GNETSTEPS);