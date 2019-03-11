* Decommissioning introduced by Juan Gea Bermúdez 2019.

SET IGDECOM(G)  "Technologies  allowed to be decommissioned endogenously. Particularly for exogenous technologies, if not included in this set, the exogenous development in GKFX will be the one taking place";

IGDECOM(G)$(GDATA(G,'GDDECOM') EQ 1)= YES;



