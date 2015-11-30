* File uc_annual_updata.inc.
* This file containts annual updating for the unit commitment add-on to Balmorel.
* Implemented by Hans Ravn 2006-2007.
* Revised and enhanced by Lars Bregnsbæk 2011.

* Simple bounds are set on the number of units online, offline, started and
* shut-down within a single hour.


* Exogenous capacity:


VUCON.up(IA,IGUC,S,T)=INF;
VUCU.up(IA,IGUC,S,T) =INF;
VUCD.up(IA,IGUC,S,T) =INF;

* At most a number of units equal to the installed capacity, divided by the unit size rounded up, can be committed, started or shutdown at one time.
VUCON.up(IA,IGUC,S,T)$IAGK_Y(IA,IGUC) = CEIL((IGKVACCTOY(IA,IGUC) + IGKFX_Y(IA,IGUC))/GDATA(IGUC,'GDUCUNITSIZE'));
VUCU.up(IA,IGUC,S,T)$IAGK_Y(IA,IGUC)  = VUCON.up(IA,IGUC,S,T);
VUCD.up(IA,IGUC,S,T)$IAGK_Y(IA,IGUC)  = VUCON.up(IA,IGUC,S,T);

VUCONN.up(IA,IGUC,S,T)=INF;
VUCUN.up(IA,IGUC,S,T) =INF;
VUCDN.up(IA,IGUC,S,T) =INF;

* Endogenous capacity:


* At most new units can be committed with less capacity than the investment restrictions.

* IA, FKPOT
VUCONN.up(IA,IGUC,S,T)$(IAGKN(IA,IGUC) and SUM(FFF$IGF(IGUC,FFF),FKPOT(IA,FFF)))= CEIL( ( SUM(FFF$IGF(IGUC,FFF), FKPOT(IA,FFF)
                                                                                 - SUM(G$(IAGK_Y(IA,G) and IGF(G,FFF)), (IGKVACCTOY(IA,G) + IGKFX_Y(IA,G))) )/GDATA(IGUC,'GDUCUNITSIZE')));

* IR, FKPOT
VUCONN.up(IA,IGUC,S,T)$(IAGKN(IA,IGUC) and SUM(IR$RRRAAA(IR,IA), SUM(FFF$IGF(IGUC,FFF),FKPOT(IR,FFF))))= MIN(VUCONN.up(IA,IGUC,S,T),
                                       CEIL( SUM(IR$RRRAAA(IR,IA), SUM(FFF$IGF(IGUC,FFF), FKPOT(IR,FFF)
                                                 - SUM(G$(IAGK_Y(IA,G) and IGF(G,FFF)), (IGKVACCTOY(IA,G) + IGKFX_Y(IA,G))) )/GDATA(IGUC,'GDUCUNITSIZE'))) );

* C, FKPOT
VUCONN.up(IA,IGUC,S,T)$(IAGKN(IA,IGUC) and SUM(C$ICA(C,IA), SUM(FFF$IGF(IGUC,FFF),FKPOT(C,FFF))))= MIN(VUCONN.up(IA,IGUC,S,T),
                                       CEIL( SUM(C$ICA(C,IA), SUM(FFF$IGF(IGUC,FFF), FKPOT(C,FFF)
                                                 - SUM(G$(IAGK_Y(IA,G) and IGF(G,FFF)), (IGKVACCTOY(IA,G) + IGKFX_Y(IA,G))) )/GDATA(IGUC,'GDUCUNITSIZE'))) );

$ontext
* IA, FMAXINV
VUCONN.up(IA,IGUC,S,T)$(IAGKN(IA,IGUC) and SUM(FFF$IGF(IGUC,FFF),FMAXINV(IA,FFF)))= MIN(VUCONN.up(IA,IGUC,S,T),
                                       CEIL( SUM(FFF$IGF(IGUC,FFF), FMAXINV(IA,FFF))/GDATA(IGUC,'GDUCUNITSIZE') ));

* IR, FMAXINV
VUCONN.up(IA,IGUC,S,T)$(IAGKN(IA,IGUC) and SUM(IR$RRRAAA(IR,IA), SUM(FFF$IGF(IGUC,FFF),FMAXINV(IR,FFF))))= MIN(VUCONN.up(IA,IGUC,S,T),
                                       CEIL( SUM(IR$RRRAAA(IR,IA), SUM(FFF$IGF(IGUC,FFF), FMAXINV(IR,FFF)))/GDATA(IGUC,'GDUCUNITSIZE') ));
* C, FMAXINV
VUCONN.up(IA,IGUC,S,T)$(IAGKN(IA,IGUC) and SUM(C$ICA(C,IA), SUM(FFF$IGF(IGUC,FFF),FMAXINV(C,FFF))))= MIN(VUCONN.up(IA,IGUC,S,T),
                                       CEIL( SUM(C$ICA(C,IA), SUM(FFF$IGF(IGUC,FFF), FMAXINV(C,FFF)))/GDATA(IGUC,'GDUCUNITSIZE') ));
$offtext


* Start-up and shut-down of units limited with same limits as the number of units which can be online at once.
VUCUN.up(IA,IGUC,S,T)$IAGKN(IA,IGUC) = VUCONN.up(IA,IGUC,S,T);
VUCDN.up(IA,IGUC,S,T)$IAGKN(IA,IGUC) = VUCONN.up(IA,IGUC,S,T);
