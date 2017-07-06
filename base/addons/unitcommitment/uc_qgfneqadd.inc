* File uc_qgfneqadd.inc Created 27-07-2011
* Lars Bregnbæk.
* Unit commitment add-on to Balmorel.
* This file is included from the QGFEQ equation in Balmorel.gms.

* Add cost of fixed hourly fuel use

* LB:NB: Tjek for konsistens imellem anvendelse af brændselsforbrugsvariabel og unit sizes...
+ (GDATA(G,'GDUCUNITSIZE')*VUCONN(IA,G,IS3,T)*GDATA(G,'GDUCF0')/(GDATA(G,'GDFE')*GEFFRATE(IA,G)))$IGUC(G)

* Correct for using average efficiency as marginal efficiency.
  -(GDATA(G,'GDUCF0')*VGEN_T(IA,G,IS3,T)/(GDATA(G,'GDFE')*GEFFRATE(IA,G)))$(IGUC(G) and IGE(G) and IGNOTETOH(G))
  -(GDATA(G,'GDUCF0')*GDATA(G,'GDCV')*VGHN_T(IA,G,IS3,T)/(GDATA(G,'GDFE')*GEFFRATE(IA,G)))$(IGUC(G) and IGH(G))

