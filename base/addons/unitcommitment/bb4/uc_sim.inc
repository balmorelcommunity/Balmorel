* UC Translated to BB4 by Juan Gea Bermúdez 2018.

* Simple bounds are set on the number of units online, offline, started and
* shut-down within a single hour.


* Exogenous capacity:

* At most a number of units equal to the installed capacity, divided by the unit size rounded up, can be committed, started or shutdown at one time.
VUCON.UP(IY411,IA,IGUC,IS3,T)$(GKFX(IY411,IA,IGUC) AND (NOT SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGUC)))) = CEIL((GKFX(IY411,IA,IGUC)/GDATA(IGUC,'GDUCUNITSIZE')));
VUCU.UP(IY411,IA,IGUC,IS3,T)$(GKFX(IY411,IA,IGUC) AND (NOT SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGUC))))  = VUCON.UP(IY411,IA,IGUC,IS3,T);
VUCD.UP(IY411,IA,IGUC,IS3,T)$(GKFX(IY411,IA,IGUC) AND (NOT SUM(Y$(YVALUE(Y) LE YVALUE(IY411)),IAGKNY(Y,IA,IGUC))))  = VUCON.UP(IY411,IA,IGUC,IS3,T);

