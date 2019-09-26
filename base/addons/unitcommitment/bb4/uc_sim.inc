* UC Translated to BB4 by Juan Gea Bermúdez 2018.

* Simple bounds are set on the number of units online, offline, started and
* shut-down within a single hour.

* Exogenous capacity:

* At most a number of units equal to the installed capacity, divided by the unit size rounded up, can be committed, started or shutdown at one time.
VUCON.UP(IY411,IA,IGUC,IS3,T)$(GKFX(IY411,IA,IGUC) AND (NOT SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGUC)))) = CEIL((GKFX(IY411,IA,IGUC)/GDATA(IGUC,'GDUCUNITSIZE')*(1$(NOT IGKRATE(IA,IGUC,IS3,T)) + IGKRATE(IA,IGUC,IS3,T)) ));
VUCU.UP(IY411,IA,IGUC,IS3,T)$(GKFX(IY411,IA,IGUC) AND (NOT SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGUC))))  = CEIL((GKFX(IY411,IA,IGUC)/GDATA(IGUC,'GDUCUNITSIZE')));
VUCD.UP(IY411,IA,IGUC,IS3,T)$(GKFX(IY411,IA,IGUC) AND (NOT SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGUC))))  = CEIL((GKFX(IY411,IA,IGUC)/GDATA(IGUC,'GDUCUNITSIZE')));
$ifi %PLANNED_MAINTENANCE%==yes $ifi not %ADDPLANNEDMAINTENANCE%==yes   VUCONMAINT.UP(IY411,IA,IGUC,IS3)$(GKFX(IY411,IA,IGUC) AND (NOT SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGUC)))  AND IGPLANMAINT(IGUC))  = CEIL((GKFX(IY411,IA,IGUC)/GDATA(IGUC,'GDUCUNITSIZE')));
$ifi %PLANNED_MAINTENANCE%==yes $ifi not %ADDPLANNEDMAINTENANCE%==yes   VUCUMAINT.UP(IY411,IA,IGUC,IS3)$(GKFX(IY411,IA,IGUC) AND (NOT SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGUC)))  AND IGPLANMAINT(IGUC))  = CEIL((GKFX(IY411,IA,IGUC)/GDATA(IGUC,'GDUCUNITSIZE')));
$ifi %PLANNED_MAINTENANCE%==yes $ifi not %ADDPLANNEDMAINTENANCE%==yes   VUCDMAINT.UP(IY411,IA,IGUC,IS3)$(GKFX(IY411,IA,IGUC) AND (NOT SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGUC)))  AND IGPLANMAINT(IGUC))  = CEIL((GKFX(IY411,IA,IGUC)/GDATA(IGUC,'GDUCUNITSIZE')));
$ifi %PLANNED_MAINTENANCE%==yes $ifi %ADDPLANNEDMAINTENANCE%==yes  $ifi not %SOLVETYPE%==MIP      VUCONMAINT.FX(IY411,IA,IGUC,IS3)$IAGK_HASORPOT(IY411,IA,IGUC)=UCONMAINT(IY411,IA,IGUC,IS3);
$ifi %PLANNED_MAINTENANCE%==yes $ifi %ADDPLANNEDMAINTENANCE%==yes  $ifi     %SOLVETYPE%==MIP      VUCONMAINT.FX(IY411,IA,IGUC,IS3)$IAGK_HASORPOT(IY411,IA,IGUC)=ROUND(UCONMAINT(IY411,IA,IGUC,IS3));                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         
* Updating other bounds

VGE_T.UP(IY411,IA,IGDISPATCH(IGKE),IS3,T)$(IGUC(IGKE) AND GKFX(IY411,IA,IGKE) AND (NOT SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGKE))) AND (NOT IGESTOALL(IGKE))) = GDATA(IGKE,'GDUCUNITSIZE')*VUCON.UP(IY411,IA,IGKE,IS3,T);
VGH_T.UP(IY411,IA,IGDISPATCH(IGKH),IS3,T)$(IGUC(IGKH) AND GKFX(IY411,IA,IGKH) AND (NOT SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGKH))) AND (NOT IGHSTOALL(IGKH))) = GDATA(IGKH,'GDUCUNITSIZE')*VUCON.UP(IY411,IA,IGKH,IS3,T);

