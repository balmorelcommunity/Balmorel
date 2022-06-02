SET  DC_AS(AAA)             'DC-storage areas';
SET  DC_AG(AAA)             'DC-generation areas';
SET  DC_AMAP(AAA,AAA)       'Pair of linked DC-storage and DC-generation areas';

* DC-storage areas contain the datacenter cooling demand and the coldstorages.
* DC-generation areas contain the generation technologies required to produce cooling.
* This distinction is necessary to avoid the mixing of heating and cooling, both of which are modelled as heat in Balmorel.
* DC_AMAP links each DC-storage area to its DC-generation area.
