* Addon for securing that System Constraints are forfilled


SET IGEBASE(G)           'Power plants capable of supplying base load';


IGEBASE(IGE)=YES$(IGEXT(IGE) or IGCND(IGE));
