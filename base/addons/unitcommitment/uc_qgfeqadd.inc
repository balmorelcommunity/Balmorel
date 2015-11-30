* File uc_qgfeqadd.inc Created 27-07-2011
* Lars Bregnbæk.
* Unit commitment add-on to Balmorel.
* This file is included from the QGFEQ equation in Balmorel.gms.


$ontext hans til orientering, fra balmorel.gms:
* Fuel consumption rate calculated on existing units.
QGFEQ(IA,G,IS3,T)$IAGK_Y(IA,G) ..
     VGF_T(IA,G,IS3,T)
  =E=
     (VGE_T(IA,G,IS3,T)/(GDATA(G,'GDFE')*GEFFRATE(IA,G)))$(IGNOTETOH(G) AND IGE(G))
    +(GDATA(G,'GDCV')*VGH_T(IA,G,IS3,T)/(GDATA(G,'GDFE')*GEFFRATE(IA,G)))$IGH(G)
$ifi %UnitComm%==yes $include '../../base/addons/unitcommitment/uc_qgfeqadd.inc';
;

NEDENSTÅENDE linier 2 og 3 KAN GIVE MENING, HVIS 'gdfe' er angivet som hældning frem til maxpunktet (mw) og incl. 'gducf0'.
Så er hældningen for stor som udtryk for marginal, derfor skal der lige trække lidt marginals fra.
MEN: dette må vel afhæge af antagelsen omkring 'GDUCF0' hvad angår hvor stor enhede (mange MW) der er beregnet under? Formentlig under 'GDUCUNITSIZE'?
så skal dette ikke på én eller anden måde indgå i linierne  2-3?


$offtext


* Add fixed fuel use
+ (GDATA(G,'GDUCUNITSIZE')*VUCON(IA,G,IS3,T)*GDATA(G,'GDUCF0')/(GDATA(G,'GDFE')*GEFFRATE(IA,G)))$IGUC(G)

* Correct for using average efficiency as marginal efficiency
  -(GDATA(G,'GDUCF0')*VGE_T(IA,G,IS3,T)/(GDATA(G,'GDFE')*GEFFRATE(IA,G)))$(IGUC(G) AND IGE(G) AND IGNOTETOH(G))
  -(GDATA(G,'GDUCF0')*GDATA(G,'GDCV')*VGH_T(IA,G,IS3,T)/(GDATA(G,'GDFE')*GEFFRATE(IA,G)))$(IGUC(G) AND IGH(G))

