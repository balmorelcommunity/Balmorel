EQUATIONS
QDC_VXH_T(Y,AAA,AAA,S,T)    'Cooling transmission from heat produced in DC-generation areas'
QDC_VWH_T(Y,AAA,G,S,T)      'Waste heat production from chillers in DC-generation areas'
QDC_VWH_MAX_T(Y,AAA,S,T)    'Waste-heat used by recovery heat pumps is capped by waste-heat produced by chillers in DC-generation areas'
;


* ---- COOLING FROM GENERATION-AREA TO STORAGE-AREA ---- *
QDC_VXH_T(IY411,DC_AG,DC_AS,IS3,T)$DC_AMAP(DC_AG,DC_AS)..
SUM(IAGK_HASORPOT(IY411,DC_AG,G)$(IDC_GCHILLER(G)), VGH_T(IY411,DC_AG,G,IS3,T))
=E=
VXH_T(IY411,DC_AG,DC_AS,IS3,T)
;

* ---- WASTE HEAT GENERATION ---- *
QDC_VWH_T(IY411,DC_AG,G,IS3,T)$(IAGK_HASORPOT(IY411,DC_AG,G) AND IDC_GCHILLER(G))..
VGH_T(IY411,DC_AG,G,IS3,T)*(DC_GDHE(G) + 1/GDATA(G,'GDFE') + 1)
=E=
VDC_VGWH_T(IY411,DC_AG,G,IS3,T)
;

* ---- CAP ON WASTE HEAT USE ---- *
QDC_VWH_MAX_T(IY411,DC_AG,IS3,T)..
SUM(IDC_GHEATPUMP(G), VGH_T(IY411,DC_AG,G,IS3,T)*(1/GDATA(G,'GDFE') + 1))
=L=
SUM(IDC_GCHILLER(G)$IAGK_HASORPOT(IY411,DC_AG,G),  VDC_VGWH_T(IY411,DC_AG,G,IS3,T))
;

$ONTEXT
EQUATION QDC_VGH_T:

This equation calculates the heat consumption (as fuel {VDC_VGFH_T}) of absorption chillers.
It is defined over the restricted domain with both simultaneous conditions:
- Technologies with existing or invested capacity, only in DC-generation areas: IAGK_HASORPOT(IY411,DC_AG,G)
- Technologies marked as allowed chiller technologies in DC-generation areas: IDC_GCHILLER(G)

The heat consumption is equal to the heat generation (used as cooling in this addon)
times the parameter DC_GDHE. This parameter is given as heat-in/cooling-out,
with units MWh-heat/MWh-cold.

This equation is is written in a generalised form for all chiller technologies.
Electric chillers consume no heat because their parameter DC_GDHE is equal to zero.
$OFFTEXT

$ONTEXT
EQUATION QDC_VXC_T:

This equation calculates the cooling production (modelled as heat {VGH_T}) in each
DC-generation area based on the aggregated cooling demand from all linked DC-storage areas.

The sum of all cooling transmission {VDC_VXC_T}, over the DC-storage areas that
are linked to an specific DC-generation area {DC_AS$DC_AMAP(DC_AS,DC_AG)} is equal
to the sum of the cooling generation {VGH_T} of technologies in that area that are marked
as chillers {IAGK_HASORPOT(IY411,DC_AG,G)$(IDC_GCHILLER(G))}
$OFFTEXT
