* UC Translated to BB4 by Juan Gea Berm�dez 2018.

* Simple bounds are set on the number of units online, offline, started and
* shut-down within a single hour.

* Exogenous capacity:

* At most a number of units equal to the installed capacity, divided by the unit size rounded up, can be committed, started or shutdown at one time.
VUCON.UP(IY411,IA,IGUC,IS3,T)$(GKFX(IY411,IA,IGUC) AND (NOT SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGUC))) AND (NOT (IGDECOMEXOPOT(IY411,IA,IGUC)))) = CEIL((GKFX(IY411,IA,IGUC)/GDATA(IGUC,'GDUCUNITSIZE')*(1$(NOT IGKRATE(IA,IGUC,IS3,T)) + IGKRATE(IA,IGUC,IS3,T)) ));
VUCU.UP(IY411,IA,IGUC,IS3,T)$(GKFX(IY411,IA,IGUC) AND (NOT SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGUC))) AND (NOT (IGDECOMEXOPOT(IY411,IA,IGUC))))  = CEIL((GKFX(IY411,IA,IGUC)/GDATA(IGUC,'GDUCUNITSIZE')));
VUCD.UP(IY411,IA,IGUC,IS3,T)$(GKFX(IY411,IA,IGUC) AND (NOT SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGUC))) AND (NOT (IGDECOMEXOPOT(IY411,IA,IGUC))))  = CEIL((GKFX(IY411,IA,IGUC)/GDATA(IGUC,'GDUCUNITSIZE')));
VUCON_STOLOAD.UP(IY411,IA,IGUC,IS3,T)$(GKFX(IY411,IA,IGUC) AND (NOT SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGUC))) AND (NOT (IGDECOMEXOPOT(IY411,IA,IGUC))) AND (IGESTOALL(IGUC) OR IGHSTOALL(IGUC))) = CEIL((GKFX(IY411,IA,IGUC)/GDATA(IGUC,'GDUCUNITSIZE')*(1$(NOT IGKRATE(IA,IGUC,IS3,T)) + IGKRATE(IA,IGUC,IS3,T)) ));
VUCU_STOLOAD.UP(IY411,IA,IGUC,IS3,T)$(GKFX(IY411,IA,IGUC) AND (NOT SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGUC))) AND (NOT (IGDECOMEXOPOT(IY411,IA,IGUC))) AND (IGESTOALL(IGUC) OR IGHSTOALL(IGUC)))  = CEIL((GKFX(IY411,IA,IGUC)/GDATA(IGUC,'GDUCUNITSIZE')));
VUCD_STOLOAD.UP(IY411,IA,IGUC,IS3,T)$(GKFX(IY411,IA,IGUC) AND (NOT SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGUC)))  AND (NOT (IGDECOMEXOPOT(IY411,IA,IGUC))) AND (IGESTOALL(IGUC) OR IGHSTOALL(IGUC)))  = CEIL((GKFX(IY411,IA,IGUC)/GDATA(IGUC,'GDUCUNITSIZE')));

*Limiting bounds considering planned maintenance
$ifi %import_results%==yes $ifi %ADDPLANNEDMAINTENANCE%==yes VUCON.UP(IY411,IA,IGUC,IS3,T)$(GKFX(IY411,IA,IGUC) AND (NOT SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGUC))) AND (NOT (IGDECOMEXOPOT(IY411,IA,IGUC)))) = MAX(0,CEIL((GKFX(IY411,IA,IGUC)/GDATA(IGUC,'GDUCUNITSIZE')-UCONMAINT(IY411,IA,IGUC,IS3))*(1$(NOT IGKRATE(IA,IGUC,IS3,T)) + IGKRATE(IA,IGUC,IS3,T))));
$ifi %import_results%==yes $ifi %ADDPLANNEDMAINTENANCE%==yes VUCON_STOLOAD.UP(IY411,IA,IGUC,IS3,T)$(GKFX(IY411,IA,IGUC) AND (NOT SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGUC))) AND (NOT (IGDECOMEXOPOT(IY411,IA,IGUC))) AND (IGESTOALL(IGUC) OR IGHSTOALL(IGUC))) = MAX(0,CEIL((GKFX(IY411,IA,IGUC)/GDATA(IGUC,'GDUCUNITSIZE')-UCONMAINT(IY411,IA,IGUC,IS3))*(1$(NOT IGKRATE(IA,IGUC,IS3,T)) + IGKRATE(IA,IGUC,IS3,T))));

$ifi %PLANNED_MAINTENANCE%==yes VUCONMAINT.UP(IY411,IA,IGUC,IS3)$(GKFX(IY411,IA,IGUC) AND (NOT SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGUC))) AND (NOT (IGDECOMEXOPOT(IY411,IA,IGUC)))  AND IGPLANMAINT(IGUC))  = CEIL((GKFX(IY411,IA,IGUC)/GDATA(IGUC,'GDUCUNITSIZE')));
$ifi %PLANNED_MAINTENANCE%==yes VUCUMAINT.UP(IY411,IA,IGUC,IS3)$(GKFX(IY411,IA,IGUC) AND (NOT SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGUC))) AND (NOT (IGDECOMEXOPOT(IY411,IA,IGUC)))  AND IGPLANMAINT(IGUC))  = CEIL((GKFX(IY411,IA,IGUC)/GDATA(IGUC,'GDUCUNITSIZE')));
$ifi %PLANNED_MAINTENANCE%==yes VUCDMAINT.UP(IY411,IA,IGUC,IS3)$(GKFX(IY411,IA,IGUC) AND (NOT SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGUC))) AND (NOT (IGDECOMEXOPOT(IY411,IA,IGUC))) AND IGPLANMAINT(IGUC))  = CEIL((GKFX(IY411,IA,IGUC)/GDATA(IGUC,'GDUCUNITSIZE')));


* Updating other bounds

VGE_T.UP(IY411,IA,IGDISPATCH(IGKE),IS3,T)$(IGUC(IGKE) AND GKFX(IY411,IA,IGKE) AND (NOT SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGKE))) AND (NOT (IGDECOMEXOPOT(IY411,IA,IGKE))) AND (NOT IGESTOALL(IGKE))) = GDATA(IGKE,'GDUCUNITSIZE')*VUCON.UP(IY411,IA,IGKE,IS3,T);
VGH_T.UP(IY411,IA,IGDISPATCH(IGKH),IS3,T)$(IGUC(IGKH) AND GKFX(IY411,IA,IGKH) AND (NOT SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGKH))) AND (NOT (IGDECOMEXOPOT(IY411,IA,IGKH))) AND (NOT IGHSTOALL(IGKH))) = GDATA(IGKH,'GDUCUNITSIZE')*VUCON.UP(IY411,IA,IGKH,IS3,T);

* Storage loading (MW) and unloading (MW) do not exceed capacity.
* Complements to equations QESTOLOADTLIM and QHSTOLOADTLIM for the case with no endogenous IGESTO and IGHSTO investments.

*Unloading
VGE_T.UP(IY411,IA,IGESTO,S,T)$(IGUC(IGESTO) AND GKFX(IY411,IA,IGESTO) AND (NOT SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGESTO))) AND (NOT (IGDECOMEXOPOT(IY411,IA,IGESTO)))) = GDATA(IGESTO,'GDUCUNITSIZE')*VUCON.UP(IY411,IA,IGESTO,S,T)/GDATA(IGESTO,'GDSTOHUNLD');
VGH_T.UP(IY411,IA,IGHSTO,S,T)$(IGUC(IGHSTO) AND GKFX(IY411,IA,IGHSTO) AND (NOT SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGHSTO))) AND (NOT (IGDECOMEXOPOT(IY411,IA,IGHSTO)))) = GDATA(IGHSTO,'GDUCUNITSIZE')*VUCON.UP(IY411,IA,IGHSTO,S,T)/GDATA(IGHSTO,'GDSTOHUNLD');
VGE_T.UP(IY411,IA,IGESTOS,S,T)$(IGUC(IGESTOS) AND GKFX(IY411,IA,IGESTOS) AND (NOT SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGESTOS))) AND (NOT (IGDECOMEXOPOT(IY411,IA,IGESTOS)))) = GDATA(IGESTOS,'GDUCUNITSIZE')*VUCON.UP(IY411,IA,IGESTOS,S,T)/GDATA(IGESTOS,'GDSTOHUNLD');
VGH_T.UP(IY411,IA,IGHSTOS,S,T)$(IGUC(IGHSTOS) AND GKFX(IY411,IA,IGHSTOS) AND (NOT SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGHSTOS))) AND (NOT (IGDECOMEXOPOT(IY411,IA,IGHSTOS)))) = GDATA(IGHSTOS,'GDUCUNITSIZE')*VUCON.UP(IY411,IA,IGHSTOS,S,T)/GDATA(IGHSTOS,'GDSTOHUNLD');

*Loading
VESTOLOADT.UP(IY411,IA,IGESTO,S,T)$(IGUC(IGESTO) AND GKFX(IY411,IA,IGESTO) AND (NOT SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGESTO))) AND (NOT (IGDECOMEXOPOT(IY411,IA,IGESTO)))) =
  GDATA(IGESTO,'GDUCUNITSIZE')*VUCON_STOLOAD.UP(IY411,IA,IGESTO,S,T)/GDATA(IGESTO,'GDSTOHLOAD');
VHSTOLOADT.UP(IY411,IA,IGHSTO,S,T)$(IGUC(IGHSTO) AND GKFX(IY411,IA,IGHSTO) AND (NOT SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGHSTO))) AND (NOT (IGDECOMEXOPOT(IY411,IA,IGHSTO)))) =
  GDATA(IGHSTO,'GDUCUNITSIZE')*VUCON_STOLOAD.UP(IY411,IA,IGHSTO,S,T)/GDATA(IGHSTO,'GDSTOHLOAD');
VESTOLOADTS.UP(IY411,IA,IGESTOS,S,T)$(IGUC(IGESTOS) AND GKFX(IY411,IA,IGESTOS) AND (NOT SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGESTOS))) AND (NOT (IGDECOMEXOPOT(IY411,IA,IGESTOS)))) =
  GDATA(IGESTOS,'GDUCUNITSIZE')*VUCON_STOLOAD.UP(IY411,IA,IGESTOS,S,T)/GDATA(IGESTOS,'GDSTOHLOAD');
VHSTOLOADTS.UP(IY411,IA,IGHSTOS,S,T)$(IGUC(IGHSTOS) AND GKFX(IY411,IA,IGHSTOS) AND (NOT SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGHSTOS))) AND (NOT (IGDECOMEXOPOT(IY411,IA,IGHSTOS)))) =
  GDATA(IGHSTOS,'GDUCUNITSIZE')*VUCON_STOLOAD.UP(IY411,IA,IGHSTOS,S,T)/GDATA(IGHSTOS,'GDSTOHLOAD');
