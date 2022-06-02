EQUATIONS
QDC_VXH_T(Y,AAA,AAA,S,T)            'Transmission of cooling produced by chiller technologies from DC-generation areas to DC-storage areas'
QDC_FREECOOLING_T(Y,S,T,AAA,AAA)    'Free-cooling generation covers only fraction of cooling demand, given by DC_FREECOOLING'
;


* ---- COOLING TRANSMISSION FROM GENERATION-AREA TO STORAGE-AREA ---- *
* Cooling (Balmorel-heat) produced by chiller technologies from DC-generation areas is forcefully transfered to DC-storage areas.
* Equality forces that only these chiller technologies are allowed to serve cooling demand or cooling storages in DC-storage areas.
QDC_VXH_T(IY411,DC_AG,DC_AS,IS3,T)$DC_AMAP(DC_AG,DC_AS)..
SUM(IAGK_HASORPOT(IY411,DC_AG,G)$(IDC_GCHILLER(G) OR IDC_FREECOOLING(G)), VGH_T(IY411,DC_AG,G,IS3,T))
=E=
VXH_T(IY411,DC_AG,DC_AS,IS3,T)
;

* ---- FREE-COOLING GENERATION ---- *
* Free-cooling generation covers, as a maximum, the fraction of current cooling demand given by DC_FREECOOLING_POTENTIAL
QDC_FREECOOLING_T(IY411,IS3,T,DC_AG,DC_AS)$DC_AMAP(DC_AG,DC_AS)..
SUM(IAGK_HASORPOT(IY411,DC_AG,G)$(IDC_FREECOOLING(G)), VGH_T(IY411,DC_AG,G,IS3,T))
=L=
(SUM(DHUSER, ((DH(IY411,DC_AS,DHUSER) * DH_VAR_T(DC_AS,DHUSER,IS3,T)) / IDH_SUMST(DC_AS,DHUSER))$(IDH_SUMST(DC_AS,DHUSER) GT 0)*DC_FREECOOLING_POTENTIAL(IS3,T,DC_AS,DHUSER)))
;